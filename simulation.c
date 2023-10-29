
#include "simulation.h"

Simulation sim_create()
{
    Simulation sim;
    sim.w_array = WArray_create();
    sim.p_array = PArray_create();
    sim.time = 0;
    sim.running = true;
    sim.nb_particules = 0;

    return sim;
}

void sim_free(Simulation *sim)
{
    PArray_free(sim->p_array);
    WArray_free(sim->w_array);
}

void walls_render(WArray *w_array)
{
    for (int i = 0; i < w_array->used; i++)
    {
        DrawLineV(w_array->walls[i].pos1, w_array->walls[i].pos2, RED);
    }
    
}

WArray *WArray_create()
{
    WArray *w_array = malloc(sizeof(WArray));
    w_array -> size = 8;
    w_array -> used = 0;

    w_array->walls = malloc(w_array->size * sizeof(Particule));

    return w_array;
}

Wall wall_create(Vector2 pos1, Vector2 pos2)
{
    Wall w;
    w.pos1 = pos1;
    w.pos2 = pos2;
    return w;
}

void WArray_add(WArray *w_array, Vector2 pos1, Vector2 pos2)
{
    if(w_array->used == w_array->size)
    {
        w_array->size *= 2;
        w_array->walls = reallocarray(w_array->walls, sizeof(Wall), w_array->size*sizeof(Wall));
    }
    w_array->walls[w_array->used] = wall_create(pos1, pos2);
    w_array->used++;
}

void WArray_free(WArray *w_array)
{
    free(w_array->walls);
    free(w_array);
}

void sim_add_mesh(Simulation *sim, int n, Vector2 *points, bool closed)
{
    for (int i = 0; i < n-1; i++)
    {
        WArray_add(sim->w_array, points[i], points[i+1]);
    }
    if(closed)
    {
        WArray_add(sim->w_array, points[0], points[n-1]);
    }
}

void sim_add_particule(Simulation *sim, Vector2 pos, float radius, Vector2 *dest, int nb_dest)
{
    PArray_add(sim->p_array, particule_create(pos, radius, dest, nb_dest));
    sim->nb_particules++;
}

void sim_tick(Simulation *sim)
{
    if(sim->nb_particules != 0)
    {
        sim->time += 0.1;
    }

    for (int i = 0; i < sim->p_array->used; i++)
    {
        sim->p_array->particules[i].press = 0;
    }
    
    for (int i = 0; i < sim->p_array->used; i++)
    if(sim->p_array->particules[i].visible)
    {
        particules_tick(sim, i);
    }
    
}

void sim_render(Simulation *sim)
{   
    char buffer[50];
    int min = sim->time / 60;
    sprintf(buffer, "Time : %d min %f s", min, (sim->time - (float) min*60.0));
    DrawText(buffer, 1080/2+50, 10, 20, BLACK);
    
    sprintf(buffer, "particules restantes : %d", sim->nb_particules);
    DrawText(buffer, 1080/2+350, 10, 20, BLACK);


    // for (int i = 0; i < sim->p_array->particules[0].nb_dest; i++)
    // {
    //     DrawCircleV(sim->p_array->particules[0].dest[i], 60, GREEN);
    // }
    

    DrawFPS(1400, 10);

    particules_render(sim->p_array);
    walls_render(sim->w_array);
    
}

Vector2 walls_collision(Simulation *sim, int i)
{
    #define P sim->p_array->particules
    #define W sim->w_array->walls


    for (int j = 0; j < sim->w_array->used; j++)
    {
        Vector2 closest = {0.0f, 0.0f};

        if(collision_circle_line(P[i].pos, P[i].radius, W[j].pos1, W[j].pos2, &closest))
        {
            DrawCircleV(closest, 5, RED);
            float dist = P[i].radius - distance(P[i].pos, closest);
            Vector2 dir = dir_vector(closest, P[i].pos, dist);
            
            P[i].pos.x += dir.x;
            P[i].pos.y += dir.y;
        }
    }
        
}

float speed_calc(float x, float max, float security, float radius) { return max*(1-exp(-(x - radius)/security)); }

void particules_tick(Simulation *sim, int i)
{
    #define P sim->p_array->particules
    #define W sim->w_array->walls
    if(!P[i].visible) return;


    P[i].vel = dir_vector(P[i].pos, P[i].dest[P[i].cur_dest], P[i].speed);

    Vector2 oldPos = P[i].pos;

    P[i].pos.x += P[i].vel.x;
    P[i].pos.y += P[i].vel.y;

    float min_dist = 99999.f;

    for(int j = 0; j < sim->p_array->used; j++)
    {
        float cur_dist = particules_collision(sim->p_array, i, j);
        if(cur_dist != 0 && cur_dist < min_dist) min_dist = cur_dist;
    }

    P[i].pos.x = oldPos.x + P[i].vel.x;
    P[i].pos.y = oldPos.y + P[i].vel.y;

    walls_collision(sim, i);

    if(distance(P[i].dest[P[i].cur_dest], P[i].pos) < 60)
    {
        P[i].cur_dest++;
        if(P[i].cur_dest == P[i].nb_dest)
        {
            sim->nb_particules --;
            P[i].visible = false;
        }
    }
}

void sim_load_map(Simulation *sim, const char *filename)
{
    FILE *stream = fopen(filename, "r");
    int nb_vect;
    fscanf(stream, "%d\n", &nb_vect);

    for(int i = 0; i < nb_vect; i++)
    {
        int nb;
        int closed;
        fscanf(stream, "%d, %d\n", &nb, &closed);
        Vector2 *points = malloc(nb*sizeof(Vector2));

        for(int j = 0; j < nb; j++)
        {
            int x,y;
            fscanf(stream, "%d, %d\n", &x, &y);
            points[j].x = x;
            points[j].y = y;
        }
        
        if(closed == 1)
        {
            sim_add_mesh(sim, nb, points, true);
        }else
        {
            sim_add_mesh(sim, nb, points, false);
        }
        
        free(points);
    }


}
