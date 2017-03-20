
#include <stdio.h>
#include <math.h>
#include "physics.h"

VECTOR2D newVector(float x, float y)
{
    VECTOR2D tmp;
    tmp.i = x;
    tmp.j = y;
    return tmp;
}

VECTOR2D zeroVector(void)
{
    return (VECTOR2D){0, 0};
}

float getMag(VECTOR2D VEC_A)
{
    return sqrt(VEC_A.i * VEC_A.i + VEC_A.j * VEC_A.j);
}

float dotP(VECTOR2D A, VECTOR2D B)
{
    return A.i * B.i + A.j * B.j;
}

VECTOR2D scalarP(VECTOR2D A, float f)
{
    VECTOR2D tmp = newVector(0, 0);
    tmp.i = A.i * f;
    tmp.j = A.j * f;
    return tmp;
}

VECTOR2D sumVector(VECTOR2D A, VECTOR2D B)
{
    VECTOR2D tmp = newVector(0, 0);
    tmp.i = A.i + B.i;
    tmp.j = A.j + B.j;
    return tmp;
}

VECTOR2D subVector(VECTOR2D A, VECTOR2D B)
{
    return sumVector(A, scalarP(B, -1));
}

VECTOR2D unitVector(VECTOR2D A)
{
    VECTOR2D tmp = newVector(0, 0);
    float mag = getMag(A);
    tmp.i = A.i / mag;
    tmp.j = A.j / mag;
    return tmp;
}

VECTOR2D getComponent(VECTOR2D A, VECTOR2D N)
{
    VECTOR2D N_CAP = newVector(0, 0);
    VECTOR2D result = newVector(0, 0);
    N_CAP = unitVector(N);
    result = scalarP(N_CAP, dotP(A, N_CAP));
    return result;
}


void printV(VECTOR2D A)
{
    printf("%.1fi + %.1fj\n", A.i, A.j);
}
