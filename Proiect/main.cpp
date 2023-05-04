#include <iostream>
#include <cstring>
#include <graphics.h>
#include <winbgim.h>
#include <conio.h>
#include <math.h>
#include <Mmsystem.h>
#include <windows.h>
using namespace std;
#define engleza -1
#define romana 1
#define muzica_off 0
#define muzica_on 1
#define rand_car1 1
#define rand_car2 2
#define rand_car3 3
#define loc_imposibil 2
#define loc_ocupat 1
#define loc_liber 0

struct pozitie
{
    int x;
    int y;
};

struct masina
{
    pozitie pozCurenta, pozAnterioara;
    int viteza, culoare;
    /*pozitie punctStart[100], punctFinish[100];
    int nrMutari;*/
};

struct tablaJoc
{
    masina car1, car2, car3; // max 3 playeri
    pozitie punctFinish1, punctFinish2;
    int limba = 1; // romana setata default
    int Muzica=0; // OFF setata default
    int nrJucatori=0;
    int rand;
    int matriceJoc[79][99];
} TJ;

bool verificaCoordonate(int &x, int &y, int culoare) //!! posibile modificari
{
    if(getpixel(x,y)== culoare)
    {
        if((x%10 <= 4) && (10+y/10*10-y <= 4) && (y/10%2 == 0) && (x/10%2 == 1)) // sfera dreapta sus
        {
            x=x/10*10;
            y=10+y/10*10;
            return 1;
        }
        else if ((x%10 <= 4) && (y%10 <= 4) && (y/10%2 == 1) && (x/10%2 == 1)) // sfera dreapta jos
        {
            x=x/10*10;
            y=y/10*10;
            return 1;
        }
        else if ((10+x/10*10-x <= 4) && (10+y/10*10-y <= 4) && (y/10%2 == 0) && (x/10%2 == 0)) // sfera stanga sus
        {
            x=10+x/10*10;
            y=10+y/10*10;
            return 1;
        }
        else if ((10+x/10*10-x <= 4) && (y%10 <= 4) && (y/10%2 == 1) && (x/10%2 == 0)) // sfera stanga jos
        {
            x=10+x/10*10;
            y=y/10*10;
            return 1;
        }
    }
    return 0;
}

bool verificaConditieFinish(masina car) // se verifica conditia de castig al jocului
{
    if((car.pozCurenta.x > TJ.punctFinish1.x) && (car.pozCurenta.x < TJ.punctFinish2.x))
    {
        if((car.pozAnterioara.y < TJ.punctFinish1.y) && (car.pozCurenta.y >= TJ.punctFinish1.y))
        {
            if(car.viteza!=0)
            {
                return 1;
            }
        }
    }
    return 0;
}

void initializareMatriceHarta() // se pun valorile pentru matrice
{
    int i, j;
    // a se verifica pe desen matrix_schematic
    for(i = 1; i <= 79; i+=2)
    {
        for(j = 1; j <= 99; j+=2)
        {
            if(i <= 5 )
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if( j <= 3 )
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if(j==93 || j==95 || j==97)
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if(i==77)
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 67 && i <= 75) && (j >= 59 && j <= 63))
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 7 && i <= 31) && (j >= 69 && j <= 91))
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 7 && i <= 25) && (j >= 57 && j <= 67))
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 7 && i <= 15) && (j >= 51 && j <= 55))
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 61 && i <= 75) && (j >= 69 && j <= 91))
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 63 && i <= 75) && (j >= 65 && j <= 69))
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 67 && i <= 75) && (j >= 65 && j <= 67))
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 53 && i <= 61) && (j >= 5 && j <= 21))
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 13 && i <= 45) && (j >= 11 && j <= 41))
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 39 && i <= 53) && (j >= 43 && j <= 81))
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 55 && i <= 69) && (j >= 33 && j <= 49))
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 47 && i <= 53) && (j >= 33 && j <= 41))
            {
                TJ.matriceJoc[i][j]=2;
            }
            else if((i >= 27 && i <= 37) && (j >= 43 && j <= 47))
            {
                TJ.matriceJoc[i][j]=2;
            }
        }
    }
    // dreapta sus
    TJ.matriceJoc[17][53]=2;
    TJ.matriceJoc[19][53]=2;
    TJ.matriceJoc[17][55]=2;
    TJ.matriceJoc[19][55]=2;
    TJ.matriceJoc[21][55]=2;
    TJ.matriceJoc[23][55]=2;
    TJ.matriceJoc[25][61]=2;
    TJ.matriceJoc[27][61]=2;
    TJ.matriceJoc[27][63]=2;
    TJ.matriceJoc[29][63]=2;
    TJ.matriceJoc[27][65]=2;
    TJ.matriceJoc[29][65]=2;
    TJ.matriceJoc[27][67]=2;
    TJ.matriceJoc[29][67]=2;
    TJ.matriceJoc[33][87]=2;
    TJ.matriceJoc[33][89]=2;
    TJ.matriceJoc[33][91]=2;
    TJ.matriceJoc[7][49]=2;

    // dreapta jos
    TJ.matriceJoc[65][67]=2;
    TJ.matriceJoc[55][91]=2;
    TJ.matriceJoc[57][91]=2;
    TJ.matriceJoc[59][91]=2;
    TJ.matriceJoc[59][89]=2;
    TJ.matriceJoc[65][63]=2;
    TJ.matriceJoc[63][63]=2;
    TJ.matriceJoc[65][61]=2;
    // stanga jos
    TJ.matriceJoc[75][5]=2;
    // stanga mijloc
    TJ.matriceJoc[63][5]=2;
    TJ.matriceJoc[55][23]=2;
    TJ.matriceJoc[55][25]=2;
    TJ.matriceJoc[57][23]=2;
    TJ.matriceJoc[57][25]=2;
    TJ.matriceJoc[59][23]=2;
    TJ.matriceJoc[59][25]=2;
    // mijloc stanga & jos
    TJ.matriceJoc[47][29]=2;
    TJ.matriceJoc[47][31]=2;
    TJ.matriceJoc[63][31]=2;
    TJ.matriceJoc[65][31]=2;
    TJ.matriceJoc[67][31]=2;
    TJ.matriceJoc[67][29]=2;
    TJ.matriceJoc[65][29]=2;
    TJ.matriceJoc[67][27]=2;
    // mijloc dreapta jos & mijloc
    TJ.matriceJoc[55][51]=2;
    TJ.matriceJoc[55][53]=2;
    TJ.matriceJoc[55][55]=2;
    TJ.matriceJoc[55][57]=2;
    TJ.matriceJoc[55][59]=2;
    TJ.matriceJoc[57][51]=2;
    TJ.matriceJoc[57][53]=2;
    TJ.matriceJoc[57][55]=2;
    TJ.matriceJoc[57][57]=2;
    TJ.matriceJoc[59][51]=2;
    TJ.matriceJoc[59][53]=2;
    TJ.matriceJoc[61][51]=2;
    TJ.matriceJoc[51][83]=2;
    TJ.matriceJoc[49][83]=2;
    TJ.matriceJoc[47][83]=2;
    TJ.matriceJoc[47][85]=2;
    TJ.matriceJoc[45][85]=2;
    TJ.matriceJoc[45][83]=2;
    TJ.matriceJoc[43][83]=2;
    // mijloc sus-dreapta
    TJ.matriceJoc[25][45]=2;
    TJ.matriceJoc[21][43]=2;
    TJ.matriceJoc[23][43]=2;
    TJ.matriceJoc[25][43]=2;
    TJ.matriceJoc[37][49]=2;
    TJ.matriceJoc[35][49]=2;
    TJ.matriceJoc[33][49]=2;
    TJ.matriceJoc[31][49]=2;
    TJ.matriceJoc[29][49]=2;
    TJ.matriceJoc[37][51]=2;
    TJ.matriceJoc[35][51]=2;
    TJ.matriceJoc[33][51]=2;
    TJ.matriceJoc[37][53]=2;
    TJ.matriceJoc[35][53]=2;
    TJ.matriceJoc[37][55]=2;
    TJ.matriceJoc[37][57]=2;
    // linie curba stanga jos
    TJ.matriceJoc[69][17]=2;
    TJ.matriceJoc[69][19]=2;
    TJ.matriceJoc[69][21]=2;
    TJ.matriceJoc[69][23]=2;
    TJ.matriceJoc[69][25]=2;
    TJ.matriceJoc[69][27]=2;
    TJ.matriceJoc[69][29]=2;
    TJ.matriceJoc[69][31]=2;
    // 0
    TJ.matriceJoc[7][49]=0;
    TJ.matriceJoc[35][91]=2;
    TJ.matriceJoc[41][83]=2;
    TJ.matriceJoc[43][85]=2;
    //!! DE VERIFICAT
    /*for(i=1;i<79;i+=2){
        for(j=1;j<=99;j+=2){
            cout<<TJ.matriceJoc[i][j]<<" ";
        }
        cout<<endl;
    }*/
}

