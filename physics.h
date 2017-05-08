#ifndef PHYSICS_H
#define PHYSICS_H

#define ORIGIN {0, 0}
#define G_ACC {0, -10}

typedef struct _vector_2d
{
  float i;
  float j;
} VECTOR2D;

typedef struct _world
{
  VECTOR2D gravity;
  VECTOR2D origin;
} WORLD;

typedef VECTOR2D POS_V;
typedef VECTOR2D DSP_V;
typedef VECTOR2D VEL_V;
typedef VECTOR2D ACC_V;
typedef VECTOR2D FORCE_V;

VECTOR2D newVector(float x, float y);
VECTOR2D zeroVector(void);
float getMag(VECTOR2D VEC_A);
float dotP(VECTOR2D A, VECTOR2D B);
VECTOR2D scalarP(VECTOR2D A, float f);
VECTOR2D sumVector(VECTOR2D A, VECTOR2D B);
VECTOR2D subVector(VECTOR2D A, VECTOR2D B);
VECTOR2D unitVector(VECTOR2D A);
VECTOR2D getComponent(VECTOR2D A, VECTOR2D N);
void addVectorPointer(VECTOR2D *ptr_a, VECTOR2D b);

#endif // PHYSICS_H
