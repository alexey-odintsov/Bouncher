#ifndef GGEOMETRYH
#define GGEOMETRYH

#include <windows.h>
#include <math.h>

struct vector3f
{
    float x, y, z;
};

vector3f  vInit();
vector3f  vInit(float x, float y, float z);
vector3f  vInit(vector3f a);

vector3f  vAdd(vector3f a, vector3f b);
vector3f  vSub(vector3f a, vector3f b);
vector3f  vScale(vector3f a, float k);
vector3f  vNormalize(vector3f a);
vector3f  vCrossProduct(vector3f a, vector3f b);
float     vDotProduct(vector3f a, vector3f b);
float     vMagnitude(vector3f a);
float     vDistance(vector3f a, vector3f b);

#endif