void desenareMatrice(masina car) // desenarea posibilelor mutari
{
    //!! VERIFICARE IN "ZONE MUTARI.JPEG"
    int x, y;
    x=car.pozCurenta.x;
    y=car.pozCurenta.y;
    setcolor(car.culoare);
    if(car.viteza==0)
    {
        if(TJ.matriceJoc[y/10+2][x/10]==0)
        {
            for(int i=4; i>=1; i--)
            {
                circle(x, y+20, i);
            }
        }
        if(TJ.matriceJoc[y/10+2][x/10-2]==0)
        {
            for(int i=4; i>=1; i--)
            {
                circle(x-20, y+20, i);
            }
        }
        if(TJ.matriceJoc[y/10+2][x/10+2]==0)
        {
            for(int i=4; i>=1; i--)
            {
                circle(x+20, y+20, i);
            }
        }
    }
    else if((x>3 && x<11)&&(y>=13 && y<=45)) // PRIMA ZONA
    {
        if(car.viteza==1)
        {
            if(TJ.matriceJoc[y/10+2][x/10]==0) // 1m
            {
                for(int i=4; i>=1; i--) // 1s
                {
                    circle(x, y+20, i);
                }
            }
            if(TJ.matriceJoc[y/10+2][x/10-2]==0) // 1s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+20, i);
                }
            }
            if(TJ.matriceJoc[y/10+4][x/10+2]==0) // 1d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+40, i);
                }
            }
            if(TJ.matriceJoc[y/10+4][x/10]==0) // 2m
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+40, i);
                }
            }
            if(TJ.matriceJoc[y/10+4][x/10-2]==0) // 2s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+40, i);
                }
            }
            if(TJ.matriceJoc[y/10+4][x/10+2]==0) // 2d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+40, i);
                }
            }
        }
        else if(car.viteza==2)
        {
            if(TJ.matriceJoc[y/10+2][x/10]==0) // 1m
            {
                for(int i=4; i>=1; i--) // 1s
                {
                    circle(x, y+20, i);
                }
            }
            if(TJ.matriceJoc[y/10+2][x/10-2]==0) // 1s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+20, i);
                }
            }
            if(TJ.matriceJoc[y/10+4][x/10+2]==0) // 1d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+40, i);
                }
            }
            if(TJ.matriceJoc[y/10+4][x/10]==0) // 2m
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+40, i);
                }
            }
            if(TJ.matriceJoc[y/10+4][x/10-2]==0) // 2s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+40, i);
                }
            }
            if(TJ.matriceJoc[y/10+4][x/10+2]==0) // 2d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+40, i);
                }
            }
            if(TJ.matriceJoc[y/10+6][x/10]==0) // 3m
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+60, i);
                }
            }
            if(TJ.matriceJoc[y/10+6][x/10-2]==0) // 3s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+60, i);
                }
            }
            if(TJ.matriceJoc[y/10+6][x/10+2]==0) // 3d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+60, i);
                }
            }
        }
        else if(car.viteza==3)
        {
            if(TJ.matriceJoc[y/10+4][x/10]==0) // 2m
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+40, i);
                }
            }
            if(TJ.matriceJoc[y/10+4][x/10-2]==0) // 2s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+40, i);
                }
            }
            if(TJ.matriceJoc[y/10+4][x/10+2]==0) // 2d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+40, i);
                }
            }
            if(TJ.matriceJoc[y/10+6][x/10]==0) // 3m
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+60, i);
                }
            }
            if(TJ.matriceJoc[y/10+6][x/10-2]==0) // 3s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+60, i);
                }
            }
            if(TJ.matriceJoc[y/10+6][x/10+2]==0) // 3d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+60, i);
                }
            }
            if(TJ.matriceJoc[y/10+8][x/10]==0) // 4m
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+80, i);
                }
            }
            if(TJ.matriceJoc[y/10+8][x/10-2]==0) // 4s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+80, i);
                }
            }
            if(TJ.matriceJoc[y/10+8][x/10+2]==0) // 4d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+80, i);
                }
            }
        }
        else if(car.viteza==4)
        {
            if(TJ.matriceJoc[y/10+6][x/10]==0) // 3m
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+60, i);
                }
            }
            if(TJ.matriceJoc[y/10+6][x/10-2]==0) // 3s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+60, i);
                }
            }
            if(TJ.matriceJoc[y/10+6][x/10+2]==0) // 3d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+60, i);
                }
            }
            if(TJ.matriceJoc[y/10+8][x/10]==0) // 4m
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+80, i);
                }
            }
            if(TJ.matriceJoc[y/10+8][x/10-2]==0) // 4s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+80, i);
                }
            }
            if(TJ.matriceJoc[y/10+8][x/10+2]==0) // 4d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+80, i);
                }
            }
            if(TJ.matriceJoc[y/10+10][x/10]==0) // 5m
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+100, i);
                }
            }
            if(TJ.matriceJoc[y/10+10][x/10-2]==0) // 5s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+100, i);
                }
            }
            if(TJ.matriceJoc[y/10+10][x/10+2]==0) // 5d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+100, i);
                }
            }
        }
        else if(car.viteza==5)
        {
            if(TJ.matriceJoc[y/10+8][x/10]==0) // 4m
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+80, i);
                }
            }
            if(TJ.matriceJoc[y/10+8][x/10-2]==0) // 4s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+80, i);
                }
            }
            if(TJ.matriceJoc[y/10+8][x/10+2]==0) // 4d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+80, i);
                }
            }
            if(TJ.matriceJoc[y/10+10][x/10]==0) // 5m
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+100, i);
                }
            }
            if(TJ.matriceJoc[y/10+10][x/10-2]==0) // 5s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+100, i);
                }
            }
            if(TJ.matriceJoc[y/10+10][x/10+2]==0) // 5d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+100, i);
                }
            }
            if(TJ.matriceJoc[y/10+12][x/10]==0) // 6m
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+120, i);
                }
            }
            if(TJ.matriceJoc[y/10+12][x/10-2]==0) // 6s
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+120, i);
                }
            }
            if(TJ.matriceJoc[y/10+12][x/10+2]==0) // 6d
            {
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+120, i);
                }
            }
        }
    }
}

