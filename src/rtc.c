#include "../include/global.h"
#include "../include/play_time.h"
#include "../include/rtc.h"
#include "../include/script.h"
#include "../include/new/ram_locs.h"

extern u16 sRTCErrorStatus;
extern u8 sRTCProbeResult;
extern u16 sRTCSavedIme;
extern u8 sRTCFrameCount;
extern u32 gLastClockSecond;

extern struct SiiRtcInfo sRtc; //0x3005E88

// const rom
static const struct SiiRtcInfo sRtcDummy = {.year = 0, .month = MONTH_JAN, .day = 1, .hour = 0x10}; // 2000 Jan 1, 10:00 AM (hex is intentional)

static const s32 sNumDaysInMonths[12] =
{
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
};

void RtcDisableInterrupts(void)
{
	sRTCSavedIme = REG_IME;
	REG_IME = 0;
}

void RtcRestoreInterrupts(void)
{
	REG_IME = sRTCSavedIme;
}

u32 ConvertBcdToBinary(u8 bcd)
{
	if (bcd > 0x9F)
		return 0xFF;

	if ((bcd & 0xF) <= 9)
		return (10 * ((bcd >> 4) & 0xF)) + (bcd & 0xF);
	else
		return 0xFF;
}

static bool8 IsLeapYear(u32 year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return TRUE;

	return FALSE;
}

void RtcInit(void)
{
	sRTCErrorStatus = 0;

	RtcDisableInterrupts();
	SiiRtcUnprotect();
	sRTCProbeResult = SiiRtcProbe();
	RtcRestoreInterrupts();

	if ((sRTCProbeResult & 0xF) != 1)
	{
		sRTCErrorStatus = RTC_INIT_ERROR | RTC_NO_HARDWARE;
		return;
	}

	if (sRTCProbeResult & 0xF0)
		sRTCErrorStatus = RTC_INIT_WARNING;
	else
		sRTCErrorStatus = 0;

	RtcGetRawInfo(&sRtc);
	sRTCErrorStatus = RtcCheckInfo(&sRtc);
}

u16 RtcGetErrorStatus(void)
{
	return sRTCErrorStatus;
}

void RtcGetInfo(struct SiiRtcInfo *rtc)
{
	if (sRTCErrorStatus & RTC_ERR_FLAG_MASK)
		*rtc = sRtcDummy;
	else
		RtcGetRawInfo(rtc);
}

void RtcGetDateTime(struct SiiRtcInfo *rtc)
{
	RtcDisableInterrupts();
	SiiRtcGetDateTime(rtc);
	RtcRestoreInterrupts();
}

void RtcGetStatus(struct SiiRtcInfo *rtc)
{
	RtcDisableInterrupts();
	SiiRtcGetStatus(rtc);
	RtcRestoreInterrupts();
}

void RtcGetRawInfo(struct SiiRtcInfo *rtc)
{
	RtcGetStatus(rtc);
	RtcGetDateTime(rtc);
}

u16 RtcCheckInfo(struct SiiRtcInfo *rtc)
{
	u16 errorFlags = 0;
	s32 year;
	s32 month;
	s32 value;

	if (rtc->status & SIIRTCINFO_POWER)
		errorFlags |= RTC_ERR_POWER_FAILURE;

	if (!(rtc->status & SIIRTCINFO_24HOUR))
		errorFlags |= RTC_ERR_12HOUR_CLOCK;

	year = ConvertBcdToBinary(rtc->year);

	if (year == 0xFF)
		errorFlags |= RTC_ERR_INVALID_YEAR;

	month = ConvertBcdToBinary(rtc->month);

	if (month == 0xFF || month == 0 || month > 12)
		errorFlags |= RTC_ERR_INVALID_MONTH;

	value = ConvertBcdToBinary(rtc->day);

	if (value == 0xFF)
		errorFlags |= RTC_ERR_INVALID_DAY;

	if (month == MONTH_FEB)
	{
		if (value > IsLeapYear(year) + sNumDaysInMonths[month - 1])
			errorFlags |= RTC_ERR_INVALID_DAY;
	}
	else
	{
		if (value > sNumDaysInMonths[month - 1])
			errorFlags |= RTC_ERR_INVALID_DAY;
	}

	value = ConvertBcdToBinary(rtc->hour);

	if (value > 24)
		errorFlags |= RTC_ERR_INVALID_HOUR;

	value = ConvertBcdToBinary(rtc->minute);

	if (value > 60)
		errorFlags |= RTC_ERR_INVALID_MINUTE;

	value = ConvertBcdToBinary(rtc->second);

	if (value > 60)
		errorFlags |= RTC_ERR_INVALID_SECOND;

	return errorFlags;
}

