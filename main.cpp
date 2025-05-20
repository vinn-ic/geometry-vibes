#include "raylib.h"

#include <vector>
#include <string>
#include <iostream>
#include <random>

using namespace std;


class Player{
    public:

        Vector2 rect;
        float size = 40;
        int speedY = 12;
        int spawX = 50;
        bool boolIsDown = true;
        bool isDeath = true;
        Vector2 v1, v2, v3;
        Rectangle rectColission;


       

    public:
        Player(Vector2 rect) {
            this->rect = rect;
            this->rectColission = {rect.x,rect.y};
            
        }

        void move(){
            //move player! 
            if(!isDeath){
                rect.x += 9;
            }
            
            if(boolIsDown && !isDeath){
                rect.y += speedY;
            }else if(!boolIsDown && !isDeath){
                rect.y -= speedY;
            }

            
            if(IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                isDeath = false;
                boolIsDown = false;
            }else{
                boolIsDown = true;
            }
            

            if(rect.y <= 0) rect.y=0;
            if(rect.y >= 900-size) rect.y=900-size;

            rectColission = {rect.x,rect.y};
        }

        void drawPlayer() {

            DrawRectangle(rect.x,rect.y,(rect.x-5)-rect.x+size,(rect.y-rect.y+size),(Color){ 0, 0, 0, 0 });

            
            if (boolIsDown) {
                // Triângulo apontando para baixo
                v1 = {rect.x-5, rect.y}; // ponta de cima
                v2 = {rect.x-10 , rect.y + size};
                v3 = {rect.x + size, ((v1.y + v2.y)/2)+10};
            } else {
                v1 = {rect.x-10, rect.y}; // ponta de cima
                v2 = {rect.x , rect.y + size};
                v3 = {rect.x + size, ((v1.y + v2.y)/2)-10};
            }
            DrawTriangle(v1, v2, v3, BLUE);             
                
                
                
            }
};
class LgGame{
public:
    bool isMenu;
    int telaX = 1200;
    int telaY = 900;

    int maior;//remover isso depois!!!!!!!!!!
    int menor=400;//remover isso depois!!!!!!!!!!

    vector<int> grounds = {300};
    
    vector<Rectangle> groundsForColissionTop = {};
    vector<Rectangle> groundsForColissionDown = {};

    
    LgGame(bool isMenu = true,Vector2 rect = {350,400}){
        this->isMenu = isMenu;
    }

    void colisao(Rectangle rectColission, Player& player){
        for(Rectangle ground : groundsForColissionTop){
            if(CheckCollisionRecs(rectColission,ground)){
                
                player.rect.x = 50;
                player.rect.y = 300;
                player.isDeath = true;   
                grounds.clear();
                groundsForColissionDown.clear();
                groundsForColissionTop.clear();
            }
        }
        for(Rectangle ground : groundsForColissionDown){
            if(CheckCollisionRecs(rectColission,ground)){
                
                player.rect.x = 50;
                player.rect.y = 300;
                player.isDeath = true;
                grounds.clear();
                groundsForColissionDown.clear();
                groundsForColissionTop.clear();
            }
        }

    }

    void GerarParedes(Vector2 Player){
        float xGTop = 550;
        float largura = 50; 
        int segGround = 350;

        int ultimoRanom = 400;
        int intervaloRandom;
        int numberRandom;

        
        //random grounds!!
        random_device rd;
        random_device rd2;
        

        mt19937 gen(rd());
        mt19937 gen2(rd2());

        
        uniform_int_distribution<> dist2(50,100);
        intervaloRandom = dist2(gen2);

        uniform_int_distribution<> dist(ultimoRanom-intervaloRandom,ultimoRanom+intervaloRandom); //numero que pode ser gerados!!


        numberRandom = dist(gen);
        ultimoRanom = numberRandom;
        cout << ultimoRanom << "\n";


        if(ultimoRanom > maior){
            maior = ultimoRanom;
            cout << "maior: " << maior << "\n";
        }else if(ultimoRanom < menor){
            menor = ultimoRanom;
            cout << "menor: " << menor << "\n";
        }

        grounds.push_back(numberRandom);

       

        for(int ground : grounds){
     
            float toppAltura = ground - (segGround/2);
            float baseY = ground + (segGround/2);
            float baseAltura = telaY - baseY;


            DrawRectangle(xGTop,0,largura,toppAltura,RED);//baixo
            DrawRectangle(xGTop,baseY,largura,baseAltura,RED);//cima
            Rectangle valoresbaixo = {xGTop,0,largura,toppAltura};
            Rectangle valoresCima = {xGTop,baseY,largura,baseAltura};

            groundsForColissionTop.push_back(valoresCima);
            groundsForColissionDown.push_back(valoresbaixo);

            xGTop +=largura; 
     
        }
        

    }
};







//vector<Rectangle> grounds;

Vector2 Vector2Lerp(Vector2 start, Vector2 end, float alpha) {
    start.y = 900/2; //telaY/2!
    return (Vector2) { start.x + alpha * (end.x - start.x), 900/2 };
}



int main(){
    Player player({50,400});
    //350,50
    LgGame lgGame(true);

    bool isGerour = true;

    const int maxTrailSize = 60;
    vector<Vector2> trail;

    InitWindow(lgGame.telaX,lgGame.telaY, "geomety vibes");
    SetTargetFPS(60);

    Camera2D camera = {0};
    camera.offset = {1200/3.0f,900/2};
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {//main loop!!
        BeginDrawing();
        ClearBackground(BLACK);

    if (lgGame.isMenu) {
        int boxWidth = 400;
        int boxHeight = 200;
        int boxX = (lgGame.telaX - boxWidth) / 2;
        int boxY = (lgGame.telaY - boxHeight) / 2;

        if (IsKeyPressed(KEY_ENTER)) {
            lgGame.isMenu = false;
        }

        DrawRectangle(boxX, boxY, boxWidth, boxHeight, LIGHTGRAY);
        DrawText("enter para jogar", lgGame.telaX / 2, lgGame.telaY / 2, 20, RED);
    } else {
        BeginMode2D(camera);

        for (size_t i = 0; i < trail.size(); i++) {
            float alpha = (float)i / trail.size();
            Vector2 pos = trail[i];
            Vector2 size = {8, 29};
            Vector2 origin = {size.x / 2, size.y / 2};
            DrawRectanglePro(Rectangle{pos.x, pos.y + 20, size.x, size.y}, origin, 0, Fade(BLUE, alpha));
        }
        

        trail.push_back(player.rect);
        if (trail.size() > maxTrailSize) {
            trail.erase(trail.begin());
        }

        camera.target = Vector2Lerp(camera.target, {player.rect.x, player.rect.y}, 0.1f);
        
        lgGame.GerarParedes(player.rect);
           
        player.move();
        lgGame.colisao(player.rectColission, player);
        player.drawPlayer();
        
        DrawRectangle(player.rect.x-400,70,150,80,YELLOW);
        DrawText(TextFormat("%.1fM", player.rect.x - 50), player.rect.x - 350, 70, 20, BLUE);

        EndMode2D();
    }

    EndDrawing();
}

CloseWindow(); // Libera recursos

cout << "maior: " << lgGame.maior << "\n";
cout << "menor: " << lgGame.menor << "\n";

return 0;
}


//g++ main.cpp -o main.exe -I"D:/raylib/src" -L"D:/raylib/build/raylib" -lraylib -lopengl32 -lgdi32 -lwinmm