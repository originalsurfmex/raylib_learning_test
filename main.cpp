#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldVec() { return worldVec; }
    void setScreenVec(int winW, int winH);
    void tick(float dt);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenVec;
    Vector2 worldVec;
    Vector2 charOrigin{0.0, 0.0};
    float charScale{4.0};
    int charSprites{6};
    //right = 1, left = -1
    float rightleft{1.0f};
    //animation
    float runningTime{};
    int frame{};
    float speed{4.0f};
    const int maxFrames{charSprites};
    const float updateTime{1.0f / 16.0f};
};

void Character::setScreenVec(int winW, int winH)
{
    screenVec = {
        (float)winW / 2.0f - charScale * (0.5f * ((float)texture.width / (float)charSprites)),
        (float)winH / 2.0f - charScale * (0.5f * (float)texture.height)};
}

void Character::tick(float dt)
{
    dt = GetFrameTime();
    runningTime += dt;

    Vector2 direction{0.0, 0.0};

    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (IsKeyDown(KEY_LEFT_SHIFT))
        speed = 6.0;
    else
        speed = 3.0;

    if (Vector2Length(direction) != 0.0)
    {
        //normalize the vector so it has a length of 1.0
        //then scale it to the speed setting provided
        //then use subtract to move it in the negative direction
        //(so it scrolls opposite of direction keys)
        worldVec = Vector2Add(worldVec, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.0f ? rightleft = -1.0f : rightleft = 1.0f;
        texture = run;
    }
    else
        texture = idle;

    //DrawTextureEx(map, mapVec, 0.0, mapScale, WHITE);

    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if (frame > charSprites)
            frame = 0;
    }

    Rectangle charRecSrc{0.0f + ((float)frame * ((float)texture.width / (float)charSprites)), 0.0f, rightleft * (float)texture.width / (float)charSprites, (float)texture.height};
    Rectangle charRecDest{screenVec.x, screenVec.y, ((float)texture.width / (float)charSprites) * charScale, (float)texture.height * charScale};
    DrawTexturePro(texture, charRecSrc, charRecDest, charOrigin, 0.0f, WHITE);
}

int main()
{
    const int windowHW(384);

    /* -------------------------------- preamble -------------------------------- */
    InitWindow(windowHW, windowHW, "whut whuuuuuuuuuuuuuut");
    SetTargetFPS(60);
    float dt{};

    Texture2D map = LoadTexture("nature_tileset/Map24x24.png");
    // Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    const float mapScale = 4.0;
    Vector2 mapVec = {0.0f, 0.0f};

    Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knightRun = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = knightIdle;
    const int knightSprites{6};
    const float knightScale{4.0};
    const Vector2 knightOrigin{0.0f, 0.0f};
    Vector2 knightVec{
        // the 0.5f is so that we draw the center of the sprite
        (float)windowHW / 2.0f - knightScale * (0.5f * ((float)knightIdle.width / (float)knightSprites)),
        (float)windowHW / 2.0f - knightScale * (0.5f * (float)knightIdle.height)};

    //rightleft right = 1, left = -1
    //passing a negative value to the source triangle will flip the texture
    int rightleft{1};

    float runningTime{};
    int frame{};
    const float updateTime{1.0f / 18.0f};

    float speed{};

    /* ------------------------------- while loop ------------------------------- */
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        dt = GetFrameTime();
        runningTime += dt;

        Vector2 direction{0.0, 0.0};

        if (IsKeyDown(KEY_A))
            direction.x -= 1.0;
        if (IsKeyDown(KEY_D))
            direction.x += 1.0;
        if (IsKeyDown(KEY_W))
            direction.y -= 1.0;
        if (IsKeyDown(KEY_S))
            direction.y += 1.0;

        if (IsKeyDown(KEY_LEFT_SHIFT))
            speed = 6.0;
        else
            speed = 3.0;

        if (Vector2Length(direction) != 0.0)
        {
            //normalize the vector so it has a length of 1.0
            //then scale it to the speed setting provided
            //then use subtract to move it in the negative direction
            //(so it scrolls opposite of direction keys)
            mapVec = Vector2Subtract(mapVec, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.0f ? rightleft = -1.0f : rightleft = 1.0f;
            knight = knightRun;
        }
        else
            knight = knightIdle;

        DrawTextureEx(map, mapVec, 0.0, mapScale, WHITE);

        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.0f;
            if (frame > knightSprites)
                frame = 0;
        }

        Rectangle knightSrc{0.0f + ((float)frame * ((float)knightIdle.width / (float)knightSprites)), 0.0f, rightleft * (float)knightIdle.width / (float)knightSprites, (float)knightIdle.height};
        Rectangle knightDest{knightVec.x, knightVec.y, ((float)knightIdle.width / (float)knightSprites) * knightScale, (float)knightIdle.height * knightScale};
        DrawTexturePro(knight, knightSrc, knightDest, knightOrigin, 0.0f, WHITE);

        DrawText(TextFormat("X: %0.0f", -mapVec.x), 10, 10, 10, WHITE);
        DrawText(TextFormat("Y: %0.0f", -mapVec.y), 10, 20, 10, WHITE);
        EndDrawing();
    }
    CloseWindow();
}