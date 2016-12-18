#ifndef RAYTRACING_H_INCLUDED
#define RAYTRACING_H_INCLUDED

#include <cmath>
#include "quadric.h"
#include "classes.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Vec rayTracing(Ray ray, int depth, Config config);
double distance(Vec ptA, Vec ptB);

#endif // RAYTRACING_H_INCLUDED
