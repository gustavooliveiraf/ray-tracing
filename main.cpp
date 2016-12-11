#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <Eigen/Dense>
#include <opencv.hpp>

#include "quadric.h"

int main() {//(int argc, char** argv)
	FILE *stream;
	freopen_s(&stream, "entrada.txt", "r", stdin);
	//freopen("saida.out", "w", stdout);

	char buffer[222000] = "";
	char output[222000]="", supersample[4] = "";
	double back_r = 0, back_g = 0, back_b = 0;
	double x0=0, y0=0, x1=0, y1=0, Ia = 0;
	int w = 0, h = 0, profundidade = 0;
	Light *light = (Light*)malloc(sizeof(Light));
	Quad *quad = (Quad*)malloc(sizeof(Quad));
	Vec eye;
	
	int contl = 0, contQ = 0;

	while (scanf_s(" %s", buffer) > 0) {
		if (buffer[0] != '#') {
			if (strcmp(buffer, "output") == 0) {
				scanf_s(" %s", output);
			}
			else if (strcmp(buffer, "eye") == 0) {
				double x=0, y=0, z=0;
				scanf_s(" %lf %lf %lf", &x, &y, &z);
				eye = mkvec(x, y, z);
				//printf("%lf %lf %lf\n", eye.x, eye.y, eye.z);
			}
			else if (strcmp(buffer, "ortho") == 0) {
				scanf_s(" %lf %lf %lf %lf", &x0, &y0, &x1, &y1);
			}
			else if (strcmp(buffer, "size") == 0) {
				scanf_s(" %d %d", &w, &h);
			}
			else if (strcmp(buffer, "background") == 0) {
				scanf_s(" %lf %lf %lf", &back_r, &back_g, &back_b);
			}
			else if (strcmp(buffer, "ambient") == 0) {
				scanf_s(" %lf", &Ia);
			}
			else if (strcmp(buffer, "light") == 0) {
				double x=0, y=0, z=0, Int=0;
				scanf_s(" %lf %lf %lf %lf", &x, &y, &z, &Int);
				light = (Light*)realloc(light, (contl +1) * sizeof(Light));
				light[contl].dir = mkvec(x, y, z);
				light[contl++].Int = Int;
			}
			else if (strcmp(buffer, "supersample ") == 0) {
				scanf_s(" %s", supersample);
			}
			else if (strcmp(buffer, "profundidade") == 0) {
				scanf_s(" %d", &profundidade);
			}
			else if (strcmp(buffer, "object") == 0) {
				quad = (Quad*)realloc(quad, (contQ + 1) * sizeof(Quad));
				scanf_s(" %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %d %lf %lf %lf",
					&quad[contQ].a, &quad[contQ].b, &quad[contQ].c, &quad[contQ].d, &quad[contQ].e, &quad[contQ].f, &quad[contQ].g,
					&quad[contQ].h, &quad[contQ].j, &quad[contQ].k, &quad[contQ].m.r, &quad[contQ].m.g, &quad[contQ].m.b,
					&quad[contQ].m.Ka, &quad[contQ].m.Kd, &quad[contQ].m.Ks, &quad[contQ].m.n, &quad[contQ].m.KS, &quad[contQ].m.KT, &quad[contQ].m.ir);
				contQ++;
			}
			else {
				printf("entrada invalida\n");
			}
		}
		else {   
			scanf_s(" %[^\n]", buffer);
		}
		strcpy_s(buffer, "");
	}

	printf("%lf\n", quad[0].a);

	return 0;
}