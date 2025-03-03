#include "global.h"

void* Lib_MemCpy(void* dest, void* src, size_t size) {
    bcopy(src, dest, size);

    return dest;
}

void* Lib_MemSet(void* buffer, s32 value, size_t size) {
    u8* v0;
    s32 i;

    if (value == 0) {
        bzero(buffer, (u32)size);

        return buffer;
    }

    for (v0 = (u8*)buffer, i = size; i > 0; i--) {
        *v0++ = value;
    }

    return buffer;
}

f32 Math_CosS(s16 angle) {
    return coss(angle) * SHT_MINV;
}

f32 Math_SinS(s16 angle) {
    return sins(angle) * SHT_MINV;
}

s32 Math_StepToIImpl(s32 start, s32 target, s32 step) {
    s32 ret;

    if (target >= start) {
        ret = start + step;
        if (target >= ret) {
            return ret;
        }
    } else {
        ret = start - step;
        if (ret >= target) {
            return ret;
        }
    }
    return target;
}

void Math_StepToIGet(s32* pValue, s32 target, s32 step) {
    *pValue = Math_StepToIImpl(*pValue, target, step);
}

s32 Math_StepToI(s32* pValue, s32 target, s32 step) {
    Math_StepToIGet(pValue, target, step);

    return target == *pValue;
}

s32 Math_ScaledStepToS(s16* pValue, s16 target, s16 step) {
    f32 f0;

    if (step != 0) {
        f0 = gFramerateDivisorHalf;

        if ((s16)(*pValue - target) > 0) {
            step = -step;
        }

        *pValue += (s16)(step * f0);

        if (((s16)(*pValue - target) * step) >= 0) {
            *pValue = target;

            return true;
        }
    } else if (target == *pValue) {
        return true;
    }

    return false;
}

s32 Math_StepToS(s16* pValue, s16 target, s16 step) {
    if (step != 0) {
        if (target < *pValue) {
            step = -step;
        }

        *pValue += step;

        if (((*pValue - target) * step) >= 0) {
            *pValue = target;

            return true;
        }
    } else if (target == *pValue) {
        return true;
    }

    return false;
}

s32 Math_StepToC(s8* pValue, s8 target, s8 step) {
    if (step != 0) {
        if (target < *pValue) {
            step = -step;
        }

        *pValue += step;

        if (((*pValue - target) * step) >= 0) {
            *pValue = target;

            return true;
        }
    } else if (target == *pValue) {
        return true;
    }

    return false;
}

s32 Math_StepToF(f32* pValue, f32 target, f32 step) {
    if (step != 0.0f) {
        if (target < *pValue) {
            step = -step;
        }

        *pValue += step;

        if (((*pValue - target) * step) >= 0) {
            *pValue = target;

            return true;
        }
    } else if (target == *pValue) {
        return true;
    }

    return false;
}

s32 Math_StepUntilAngleS(s16* pValue, s16 target, s16 step) {
    s16 orig = *pValue;

    *pValue += step;

    if (((s16)(*pValue - target) * (s16)(orig - target)) <= 0) {
        *pValue = target;

        return true;
    }

    return false;
}

s32 Math_StepToAngleS(s16* pValue, s16 target, s16 step) {
    s32 diff = target - *pValue;

    if (diff < 0) {
        step = -step;
    }

    if (diff > INT16_MAX) {
        step = -step;
        diff = -UINT16_MAX - -diff;
    } else if (diff <= INT16_MIN) {
        diff += UINT16_MAX;
        step = -step;
    }

    if (step != 0) {
        *pValue += step;

        if ((diff * step) <= 0) {
            *pValue = target;
            return true;
        }
    } else if (target == *pValue) {
        return true;
    }

    return false;
}

s32 Math_AsymStepToS(s16* pValue, s16 target, s16 incrStep, s16 decrStep) {
    s16 step = ((target - *pValue) >= 0) ? incrStep : decrStep;

    if (step != 0) {
        if (target < *pValue) {
            step = -step;
        }

        *pValue += step;

        if (((*pValue - target) * step) >= 0) {
            *pValue = target;
            return true;
        }
    } else if (target == *pValue) {
        return true;
    }

    return false;
}

