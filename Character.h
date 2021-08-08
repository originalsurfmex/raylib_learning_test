#include "raylib.h"
class Character
{
public:
    Character(int screenW, int screenH);
    Vector2 getWorldVec() { return worldVec; }
    //void setScreenVec(int winW, int winH);
    void tick(float dt);
    void undoMovement(); // map boundaries
    //int screenW{};
    //int screenH{};

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenVec{}; //where to locate the character on the screen
    Vector2 worldVec{}; //used to get the map vector
    Vector2 worldVecLastFrame{}; // for map boundary limits
    Vector2 charOrigin{}; //to draw character with DrawTexturePro
    float charScale{4.0};
    int charSprites{6};
    //right = 1, left = -1
    float rightleft{1.0f};
    //animation
    float runningTime{};
    int frame{};
    float speed{4.0f};
    float width{};
    float height{};
    const int maxFrames{charSprites};
    const float updateTime{1.0f / 16.0f};
};

