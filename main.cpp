#include "raylib.h"

#include <vector>
#include <string>

struct Player{
    Vector2 rect;
    float size = 40;
    bool boolIsDown;
};


int speedY = 12;
Player player;

void drawPlayer(Player& player) {
    Vector2 v1, v2, v3;
    if (player.boolIsDown) {
        // Triângulo apontando para baixo
        v1 = {player.rect.x-5, player.rect.y}; // ponta de cima
        v2 = {player.rect.x-10 , player.rect.y + player.size};
        v3 = {player.rect.x + player.size, ((v1.y + v2.y)/2)+10};
    } else {
        v1 = {player.rect.x-10, player.rect.y}; // ponta de cima
        v2 = {player.rect.x , player.rect.y + player.size};
        v3 = {player.rect.x + player.size, ((v1.y + v2.y)/2)-10};
    }
    DrawTriangle(v1, v2, v3, BLUE);
}

void move(){
    //move player!  
    if(player.boolIsDown){
        player.rect.y += speedY;
    }else if(!player.boolIsDown){
        player.rect.y -= speedY;
    }

    
    if(IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        player.boolIsDown = false;
    }else{
        player.boolIsDown = true;
    }

    if(player.rect.y <= 0) player.rect.y=0;
    if(player.rect.y >= 900-player.size) player.rect.y=900-player.size;

}

int main(){
    player = {{350,50}};

    InitWindow(1200,900, "geomety vibes");
    SetTargetFPS(60);

    while(!WindowShouldClose()){//loop main
        float dt = GetFrameTime();
        move();
        
        BeginDrawing();//block drawing!
        ClearBackground(BLACK);
        drawPlayer(player);

        EndDrawing();

    };
}