void stergereMatrice(masina car) // stergerea posibilelor mutari dupa prima mutare facuta
{
    //!! VERIFICARE IN "ZONE MUTARI.JPEG"
    int x, y;
    x=car.pozCurenta.x;
    y=car.pozCurenta.y;
    if(car.viteza==0)
    {
        if(TJ.matriceJoc[y/10+2][x/10]==0) // 1m
        {
            setcolor(WHITE);
            for(int i=4; i>=1; i--)
            {
                circle(x, y+20, i);
            }
            setcolor(7);
            line(x-4, y+20, x+4, y+20);
            line(x, y+16, x, y+24);
        }
        if(TJ.matriceJoc[y/10+2][x/10-2]==0) // 1s
        {
            setcolor(WHITE);
            for(int i=4; i>=1; i--)
            {
                circle(x-20, y+20, i);
            }
            setcolor(7);
            line(x-24, y+20, x-16, y+20);
            line(x-20, y+16, x-20, y+24);
        }
        if(TJ.matriceJoc[y/10+2][x/10+2]==0) //1d
        {
            setcolor(WHITE);
            for(int i=4; i>=1; i--)
            {
                circle(x+20, y+20, i);
            }
            setcolor(7);
            line(x+16, y+20, x+24, y+20);
            line(x+20, y+16, x+20, y+24);
        }
    }
    else if((x>3 && x<11)&&(y>=13 && y<=45)) // PRIMA ZONA
    {
        if(car.viteza==1)
        {
            if(TJ.matriceJoc[y/10+2][x/10]==0) // 1m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+20, i);
                }
                setcolor(7);
                line(x-4, y+20, x+4, y+20);
                line(x, y+16, x, y+24);
            }
            if(TJ.matriceJoc[y/10+2][x/10-2]==0) // 1s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+20, i);
                }
                setcolor(7);
                line(x-24, y+20, x-16, y+20);
                line(x-20, y+16, x-20, y+24);
            }
            if(TJ.matriceJoc[y/10+4][x/10+2]==0) // 1d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+40, i);
                }
                setcolor(7);
                line(x+16, y+20, x+24, y+20);
                line(x+20, y+16, x+20, y+24);
            }
            if(TJ.matriceJoc[y/10+4][x/10]==0) // 2m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+40, i);
                }
                setcolor(7);
                line(x-4, y+40, x+4, y+40);
                line(x, y+36, x, y+44);
            }
            if(TJ.matriceJoc[y/10+4][x/10-2]==0) // 2s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+40, i);
                }
                setcolor(7);
                line(x-24, y+40, x-16, y+40);
                line(x-20, y+36, x, y+44);
            }
            if(TJ.matriceJoc[y/10+4][x/10+2]==0) // 2d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+40, i);
                }
                setcolor(7);
                line(x+16, y+40, x+24, y+40);
                line(x+20, y+36, x+20, y+44);
            }
        }
        else if(car.viteza==2)
        {
            if(TJ.matriceJoc[y/10+2][x/10]==0) // 1m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--) // 1s
                {
                    circle(x, y+20, i);
                }
                setcolor(7);
                line(x-4, y+20, x+4, y+20);
                line(x, y+16, x, y+24);
            }
            if(TJ.matriceJoc[y/10+2][x/10-2]==0) // 1s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+20, i);
                }
                setcolor(7);
                line(x-24, y+20, x-16, y+20);
                line(x-20, y+16, x, y+24);
            }
            if(TJ.matriceJoc[y/10+4][x/10+2]==0) // 1d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+40, i);
                }
                setcolor(7);
                line(x+16, y+20, x+24, y+20);
                line(x+20, y+16, x+20, y+24);
            }
            if(TJ.matriceJoc[y/10+4][x/10]==0) // 2m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+40, i);
                }
                setcolor(7);
                line(x-4, y+40, x+4, y+40);
                line(x, y+36, x, y+44);
            }
            if(TJ.matriceJoc[y/10+4][x/10-2]==0) // 2s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+40, i);
                }
                setcolor(7);
                line(x-24, y+40, x-16, y+40);
                line(x-20, y+36, x, y+44);
            }
            if(TJ.matriceJoc[y/10+4][x/10+2]==0) // 2d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+40, i);
                }
                setcolor(7);
                line(x+16, y+40, x+24, y+40);
                line(x+20, y+36, x+20, y+44);
            }
            if(TJ.matriceJoc[y/10+6][x/10]==0) // 3m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+60, i);
                }
                setcolor(7);
                line(x-4, y+60, x+4, y+60);
                line(x, y+56, x, y+64);
            }
            if(TJ.matriceJoc[y/10+6][x/10-2]==0) // 3s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+60, i);
                }
                setcolor(7);
                line(x-24, y+60, x-16, y+60);
                line(x-20, y+56, x, y+64);
            }
            if(TJ.matriceJoc[y/10+6][x/10+2]==0) // 3d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+60, i);
                }
                setcolor(7);
                line(x+16, y+60, x+24, y+60);
                line(x+20, y+56, x+20, y+64);
            }
        }
        else if(car.viteza==3)
        {
            if(TJ.matriceJoc[y/10+4][x/10]==0) // 2m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+40, i);
                }
                setcolor(7);
                line(x-4, y+40, x+4, y+40);
                line(x, y+36, x, y+44);
            }
            if(TJ.matriceJoc[y/10+4][x/10-2]==0) // 2s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+40, i);
                }
                setcolor(7);
                line(x-24, y+40, x-16, y+40);
                line(x-20, y+36, x, y+44);
            }
            if(TJ.matriceJoc[y/10+4][x/10+2]==0) // 2d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+40, i);
                }
                setcolor(7);
                line(x+16, y+40, x+24, y+40);
                line(x+20, y+36, x+20, y+44);
            }
            if(TJ.matriceJoc[y/10+6][x/10]==0) // 3m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+60, i);
                }
                setcolor(7);
                line(x-4, y+60, x+4, y+60);
                line(x, y+56, x, y+64);
            }
            if(TJ.matriceJoc[y/10+6][x/10-2]==0) // 3s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+60, i);
                }
                setcolor(7);
                line(x-24, y+60, x-16, y+60);
                line(x-20, y+56, x, y+64);
            }
            if(TJ.matriceJoc[y/10+6][x/10+2]==0) // 3d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+60, i);
                }
                setcolor(7);
                line(x+16, y+60, x+24, y+60);
                line(x+20, y+56, x+20, y+64);
            }
            if(TJ.matriceJoc[y/10+8][x/10]==0) // 4m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+80, i);
                }
                setcolor(7);
                line(x-4, y+80, x+4, y+80);
                line(x, y+76, x, y+84);
            }
            if(TJ.matriceJoc[y/10+8][x/10-2]==0) // 4s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+80, i);
                }
                setcolor(7);
                line(x-24, y+80, x-16, y+80);
                line(x-20, y+76, x, y+84);
            }
            if(TJ.matriceJoc[y/10+8][x/10+2]==0) // 4d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+80, i);
                }
                setcolor(7);
                line(x+16, y+80, x+24, y+80);
                line(x+20, y+76, x+20, y+84);
            }
        }
        else if(car.viteza==4)
        {
            if(TJ.matriceJoc[y/10+6][x/10]==0) // 3m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+60, i);
                }
                setcolor(7);
                line(x-4, y+60, x+4, y+60);
                line(x, y+56, x, y+64);
            }
            if(TJ.matriceJoc[y/10+6][x/10-2]==0) // 3s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+60, i);
                }
                setcolor(7);
                line(x-24, y+60, x-16, y+60);
                line(x-20, y+56, x, y+64);
            }
            if(TJ.matriceJoc[y/10+6][x/10+2]==0) // 3d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+60, i);
                }
                setcolor(7);
                line(x+16, y+60, x+24, y+60);
                line(x+20, y+56, x+20, y+64);
            }
            if(TJ.matriceJoc[y/10+8][x/10]==0) // 4m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+80, i);
                }
                setcolor(7);
                line(x-4, y+80, x+4, y+80);
                line(x, y+76, x, y+84);
            }
            if(TJ.matriceJoc[y/10+8][x/10-2]==0) // 4s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+80, i);
                }
                setcolor(7);
                line(x-24, y+80, x-16, y+80);
                line(x-20, y+76, x, y+84);
            }
            if(TJ.matriceJoc[y/10+8][x/10+2]==0) // 4d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+80, i);
                }
                setcolor(7);
                line(x+16, y+80, x+24, y+80);
                line(x+20, y+76, x+20, y+84);
            }
            if(TJ.matriceJoc[y/10+10][x/10]==0) // 5m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+100, i);
                }
                setcolor(7);
                line(x-4, y+100, x+4, y+10);
                line(x, y+96, x, y+104);
            }
            if(TJ.matriceJoc[y/10+10][x/10-2]==0) // 5s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+100, i);
                }
                setcolor(7);
                line(x-24, y+100, x-16, y+100);
                line(x-20, y+96, x, y+104);
            }
            if(TJ.matriceJoc[y/10+10][x/10+2]==0) // 5d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+100, i);
                }
                setcolor(7);
                line(x+16, y+100, x+24, y+100);
                line(x+20, y+96, x+20, y+104);
            }
        }
        else if(car.viteza==5)
        {
            if(TJ.matriceJoc[y/10+8][x/10]==0) // 4m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+80, i);
                }
                setcolor(7);
                line(x-4, y+80, x+4, y+80);
                line(x, y+76, x, y+84);
            }
            if(TJ.matriceJoc[y/10+8][x/10-2]==0) // 4s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+80, i);
                }
                setcolor(7);
                line(x-24, y+80, x-16, y+80);
                line(x-20, y+76, x, y+84);
            }
            if(TJ.matriceJoc[y/10+8][x/10+2]==0) // 4d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+80, i);
                }
                setcolor(7);
                line(x+16, y+80, x+24, y+80);
                line(x+20, y+76, x+20, y+84);
            }
            if(TJ.matriceJoc[y/10+10][x/10]==0) // 5m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+100, i);
                }
                setcolor(7);
                line(x-4, y+100, x+4, y+10);
                line(x, y+96, x, y+104);
            }
            if(TJ.matriceJoc[y/10+10][x/10-2]==0) // 5s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+100, i);
                }
                setcolor(7);
                line(x-24, y+100, x-16, y+100);
                line(x-20, y+96, x, y+104);
            }
            if(TJ.matriceJoc[y/10+10][x/10+2]==0) // 5d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+100, i);
                }
                setcolor(7);
                line(x+16, y+100, x+24, y+100);
                line(x+20, y+96, x+20, y+104);
            }
            if(TJ.matriceJoc[y/10+12][x/10]==0) // 6m
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x, y+120, i);
                }
                setcolor(7);
                line(x-4, y+120, x+4, y+120);
                line(x, y+116, x, y+124);
            }
            if(TJ.matriceJoc[y/10+12][x/10-2]==0) // 6s
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x-20, y+120, i);
                }
                setcolor(7);
                line(x-24, y+120, x-16, y+120);
                line(x-20, y+116, x, y+124);
            }
            if(TJ.matriceJoc[y/10+12][x/10+2]==0) // 6d
            {
                setcolor(WHITE);
                for(int i=4; i>=1; i--)
                {
                    circle(x+20, y+120, i);
                }
                setcolor(7);
                line(x+16, y+120, x+24, y+120);
                line(x+20, y+116, x+20, y+124);
            }
        }
    }
}

