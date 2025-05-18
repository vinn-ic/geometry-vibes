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

       

    public:
        Player(Vector2 rect) {
            this->rect = rect;
            
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
        }

        void drawPlayer() {
            Vector2 v1, v2, v3;
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
                
                
                //if(CheckCollisionPointRec(v1,ground) || CheckCollisionPointRec(v2,ground) || CheckCollisionPointRec(v3,ground)){
                    //if(ground.y > 0 || ground.y < telaY){
                        //rect.x = spawX;
                        //rect.y = 400;
                        //isDeath = true;
                    //}
                //}
            }
};
class LgGame : public Player{
public:
    bool isMenu;
    int telaX = 1200;
    int telaY = 900;
    vector<int> grounds = {300};
    
    LgGame(bool isMenu = true,Vector2 rect = {350,400}) : Player(rect){
        this->isMenu = isMenu;
    }

    void GerarParedes(Vector2 Player){
        int xGTop = 550;
        int largura = 50; 
        int segGround = 250;

        int ultimoRanom = 400;

        
        //random grounds!!
        random_device rd;
        random_device rd2;

        mt19937 gen(rd());
        mt19937 gen2(rd2());

        uniform_int_distribution<> dist(ultimoRanom-50,ultimoRanom+50);//numero que pode ser gerados!!
        uniform_int_distribution<> dist2(200,300);


        int numberRan = dist(gen);
        ultimoRanom = numberRan;
        cout << ultimoRanom << "\n";

        grounds.push_back(numberRan);

        segGround = dist2(gen2);

        for(int ground : grounds){
     
            int toppAltura = ground - (segGround/2);
            int baseY = ground + (segGround/2);
            int baseAltura = telaY - baseY;


            DrawRectangle(xGTop,0,largura,toppAltura,RED);//deixar a largura maior!!!!!!!! ver se isso esta funcionando
            DrawRectangle(xGTop,baseY,largura,baseAltura,YELLOW);
            xGTop +=largura; 
     
        }
        

    }
};







//vector<Rectangle> grounds;

Vector2 Vector2Lerp(Vector2 start, Vector2 end, float alpha) {
    return (Vector2){
    start.x + alpha * (end.x - start.x),
    start.y = 900/2//telaY/2!
    };
}



int main(){
    Player player({350,400});
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
        player.drawPlayer();
        

        DrawText(TextFormat("%.1fM", player.rect.x - 50), player.rect.x - 350, 70, 20, BLUE);

        EndMode2D();
    }

    EndDrawing();
}

CloseWindow(); // Libera recursos
return 0;
}


//g++ main.cpp -o main.exe -I"D:/raylib/src" -L"D:/raylib/build/raylib" -lraylib -lopengl32 -lgdi32 -lwinmmmian
