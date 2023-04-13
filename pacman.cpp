#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
using namespace std;
int pacmanx = 9; // x position of pacman
int pacmany = 31; // y position of pacman
int score = 0;
int ghostX = 19; // x position of ghost
int ghostY = 25; // y position of ghost

int g1x = 16;
int g1y = 30;
int flag1 = 0;

int lives = 3;

int g2x = 1;
int g2y = 29;
int flag2 = 0;

int g3x = 1;
int g3y = 60;

int g4x = 15;
int g4y = 20;

int previousItem = ' ';

fstream file;
void movepacmanleft();
void movepacmanright();
void movepacmanup();
void movepacmandown();
void loadmaze();
void storemaze();
bool gameover();
int calculatescore();
int ghostDirection();
void gotoxy(int y, int x);
void printscore();
void ghostvertical();
int moveGhost1();
void moveGhost2();
void moveGhost3();
int moveGhost4();
void winner();

char maze[24][71] = {{"#####################################################################"},
                     {"||.. .....................................................  ......  ||"},
                     {"||.. %%%%%%%%%%%%%%%% ...... ...     %%%%%%%%%%%%%%  |%|..   %%%%   ||"},
                     {"||..        |%|   |%|     |%|...     |%|        |%|  |%|..    |%|   ||"},
                     {"||..        |%|   |%|     |%|...     |%|        |%|  |%|..    |%|   ||"},
                     {"||..        %%%%%%%%  . . |%|...     %%%%%%%%%%%%%%     ..   %%%%.  ||"},
                     {"||..        |%|       . . |%|...    ............... |%| ..       .  ||"},
                     {"||..        %%%%%%%%%%. . |%|...    %%%%%%%%%%%%    |%| ..   %%%%.  ||"},
                     {"||..               |%|.             |%|......       |%| ....  |%|.  ||"},
                     {"||..     ......... |%|.        P    |%|......|%|        ..    |%|.  ||"},
                     {"||..|%|  |%|%%%|%|.|%|. |%|            ......|%|        ..|%| |%|.  ||"},
                     {"||..|%|  |%|   |%|..    %%%%%%%%%%%%%  ......|%|         .|%|.      ||"},
                     {"||..|%|  |%|   |%|..           ...|%|     %%%%%%        . |%|.      ||"},
                     {"||..|%|            .           ...|%|               |%| ..|%|.      ||"},
                     {"||..|%|  %%%%%%%%%%%%%%        ...|%|%%%%%%%%%%     |%| ..|%|%%%%%  ||"},
                     {"||...............................................   |%| ..........  ||"},
                     {"||   ............................................          .......  ||"},
                     {"||..|%|  |%|   |%|..    %%%%%%%%%%%%%  ......|%|    |%| ..|%|.      ||"},
                     {"||..|%|  |%|   |%|..           ...|%|     %%%%%%    |%| ..|%|.      ||"},
                     {"||..|%|           ..     ..    ...|%|               |%| ..|%|       ||"},
                     {"||..|%|  %%%%%%%%%%%%%%        ...|%|%%%%%%%%%%     |%| ..|%|%%%%%  ||"},
                     {"||...............................................   |%| ..........  ||"},
                     {"||  .............................................          .......  ||"},
                     {"##################################################################### "}};

