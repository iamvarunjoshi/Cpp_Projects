#include <iostream>
#include<conio.h>
#include<windows.h>

using namespace std;
bool gameOver;
//dimension of map

const int width = 20;
const int height = 20;
int x,y,fruitX,fruitY,score;
enum eDirection{STOP=0, LEFT , RIGHT , UP , DOWN};
eDirection dir;
//coordinate array for tail.
int tailX[100], tailY[100];
int nTail;

void Setup()
{
    gameOver = false;
    //snake will be in the mid
    dir = STOP;
    x = width / 2;
    y = height / 2;
    //creates rand no b/w 0-20
    fruitX = rand() % width;
    fruitY = rand() % height;
}
void Draw()
{
    system("cls"); //system("clear");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "*";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input()
{    //if key's pressed.
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
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            //gameOver = true;
            break;
        }
    }

}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    
    for (int i = 1; i < nTail; i++)
    {   prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
      }
    //if (x > width || y > height || x < 0 || y < 0)
      // gameOver = true;
    if (x > width-1)
        x = 0;
    else if (x < 0)
        x = width-1;

    if (y > height-1)
        y = 0;
    else if (y < 0)
        y = height - 1;


    for (int i=0;i<nTail;i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
    if (x == fruitX && y == fruitY)
    {
        score=score+10;
        nTail++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}




int main()
{
    Setup();
    while (!gameOver)
    {
        Sleep(10);
        Draw();
        Input();
        Logic();
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
