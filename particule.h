#ifndef PARTICULE_H_
#define PARTICULE_H_

#include <stdlib.h>
#include "raylib.h"
#include <math.h>
#include <stdbool.h>
#include "tools.h"

    struct Particule {
        Vector2 pos;
        Vector2 vel;
        Vector2 *dest;
        int nb_dest;
        int cur_dest;

        float radius;
        float speed;
        bool visible;
        int press;

    }; typedef struct Particule Particule;

    struct PArray {
        int used;
        int size;
        Particule *particules;

    }; typedef struct PArray PArray;

    typedef struct WArray WArray;

    PArray *PArray_create();
    void PArray_add(PArray *p_array, Particule particule);
    void PArray_free(PArray *p_array);
    
    Particule particule_create(Vector2 pos, float radius, Vector2 *dest, int nb_dest);
    void particules_render(PArray *p_array);
    float particules_collision(PArray *p, int i, int j);
    


#endif