void printmaze()
{
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 71; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
}
main()
{
    loadmaze();
    bool gamerunning = true;
    system("CLS");
    printmaze();
    while (gamerunning)
    {
        Sleep(200);
        moveGhost1();
        moveGhost2();
        moveGhost3();
        moveGhost4();

        printscore();

        if (gameover())
        {
            gamerunning = false;
        }

        if (GetAsyncKeyState(VK_LEFT))
        {
            movepacmanleft(); // to move pacman left
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movepacmanright(); //to move pacman right
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movepacmanup(); // to move pacman up
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movepacmandown(); // to move pacman down
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gamerunning = false; // game end
        }

        if (score == 350)
        {
            winner();
            gamerunning = false;
        }
    }
}
void storemaze()
{

    file.open("game.txt", ios::out);
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 71; j++)
        {
            file << maze[i][j];
        }
        file << endl;
    }
    file.close();
}
void loadmaze()
{

    file.open("game.txt", ios::in);
    for (int i = 0; i < 24; i++)
    {
        string a;
        getline(file, a);
        for (int j = 0; j < 71; j++)
        {
            // file >> maze[i][j];

            maze[i][j] = a[j];
        }
        // file << endl;
    }
    file.close();
}
void movepacmanleft()
{
    if (maze[pacmanx][pacmany - 1] == ' ' || maze[pacmanx][pacmany - 1] == '.')
    {
        maze[pacmanx][pacmany] = ' ';

        if (maze[pacmanx][pacmany - 1] == '.')
        {
            score++;
        }
        gotoxy(pacmany, pacmanx);
        cout << ' ';

        pacmany = pacmany - 1;
        gotoxy(pacmany, pacmanx);
        cout << 'p';
    }
}
void movepacmanright()
{
    if (maze[pacmanx][pacmany + 1] == ' ' || maze[pacmanx][pacmany + 1] == '.')
    {
        maze[pacmanx][pacmany] = ' ';
        if (maze[pacmanx][pacmany + 1] == '.')
        {
            score++;
        }
        gotoxy(pacmany, pacmanx);
        cout << ' ';

        pacmany = pacmany + 1;
        gotoxy(pacmany, pacmanx);
        cout << 'p';
    }
}

void movepacmanup()
{
    if (maze[pacmanx - 1][pacmany] == ' ' || maze[pacmanx - 1][pacmany] == '.')
    {

        maze[pacmanx][pacmany] = ' ';
        if (maze[pacmanx - 1][pacmany] == '.')
        {
            score++;
        }
        gotoxy(pacmany, pacmanx);
        cout << ' ';

        pacmanx = pacmanx - 1;
        gotoxy(pacmany, pacmanx);
        cout << 'p';
    }
}

void movepacmandown()
{
    if (maze[pacmanx + 1][pacmany] == ' ' || maze[pacmanx + 1][pacmany] == '.')
    {
        maze[pacmanx][pacmany] = ' ';
        if (maze[pacmanx + 1][pacmany] == '.')
        {
            score++;
        }
        gotoxy(pacmany, pacmanx);
        cout << ' ';

        pacmanx = pacmanx + 1;
        gotoxy(pacmany, pacmanx);
        cout << 'p';
    }
}

void printscore()
{
    gotoxy(70, 10);
    cout << "Score: " << score << endl;
    gotoxy(70, 11);
    cout << "Lives: " << lives << endl;
}

