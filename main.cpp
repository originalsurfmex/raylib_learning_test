#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    const int windowHW(384);

    /* -------------------------------- preamble -------------------------------- */
    InitWindow(windowHW, windowHW, "whut whuuuuuuuuuuuuuut");
    SetTargetFPS(60);

    Texture2D map = LoadTexture("nature_tileset/Map24x24.png");
    const float mapScale = 4.0;
    Vector2 mapVec = {0.0f, 0.0f};

    Character knight(windowHW, windowHW);
    //knight.setScreenVec(windowHW, windowHW);

    /* ------------------------------- while loop ------------------------------- */
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        float dt = GetFrameTime();

        mapVec = Vector2Scale(knight.getWorldVec(), -1.0f);

        DrawTextureEx(map, mapVec, 0.0, mapScale, WHITE);
        knight.tick(dt);

        //map boundaries
        if (knight.getWorldVec().x < 0.0f || knight.getWorldVec().y < 0.0f ||
            knight.getWorldVec().x + windowHW > map.width * mapScale ||
            knight.getWorldVec().y + windowHW > map.height * mapScale)
        {
            //this prevents leaving boundaries before the next frame is refreshed
            knight.undoMovement();
        }

        DrawText(TextFormat("X: %0.0f", -mapVec.x), 10, 10, 10, WHITE);
        DrawText(TextFormat("Y: %0.0f", -mapVec.y), 10, 20, 10, WHITE);
        EndDrawing();
    }
    CloseWindow();
}