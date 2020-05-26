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
};

void CircleCor(Ball *Circle);
void Push(Ball *one, Ball *two);
void Circle(Ball Circle);
void Rectangle(Ball Border);

int main(){
    Ball mas[3];
    mas[0]={85, 85, 75, 127, 255, 0, 6, 7, 10, 10, 930, 590};      //—читывание: x, y, r,   R, G, B,   Vx, Vy,   Grx0, Gry0, Grx, Gry
    mas[1]={250, 60, 50, 255, 0, 255, 9, 10, 10, 10, 930, 590};
    mas[2]={640, 35, 25, 0, 250, 154, 13, 8, 10, 10, 930, 590};

    txCreateWindow(940, 600);
    txBegin();

    while(!GetAsyncKeyState(VK_ESCAPE)){
        for(int i=0; i<3; i++){
            Rectangle(mas[i]);
        }

        for(int i=0; i<3; i++){
            for(int j=0; j<i; j++)
                Push(&mas[i], &mas[j]);

            CircleCor(&mas[i]);
            Circle(mas[i]);
        }
        txSleep(10);
    }

    txEnd();
    return 0;
}

void CircleCor(Ball *Circle){
    Circle->x+=Circle->Vx;
    Circle->y+=Circle->Vy;

    if(Circle->x+Circle->r>Circle->Gran.Grx){
        Circle->x=Circle->Gran.Grx-(Circle->x+Circle->r)%Circle->Gran.Grx-Circle->r;
        Circle->Vx*=-1;
    }
    else if(Circle->x-Circle->r<Circle->Gran.Grx0){
        Circle->x=2*Circle->Gran.Grx0-Circle->x+2*Circle->r;
        Circle->Vx*=-1;
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

void Push(Ball *one, Ball *two){
    int r=(two->x-one->x)*(two->x-one->x)+(two->y-one->y)*(two->y-one->y);

    if(r<=(one->r+two->r)*(one->r+two->r)){
        int tmp=one->Vx;
        one->Vx=two->Vx;
        two->Vx=tmp;
        tmp=one->Vy;
        one->Vy=two->Vy;
        two->Vy=tmp;
    }
}

void Circle(Ball Circle){
    txSetColor(RGB(0, 0 ,0));
    txSetFillColor(RGB(Circle.R, Circle.G,Circle.B));
    txCircle(Circle.x, Circle.y, Circle.r);
}

void Rectangle(Ball Border){
    txSetFillColor(RGB(0, 0, 0));
    txSetColor(RGB(0, 255, 255));
    txRectangle(Border.Gran.Grx0, Border.Gran.Gry0, Border.Gran.Grx, Border.Gran.Gry);
}
