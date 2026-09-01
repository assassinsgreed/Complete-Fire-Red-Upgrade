#ifndef GUARD_BATTLE_SPEED_H
#define GUARD_BATTLE_SPEED_H

void __attribute__((long_call)) BattleMainCB1(void); //Vanilla, address in BPRE.ld

void NewBattleMainCB2(void); //Hooked over the vanilla BattleMainCB2

#endif
