
#include "raylib.h"
#include "particule.h"
#include "simulation.h"

int main(int argc, char **argv)
{
    if(argc <= 1)
    {
        printf("Veuillez entrer une map valide\n");
        return 0;
    }   
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    Vector2 screen = {1500, 1000};

    InitWindow(screen.x, screen.y, "Simulation de foule");
    SetTargetFPS(120);

    Simulation sim = sim_create();


    //destinations
    Vector2 dest2[1] = { {.x = 300, .y = 1050} };
    Vector2 dest4[1] = { {.x = 1200, .y = 1050} };
    Vector2 dest5[1] = { {.x = -50, .y = 750} };

    //--------- ajout des particules --------------
    for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++)
    {
        Vector2 pos = {700 + 31 * i, 500 + 31 * j};

        sim_add_particule(&sim, pos, 20 + rand()%10, dest5, 1);
        
    }
    //---------------------------------------------

    char buffer[50];
    sprintf(buffer, "maps/%s", argv[1]);
    sim_load_map(&sim, buffer);



    while (!WindowShouldClose())
    {
        sim_tick(&sim);

        BeginDrawing();
        ClearBackground(WHITE);

        sim_render(&sim);

        EndDrawing();
    }

    sim_free(&sim);

    CloseWindow();

    return 0;
}