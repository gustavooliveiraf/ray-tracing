#ifndef RAYTRACING_H_INCLUDED
#define RAYTRACING_H_INCLUDED

#include "quadric.h"

typedef struct color{
    double  r;// Red component
	double  b;// Blue component
	double  g;// Green component
}Color;

Color backGround;
Color black;
Quad *quad;
int contQ;
Light *light;

Color rayTracing(Ray ray, int depth);
float distance(Vec ptA, Vec ptB);



#endif // RAYTRACING_H_INCLUDED