static void UpdateClockFromRtc(struct SiiRtcInfo *rtc)
{
	gClock.year = ConvertBcdToBinary(rtc->year) + 2000; //Base year is 2000
	gClock.month = ConvertBcdToBinary(rtc->month);
	gClock.day = ConvertBcdToBinary(rtc->day);
	gClock.dayOfWeek = ConvertBcdToBinary(rtc->dayOfWeek);
	gClock.hour = ConvertBcdToBinary(rtc->hour);
	gClock.minute = ConvertBcdToBinary(rtc->minute);
	gClock.second = ConvertBcdToBinary(rtc->second);

	if (gInvertAMPM)
	{
		if (gClock.hour >= 12)
			gClock.hour -= 12;
		else
			gClock.hour += 12;
	}
}

void __attribute__((long_call)) break_func();
extern const u8 SystemScript_StopZooming[];
void RtcCalcLocalTime(void)
{
	if (sRTCFrameCount == 0)
	{
		// SiiRtcProbe() drives the cartridge GPIO lines, which on a cart without an
		// RTC are just ROM address space. Probe at most once and remember the answer:
		// this runs every second for the whole session, and on a flash-based repro
		// cart a burst of writes into ROM space can latch the chip into command mode,
		// after which every instruction fetch returns chip ID data instead of code.
		if (!(sRTCErrorStatus & RTC_PROBE_DONE))
		{
			RtcInit();
			sRTCErrorStatus |= RTC_PROBE_DONE;
		}
		else if (!(sRTCErrorStatus & RTC_NO_HARDWARE))
		{
			// Re-read where a probe did find hardware, and re-check the values rather
			// than latching the first result, so a clock caught mid-update recovers.
			RtcDisableInterrupts();
			SiiRtcUnprotect(); // Clears sLocked, which an interrupted read would otherwise wedge TRUE forever
			RtcRestoreInterrupts();

			RtcGetRawInfo(&sRtc);
			sRTCErrorStatus = RtcCheckInfo(&sRtc) | RTC_PROBE_DONE;
		}

		// RTC_INIT_ERROR sits outside RTC_ERR_FLAG_MASK, so a failed probe used to
		// leave sRtc untouched and feed whatever was already in it to the clock.
		if (sRTCErrorStatus & (RTC_ERR_FLAG_MASK | RTC_NO_HARDWARE))
			sRtc = sRtcDummy;

		//u8 prevSecond = gClock.second;
		UpdateClockFromRtc(&sRtc);

		/*if (prevSecond == gClock.second
		&& !ScriptContext2_IsEnabled())
		//Probably needs an overworld check and a minute/hour/day etc check too
		//Also the below value should be ~70 for it to work normally
		//Really best to use a custom task that runs in the overworld for this
		{
			ScriptContext2_Enable();
			ScriptContext1_SetupScript(SystemScript_StopZooming);
		}*/
	}
	else if (sRTCFrameCount >= 60) //Update once a second
	{
		sRTCFrameCount = 0;
		return;
	}

	++sRTCFrameCount;
}

void ForceClockUpdate(void)
{
	sRTCFrameCount = 0;
}

void DirectClockUpdate(void)
{
	sRTCFrameCount = 0;
	RtcCalcLocalTime();
}

void PlayTimeCounter_Update(void)
{
	if (sPlayTimeCounterState == PLAYTIME_RUNNING)
	{
		bool8 secondPassed;

		if (gSaveBlock2->playTimeVBlanks < 0xFF)
			++gSaveBlock2->playTimeVBlanks;

		if (RtcGetErrorStatus() & RTC_ERR_FLAG_MASK)
			secondPassed = gSaveBlock2->playTimeVBlanks > 59;
		else
			secondPassed = gClock.second != gLastClockSecond //Sync clock to RTC
			            && gSaveBlock2->playTimeVBlanks > 59; //But make sure a second ingame has actually passed and the player didn't just pause the game

		if (secondPassed)
		{
			gSaveBlock2->playTimeVBlanks = 0;
			gLastClockSecond = gClock.second;
			gSaveBlock2->playTimeSeconds++;
			if (gSaveBlock2->playTimeSeconds > 59)
			{
				gSaveBlock2->playTimeSeconds = 0;
				gSaveBlock2->playTimeMinutes++;
				if (gSaveBlock2->playTimeMinutes > 59)
				{
					gSaveBlock2->playTimeMinutes = 0;
					gSaveBlock2->playTimeHours++;
					if (gSaveBlock2->playTimeHours > 999)
						PlayTimeCounter_SetToMax();
				}
			}
		}
	}
}
