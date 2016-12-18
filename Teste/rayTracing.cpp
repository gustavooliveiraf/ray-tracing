#include "classes.h"
#include "rayTracing.h"

Vec rayTracing(Ray ray, int depth, Config config) {
	if (ray.depth >= 0) {
		for (int i = 0; i < config.object.size(); i++) {
			if (intersect(ray, &config.object[i]) != -1)
			{

				return mkvec(config.object[i].m.r, config.object[i].m.g, config.object[i].m.b);
			}
		}
		return config.background;
	}

	return mkvec(0, 0, 0);
}