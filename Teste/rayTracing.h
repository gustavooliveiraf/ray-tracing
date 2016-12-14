#ifndef RAYTRACING_H_INCLUDED
#define RAYTRACING_H_INCLUDED

#include <cmath>
#include "quadric.h"
#include "classes.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Color rayTracing(Ray ray, std::vector<Quad> object);
double distance(Vec ptA, Vec ptB);
Color rgb(double a, double b, double c);
Color nc();
Vec get_center(Quad quad);

#endif // RAYTRACING_H_INCLUDED
