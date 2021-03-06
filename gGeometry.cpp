/************************************************************************************************
*                                                                                               *
*                                                                                               *
************************************************************************************************/

#include "gGeometry.h"

/************************************************************************************************
* Zero vector initialization                                                                    *
************************************************************************************************/
vector3f vInit()
{
    vector3f v;

    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;

    return v;
}

/************************************************************************************************
* Vector initialization by x, y, z                                                              *
************************************************************************************************/
vector3f vInit(float x, float y, float z)
{
    vector3f v;

    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}

/************************************************************************************************
* Copying vector initialization                                                                 *
************************************************************************************************/
vector3f vInit(vector3f a)
{
    vector3f v;

    v.x = a.x;
    v.y = a.y;
    v.z = a.z;

    return v;
}

/************************************************************************************************
* Vectors adition                                                                               *
************************************************************************************************/
vector3f vAdd(vector3f a, vector3f b)
{
    vector3f v;

    v.x = a.x + b.x;
    v.y = a.y + b.y;
    v.z = a.z + b.z;

    return v;
}

/************************************************************************************************
* Vectors substraction                                                                          *
************************************************************************************************/
vector3f vSub(vector3f a, vector3f b)
{
    vector3f v;

    v.x = a.x - b.x;
    v.y = a.y - b.y;
    v.z = a.z - b.z;

    return v;
}

/************************************************************************************************
* Vector scaling                                                                                *
************************************************************************************************/
vector3f vScale(vector3f a, float k)
{
    vector3f v;

    v.x = a.x*k;
    v.y = a.y*k;
    v.z = a.z*k;

    return v;
}

/************************************************************************************************
* Vector normalization                                                                          *
************************************************************************************************/
vector3f vNormalize(vector3f a)
{
    vector3f  v;
    float     magn;

    magn = vMagnitude(a);
    v.x = a.x/magn;
    v.y = a.y/magn;
    v.z = a.z/magn;

    return v;
}

/************************************************************************************************
* Vector cross product                                                                          *
************************************************************************************************/
vector3f vCrossProduct(vector3f a, vector3f b)
{
    vector3f  v;

    v.x = a.y*b.z - a.z*b.y;
    v.y = a.z*b.x - a.x*b.z;
    v.z = a.x*b.y - a.y*b.x;

    return v;
}

/************************************************************************************************
* Vector dot poduct                                                                             *
************************************************************************************************/
float vDotProduct(vector3f a, vector3f b)
{
    return (a.x*b.x + a.y*b.y + a.z*b.z);
}

/************************************************************************************************
* Return vector magnitude                                                                       *
************************************************************************************************/
float vMagnitude(vector3f a)
{
    return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z);
}

/************************************************************************************************
* Return distance between two vectors                                                           *
************************************************************************************************/
float vDistance(vector3f a, vector3f b)
{
    return (float)fabs(sqrtf((b.x-a.x)*(b.x-a.x)
                            +(b.y-a.y)*(b.y-a.y)
                            +(b.z-a.z)*(b.z-a.z)));
}
