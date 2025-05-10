#include "raylib.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Player{
    Vector2 rect;
    float size = 40;
    bool boolIsDown;
    bool isDeath = true;
};
struct LgGame{
    int fase=1;
    bool isMenu=true;
};

int spawX = 50;
int speedY = 12;
int telaX = 1200;
int telaY = 900;

Player player;
LgGame lgGame;
vector<Rectangle> grounds;

Vector2 Vector2Lerp(Vector2 start, Vector2 end, float alpha) {
    return (Vector2){
        start.x + alpha * (end.x - start.x),
        start.y = 900/2

        };
}

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

    for(const auto& ground : grounds){
        if(CheckCollisionPointRec(v1,ground)){
            cout << "ponta de cima base\n";
        }if(CheckCollisionPointRec(v2, ground)){
            cout << "ponta de baixo base\n";
        }if(CheckCollisionPointRec(v3,ground)){
            cout << "ponta da frente\n";
        }
        
        
        
        if(CheckCollisionPointRec(v1,ground) || CheckCollisionPointRec(v2,ground) || CheckCollisionPointRec(v3,ground)){
            if(ground.y > 0 || ground.y < telaY){
                player.rect.x = spawX;
                player.rect.y = 400;
                player.isDeath = true;
            }
        }
    }
}



void move(){
    //move player! 
    if(!player.isDeath){
        player.rect.x += 9;
    }
    
    if(player.boolIsDown && !player.isDeath){
        player.rect.y += speedY;
    }else if(!player.boolIsDown && !player.isDeath){
        player.rect.y -= speedY;
    }

    
    if(IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        player.isDeath = false;
        player.boolIsDown = false;
    }else{
        player.boolIsDown = true;
    }
    

    if(player.rect.y <= 0) player.rect.y=0;
    if(player.rect.y >= 900-player.size) player.rect.y=900-player.size;
    
}



int main(){
    
    
    if(lgGame.fase == 1){

        float x = 300;
        float width = 200;
        float passageHeight = 400;
        float topY[] = {
            350, 300, 250, 300, 350, // zigue-zague inicial
            400, 450, 400, 350, 300, // subida e descida
            400, 500, 600, 500, 450, // túnel superior
            400, 350, 400, 450, 300,
            250, 150, 50 , 0 ,  0,
            0,50,100,250,300,350,
            300,300,300,300,300,300,300,300,290,280,270,260,250,240
        };
        
        // Gerar paredes com base em topY
        for (int i = 0; i < sizeof(topY)/sizeof(float); i++) {
            if(i > 15 && i < 32) passageHeight-=3;
            if(i > 32) passageHeight-=5;
            
            grounds.push_back({x, 0, width, topY[i]});                           // parede de cima
            grounds.push_back({x, topY[i] + passageHeight, width, telaY - (topY[i] + passageHeight)});
            x += width;
        }
    }




    player = {{350,50}};
    

    const int maxTrailSize = 60;
    vector<Vector2> trail;

    InitWindow(telaX,telaY, "geomety vibes");
    SetTargetFPS(60);

    Camera2D camera = {0};
    camera.offset = {1200/3.0f,900/2};
    camera.zoom = 1.0f;

    while(!WindowShouldClose()){//loop main
        if(!lgGame.isMenu){

            cout << player.rect.x << "\n";
            float dt = GetFrameTime();
            move();
            
            trail.push_back(player.rect);
            if (trail.size() > maxTrailSize) {
                trail.erase(trail.begin()); // Remove a mais antiga
            }
            
            
            camera.target = Vector2Lerp(camera.target, {player.rect.x, player.rect.y},0.1f);
        }
        if(lgGame.isMenu){//MENU!!!!
            int boxWidth = 400;
            int boxHeight = 200;
            int boxX = (telaX - boxWidth) / 2;
            int boxY = (telaY - boxHeight) / 2;
            
            if(IsKeyDown(KEY_ENTER)){
                lgGame.isMenu = false;
            }

            BeginDrawing();
            ClearBackground(BLACK);

            DrawRectangle(boxX,boxY,boxWidth,boxHeight,LIGHTGRAY);
            
            

            DrawText("enter para jogar",telaX/2,telaY/2,20,RED);

            EndDrawing();
        }else if(!lgGame.isMenu){//desenho do jogo!!!!

            BeginDrawing();//block drawing!
            
            BeginMode2D(camera);
            ClearBackground(BLACK);
            
        for (size_t i = 0; i < trail.size(); i++) {
            float alpha = (float)i / trail.size(); // Fading effect
            Vector2 pos = trail[i];
            Vector2 size = {8, 29};
            Vector2 origin = {size.x / 2, size.y/2};
            DrawRectanglePro(Rectangle{pos.x, pos.y+20, size.x, size.y}, origin, 0, Fade(BLUE, alpha));
        }

        for(const auto &ground : grounds){
            if(ground.y > 0 || ground.y < telaY){
                DrawRectangleRec(ground, RED);
            }
        }
        
        drawPlayer(player);
        
        
        EndDrawing();
    }

    };
}