/*
 * File: z_dm_char07.c
 * Overlay: ovl_Dm_Char07
 * Description: Different Milk Bar Objects (Stage, Credits Stage, Spotlights, Dishes)
 */

#include "z_dm_char07.h"
#include "objects/object_milkbar/object_milkbar.h"

#define FLAGS 0x00000030

#define THIS ((DmChar07*)thisx)

void DmChar07_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar07_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar07_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar07_Draw(Actor* thisx, GlobalContext* globalCtx);

void DmChar07_DoNothing(DmChar07* this, GlobalContext* globalCtx);

const ActorInit Dm_Char07_InitVars = {
    ACTOR_DM_CHAR07,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MILKBAR,
    sizeof(DmChar07),
    (ActorFunc)DmChar07_Init,
    (ActorFunc)DmChar07_Destroy,
    (ActorFunc)DmChar07_Update,
    (ActorFunc)DmChar07_Draw,
};

void DmChar07_SetupAction(DmChar07* this, DmChar07ActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void DmChar07_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmChar07* this = THIS;

    this->isStage = 0;
    Actor_SetScale(&this->dyna.actor, 1.0f);
    this->spotlightFlags = DMCHAR07_GET_SPOTLIGHTFLAGS(thisx);
    thisx->params = DMCHAR07_GET_TYPE(thisx);
    if (this->dyna.actor.params == DMCHAR07_STAGE) {
        Actor_SetScale(&this->dyna.actor, 0.1f);
        this->isStage = 1;
        DynaPolyActor_Init(&this->dyna, 0);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_milkbar_Colheader_006688);
    } else {
        Actor_SetScale(&this->dyna.actor, 1.0f);
    }
    DmChar07_SetupAction(this, DmChar07_DoNothing);
}

void DmChar07_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DmChar07* this = THIS;

    if (this->isStage) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void DmChar07_DoNothing(DmChar07* this, GlobalContext* globalCtx) {
}

void DmChar07_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmChar07* this = THIS;

    this->actionFunc(this, globalCtx);
}

void DmChar07_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmChar07* this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (this->dyna.actor.params) {
        case DMCHAR07_STAGE:
            gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_002CD0);
            break;
        case DMCHAR07_CREDITS_STAGE:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_milkbar_Matanimheader_0105F8));
            gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_007918);
            gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_000240);
            gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_000790);
            gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_000CC0);
            gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_001210);
            gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_0016B8);
            break;
        case DMCHAR07_SPOTLIGHTS:
            if (this->spotlightFlags & DMCHAR07_STAGE_RIGHT_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_000240);
            }
            if (this->spotlightFlags & DMCHAR07_UPSTAGE_RIGHT_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_000790);
            }
            if (this->spotlightFlags & DMCHAR07_STAGE_CENTER_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_000CC0);
            }
            if (this->spotlightFlags & DMCHAR07_UPSTAGE_LEFT_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_001210);
            }
            if (this->spotlightFlags & DMCHAR07_DOWNSTAGE_CENTER_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_0016B8);
            }
            break;
        case DMCHAR07_DISHES:
            gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_010D68);
            break;
    }

    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (this->dyna.actor.params) {
        case DMCHAR07_STAGE:
            gSPDisplayList(POLY_XLU_DISP++, object_milkbar_DL_002BA0);
            break;
        case DMCHAR07_CREDITS_STAGE:
            gSPDisplayList(POLY_XLU_DISP++, object_milkbar_DL_0076A0);
            gSPDisplayList(POLY_XLU_DISP++, object_milkbar_DL_000100);
            gSPDisplayList(POLY_XLU_DISP++, object_milkbar_DL_000650);
            gSPDisplayList(POLY_XLU_DISP++, object_milkbar_DL_000B80);
            gSPDisplayList(POLY_XLU_DISP++, object_milkbar_DL_0010D0);
            gSPDisplayList(POLY_XLU_DISP++, object_milkbar_DL_0015E0);
            break;
        case DMCHAR07_SPOTLIGHTS:
            if (this->spotlightFlags & DMCHAR07_STAGE_RIGHT_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_000100);
            }
            if (this->spotlightFlags & DMCHAR07_UPSTAGE_RIGHT_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_000650);
            }
            if (this->spotlightFlags & DMCHAR07_STAGE_CENTER_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_000B80);
            }
            if (this->spotlightFlags & DMCHAR07_UPSTAGE_LEFT_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_0010D0);
            }
            if (this->spotlightFlags & DMCHAR07_DOWNSTAGE_CENTER_SPOTLIGHT) {
                gSPDisplayList(POLY_OPA_DISP++, object_milkbar_DL_0015E0);
            }
            break;
        case DMCHAR07_DISHES:
            break;
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
