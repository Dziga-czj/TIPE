#include "handler.h"

#define h handler

handler create_handler(const char *filename)
{
    handler h;
    h.nb_meshs = 0;
    h.nb_buttons = 1;

    h.buttons = malloc(h.nb_buttons * sizeof(Rectangle));

    h.buttons[0].height = 50;
    h.buttons[0].width = 150;
    h.buttons[0].x = 500;
    h.buttons[0].y = 500;

    h.editing = false;
    h.nb_points = 0;
    h.points = NULL;

    h.fp = fopen(filename, "w");

    return h;
}


void tick(handler *handler)
{
    
    Vector2 mousePos = GetMousePosition();


    if(IsMouseButtonPressed(0))
    for(int i = 0; i < handler->nb_buttons; i++)
    {
        if(CheckCollisionPointRec(mousePos, handler->buttons[i]))
        {
            if(i == 0)
            {
                
            }
        }
    }   

    if(IsMouseButtonPressed(0))
    {
        add_point(handler, mousePos);
    }

    if(IsKeyPressed(KEY_SPACE))
    {
        editing_stop(handler);
    }

    if(IsKeyPressed(KEY_BACKSPACE))
    {
        mesh_delete_last(handler);
    }
    
    if(IsKeyPressed(KEY_ENTER))
    {
        add_mesh(handler, false);
    }
    if(IsKeyPressed(KEY_RIGHT_SHIFT))
    {
        add_mesh(handler, true);
    }
    if(IsKeyPressed(KEY_S))
    {
        if(h->nb_meshs != 0)
        load_into_file(handler);
    }

}

void load_into_file(handler *handler)
{
    if(h->fp == NULL){
        printf("\n\nError loading file\n\n");
        exit(1);
    }
    rewind(h->fp);

    fprintf(h->fp, "%d\n", h->nb_meshs);

    for (int j = 0; j < h->nb_meshs; j++)
    {
        fprintf(h->fp, "%d, %d\n", h->meshs[j].nb_p, h->meshs[j].closed);

        for (int i = 0; i < h->meshs[j].nb_p; i++)
        {
            fprintf(h->fp, "%d, %d\n", (int) h->meshs[j].points[i].x, (int) h->meshs[j].points[i].y);
        }
        
    }
    
    
}

void add_mesh(handler *handler, bool closed)
{
    if(!handler->editing) return;
    if(h->nb_points == 1) return editing_stop(handler);

    handler->nb_meshs++;
    handler->meshs = reallocarray(handler->meshs, sizeof(Mesh), h->nb_meshs*sizeof(Mesh));
    h->meshs[h->nb_meshs -1] = create_mesh(handler);
    h->meshs[h->nb_meshs -1].closed = closed;
    editing_stop(handler);
}

mesh create_mesh(handler *handler)
{
    mesh m;
    m.closed = false;
    m.nb_p = handler->nb_points;
    m.points = malloc(m.nb_p * sizeof(Vector2));
    for(int i = 0; i < m.nb_p; i++)
    {
        m.points[i] = handler->points[i];
    }
    return m;
}


void render(handler *handler)
{

    DrawText("S : sauvegarder map", 1000, 20, 20, BLACK);

    if(handler->nb_meshs != 0)
    DrawText("BACKSPACE : supprimer le dernier mesh", 1000, 40, 20, BLACK);

    if(handler->editing)
    {
        DrawText("EDITING", 20, 20, 40, RED);
        
        DrawText("ENTER : ajouter le mesh", 1000, 80-20*(h->nb_meshs == 0), 20, BLACK);
        DrawText("RSHIFT : ajouter le mesh fermé", 1000, 100-20*(h->nb_meshs == 0), 20, BLACK);
        DrawText("SPACE : arreter l'edition", 1000, 120-20*(h->nb_meshs == 0), 20, BLACK);
    }

    
    /*
    for (int i = 0; i < handler->nb_buttons; i++)
    {
        DrawRectangleRec(handler->buttons[i], RED);
    }
    */
    if(h->nb_points >= 2)
    for (int i = 1; i < h->nb_points; i++)
    {
        DrawLineV(h->points[i-1], h->points[i], RED);
    }

    for (int i = 0; i < h->nb_meshs; i++)
    {
        for (int j = 1; j < h->meshs[i].nb_p ; j++)
        {
            DrawLineV(h->meshs[i].points[j-1], h->meshs[i].points[j], GREEN);
        }
        if(h->meshs[i].closed)
        DrawLineV(h->meshs[i].points[0], h->meshs[i].points[h->meshs[i].nb_p -1], GREEN);
    }
    
    
    if(h->nb_points == 1) DrawCircleV(h->points[0], 5, RED);

}

void add_point(handler *handler, Vector2 pos)
{
    h->nb_points ++;
    if(!h->editing)
    {
        h->points = malloc(sizeof(Vector2));
        
        h->editing = true;
    }else
    {
        h->points = reallocarray(h->points, sizeof(Vector2), h->nb_points * sizeof(Vector2));
    }


    h->points[h->nb_points-1].x = pos.x;
    h->points[h->nb_points-1].y = pos.y;

    
}

void mesh_delete_last(handler *handler)
{
    if(handler->nb_meshs == 0) return;
    free(h->meshs[h->nb_meshs-1].points);
    h->nb_meshs --;
    h->meshs = reallocarray(h->meshs, sizeof(mesh), h->nb_meshs * sizeof(mesh));
}

void editing_stop(handler *handler)
{
    h->editing = false;
    free(h->points);
    h->points = NULL;
    h->nb_points = 0;
}

void handler_free(handler *handler)
{
    for (int i = 0; i < handler->nb_meshs; i++)
    {
        free(h->meshs[i].points);
    }
    
    free(handler->buttons);
    if(handler->nb_points > 0) free(handler->points);
    
    free(handler->meshs);
    fclose(h->fp);
}


