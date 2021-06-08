#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#include <dos.h>
#include <dir.h>
using namespace std;
const int heigh = 20, width = 20;
int x, y, fruitx, fruity, score;
bool choosen;
enum direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
direction dir;
vector<char> game{'g', 'a', 'm', 'e', 'o', 'v', 'e', 'r'};
bool gameover;
int snakex[361];
int snakey[361];
int snake = 3;
void SetColor(int ForgC);
void gotoxy(int column, int line);
void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;

        case 's':
            dir = DOWN;
            break;
        case 'w':
            dir = UP;
            break;

        case ' ':
            gameover = true;
            break;
        }
    }
}
void logic()
{   

    int prevx = snakex[0] = x;
    int prevy = snakey[0] = y;
    int prev2x;
    int prev2y;
    for (int i = 1; i < snake; i++)
    {
        prev2x = snakex[i];
        prev2y = snakey[i];
        snakex[i] = prevx;
        snakey[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    switch (dir)
    {
    case UP:
        x--;
        break;

    case DOWN:
        x++;
        break;

    case RIGHT:
        y++;
        break;
    case LEFT:
        y--;
        break;
    default:
        break;
    }

    if (x <= 0 || x > width - 2 || y <=0 || y > heigh - 2)
        gameover = true;
       
    for (int i = 1; i < snake; i++)
    {
        if (snakex[i] == x && snakey[i] == y)
            gameover = true;
    }
  
    if (x == fruitx && y == fruity)
    {
        score += 10;
        fruitx = (rand() % (heigh - 1)) + 1;
        fruity = (rand() & (width - 1)) + 1;
        snake++;
    }
}
void setup()
{
    SetColor(25);
    gameover = false;
    dir = DOWN;
    x = width / 2;
    y = heigh / 2;
    snakex[0] = x;
    snakey[0] = y;
    for (int i = 1; i < snake; i++)
    {
        snakex[i] = x - i;
        snakey[i] = y;
    }

    fruitx = rand() % (width - 1);
    fruity = rand() % (heigh - 1);
    score = 0;
}
void draw()
{
    system("cls");

    for (int i = 0; i < width; i++)
    {
        gotoxy(i + 15, 0 + 5);
        cout << "+";
    }
    cout << endl;
    if (gameover)
    {
        int index = 0;
        for (int i = 1; i < heigh - 1; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0 || j == width - 1)
                {
                    gotoxy(j + 15, i + 5);
                    cout << "+";
                }

                if (j >= (width / 2 - 4) && (j < width / 2 + 4) && i == heigh / 2)
                {
                    gotoxy(j + 15, i + 5);
                    cout << game[index];
                    index++;
                }
            }
        }
    }
    else
    {   SetColor(10);
        for (int k = 1; k < snake; k++)
        {

            gotoxy(snakey[k] + 15, snakex[k] + 5);
            cout << "0";
        }
   SetColor(25);
        for (int i = 1; i < heigh - 1; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0 || j == width - 1)
                {
                    gotoxy(j + 15, i + 5);
                    cout << "+";
                }
                if (i == fruitx && j == fruity)
                {
                    gotoxy(j + 15, i + 5);
                    cout << "F";
                }
                else if (i == x && j == y)
                {
                    gotoxy(j + 15, i + 5);
                       SetColor(10);
                    cout << "$";
                       SetColor(25);
                }
            }
        }
    }

    for (int i = 0; i < width; i++)
    {
        gotoxy(i + 15, heigh - 1 + 5);
        cout << "+";
    }
    gotoxy(0 + 15, heigh + 5);
    cout << "SCORE:" << score << endl;
    Sleep(100);
}
int main()
{
    setup();
    draw();
    while (!gameover)
    {

        input();
        logic();
        draw();
    }
}
void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord);
}

void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
