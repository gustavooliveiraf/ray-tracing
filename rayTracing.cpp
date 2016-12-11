#include "rayTracing.h"

/** TO DOs */


Color rayTracing(Ray ray, int depth){
    Quad *object = NULL;
    float minDist = INFINITY;

    // ponto onde o raio intersectou um objeto
    Vec hitPoint;

    // pra cada objeto na scene, verifica se o raio lancado o intersecta
    for(int i = 0; i < contQ; i++){
        if(intersect(ray, quad[i]) > 0){/** checar essa funcao pra entender o retorno dela e ver como pegar o hitPoint */
            float dist =  distance(hitPoint, ray.org);
            if(dist < minDist){
                minDist = dist;
                object = quad[i];
            }
        }
    }

    // se o raio nao intersecta nenhum objeto, retorna a cor de background
    if(object == NULL){
        return backGround;
    }

    // raio de luz
    Ray lightRay;
    lightRay.org = light.dir;
    lightRay.dir = vsub(light.dir, hitPoint);
    lightRay.depth = distance(light.dir, hitPoint); //light.Int;

    for(int i = 0; i < contQ; i++){
        // se a luz bate em algum objeto antes de chegar no hitPoint, entao hitpoint está na sombra
        if(intersect(lightRay, quad[i]) > 0){/** checar essa funcao pra entender o retorno dela e saber se eh > ou < */
            return black;
        }
    }



    Color c;
    c.r = object.r * light.Int;
    c.g = object.g * light.Int;
    c.b = object.b * light.Int;

    if(depth > 0){
        //emitir novo raio e pegar raytracing dele com depth-1;
        Ray reflect;/** ver como calcular esse raio */
        Color cor = rayTracing(reflect, depth-1);
        c.r = c.r + cor.r;
        c.g = c.g + cor.g;
        c.b = c.b + cor.b;
    }

    return c;
}


float distance(Vec ptA, Vec ptB){
    float dx = ptA.x - ptb.x,
        dy = ptA.y - ptb.y,
        dz = ptA.z - ptb.z;

    return sqrt(dx*dx + dy*dy + dz*dz);
}
