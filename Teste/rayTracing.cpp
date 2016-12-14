#include "rayTracing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

Color rayTracing(Ray ray, std::vector<Quad> object) {
    for(int i = 0; i < object.size(); i++) {
        if (intersect(ray, &object[i]) != -1)
        {
            return rgb(object[i].m.r, object[i].m.g, object[i].m.b);
        } else {
            return nc();
        }
    }
}


double distance(Vec ptA, Vec ptB) {
    double dx = ptA.x - ptB.x,
        dy = ptA.y - ptB.y,
        dz = ptA.z - ptB.z;

    return sqrt(dx*dx + dy*dy + dz*dz);
}

 Color nc() {
    Color color;
    color.r = -1;
    color.g = -1;
    color.b = -1;
    return color;
 }

 Color rgb(double a, double b, double c) {
    Color color;
    color.r = a;
    color.g = b;
    color.b = c;
    return color;
 }
