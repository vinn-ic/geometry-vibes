#include "raylib.h"

#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <cmath>

using namespace std;

float spawPadrao = -300;
int velocidade = 9;
int speedY = 12;
class Player{
    public:

        Vector2 rect;
        float size = 40;
        
        int spawX = 50;
        
        bool boolIsDown = true;
        bool isDeath = true;
        Vector2 v1, v2, v3;
        Rectangle rectColission;

        int pont = 0;
        int best = 0;

    


       

    public:
        Player(Vector2 rect) {
            this->rect = rect;
            this->rectColission = {rect.x,rect.y};
            
        }

        void move(){
            //move player! 
            if(!isDeath){
                rect.x += velocidade;
                pont++;
                if(pont <= 0){
                pont = 0;
                }if(pont > best){
                best = pont;
                }
            }
            if(rect.x > 0.1f && fmod(rect.x, 1000.0f) < 1.0f){
                cout << "aumento de velocidadeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee" << "\n";
                velocidade += 3;
                speedY += 3;
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
    bool boolisGerar = true;
    


    int maior;//remover isso depois!!!!!!!!!!
    int menor=400;//remover isso depois!!!!!!!!!!

    vector<int> grounds = {300};
    
    vector<Rectangle> groundsForColission = {};

    
    LgGame(bool isMenu = true,Vector2 rect = {350,400}){
        this->isMenu = isMenu;
    }

    void colisao(Rectangle rectColission, Player& player){
        for(Rectangle ground : groundsForColission){
            if(CheckCollisionRecs(rectColission,ground)){
                
                player.rect.x = spawPadrao;
                player.rect.y = 300;
                velocidade = 9;
                boolisGerar = true;
                speedY = 12;
                player.isDeath = true;   
                grounds.clear();
                grounds.push_back(300);
                groundsForColission.clear();
            }
        }

    }

    void GerarParedes(Player& player, Vector2 camera){
        float xGTop = 0;
        float largura = 50; 
        int segGround = 350;

        int ultimoRanom = 400;
        int intervaloRandom;
        int numberRandom;

        

        if(player.rect.x > 0.1f && fmod(player.rect.x, 50.0f) < 1.0f || boolisGerar){//if de geração de paredes EU TO FICANDO LOKO!!
            
            cout << "gerando mais paredes!!" << "\n";
            //random grounds!!
            random_device rd;
            random_device rd2;
            
            
            mt19937 gen(rd());
            mt19937 gen2(rd2());
            
            
            uniform_int_distribution<> dist2(50,100);
            intervaloRandom = dist2(gen2);
            
            uniform_int_distribution<> dist(0,telaY); //numero que pode ser gerados!!
            
            
            numberRandom = dist(gen);
            ultimoRanom = numberRandom;
            
            
            
            if(ultimoRanom > maior){
                maior = ultimoRanom;
                cout << "maior: " << maior << "\n";
            }else if(ultimoRanom < menor){
                menor = ultimoRanom;
                cout << "menor: " << menor << "\n";
            }
            int ultimoElementoArray = grounds.back();
            if(ultimoElementoArray > numberRandom){
                for(int i = ultimoElementoArray+10; i > numberRandom;i-=10){
                    grounds.push_back(i);
                }
            }else if(ultimoElementoArray < numberRandom){
                for(int i = ultimoElementoArray+10; i < numberRandom;i+=10){
                    grounds.push_back(i);
                }
            }
                
                cout << "grounds>>"<< grounds.size() << "\n" << "groundsForColission>>" << groundsForColission.size()<< "\n";
                boolisGerar = false;
            }//fim do pior if da minha vida!!!!
                
            for(int ground : grounds){
                if(xGTop > camera.x){
                    float toppAltura = ground - (segGround/2);
                    float baseY = ground + (segGround/2);
                    float baseAltura = telaY - baseY;
                    

                    DrawRectangle(xGTop,0,largura,toppAltura,RED);//baixo
                    DrawRectangle(xGTop,baseY,largura,baseAltura,RED);//cima
                    Rectangle valoresbaixo = {xGTop,0,largura,toppAltura};
                    Rectangle valoresCima = {xGTop,baseY,largura,baseAltura};
                    
                    groundsForColission.push_back(valoresCima);
                    groundsForColission.push_back(valoresbaixo);

                
                    
                }

                xGTop += largura;

                    
        
            }
        

    }
    };

//vector<Rectangle> grounds;

Vector2 Vector2Lerp(Vector2 start, Vector2 end) {
    return (Vector2) { start.x + 0.1f * (end.x - start.x), 900/2 };
}


int bestPo = 0;
int main(){
    Player player({spawPadrao,400});
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
        camera.target = Vector2Lerp(camera.target, {player.rect.x, player.rect.y});
        
        lgGame.GerarParedes(player, camera.target);
        
           
        player.move();
        lgGame.colisao(player.rectColission, player);
        player.drawPlayer();
        
        DrawRectangle(player.rect.x-400,70,150,80,YELLOW);
        
        
        DrawText(TextFormat("%.1dPontuação", player.pont), player.rect.x - 350, 70, 20, BLUE);
        DrawText(TextFormat("%.1dMelhor pontuação",player.best), player.rect.x - 350, 100,20,BLUE);
        DrawText(TextFormat("%.1d", GetFPS()),player.rect.x-350,150,20,BLUE);


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