void foaiePatratele() // desenare caiet patratele
{
    int i;
    setcolor(7); // LIGHT Gray
    for (i=10; i<=990; i+=20) // verticala
    {
        line(i,10,i,790);
    }
    for(i=10; i<=790; i+=20) // orizontala
    {
        line(10,i,990,i);
    }
}

void genereazaHarta() // se genereaza harta
{
    setbkcolor(WHITE);
    clearviewport();
    foaiePatratele();
    int x[4],y[4];
    double puty,putx,t;
    setcolor(RED);
    line(30,130,110,130); // linie start & finish
    setcolor(8);
    // LINIE EXTERIOR
    // linia 1
    line(30, 130, 30, 470);
    // curba 1
    x[0]=30;
    y[0]=470;
    x[1]=30;
    y[1]=530;
    x[2]=30;
    y[2]=530;
    x[3]=110;
    y[3]=530;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // linia 2
    line(110, 530, 170, 530);
    // curba 2
    x[0]=170;
    y[0]=530;
    x[1]=290;
    y[1]=530;
    x[2]=290;
    y[2]=610;
    x[3]=170;
    y[3]=610;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // linia 3
    line(170, 610, 110, 610);
    // curba 3
    x[0]=110;
    y[0]=610;
    x[1]=10;
    y[1]=610;
    x[2]=10;
    y[2]=770;
    x[3]=110;
    y[3]=770;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // linia 4
    line(110, 770, 570, 770);
    // curba 4
    x[0]=570;
    y[0]=770;
    x[1]=580;
    y[1]=610;
    x[2]=620;
    y[2]=610;
    x[3]=750;
    y[3]=610;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // linia 5
    line(750, 610, 810, 610);
    // curba 5
    x[0]=810;
    y[0]=610;
    x[1]=930;
    y[1]=610;
    x[2]=930;
    y[2]=450;
    x[3]=930;
    y[3]=390;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // curba 6
    x[0]=930;
    y[0]=390;
    x[1]=930;
    y[1]=330;
    x[2]=810;
    y[2]=310;
    x[3]=750;
    y[3]=310;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // linia 6
    line(750, 310, 690, 310);
    // curba 7
    x[0]=690;
    y[0]=310;
    x[1]=570;
    y[1]=310;
    x[2]=490;
    y[2]=170;
    x[3]=490;
    y[3]=50;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // linia 7
    line(490, 50, 110, 50);
    // curba 8
    x[0]=30;
    y[0]=130;
    x[1]=30;
    y[1]=50;
    x[2]=30;
    y[2]=50;
    x[3]=110;
    y[3]=50;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // LINIE INTERIOR
    // linia 1
    line(110, 130, 110, 450);
    // curba 1
    x[0]=110;
    y[0]=450;
    x[1]=130;
    y[1]=450;
    x[2]=330;
    y[2]=440;
    x[3]=330;
    y[3]=530;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // linia 2
    line(110, 130, 110, 450);
    // curba 2
    x[0]=110;
    y[0]=450;
    x[1]=130;
    y[1]=450;
    x[2]=330;
    y[2]=440;
    x[3]=330;
    y[3]=530;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // linia 3
    line(330, 530, 330, 570);
    // curba 3
    x[0]=330;
    y[0]=570;
    x[1]=330;
    y[1]=650;
    x[2]=230;
    y[2]=690;
    x[3]=170;
    y[3]=690;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // linia 4
    line(170, 690, 490, 690);
    // curba 4
    x[0]=490;
    y[0]=690;
    x[1]=490;
    y[1]=590;
    x[2]=630;
    y[2]=530;
    x[3]=690;
    y[3]=530;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // linia 5
    line(690, 530, 810, 530);
    // curba 5
    x[0]=810;
    y[0]=390;
    x[1]=890;
    y[1]=410;
    x[2]=850;
    y[2]=510;
    x[3]=810;
    y[3]=530;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // linia 6
    line(810, 390, 630, 390);
    // curba 6
    x[0]=630;
    y[0]=390;
    x[1]=550;
    y[1]=390;
    x[2]=410;
    y[2]=210;
    x[3]=410;
    y[3]=130;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    // curba 7
    x[0]=410;
    y[0]=130;
    x[1]=390;
    y[1]=110;
    x[2]=130;
    y[2]=110;
    x[3]=110;
    y[3]=130;
    for(t=0.0; t<=1.0; t=t+0.001)
    {
        putx=pow(1-t,3)*x[0]+ 3*t*pow(1-t,2)*x[1]+ 3*t*t*pow(1-t,1)*x[2]+ pow(t,3)*x[3];
        puty=pow(1-t,3)*y[0]+ 3*t*pow(1-t,2)*y[1]+ 3*t*t*pow(1-t,1)*y[2]+ pow(t,3)*y[3];
        putpixel(putx,puty,8);
    }
    TJ.punctFinish1.x=30;
    TJ.punctFinish1.y=130;
    TJ.punctFinish2.x=110;
    TJ.punctFinish2.y=130;
    TJ.car1.viteza=0;
    TJ.car2.viteza=0;
    TJ.car3.viteza=0;
    if (TJ.nrJucatori==1)
    {
        TJ.car1.pozCurenta.x=70;
        TJ.car1.pozCurenta.y=130;
        TJ.car1.pozAnterioara.x=70;
        TJ.car1.pozAnterioara.y=130;
        setcolor(TJ.car1.culoare);
        circle(TJ.car1.pozCurenta.x,TJ.car1.pozCurenta.y,5);
    }
    else if(TJ.nrJucatori==2)
    {
        TJ.car1.pozCurenta.x=50;
        TJ.car1.pozCurenta.y=130;
        TJ.car1.pozAnterioara.x=50;
        TJ.car1.pozAnterioara.y=130;
        setcolor(TJ.car1.culoare);
        circle(TJ.car1.pozCurenta.x,TJ.car1.pozCurenta.y,5);
        TJ.car2.pozCurenta.x=90;
        TJ.car2.pozCurenta.y=130;
        TJ.car2.pozAnterioara.x=90;
        TJ.car2.pozAnterioara.y=130;
        setcolor(TJ.car2.culoare);
        circle(TJ.car2.pozCurenta.x,TJ.car2.pozCurenta.y,5);
    }
    else if(TJ.nrJucatori==3)
    {
        TJ.car1.pozCurenta.x=50;
        TJ.car1.pozCurenta.y=130;
        TJ.car1.pozAnterioara.x=50;
        TJ.car1.pozAnterioara.y=130;
        setcolor(TJ.car1.culoare);
        circle(TJ.car1.pozCurenta.x,TJ.car1.pozCurenta.y,5);
        TJ.car2.pozCurenta.x=70;
        TJ.car2.pozCurenta.y=130;
        TJ.car2.pozAnterioara.x=70;
        TJ.car2.pozAnterioara.y=130;
        setcolor(TJ.car2.culoare);
        circle(TJ.car2.pozCurenta.x,TJ.car2.pozCurenta.y,5);
        TJ.car3.pozCurenta.x=90;
        TJ.car3.pozCurenta.y=130;
        TJ.car3.pozAnterioara.x=90;
        TJ.car3.pozAnterioara.y=130;
        setcolor(TJ.car3.culoare);
        circle(TJ.car3.pozCurenta.x,TJ.car3.pozCurenta.y,5);
    }
    //!!VERIFICARE
    /*for(int i=1;i<=79;i+=2){
     for(int j=1; j<=99; j+=2){
        if(TJ.matriceJoc[i][j]==0){
            for(int d=0; d<=3;d++)
            {
                setcolor(RED);
                circle(j*10, i*10, d);
            }
        }
        else if(TJ.matriceJoc[i][j]==2)
        {
            for(int d=0; d<=3;d++)
            {
                setcolor(GREEN);
                circle(j*10, i*10, d);
            }
        }
        }
        cout<<endl;
    }*/
    rectangle(0,0,getmaxx(),getmaxy());
    setfillstyle(SOLID_FILL,8);
    floodfill(10,10,8);
    floodfill(130,150,8);
}

