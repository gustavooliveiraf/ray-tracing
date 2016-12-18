#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "quadric.h"
#include "classes.h"
#include "rayTracing.h"

using namespace std;

#define INFINITY 1e8

Config config;

double distance(Vec ptA, Vec ptB) {
	double dx = ptA.x - ptB.x,
		dy = ptA.y - ptB.y,
		dz = ptA.z - ptB.z;

	return sqrt(dx*dx + dy*dy + dz*dz);
}

Vec rayTracing2(Ray ray, int depth, Config config) {
	if (depth <= config.profundidade) {
		Quad *object = NULL;
		ray.depth = INFINITY;
		normalize(&ray.dir);
		double t = 0;
		for (int i = 0; i < config.object.size(); i++) {
			double t2 = intersect(ray, &config.object[i]);
			if (t2 != -1) {
				//double distance2 = distance(ray.org, vadd(ray.org, svmpy(t2, ray.dir)));
				if (t2 < ray.depth) {
					object = &config.object[i];
					ray.depth = t2;
					t = t2;
				}
			}
		}

		if (object == NULL)
			return config.background;

		Vec pInter = ray.org + (ray.dir * t);
		Vec origemObject = mkvec(-object->g, -object->h, -object->j);
		Vec n = pInter - origemObject; normalize(&n);
		double NdotRay = dot(n, ray.dir);
		Ray r;
		r.dir = (n * (2 * NdotRay)) - ray.dir; normalize(&r.dir);
		r.org = pInter;
		Vec dif = rayTracing2(r, depth + 1, config);

		Ray l;
		Vec amb;
		bool flag = true;
		for (int i = 0; i < config.light.size(); i++) { // somando as luzes
			l.org = config.light[i].dir;
			l.dir = pInter - config.light[i].dir;
			normalize(&l.dir);
			for (int j = 0; j < config.object.size(); j++) {
				double t2 = intersect(l, &config.object[i]);
				if (t2 != -1) {
					// double distance2 = distance(l.org, vadd(l.org, svmpy(t, l.dir)));
					if (t2 < ray.depth) {
						flag = false;
						break;
					}
				}
			}
			if (flag) {
				double LdotN = dot(n, l.dir);
				dif.x += config.light[i].Int * object->m.Kd * LdotN * object->m.r;
				dif.y += config.light[i].Int * object->m.Kd * LdotN * object->m.g;
				dif.z += config.light[i].Int * object->m.Kd * LdotN * object->m.b;
			}
			flag = true;
		}

		amb = mkvec(config.ambient * object->m.Ka * object->m.r,
					config.ambient * object->m.Ka * object->m.g,
					config.ambient * object->m.Ka * object->m.b);

		return amb + svmpy(object->m.KS, amb);
	}
	else
		return mkvec(0,0,0);
}

int main () {
    string line, opt;
    ifstream configFile ("entrada.txt");
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
                stream >> config.background.x >> config.background.y >> config.background.z;
                continue;
            }

            if(opt == "object") {
                Quad object;
                stream >> object.a >> object.b >> object.c >> object.d >> object.e >> object.f >> object.g >> object.h >> object.j >> object.k
                >> object.m.r >> object.m.g >> object.m.b >> object.m.Ka >> object.m.Kd >> object.m.Ks >> object.m.n >> object.m.KS >> object.m.KT >> object.m.ir;
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

    Vec tela[200][200]; ///////!/////// tem que
    double pxW = abs(config.x0 - config.x1)/config.width;
	double pxH = abs(config.y0 - config.y1)/config.height;

	for(int c = 0; c < config.height; c ++) {
        for (int l = 0; l < config.width; l++) {
            Vec px;
			px.x = config.x0 + l*pxW + pxW / 2;
			px.y = config.y0 + c*pxH + pxH / 2;
            px.z = 0;

            Ray ray;
            ray.org = config.eye;
            ray.dir = vsub(px, config.eye);
            ray.depth = config.profundidade; // so pra inicializar

            tela[l][c] = rayTracing2(ray, 0, config);

            tela[l][c].x = (int) tela[l][c].x * 255;
            tela[l][c].y = (int) tela[l][c].y * 255;
            tela[l][c].z = (int) tela[l][c].z * 255;
        }
	}

	// teste ////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Vec a, b, c;
	//a = mkvec(1, 2, 3);
	//b = mkvec(4, 5, 6);
	//int d = 10;
	//c = (b - a) * d;

	//std::cout << c.x << " " << c.y << " " << c.z << endl;

	// teste

    ofstream output;
    output.open (config.output.c_str());
    output << "P3" << endl;
    output << config.width << " " << config.height << endl;
    output << color_max << endl;
    for(int c = 0; c < config.height; c ++) {
        for (int l = 0; l < config.width; l++) {
            output << tela[l][c].x << " " << tela[l][c].y << " " << tela[l][c].z << " ";
        }
        output << endl;
	}
    output.close();

    return 0;
}

