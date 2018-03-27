#include "Frustum.hpp"


void NormalizePlane(float frustum[6][4], int side)
{
    float magnitude = sqrtf(
            frustum[side][A] * frustum[side][A]
            + frustum[side][B] * frustum[side][B]
            + frustum[side][C] * frustum[side][C]
    );

    frustum[side][A] /= magnitude;
    frustum[side][B] /= magnitude;
    frustum[side][C] /= magnitude;
    frustum[side][D] /= magnitude;
}

void Frustum::CalculateFrustum(const glm::mat4 & projMatrix, const glm::mat4 & viewMatrix)
{
    float proj[16];
    float modl[16];
    float clip[16];

    for (int i = 0; i < 16; ++i)
        proj[i] = glm::value_ptr(projMatrix)[i];
    for (int i = 0; i < 16; ++i)
        modl[i] = glm::value_ptr(viewMatrix)[i];

    clip[0] = modl[0] * proj[0] + modl[1] * proj[4] + modl[2] * proj[8] + modl[3] * proj[12];
    clip[1] = modl[0] * proj[1] + modl[1] * proj[5] + modl[2] * proj[9] + modl[3] * proj[13];
    clip[2] = modl[0] * proj[2] + modl[1] * proj[6] + modl[2] * proj[10] + modl[3] * proj[14];
    clip[3] = modl[0] * proj[3] + modl[1] * proj[7] + modl[2] * proj[11] + modl[3] * proj[15];

    clip[4] = modl[4] * proj[0] + modl[5] * proj[4] + modl[6] * proj[8] + modl[7] * proj[12];
    clip[5] = modl[4] * proj[1] + modl[5] * proj[5] + modl[6] * proj[9] + modl[7] * proj[13];
    clip[6] = modl[4] * proj[2] + modl[5] * proj[6] + modl[6] * proj[10] + modl[7] * proj[14];
    clip[7] = modl[4] * proj[3] + modl[5] * proj[7] + modl[6] * proj[11] + modl[7] * proj[15];

    clip[8] = modl[8] * proj[0] + modl[9] * proj[4] + modl[10] * proj[8] + modl[11] * proj[12];
    clip[9] = modl[8] * proj[1] + modl[9] * proj[5] + modl[10] * proj[9] + modl[11] * proj[13];
    clip[10] = modl[8] * proj[2] + modl[9] * proj[6] + modl[10] * proj[10] + modl[11] * proj[14];
    clip[11] = modl[8] * proj[3] + modl[9] * proj[7] + modl[10] * proj[11] + modl[11] * proj[15];

    clip[12] = modl[12] * proj[0] + modl[13] * proj[4] + modl[14] * proj[8] + modl[15] * proj[12];
    clip[13] = modl[12] * proj[1] + modl[13] * proj[5] + modl[14] * proj[9] + modl[15] * proj[13];
    clip[14] = modl[12] * proj[2] + modl[13] * proj[6] + modl[14] * proj[10] + modl[15] * proj[14];
    clip[15] = modl[12] * proj[3] + modl[13] * proj[7] + modl[14] * proj[11] + modl[15] * proj[15];

    frustum_[RIGHT][A] = clip[3] - clip[0];
    frustum_[RIGHT][B] = clip[7] - clip[4];
    frustum_[RIGHT][C] = clip[11] - clip[8];
    frustum_[RIGHT][D] = clip[15] - clip[12];

    NormalizePlane(frustum_, RIGHT);

    frustum_[LEFT][A] = clip[3] + clip[0];
    frustum_[LEFT][B] = clip[7] + clip[4];
    frustum_[LEFT][C] = clip[11] + clip[8];
    frustum_[LEFT][D] = clip[15] + clip[12];

    NormalizePlane(frustum_, LEFT);

    frustum_[BOTTOM][A] = clip[3] + clip[1];
    frustum_[BOTTOM][B] = clip[7] + clip[5];
    frustum_[BOTTOM][C] = clip[11] + clip[9];
    frustum_[BOTTOM][D] = clip[15] + clip[13];

    NormalizePlane(frustum_, BOTTOM);

    frustum_[TOP][A] = clip[3] - clip[1];
    frustum_[TOP][B] = clip[7] - clip[5];
    frustum_[TOP][C] = clip[11] - clip[9];
    frustum_[TOP][D] = clip[15] - clip[13];

    NormalizePlane(frustum_, TOP);

    frustum_[BACK][A] = clip[3] - clip[2];
    frustum_[BACK][B] = clip[7] - clip[6];
    frustum_[BACK][C] = clip[11] - clip[10];
    frustum_[BACK][D] = clip[15] - clip[14];

    NormalizePlane(frustum_, BACK);

    frustum_[FRONT][A] = clip[3] + clip[2];
    frustum_[FRONT][B] = clip[7] + clip[6];
    frustum_[FRONT][C] = clip[11] + clip[10];
    frustum_[FRONT][D] = clip[15] + clip[14];

    NormalizePlane(frustum_, FRONT);
}

bool Frustum::PointInFrustum(float x, float y, float z)
{
    for (auto & i : frustum_) {
        if (i[A] * x + i[B] * y + i[C] * z + i[D] <= 0) {
            return false;
        }
    }
    return true;
}

bool Frustum::SphereInFrustum(float x, float y, float z, float radius)
{
    for (auto & i : frustum_) {
        if (i[A] * x + i[B] * y + i[C] * z + i[D] <= -radius) {
            return false;
        }
    }
    return true;
}

bool Frustum::CubeInFrustum(float x, float y, float z, float width, float height, float depth)
{
    for (auto &i : frustum_) {
        if (i[A] * (x - width) + i[B] * (y - height) + i[C] * (z - depth) + i[D] > 0)
            continue;
        if (i[A] * (x + width) + i[B] * (y - height) + i[C] * (z - depth) + i[D] > 0)
            continue;
        if (i[A] * (x - width) + i[B] * (y + height) + i[C] * (z - depth) + i[D] > 0)
            continue;
        if (i[A] * (x + width) + i[B] * (y + height) + i[C] * (z - depth) + i[D] > 0)
            continue;
        if (i[A] * (x - width) + i[B] * (y - height) + i[C] * (z + depth) + i[D] > 0)
            continue;
        if (i[A] * (x + width) + i[B] * (y - height) + i[C] * (z + depth) + i[D] > 0)
            continue;
        if (i[A] * (x - width) + i[B] * (y + height) + i[C] * (z + depth) + i[D] > 0)
            continue;
        if (i[A] * (x + width) + i[B] * (y + height) + i[C] * (z + depth) + i[D] > 0)
            continue;
        return false;
    }

    return true;
}

bool Frustum::CubeInFrustum(const glm::vec3 &pos, const glm::vec3 &dim)
{
    return CubeInFrustum(pos.x, pos.y, pos.z, dim.x, dim.y, dim.z);
}