void urmaMasina(masina car) // se traseaza linii
{
    int pozX, pozY;
    int ok=0;
    desenareMatrice(car);
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            pozX=mousex();
            pozY=mousey();
            if(verificaCoordonate(pozX, pozY, car.culoare)!=0)
            {
                stergereMatrice(car);
                car.pozAnterioara.x=car.pozCurenta.x;
                car.pozAnterioara.y=car.pozCurenta.y;
                car.pozCurenta.x=pozX;
                car.pozCurenta.y=pozY;
                setcolor(car.culoare);
                line(car.pozAnterioara.x, car.pozAnterioara.y, car.pozCurenta.x, car.pozCurenta.y);
                // schimbareViteza(car);
                TJ.matriceJoc[car.pozAnterioara.y/10][car.pozAnterioara.x/10]=0;
                TJ.matriceJoc[car.pozCurenta.y/10][car.pozCurenta.x/10]=1;
                ok=1;
            }
        }
    }
    while(ok==0);
}

void startJOC() // aici se joaca
{
    initializareMatriceHarta();
    genereazaHarta();
    TJ.rand=1;
    do
    {
        if(TJ.nrJucatori==1)
        {
            if(verificaConditieFinish(TJ.car1)==1)
            {
                cout<<"Câștigătorul este jucătorul numărul 1!";
            }
            else // se ruleaza jocul in continuare
            {
                urmaMasina(TJ.car1);
            }
        }
        else if(TJ.nrJucatori==2)
        {
            if(verificaConditieFinish(TJ.car1)==1)
            {
                cout<<"Câștigătorul este jucătorul numărul 1!";
            }
            else if(verificaConditieFinish(TJ.car2)==1)
            {
                cout<<"Câștigătorul este jucătorul numărul 2!";
            }
            else // se ruleaza jocul in continuare
            {
                if(TJ.rand==1)
                {
                    urmaMasina(TJ.car1);
                    TJ.rand++;
                }
                else
                {
                    urmaMasina(TJ.car2);
                    TJ.rand--;
                }
            }
        }
        else if(TJ.nrJucatori==3)
        {
            if(verificaConditieFinish(TJ.car1)==1)
            {
                cout<<"Câștigătorul este jucătorul numărul 1!";
            }
            else if(verificaConditieFinish(TJ.car2)==1)
            {
                cout<<"Câștigătorul este jucătorul numărul 2!";
            }
            else if(verificaConditieFinish(TJ.car3)==1)
            {
                cout<<"Câștigătorul este jucătorul numărul 3!";
            }
            else // se ruleaza jocul in continuare
            {
                if(TJ.rand==1)
                {
                    urmaMasina(TJ.car1);
                    TJ.rand++;
                }
                else if(TJ.rand==2)
                {
                    urmaMasina(TJ.car2);
                    TJ.rand++;
                }
                else if(TJ.rand==3)
                {
                    urmaMasina(TJ.car3);
                    TJ.rand=1;
                }
            }
        }
    }
    while((verificaConditieFinish(TJ.car1)!=1) || (verificaConditieFinish(TJ.car2)!=1) || (verificaConditieFinish(TJ.car3)!=1));
    if((verificaConditieFinish(TJ.car1)==1))
    {
        cout<<"Câștigătorul este jucătorul numărul 1!";
    }
    else if((verificaConditieFinish(TJ.car2)==1))
    {
        cout<<"Câștigătorul este jucătorul numărul 2!";
    }
    else if((verificaConditieFinish(TJ.car3)==1))
    {
        cout<<"Câștigătorul este jucătorul numărul 3!";
    }
    getch();
}

