#ifndef Z_EN_WDHAND_H
#define Z_EN_WDHAND_H

#include "global.h"

struct EnWdhand;

typedef void (*EnWdhandActionFunc)(struct EnWdhand*, GlobalContext*);

typedef struct EnWdhand {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xA4];
    /* 0x01E8 */ EnWdhandActionFunc actionFunc;
    /* 0x01EC */ char unk_1EC[0x268];
} EnWdhand; // size = 0x454

extern const ActorInit En_Wdhand_InitVars;

#endif // Z_EN_WDHAND_H
