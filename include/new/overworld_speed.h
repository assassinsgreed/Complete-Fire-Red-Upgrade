#ifndef GUARD_OVERWORLD_SPEED_H
#define GUARD_OVERWORLD_SPEED_H

void __attribute__((long_call)) InitNpcForMovement(struct EventObject* eventObject, struct Sprite* sprite, u8 direction, u8 speed);
void __attribute__((long_call)) SetStepAnimHandleAlternation(struct EventObject* eventObject, struct Sprite* sprite, u8 animNum);
void __attribute__((long_call)) ShiftStillEventObjectCoords(struct EventObject* eventObject);
bool8 __attribute__((long_call)) NpcTakeStep(struct Sprite* sprite);
void __attribute__((long_call)) CreateBobbingEffect(struct EventObject* eventObject, struct Sprite* linkedSprite, struct Sprite* blobSprite);

//Replace the vanilla movement setup routines, which are the only two places a walking step's speed tier is chosen
void NewInitMovementNormal(struct EventObject* eventObject, struct Sprite* sprite, u8 direction, u8 speed);
void NewStartRunningAnim(struct EventObject* eventObject, struct Sprite* sprite, u8 direction);
bool8 NewUpdateMovementNormal(struct EventObject* eventObject, struct Sprite* sprite);

#endif