void iesire() // iesire din joc
{
    clearviewport();
    closegraph();
}

void pressedPLAY() // se selecteaza numarul de jucatori
{
    if(TJ.limba==1)
    {
        setbkcolor(WHITE);
        cleardevice();
        int midX = getmaxx()/2;
        int midY = getmaxy()/2;
        int ok=0,x,y;
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,10);
        readimagefile("playmenu.jpg",0,0,1000,800);
        setcolor(BLACK);
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
        int width1=textwidth("1");
        int height1=textheight("1");
        outtextxy(midX-width1/2,midY-height1,"1");
        int width2=textwidth("2");
        int height2=textheight("2");
        outtextxy(midX-width2/2,midY+height2,"2");
        int width3=textwidth("3");
        int height3=textheight("3");
        outtextxy(midX-width3/2,midY+3*height3,"3");
        int widthI=textwidth("Inapoi");
        int heightI=textheight("Inapoi");
        outtextxy(midX-widthI/2,midY+5*heightI,"Inapoi");
        int widthT=textwidth("Selecteaza numarul de jucatori");
        int heightT=textheight("Selecteaza numarul de jucători");
        outtextxy(midX-widthT/2,midY-heightT*4,"Selecteaza numarul de jucatori");
        while(ok==0)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                if(x>=midX-width1/2 && x<=midX+width1/2 && y>=midY-height1 && y<=midY+height1/2-height1/3) //1
                {
                    TJ.nrJucatori=1;
                    TJ.car1.culoare=BLUE;
                    startJOC();
                    ok=1;
                    pressedPLAY();
                }
                else if(x>=midX-width2/2 && x<=midX+width2/2 && y>=midY+height2 && y<=midY+height2*2) // 2
                {
                    TJ.nrJucatori=2;
                    TJ.car1.culoare=BLUE;
                    TJ.car2.culoare=GREEN;
                    startJOC();
                    ok=1;
                    pressedPLAY();
                }
                else if(x>=midX-width3/2 && x<=midX+width3/2 && y>=midY+3*height3 && y<=midY+4*height3) // 3
                {
                    TJ.nrJucatori=3;
                    TJ.car1.culoare=BLUE;
                    TJ.car2.culoare=GREEN;
                    TJ.car3.culoare=MAGENTA;
                    startJOC();
                    ok=1;
                    pressedPLAY();
                }
                else if(x>=midX-widthI/2 && x<=midX+widthI/2 && y>=midY+5*heightI && y<=midY+6*heightI) // inapoi
                {
                    ok=1;
                }
            }
        }
    }
    else
    {
        setbkcolor(WHITE);
        cleardevice();
        int midX = getmaxx()/2;
        int midY = getmaxy()/2;
        int ok=0,x,y;
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,10);
        readimagefile("playmenu.jpg",0,0,1000,800);
        setcolor(BLACK);
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
        int width1=textwidth("1");
        int height1=textheight("1");
        outtextxy(midX-width1/2,midY-height1,"1");
        int width2=textwidth("2");
        int height2=textheight("2");
        outtextxy(midX-width2/2,midY+height2,"2");
        int width3=textwidth("3");
        int height3=textheight("3");
        outtextxy(midX-width3/2,midY+3*height3,"3");
        int widthI=textwidth("Back");
        int heightI=textheight("Back");
        outtextxy(midX-widthI/2,midY+5*heightI,"Back");
        int widthT=textwidth("Select number of players");
        int heightT=textheight("Select number of players");
        outtextxy(midX-widthT/2,midY-heightT*4,"Select number of players");
        while(ok==0)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                if(x>=midX-width1/2 && x<=midX+width1/2 && y>=midY-height1 && y<=midY+height1/2-height1/3) //1
                {
                    TJ.nrJucatori=1;
                    TJ.car1.culoare=BLUE;
                    startJOC();
                    ok=1;
                    pressedPLAY();
                }
                else if(x>=midX-width2/2 && x<=midX+width2/2 && y>=midY+height2 && y<=midY+height2*2) // 2
                {
                    TJ.nrJucatori=2;
                    TJ.car1.culoare=BLUE;
                    TJ.car2.culoare=GREEN;
                    startJOC();
                    ok=1;
                    pressedPLAY();
                }
                else if(x>=midX-width3/2 && x<=midX+width3/2 && y>=midY+3*height3 && y<=midY+4*height3) // 3
                {
                    TJ.nrJucatori=3;
                    TJ.car1.culoare=BLUE;
                    TJ.car2.culoare=GREEN;
                    TJ.car3.culoare=MAGENTA;
                    startJOC();
                    ok=1;
                    pressedPLAY();
                }
                else if(x>=midX-widthI/2 && x<=midX+widthI/2 && y>=midY+5*heightI && y<=midY+6*heightI) // inapoi
                {
                    ok=1;
                }
            }
        }
    }
}

