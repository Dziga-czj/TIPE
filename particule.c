

#include "particule.h"
Vector2 walls_collision(PArray *p_array, int i, Vector2 *newPos, WArray *w_array);

PArray *PArray_create()
{
    PArray *p_array = malloc(sizeof(PArray));
    p_array->size = 8;
    p_array->used = 0;

    p_array->particules = malloc(p_array->size * sizeof(Particule));

    return p_array;
}

void PArray_add(PArray *p_array, Particule particule)
{
    if (p_array->used == p_array->size)
    {
        p_array->size *= 2;
        p_array->particules = reallocarray(p_array->particules, sizeof(Particule), p_array->size * sizeof(Particule));
    }
    p_array->particules[p_array->used] = particule;
    p_array->used++;
}

Particule particule_create(Vector2 pos, float radius, Vector2 *dest, int nb_dest)
{
    Particule p;
    p.pos = pos;
    p.dest = dest;
    p.vel = (Vector2){0, 0};
    p.radius = radius;
    p.speed = 2;
    p.visible = true;
    p.press = 0;
    p.nb_dest = nb_dest;
    p.dest = dest;
    p.cur_dest = 0;

    return p;
}

#define P p_array->particules

void particules_render(PArray *p_array)
{
    for (int i = 0; i < p_array->used; i++)
    {
        if(p_array->particules[i].visible)
        {
            int p  = 0;
            Color col = (Color) {p, 0, 255-p, 255};
            DrawCircleV(p_array->particules[i].pos, p_array->particules[i].radius, col);

            // Vector2 point = { .x = P[i].pos.x + P[i].vel.x*10, .y = P[i].pos.y + P[i].vel.y*10};
            // DrawLineV(P[i].pos, point, RED);

        }   
        
        
    }
}

float particules_collision(PArray *p_array, int i, int j)
{
    #define P p_array->particules

    if (j != i && P[j].visible)
    {
        float dist = distance(P[i].pos, P[j].pos);

        if (dist < (P[i].radius + P[j].radius))
        {
            float dec = -(P[i].radius + P[j].radius - dist);
            Vector2 decal = dir_vector(P[i].pos, P[j].pos, dec);
            P[i].press++;
            P[i].vel.x += decal.x;
            P[i].vel.y += decal.y;
        }
        return dist;
    }
    else return 0;
}

void PArray_free(PArray *p_array)
{
    free(p_array->particules);
    free(p_array);
}
