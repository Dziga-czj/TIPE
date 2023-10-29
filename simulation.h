#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "tools.h"
#include "particule.h"
#include <stdio.h>

    struct Wall {
        Vector2 pos1;
        Vector2 pos2;
    }; typedef struct Wall Wall;

    struct WArray {
        int used;
        int size;
        Wall *walls;
    }; typedef struct WArray WArray;

    struct Simulation {
        PArray *p_array;
        WArray *w_array;

        bool running;
        float time;
        int nb_particules;
        
    }; typedef struct Simulation Simulation;


    WArray *WArray_create();
    void WArray_add(WArray *w_array, Vector2 pos1, Vector2 pos2);
    void WArray_free(WArray *w_array);
    Wall wall_add(WArray *w_array, Vector2 pos1, Vector2 pos2);
    Wall wall_create(Vector2 pos1, Vector2 pos2);
    void walls_render(WArray *w_array);
    Vector2 walls_collision(Simulation *sim, int i);


    Simulation sim_create();
    void sim_free(Simulation *sim);
    void sim_render(Simulation *sim);
    void sim_tick(Simulation *sim);
    void sim_add_mesh(Simulation *sim, int n, Vector2 *points, bool closed);
    void sim_add_particule(Simulation *sim, Vector2 pos, float radius, Vector2 *dest, int nb_dest);
    void sim_load_map(Simulation *sim, const char *filename);

    void particules_tick(Simulation *sim, int i);

#endif