void setari() // meniu setari limba / muzica
{
    if(TJ.limba==1)
    {
        int ok=0, x, y;
        clearviewport();
        setbkcolor(WHITE);
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
        int midX = getmaxx()/2;
        int midY = getmaxy()/2;
        int widthR=textwidth("Romana");
        int heightR=textheight("Romana");
        outtextxy(midX-widthR/2,midY-heightR,"Romana");
        int widthE=textwidth("Engleza");
        int heightE=textheight("Engleza");
        outtextxy(midX-widthE/2,midY+heightE,"Engleza");
        int widthI=textwidth("Inapoi");
        int heightI=textheight("Inapoi");
        outtextxy(midX-widthI/2,midY+3*heightI,"Inapoi");
        int widthM=textwidth("Muzica ON/OFF");
        int heightM=textheight("Muzica ON/OFF");
        outtextxy(midX-widthM/2,midY-3*heightM,"Muzica ON/OFF");
        while(ok==0)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                if(x>=midX-widthM/2 && x<=midX+widthM/2 && y>=midY-3*heightM && y<=midY+heightM-3*heightM) // muzica
                {
                    if(TJ.Muzica==0)
                    {
                        PlaySound("The Legend of Xanadu - Silent Tower.wav", NULL, SND_LOOP | SND_ASYNC);
                        TJ.Muzica=1; // ON
                    }
                    else
                    {
                        PlaySound(NULL, 0, 0);
                        TJ.Muzica=0; // OFF
                    }
                }
                else if(x>=midX-widthR/2 && x<=midX+widthR/2 && y>=midY-heightR && y<=midY+heightR/2-heightR/3) // romana
                {
                    ok=1;
                    TJ.limba=1;
                }
                else if(x>=midX-widthE/2 && x<=midX+widthE/2 && y>=midY+heightE && y<=midY+heightE*2) // engleza
                {
                    ok=1;
                    TJ.limba=-1;
                }
                else if(x>=midX-widthI/2 && x<=midX+widthI/2 && y>=midY+3*heightI && y<=midY+4*heightI) // inapoi
                {
                    ok=1;
                }
            }
        }
    }
    else
    {
        int ok=0, x, y;
        clearviewport();
        setbkcolor(WHITE);
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
        int midX = getmaxx()/2;
        int midY = getmaxy()/2;
        int widthR=textwidth("Romanian");
        int heightR=textheight("Romanian");
        outtextxy(midX-widthR/2,midY-heightR,"Romanian");
        int widthE=textwidth("English");
        int heightE=textheight("English");
        outtextxy(midX-widthE/2,midY+heightE,"English");
        int widthI=textwidth("Back");
        int heightI=textheight("Back");
        outtextxy(midX-widthI/2,midY+3*heightI,"Back");
        int widthM=textwidth("Music ON/OFF");
        int heightM=textheight("Music ON/OFF");
        outtextxy(midX-widthM/2,midY-3*heightM,"Music ON/OFF");
        while(ok==0)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                if(x>=midX-widthM/2 && x<=midX+widthM/2 && y>=midY-3*heightM && y<=midY+heightM-3*heightM) // muzica
                {
                    if(TJ.Muzica==0)
                    {
                        PlaySound("The Legend of Xanadu - Silent Tower.wav", NULL, SND_LOOP | SND_ASYNC);
                        TJ.Muzica=1; // ON
                    }
                    else
                    {
                        PlaySound(NULL, 0, 0);
                        TJ.Muzica=0; // OFF
                    }
                }
                else if(x>=midX-widthR/2 && x<=midX+widthR/2 && y>=midY-heightR && y<=midY+heightR/2-heightR/3) // romana
                {
                    ok=1;
                    TJ.limba=1;
                }
                else if(x>=midX-widthE/2 && x<=midX+widthE/2 && y>=midY+heightE && y<=midY+heightE*2) // engleza
                {
                    ok=1;
                    TJ.limba=-1;
                }
                else if(x>=midX-widthI/2 && x<=midX+widthI/2 && y>=midY+3*heightI && y<=midY+4*heightI) // inapoi
                {
                    ok=1;
                }
            }
        }
    }
}

