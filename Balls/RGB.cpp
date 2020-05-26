#include <TXLib.h>

using namespace std;

int x[3]={75, 50, 25};
int y[3]={75, 50, 25};
int R[3]={75, 50, 25};
int Vx[3]={1, 2, 5};
int Vy[3]={3, 4, 3};

void Circle(int x, int y, int R, int r, int g, int b){
    txSetColor(RGB(r, g ,b));
    txSetFillColor(RGB(r, g ,b));
    txCircle(x, y, R);
}

void CircleCor(int Grx0, int Gry0, int Grx, int Gry, int i){
        x[i]+=Vx[i];
        y[i]+=Vy[i];
        if(x[i]+R[i]>Grx){
            x[i]=Grx-(x[i]+R[i])%Grx-R[i];
            Vx[i]=-Vx[i];
        }
        else if(x[i]-R[i]<Grx0){
            x[i]=2*Grx0-x[i]+2*R[i];
            Vx[i]=-Vx[i];
        }

        if(y[i]+R[i]>Gry){
            y[i]=Gry-(y[i]+R[i])%Gry-R[i];
            Vy[i]=-Vy[i];
        }
        else if(y[i]-R[i]<Gry0){
            y[i]=2*Gry0-y[i]+2*R[i];
            Vy[i]=-Vy[i];
        }
}

int main(){
    int Grx0=10, Gry0=10, Grx=1190, Gry=590;
    int r[3]={127, 255, 148};
    int g[3]={255, 0, 0};
    int b[3]={0, 255, 211};

    cout << "Пожалуйста, введите границы (x0, y0, x, y)" << endl;
    //cin >> Grx0 >> Gry0 >> Grx >> Gry;                              //считывание границ
    txCreateWindow(1200, 600);
    txBegin();

    while(!GetAsyncKeyState(VK_ESCAPE)){
        for(int i=0; i<3; i++){
            CircleCor(Grx0, Gry0, Grx, Gry, i);
            Circle(x[i], y[i], R[i], r[i]--, g[i]--, b[i]++);
        }
        txSleep(1);
        txSetFillColor(RGB(0, 0, 0));
        //txClear();
        txSetColor(RGB(0, 255, 255));
        //txRectangle(Grx0, Gry0, Grx, Gry);
    }

    txEnd();
    return 0;
}
