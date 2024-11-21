#include "Math.h"
#include "Vector3D.h"

float Math::pi()
{
    return 3.14159265359;
}

float Math::toDegrees(float angle)
{
    return angle * 57.2958;
}

float Math::toRadians(float angle)
{
    return angle * 0.0174533;
}
