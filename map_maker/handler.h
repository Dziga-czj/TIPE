#ifndef HANDLER_H_
#define HANDLER_H_

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>


struct mesh {
    Vector2 *points;
    int nb_p;
    bool closed;

}; typedef struct mesh mesh;


struct handler {


    Rectangle *buttons;
    int nb_buttons;

    bool editing;

    Vector2 *points;
    int nb_points;

    FILE *fp;

    mesh *meshs;
    int nb_meshs;
    

}; typedef struct handler handler;

void tick(handler *handler);
handler create_handler(const char *filename);
void render(handler *handler);
void handler_free(handler *handler);
void add_point(handler *handler, Vector2 pos);
void editing_stop(handler *handler);
void add_mesh(handler *handler, bool closed);
mesh create_mesh(handler *handler);
void mesh_delete_last(handler *handler);

void load_into_file(handler *handler);

#endif
