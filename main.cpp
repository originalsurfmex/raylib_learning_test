#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

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
    Prop rock(Vector2{200.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png"));

    /* ------------------------------- while loop ------------------------------- */
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        float dt = GetFrameTime();

        mapVec = Vector2Scale(knight.getWorldPos(), -1.0f);
        DrawTextureEx(map, mapVec, 0.0, mapScale, WHITE);

        //rock.Render(knight.getWorldPos());
        knight.tick(dt);
        //rock.Render(knight.getWorldPos()); //if its placed here it glitches

        //map boundaries
        if (knight.getWorldPos().x < 0.0f ||
            knight.getWorldPos().y < 0.0f ||
            knight.getWorldPos().x + windowHW > map.width * mapScale ||
            knight.getWorldPos().y + windowHW > map.height * mapScale)
        {
            //this prevents leaving boundaries before the next frame is refreshed
            knight.undoMovement();
            //rock.undoMovement(); //trying to fix that glitch
        }

        DrawText(TextFormat("X: %0.0f", -mapVec.x), 10, 10, 10, WHITE);
        DrawText(TextFormat("Y: %0.0f", -mapVec.y), 10, 20, 10, WHITE);
        EndDrawing();
    }
    CloseWindow();
}