void meniuPrincipal() // meniul jocului
{
    if(TJ.limba==1)
    {
        setbkcolor(WHITE);
        cleardevice();
        setcolor(RED);
        int midX = getmaxx()/2;
        int midY = getmaxy()/2;
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,10);
        int width1 = textwidth("Raliu Auto");
        int height1 = textheight("Raliu Auto");
        readimagefile("meniu_principal.jpg",0,0,1000,800);
        outtextxy(midX-width1/2,midY-height1*2.5,"Raliu Auto");
        setcolor(3);
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
        int width2=textwidth("Joaca");
        int height2=textheight("Joaca");
        outtextxy(midX-width2/2,midY-height2,"Joaca");
        int width3=textwidth("Setari");
        int height3=textheight("Setari");
        outtextxy(midX-width3/2,midY+height3,"Setari");
        int width4=textwidth("Iesire");
        int height4=textheight("Iesire");
        outtextxy(midX-width4/2,midY+3*height4,"Iesire");
        int ok=0,x,y;
        while(ok==0)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                if(x>=midX-width2/2 && x<=midX+width2/2 && y>=midY-height2 && y<=midY+height2/2-height2/3) //play
                {
                    pressedPLAY();
                    ok=1;
                    meniuPrincipal();
                }
                else if(x>=midX-width3/2 && x<=midX+width3/2 && y>=midY+height3 && y<=midY+height3*2) // setari
                {
                    setari();
                    ok=1;
                    meniuPrincipal();
                }
                else if(x>=midX-width4/2 && x<=midX+width4/2 && y>=midY+3*height4 && y<=midY+4*height4) //iesire
                {
                    iesire();
                    ok=1;
                    return;
                }
            }
        }
    }
    else
    {
        setbkcolor(WHITE);
        cleardevice();
        setcolor(RED);
        int midX = getmaxx()/2;
        int midY = getmaxy()/2;
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,10);
        int width1 = textwidth("Raliu Auto");
        int height1 = textheight("Raliu Auto");
        readimagefile("meniu_principal.jpg",0,0,1000,800);
        outtextxy(midX-width1/2,midY-height1*2.5,"Raliu Auto");
        setcolor(3);
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,7);
        int width2=textwidth("Play");
        int height2=textheight("Play");
        outtextxy(midX-width2/2,midY-height2,"Play");
        int width3=textwidth("Settings");
        int height3=textheight("Settings");
        outtextxy(midX-width3/2,midY+height3,"Settings");
        int width4=textwidth("Exit");
        int height4=textheight("Exit");
        outtextxy(midX-width4/2,midY+3*height4,"Exit");
        int ok=0,x,y;
        while(ok==0)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                if(x>=midX-width2/2 && x<=midX+width2/2 && y>=midY-height2 && y<=midY+height2/2-height2/3) //play
                {
                    pressedPLAY();
                    ok=1;
                    meniuPrincipal();
                }
                else if(x>=midX-width3/2 && x<=midX+width3/2 && y>=midY+height3 && y<=midY+height3*2) // setari
                {
                    setari();
                    ok=1;
                    meniuPrincipal();
                }
                else if(x>=midX-width4/2 && x<=midX+width4/2 && y>=midY+3*height4 && y<=midY+4*height4) //iesire
                {
                    iesire();
                    ok=1;
                    return;
                }
            }
        }
    }
}

int main()
{
    initwindow(1000,800,"Raliu Auto");
    meniuPrincipal();
    return 0;
}

