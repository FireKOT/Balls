#include <TXLib.h>

using namespace std;

struct Border{
    int Grx0, Gry0, Grx, Gry;
};

struct Ball{
    int x, y, r;
    int R, G, B;
    int Vx, Vy;
    Border Gran;

    bool gol;
};

struct Player{
    int x, y;
    int S, H;

    int R, G, B;
};

void CircleCor(Ball *Circle);
void Push(Ball *ball, Player *player);
void Circle(Ball Circle);
void Rectangle(Ball Border);
void Bord(Player player);

int main(){
    txCreateWindow(940, 600);
    txBegin();

    Ball ball={470, 300, 50, rand()%256, rand()%256, rand()%256, 10, 8, 10, 10, 930, 590, 0};      //—читывание: x, y, r,  R, G, B,   Vx, Vy,   Grx0, Gry0, Grx, Gry
    Player Player1={30, 250, 20, 100, 0, 250, 154};
    Player Player2={890, 250, 20, 100, 0, 255, 127};

    while(!GetAsyncKeyState(VK_ESCAPE)){
        Rectangle(ball);

        Push(&ball, &Player1);
        Push(&ball, &Player2);
        CircleCor(&ball);

        Circle(ball);
        Bord(Player1);
        Bord(Player2);

        if(GetAsyncKeyState(0x57) && Player1.y-Player1.S/2-15>ball.Gran.Gry0) Player1.y-=15;
        if(GetAsyncKeyState(0x53) && Player1.y+Player1.H+Player1.S/2+15<ball.Gran.Gry) Player1.y+=15;
        if(GetAsyncKeyState(VK_UP) && Player2.y-Player2.S/2-15>ball.Gran.Gry0) Player2.y-=15;
        if(GetAsyncKeyState(VK_DOWN) && Player2.y+Player2.H+Player2.S/2+15<ball.Gran.Gry) Player2.y+=15;

        txSleep(10);

        if(ball.gol){
            ball.gol=0;

            ball.Vx+=rand()%6-3;
            ball.Vy+=rand()%6-3;

            txSleep(250);
        }

        ball.R=rand()%256;
        ball.G=rand()%256;
        ball.B=rand()%256;
    }

    txEnd();
    return 0;
}

void CircleCor(Ball *Circle){
    Circle->x+=Circle->Vx;
    Circle->y+=Circle->Vy;
    if(Circle->x+Circle->r>Circle->Gran.Grx){
        Circle->x=470;
        Circle->y=300;
        Circle->Vx*=-1;
        Circle->gol=1;
    }
    else if(Circle->x-Circle->r < Circle->Gran.Grx0){
        Circle->x=470;
        Circle->y=300;
        Circle->Vx*=-1;
        Circle->gol=1;
    }

    if(Circle->y+Circle->r>Circle->Gran.Gry){
        Circle->y=Circle->Gran.Gry-(Circle->y+Circle->r)%Circle->Gran.Gry-Circle->r;
        Circle->Vy*=-1;
    }
    else if(Circle->y-Circle->r<Circle->Gran.Gry0){
        Circle->y=2*Circle->Gran.Gry0-Circle->y+2*Circle->r;
        Circle->Vy*=-1;
    }
}

void Push(Ball *Circle, Player *player){
    if(Circle->x+Circle->r < player->x+player->S)
        if(Circle->x+Circle->r > player->x)
            if(Circle->y+Circle->r < player->y+player->H || Circle->y-Circle->r < player->y+player->H)
                if(Circle->y+Circle->r > player->y || Circle->y-Circle->r > player->y+player->H){
                    Circle->Vx*=-1;
                    Circle->x=player->x-Circle->r; //это магнитные платформы, по этому шары к ним липнут

                    player->R=Circle->R;
                    player->G=Circle->G;
                    player->B=Circle->B;
                }

    if(Circle->x-Circle->r < player->x+player->S)
        if(Circle->x-Circle->r > player->x)
            if(Circle->y+Circle->r < player->y+player->H || Circle->y-Circle->r < player->y+player->H)
                if(Circle->y+Circle->r > player->y || Circle->y-Circle->r > player->y+player->H){
                    Circle->Vx*=-1;
                    Circle->x=player->x+player->S+Circle->r;

                    player->R=Circle->R;
                    player->G=Circle->G;
                    player->B=Circle->B;
                }
}

void Circle(Ball Circle){
    txSetColor(RGB(Circle.R, Circle.G, Circle.B));
    txSetFillColor(RGB(Circle.R, Circle.G, Circle.B));
    txCircle(Circle.x, Circle.y, 50);
}

void Rectangle(Ball Border){
    txSetFillColor(RGB(0, 0, 0));
    txSetColor(RGB(0, 255, 255));
    txRectangle(Border.Gran.Grx0, Border.Gran.Gry0, Border.Gran.Grx, Border.Gran.Gry);
}

void Bord(Player player){
    txSetFillColor(RGB(player.R, player.G, player.B));
    txSetColor(RGB(player.R, player.G, player.B));

    txRectangle(player.x, player.y, player.x+player.S, player.y+player.H);
    txCircle(player.x+player.S/2, player.y, player.S/2);
    txCircle(player.x+player.S/2, player.y+player.H, player.S/2);
}
