#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "classes.h"

using namespace std;
Config config;

Color rayTracing(Ray ray, std::vector<Quad> object) {
    if(ray.depth >= 0) {
        for(int i = 0; i < object.size(); i++) {
            if (intersect(ray, &object[i]) != -1)
            {

                return rgb(object[i].m.r, object[i].m.g, object[i].m.b);
            }
        }
        return config.background;
    }

    return rgb(0,0,0);
}

Vec center(Quad quad) {
    return mkvec(-quad.g, -quad.h, -quad.j);
}


int main () {
    string line, opt;
    ifstream configFile ("entrada2.txt");
    int color_max = 255;

    while(!configFile.eof()) {

        getline(configFile, line);

        if(line.find("#") == std::string::npos) {
            stringstream stream(line);
            stream >> opt;

            if(opt == "eye") {
                stream >> config.eye.x >> config.eye.y >> config.eye.z;
                continue;
            }

            if(opt == "size") {
                stream >> config.width >> config.height;
                continue;
            }

            if(opt == "ortho") {
                stream >> config.x0 >> config.y0 >> config.x1 >> config.y1;
                continue;
            }

            if(opt == "light") {
                Light light;
                stream >> light.dir.x >> light.dir.y >> light.dir.z >> light.Int;
                 config.light.push_back(light);
                continue;
            }

            if(opt == "profundidade") {
                stream >> config.profundidade;
                continue;
            }

             if(opt == "ambient") {
                stream >> config.ambient;
                continue;
            }

            if(opt == "background") {
                stream >> config.background.r >> config.background.g >> config.background.b;
                continue;
            }

            if(opt == "object") {
                Quad object;
                stream >> object.a >> object.b >> object.c >> object.d >> object.e >> object.f >> object.g >> object.h >> object.j >> object.k
                >> object.m.r >> object.m.g >> object.m.b >> object.m.Ka >> object.m.Kd >> object.m.Ks >> object.m.n >> object.m.KS >> object.m.KT >> object.m.ir;
                object.center = center(object);
                config.object.push_back(object);
                continue;

            }

            if(opt == "output") {
                 stream >> config.output;
                 continue;
            }
        }
    }
    configFile.close();

    Color tela[config.width][config.height];
    double pxW = abs(config.x0 - config.x1)/config.width;
	double pxH = abs(config.y0 - config.y1)/config.height;

	for(int c = 0; c < config.height; c ++) {
        for (int l = 0; l < config.width; l++) {
            Vec px;
            px.x = config.x0 + l*pxW + pxW/2;
            px.y = config.y0 + c*pxH + pxH/2;
            px.z = 0;

            Ray ray;
            ray.org = config.eye;
            ray.dir = vsub(px, config.eye);
            ray.depth = config.profundidade;

            tela[l][c] = rayTracing(ray, config.object);

            tela[l][c].r = (int) tela[l][c].r * 255;
            tela[l][c].g = (int) tela[l][c].g * 255;
            tela[l][c].b = (int) tela[l][c].b * 255;
        }
	}


    ofstream output;
    output.open (config.output.c_str());
    output << "P3" << endl;
    output << config.width << " " << config.height << endl;
    output << color_max << endl;
    for(int c = 0; c < config.height; c ++) {
        for (int l = 0; l < config.width; l++) {
            output << tela[l][c].r << " " << tela[l][c].g << " " << tela[l][c].b << " ";
        }
        output << endl;
	}
    output.close();

    return 0;
}

