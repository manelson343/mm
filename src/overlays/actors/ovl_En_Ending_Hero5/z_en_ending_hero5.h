#ifndef Z_EN_ENDING_HERO5_H
#define Z_EN_ENDING_HERO5_H

#include "global.h"

struct EnEndingHero5;

typedef void (*EnEndingHero5ActionFunc)(struct EnEndingHero5*, GlobalContext*);

typedef struct EnEndingHero5 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[17];
    /* 0x1EE */ Vec3s morphTable[17];
    /* 0x254 */ EnEndingHero5ActionFunc actionFunc;
    /* 0x258 */ u16 unk258;
    /* 0x25C */ s32 unk25C;
} EnEndingHero5; // size = 0x260

extern const ActorInit En_Ending_Hero5_InitVars;

#endif // Z_EN_ENDING_HERO5_H