s32 Math_StepUntilF(f32* pValue, f32 limit, f32 step) {
    f32 orig = *pValue;

    *pValue += step;

    if (((*pValue - limit) * (orig - limit)) <= 0) {
        *pValue = limit;
        return true;
    }

    return false;
}

s32 Math_AsymStepToF(f32* pValue, f32 target, f32 incrStep, f32 decrStep) {
    f32 step = (target >= *pValue) ? incrStep : decrStep;

    if (step != 0) {
        if (target < *pValue) {
            step = -step;
        }

        *pValue += step;

        if (((*pValue - target) * step) >= 0) {
            *pValue = target;
            return true;
        }
    } else if (target == *pValue) {
        return true;
    }

    return false;
}

void func_800FF3A0(f32* distOut, s16* angleOut, Input* input) {
    f32 x = input->rel.stick_x;
    f32 y = input->rel.stick_y;
    f32 dist;

    dist = sqrtf(SQ(x) + SQ(y));
    *distOut = (60.0f < dist) ? 60.0f : dist;

    if (dist > 0.0f) {
        x = input->cur.stick_x;
        y = input->cur.stick_y;
        *angleOut = Math_FAtan2F(y, -x);
    } else {
        *angleOut = 0;
    }
}

s16 Rand_S16Offset(s16 base, s16 range) {
    return (s16)(Rand_ZeroOne() * range) + base;
}

s16 Rand_S16OffsetStride(s16 base, s16 stride, s16 range) {
    return (s16)(Rand_ZeroOne() * range) * stride + base;
}