int ghostDirection()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void winner()
{
    gotoxy(10, 20);

    cout << "  *** WINNER *** " << endl;
}
int moveGhost1()
{
    char pre;
    if ((maze[g1x][g1y - 1] == ' ' || maze[g1x][g1y - 1] == '.') && flag1 == 1)
    {
        pre = maze[g1x][g1y];
        maze[g1x][g1y] = pre;
        gotoxy(g1y, g1x);
        cout << pre;
        g1y = g1y - 1;
        gotoxy(g1y, g1x);
        cout << 'G';
    }
    else
    {
        flag1 = 0;
    }
    if ((maze[g1x][g1y + 1] == ' ' || maze[g1x][g1y + 1] == '.') && flag1 == 0)
    {
        pre = maze[g1x][g1y];
        maze[g1x][g1y] = pre;
        gotoxy(g1y, g1x);
        cout << pre;
        g1y = g1y + 1;
        gotoxy(g1y, g1x);
        cout << 'G';
    }
    else
    {
        flag1 = 1;
    }
return 0;
}
void moveGhost2()
{
    char pre;

    if ((maze[g2x - 1][g2y] == ' ' || maze[g2x - 1][g2y] == '.') && flag2 == 1)
    {
        pre = maze[g2x][g2y];

        maze[g2x][g2y] = pre;
        gotoxy(g2y, g2x);
        cout << pre;
        g2x--;
        gotoxy(g2y, g2x);
        cout << 'G';
    }
    else
    {
        flag2 = 0;
    }
    if ((maze[g2x + 1][g2y] == ' ' || maze[g2x + 1][g2y] == '.') && flag2 == 0)
    {
        pre = maze[g2x][g2y];

        maze[g2x][g2y] = pre;
        gotoxy(g2y, g2x);
        cout << pre;
        g2x++;
        gotoxy(g2y, g2x);
        cout << 'G';
    }
    else
    {
        flag2 = 1;
    }
}
void moveGhost3()
{

    int num = ghostDirection();

    char pre;

    if (num == 1)
    {
        if (maze[g3x][g3y + 1] == ' ' || maze[g3x][g3y + 1] == '.')
        {
            pre = maze[g3x][g3y];
            gotoxy(g3y, g3x);
            cout << pre;
            g3y++;

            gotoxy(g3y, g3x);
            cout << 'G';
        }
    }
    else if (num == 2)
    {
        if (maze[g3x][g3y - 1] == ' ' || maze[g3x][g3y - 1] == '.')
        {
            pre = maze[g3x][g3y];
            gotoxy(g3y, g3x);
            cout << pre;
            g3y--;

            gotoxy(g3y, g3x);
            cout << 'G';
        }
    }
    else if (num == 3)
    {
        if (maze[g3x - 1][g3y] == ' ' || maze[g3x - 1][g3y] == '.')
        {
            pre = maze[g3x][g3y];
            gotoxy(g3y, g3x);
            cout << pre;
            g3x--;

            gotoxy(g3y, g3x);
            cout << 'G';
        }
    }
    else if (num == 4)
    {
        if (maze[g3x + 1][g3y] == ' ' || maze[g3x + 1][g3y] == '.')
        {
            pre = maze[g3x][g3y];
            gotoxy(g3y, g3x);
            cout << pre;
            g3x++;

            gotoxy(g3y, g3x);
            cout << 'G';
        }
    }
}
int moveGhost4()
{
    int dx = pacmanx - g4x;
    int dy = pacmany - g4y;
    char pre;

    Sleep(50);

    if (pacmanx > g4x)
    {
        if (maze[g4x + 1][g4y] == ' ' || maze[g4x + 1][g4y] == '.')
        {
            pre = maze[g4x][g4y];
            gotoxy(g4y, g4x);
            cout << pre;
            g4x++;
            gotoxy(g4y, g4x);
            cout << 'G';
            return 1;
        }
    }
    if (pacmanx < g4x)
    {
        if (maze[g4x - 1][g4y] == ' ' || maze[g4x - 1][g4y] == '.')
        {
            pre = maze[g4x][g4y];
            gotoxy(g4y, g4x);
            cout << pre;
            g4x--;
            gotoxy(g4y, g4x);
            cout << 'G';
            return 1;
        }
    }
    if (pacmany > g4y)
    {
        if (maze[g4x][g4y + 1] == ' ' || maze[g4x][g4y + 1] == '.')
        {
            pre = maze[g4x][g4y];
            gotoxy(g4y, g4x);
            cout << pre;
            g4y++;
            gotoxy(g4y, g4x);
            cout << 'G';
            return 1;
        }
    }
    if (pacmany < g4y)
    {
        if (maze[g4x][g4y - 1] == ' ' || maze[g4x][g4y - 1] == '.')
        {
            pre = maze[g4x][g4y];
            gotoxy(g4y, g4x);
            cout << pre;
            g4y--;
            gotoxy(g4y, g4x);
            cout << 'G';
            return 1;
        }
    }
   return 0;
}
bool gameover()
{
    if (pacmanx == g1x && pacmany == g1y)
    {
        lives--;
        pacmanx = 9;
        pacmany = 31;
    }
    else if (pacmanx == g2x && pacmany == g2y)
    {
        lives--;
        pacmanx = 9;
        pacmany = 31;
    }
    else if (pacmanx == g3x && pacmany == g3y)
    {
        lives--;
        pacmanx = 9;
        pacmany = 31;
    }
    else if (pacmanx == g4x && pacmany == g4y)
    {
        lives--;
        pacmanx = 9;
        pacmany = 31;
    }
    gotoxy(pacmany, pacmanx);
    cout << 'P';
    if (lives == 0)
    {
        return true;
    }
  return false;
}
