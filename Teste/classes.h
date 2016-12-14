#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED
#include "quadric.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

class Color {
    public:
        double r, g, b;
};

Color rgb(double a, double b, double c) {
    Color color;
    color.r = a;
    color.g = b;
    color.b = c;
    return color;
 }

class Config {
    public:
    double ambient, x0, y0, x1, y1;
    int profundidade, width, height;
    std::string output;
    Vec eye;
    std::vector<Light> light;
    Color background;
    std::vector<Quad> object;
};

#endif // CLASSES_H_INCLUDED
