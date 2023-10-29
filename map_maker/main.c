
#include "raylib.h"
#include "handler.h"


int main(int argc, char **argv)
{
    if(argc <= 1)
    {
        printf("veuillez entrer un nom de map\n");
        return 0;
    }

    char buffer[50];
    sprintf(buffer, "../maps/%s", argv[1]);
    handler h = create_handler(buffer);

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    Vector2 screen = {1500, 1000};

    InitWindow(screen.x, screen.y, "Créateur de map");
    // SetTargetFPS(60);

    
   
    while (!WindowShouldClose())
    {
        tick(&h);

        BeginDrawing();
        ClearBackground(WHITE);

        render(&h);

        
        EndDrawing();
    }

    handler_free(&h);
    CloseWindow();

    return 0;
}