void Math_Vec3f_Copy(Vec3f* dest, Vec3f* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void Math_Vec3s_Copy(Vec3s* dest, Vec3s* src) {
    s16 x = src->x;
    s16 y = src->y;
    s16 z = src->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void Math_Vec3s_ToVec3f(Vec3f* dest, Vec3s* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void Math_Vec3f_ToVec3s(Vec3s* dest, Vec3f* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void Math_Vec3f_Sum(Vec3f* l, Vec3f* r, Vec3f* dest) {
    dest->x = l->x + r->x;
    dest->y = l->y + r->y;
    dest->z = l->z + r->z;
}

void Math_Vec3f_Diff(Vec3f* l, Vec3f* r, Vec3f* dest) {
    dest->x = l->x - r->x;
    dest->y = l->y - r->y;
    dest->z = l->z - r->z;
}

void Math_Vec3s_DiffToVec3f(Vec3f* dest, Vec3s* l, Vec3s* r) {
    dest->x = l->x - r->x;
    dest->y = l->y - r->y;
    dest->z = l->z - r->z;
}

void Math_Vec3f_Scale(Vec3f* vec, f32 scale) {
    vec->x *= scale;
    vec->y *= scale;
    vec->z *= scale;
}

void Math_Vec3f_ScaleAndStore(Vec3f* vec, f32 scale, Vec3f* dest) {
    dest->x = vec->x * scale;
    dest->y = vec->y * scale;
    dest->z = vec->z * scale;
}

void Math_Vec3f_Lerp(Vec3f* a, Vec3f* b, f32 t, Vec3f* dest) {
    dest->x = (b->x - a->x) * t + a->x;
    dest->y = (b->y - a->y) * t + a->y;
    dest->z = (b->z - a->z) * t + a->z;
}

void Math_Vec3f_SumScaled(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dest) {
    dest->x = b->x * scale + a->x;
    dest->y = b->y * scale + a->y;
    dest->z = b->z * scale + a->z;
}

void Math_Vec3f_AddRand(Vec3f* orig, f32 scale, Vec3f* dest) {
    dest->x = randPlusMinusPoint5Scaled(scale) + orig->x;
    dest->y = randPlusMinusPoint5Scaled(scale) + orig->y;
    dest->z = randPlusMinusPoint5Scaled(scale) + orig->z;
}

void Math_Vec3f_DistXYZAndStoreNormDiff(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dest) {
    f32 diff = Math_Vec3f_DistXYZAndStoreDiff(a, b, dest);
    f32 normScale;

    if (diff == 0) {
        return;
    }

    normScale = scale / diff;

    dest->x *= normScale;
    dest->y *= normScale;
    dest->z *= normScale;
}

f32 Math_Vec3f_DistXYZ(Vec3f* a, Vec3f* b) {
    Vec3f diff;
    Math_Vec3f_Diff(b, a, &diff);
    return sqrtf(SQ(diff.x) + SQ(diff.y) + SQ(diff.z));
}

f32 Math_Vec3f_DistXYZAndStoreDiff(Vec3f* a, Vec3f* b, Vec3f* dest) {
    Math_Vec3f_Diff(b, a, dest);
    return sqrtf(SQ(dest->x) + SQ(dest->y) + SQ(dest->z));
}

f32 Math_Vec3f_DistXZ(Vec3f* a, Vec3f* b) {
    f32 dx = b->x - a->x;
    f32 dz = b->z - a->z;
    return sqrtf(SQ(dx) + SQ(dz));
}

f32 Math_Vec3f_DistXZAndStore(Vec3f* a, Vec3f* b, f32* dx, f32* dz) {
    *dx = b->x - a->x;
    *dz = b->z - a->z;
    return sqrtf(SQ(*dx) + SQ(*dz));
}

f32 Math_Vec3f_StepToXZ(Vec3f* start, Vec3f* target, f32 speed) {
    f32 sp24;
    f32 sp20;
    f32 f0 = Math_Vec3f_DistXZAndStore(target, start, &sp24, &sp20);
    f32 f2 = f0 - speed;

    if (speed > f0) {
        f2 = 0.0f;
    }

    if (f2 == 0.0f) {
        f0 = 0.0f;
    } else {
        f0 = f2 / f0;
    }

    start->x = target->x + sp24 * f0;
    start->z = target->z + sp20 * f0;

    return f2;
}

f32 Math_Vec3f_DiffY(Vec3f* a, Vec3f* b) {
    return b->y - a->y;
}

s16 Math_Vec3f_Yaw(Vec3f* a, Vec3f* b) {
    f32 f14 = b->x - a->x;
    f32 f12 = b->z - a->z;
    return Math_FAtan2F(f12, f14);
}

s16 Math_Vec3f_Pitch(Vec3f* a, Vec3f* b) {
    return Math_FAtan2F(Math_Vec3f_DistXZ(a, b), a->y - b->y);
}

void IChain_Apply_u8(u8* ptr, InitChainEntry* ichain);
void IChain_Apply_s8(u8* ptr, InitChainEntry* ichain);
void IChain_Apply_u16(u8* ptr, InitChainEntry* ichain);
void IChain_Apply_s16(u8* ptr, InitChainEntry* ichain);
void IChain_Apply_u32(u8* ptr, InitChainEntry* ichain);
void IChain_Apply_s32(u8* ptr, InitChainEntry* ichain);
void IChain_Apply_f32(u8* ptr, InitChainEntry* ichain);
void IChain_Apply_f32div1000(u8* ptr, InitChainEntry* ichain);
void IChain_Apply_Vec3f(u8* ptr, InitChainEntry* ichain);
void IChain_Apply_Vec3fdiv1000(u8* ptr, InitChainEntry* ichain);
void IChain_Apply_Vec3s(u8* ptr, InitChainEntry* ichain);

void (*sInitChainHandlers[])(u8* ptr, InitChainEntry* ichain) = {
    IChain_Apply_u8,    IChain_Apply_s8,           IChain_Apply_u16,   IChain_Apply_s16,
    IChain_Apply_u32,   IChain_Apply_s32,          IChain_Apply_f32,   IChain_Apply_f32div1000,
    IChain_Apply_Vec3f, IChain_Apply_Vec3fdiv1000, IChain_Apply_Vec3s,
};

void Actor_ProcessInitChain(Actor* actor, InitChainEntry* ichain) {
    do {
        sInitChainHandlers[ichain->type]((u8*)actor, ichain);
    } while ((ichain++)->cont);
}

void IChain_Apply_u8(u8* ptr, InitChainEntry* ichain) {
    *(u8*)(ptr + ichain->offset) = (u8)(ichain->value);
}

void IChain_Apply_s8(u8* ptr, InitChainEntry* ichain) {
    *(u8*)(ptr + ichain->offset) = (u8)(ichain->value);
}

void IChain_Apply_u16(u8* ptr, InitChainEntry* ichain) {
    *(u16*)(ptr + ichain->offset) = (u16)(ichain->value);
}

void IChain_Apply_s16(u8* ptr, InitChainEntry* ichain) {
    *(u16*)(ptr + ichain->offset) = (u16)(ichain->value);
}

void IChain_Apply_u32(u8* ptr, InitChainEntry* ichain) {
    *(u32*)(ptr + ichain->offset) = (u32)(ichain->value);
}

void IChain_Apply_s32(u8* ptr, InitChainEntry* ichain) {
    *(u32*)(ptr + ichain->offset) = (u32)(ichain->value);
}

void IChain_Apply_f32(u8* ptr, InitChainEntry* ichain) {
    *(f32*)(ptr + ichain->offset) = (f32)(ichain->value);
}

void IChain_Apply_f32div1000(u8* ptr, InitChainEntry* ichain) {
    *(f32*)(ptr + ichain->offset) = (f32)(ichain->value) / 1000;
}

void IChain_Apply_Vec3f(u8* ptr, InitChainEntry* ichain) {
    Vec3f* v0 = (Vec3f*)(ptr + ichain->offset);
    f32 f0 = (f32)(ichain->value);

    v0->z = f0;
    v0->y = f0;
    v0->x = f0;
}

void IChain_Apply_Vec3fdiv1000(u8* ptr, InitChainEntry* ichain) {
    Vec3f* v0 = (Vec3f*)(ptr + ichain->offset);
    f32 f0 = (f32)(ichain->value) / 1000;

    v0->z = f0;
    v0->y = f0;
    v0->x = f0;
}

void IChain_Apply_Vec3s(u8* ptr, InitChainEntry* ichain) {
    Vec3s* v0 = (Vec3s*)(ptr + ichain->offset);
    s16 v1 = (s16)(ichain->value);

    v0->z = v1;
    v0->y = v1;
    v0->x = v1;
}

f32 Math_SmoothStepToF(f32* pValue, f32 target, f32 fraction, f32 step, f32 minStep) {
    f32 stepSize;

    if (*pValue != target) {
        stepSize = (target - *pValue) * fraction;

        if ((stepSize >= minStep) || (stepSize <= -minStep)) {
            if (stepSize > step) {
                stepSize = step;
            }

            if (stepSize < -step) {
                stepSize = -step;
            }

            *pValue += stepSize;
        } else {
            if (stepSize > 0) {
                if (stepSize < minStep) {
                    *pValue += minStep;

                    if (target < *pValue) {
                        *pValue = target;
                    }
                }
            } else {
                if (-minStep < stepSize) {
                    *pValue += -minStep;

                    if (*pValue < target) {
                        *pValue = target;
                    }
                }
            }
        }
    }

    return fabsf(target - *pValue);
}

void Math_ApproachF(f32* pValue, f32 target, f32 scale, f32 maxStep) {
    f32 f2;

    if (*pValue != target) {
        f2 = (target - *pValue) * scale;

        if (f2 > maxStep) {
            f2 = maxStep;
        } else if (f2 < -maxStep) {
            f2 = -maxStep;
        }

        *pValue += f2;
    }
}

void Math_ApproachZeroF(f32* pValue, f32 scale, f32 maxStep) {
    f32 f0 = *pValue * scale;

    if (maxStep < f0) {
        f0 = maxStep;
    } else if (f0 < -maxStep) {
        f0 = -maxStep;
    }

    *pValue = *pValue - f0;
}

s32 Math_SmoothStepToS(s16* pValue, s16 target, s16 scale, s16 step, s16 minStep) {
    s16 stepSize = 0;
    s16 diff = target - *pValue;

    if (*pValue != target) {
        stepSize = diff / scale;

        if ((stepSize > minStep) || (stepSize < -minStep)) {
            if (stepSize > step) {
                stepSize = step;
            }

            if (stepSize < -step) {
                stepSize = -step;
            }

            *pValue += stepSize;
        } else {
            if (diff >= 0) {
                *pValue += minStep;

                if ((s16)(target - *pValue) <= 0) {
                    *pValue = target;
                }
            } else {
                *pValue -= minStep;

                if ((s16)(target - *pValue) >= 0) {
                    *pValue = target;
                }
            }
        }
    }

    return diff;
}

void Math_ApproachS(s16* pValue, s16 target, s16 scale, s16 maxStep) {
    s16 diff = target - *pValue;
    diff /= scale;

    if (diff > maxStep) {
        *pValue += maxStep;
        return;
    }

    if (diff < -maxStep) {
        *pValue -= maxStep;
        return;
    }

    *pValue += diff;
}

void Color_RGBA8_Copy(Color_RGBA8* dst, Color_RGBA8* src) {
    dst->r = src->r;
    dst->g = src->g;
    dst->b = src->b;
    dst->a = src->a;
}

void func_801000A4(u16 sfxId) {
    play_sound(sfxId);
}

void func_801000CC(u16 sfxId) {
    func_8019F128(sfxId);
}

void Lib_PlaySfxAtPos(Vec3f* pos, u16 sfxId) {
    Audio_PlaySfxAtPos(pos, sfxId);
}

void Lib_Vec3f_TranslateAndRotateY(Vec3f* translation, s16 a, Vec3f* src, Vec3f* dst) {
    f32 sp1C;
    f32 f0;

    sp1C = Math_CosS(a);
    f0 = Math_SinS(a);
    dst->x = translation->x + (src->x * sp1C + src->z * f0);
    dst->y = translation->y + src->y;
    dst->z = translation->z + (src->z * sp1C - src->x * f0);
}

void Lib_LerpRGB(Color_RGB8* a, Color_RGB8* b, f32 t, Color_RGB8* dst) {
    f32 aF;

    aF = a->r;
    dst->r = aF + (b->r - aF) * t;
    aF = a->g;
    dst->g = aF + (b->g - aF) * t;
    aF = a->b;
    dst->b = aF + (b->b - aF) * t;
}

f32 Math_Vec3f_StepTo(Vec3f* start, Vec3f* target, f32 speed) {
    Vec3f diff;
    f32 f2;
    f32 f0;

    Math_Vec3f_Diff(target, start, &diff);
    f0 = Math3D_Vec3fMagnitude(&diff);
    if (speed < f0) {
        f2 = speed / f0;
        f0 = f0 - speed;
        start->x = start->x + f2 * diff.x;
        start->y = start->y + f2 * diff.y;
        start->z = start->z + f2 * diff.z;
    } else {
        Math_Vec3f_Copy(start, target);
        f0 = 0;
    }

    return f0;
}

void Lib_Nop801004FC(void) {
}

void* Lib_SegmentedToVirtual(void* ptr) {
    return SEGMENTED_TO_VIRTUAL(ptr);
}

void* Lib_SegmentedToVirtualNull(void* ptr) {
    if (((uintptr_t)ptr >> 28) == 0) {
        return ptr;
    }

    return SEGMENTED_TO_VIRTUAL(ptr);
}

void* Lib_PhysicalToVirtual(void* ptr) {
    if (ptr == NULL) {
        return NULL;
    } else {
        return (void*)PHYSICAL_TO_VIRTUAL(ptr);
    }
}

void* Lib_PhysicalToVirtualNull(void* ptr) {
    if (ptr == NULL) {
        return NULL;
    } else {
        return (void*)PHYSICAL_TO_VIRTUAL(ptr);
    }
}
