#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <algorithm>

int main()
{
    /* -------------------------------------------------------------------------- */
    /*                                  preamble                                  */
    /* -------------------------------------------------------------------------- */
    const int windowHW(384);
    InitWindow(windowHW, windowHW, "whut whuuuuuuuuuuuuuut");
    SetTargetFPS(60);

    Texture2D map = LoadTexture("nature_tileset/Map24x24.png");
    const float mapScale = 4.0;
    Vector2 mapVec = {0.0f, 0.0f};

    Character knight(windowHW, windowHW);
    Enemy goon(Vector2{550, 450},
               LoadTexture("characters/goblin_idle_spritesheet.png"),
               LoadTexture("characters/goblin_run_spritesheet.png"));
    goon.setSpeed(1.2f);
    Enemy slime(Vector2{20.f, 20.f},
                LoadTexture("characters/slime_idle_spritesheet.png"),
                LoadTexture("characters/slime_run_spritesheet.png"));
    slime.setSpeed(0.5f);

    Prop props[2]{
        Prop{Vector2{200.0f, 400.0f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{300.0f, 600.0f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy *enemies[]{&goon, &slime};
    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    /* -------------------------------------------------------------------------- */
    /*                                 game loop                                  */
    /* -------------------------------------------------------------------------- */
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        float dt = GetFrameTime();

        /* ------------------------------ draw the map ------------------------------ */
        mapVec = Vector2Scale(knight.getWorldPos(), -1.0f);
        DrawTextureEx(map, mapVec, 0.0, mapScale, WHITE);

        /* ------------------------------- draw props ------------------------------- */
        for (auto prop : props)
        {
            prop.setTarget(&knight);
            prop.Render();
            //DrawRectangleLinesEx(prop.getCollisionRectangle(), 1, BLUE); //test collision rectangle
            if (CheckCollisionRecs(prop.getCollisionRectangle(), knight.getCollisionRectangle()))
                knight.undoMovement();
        }

        /* ------------------------- start main knight tick ------------------------- */
        if (knight.getDamage() > 0)
        {
            knight.tick(dt);
        }
        else
        {
            knight.setAlive(false);
            DrawText("KILT!", windowHW / 2 - 55, windowHW / 2, 40, RED);
            EndDrawing();
            continue;
        }

        /* ------------------------- get them enemies going ------------------------- */
        int enemy_iter{0};
        for (auto enemy : enemies)
        {
            if (enemy->getDamage() > 0)
            {
                enemy->tick(dt);
                //DrawRectangleLinesEx(enemy->getCollisionRectangle(), 2, WHITE); //test collision rectangle
                enemy_iter++;
                DrawText(TextFormat("GOON: %0.0f", enemy->getDamage()), 10, 30 + (10 * (enemy_iter + 1)), 10, RED);
            }
            else
            {
                enemy->setAlive(false);
                enemy_iter--;
            }

            /* ------------------------ character-goon-collisions ----------------------- */
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
                CheckCollisionRecs(knight.getSwordCollision(), enemy->getCollisionRectangle()))
                enemy->setDamage(1.f);

            if (CheckCollisionRecs(knight.getCollisionRectangle(), enemy->getCollisionRectangle()))
            {
                knight.setDamage(5.f);
            }
        }

        /* ------------------------------ baddie count ------------------------------ */
        int baddies = 0;
        for (int i = 0; i < 2; i++)
        {
            baddies = 0;
            baddies += enemies[i]->getAlive();
        }
        if (baddies <= 0)
        {
            ClearBackground(BLACK);
            DrawText("RWAR!", windowHW / 2 - 55, windowHW / 2, 40, RED);
        }

        //DrawRectangleLinesEx(knight.getCollisionRectangle(), 2, RED); //test collision rectangle
        //DrawRectangleLinesEx(knight.getSwordCollision(), 3, VIOLET);
        //rock.Render(knight.getWorldPos()); // fix the 'depth fighting'

        /* ----------------------------- map boundaries ----------------------------- */
        if (knight.getWorldPos().x < 0.0f ||
            knight.getWorldPos().y < 0.0f ||
            knight.getWorldPos().x + windowHW > map.width * mapScale ||
            knight.getWorldPos().y + windowHW > map.height * mapScale)
        {
            //this prevents leaving boundaries before the next frame is refreshed
            knight.undoMovement();
        }

        //DrawText(TextFormat("X: %0.0f", -mapVec.x), 10, 10, 10, WHITE);
        DrawText(TextFormat("X: %0.0f", knight.getWorldPos().x), 10, 10, 10, WHITE);
        //DrawText(TextFormat("Y: %0.0f", -mapVec.y), 10, 20, 10, WHITE);
        DrawText(TextFormat("Y: %0.0f", knight.getWorldPos().y), 10, 20, 10, WHITE);
        DrawText(TextFormat("PLAYER: %0.0f", knight.getDamage()), 10, 30, 10, BLUE);
        //DrawText(TextFormat("ENEMIES: %i", enemy_iter), 10, 40, 10, GREEN);
        EndDrawing();
    }
    CloseWindow();
}