#include <iostream>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <windows.h>

using namespace std;

// Variables
const int TABLE_WIDTH = 40;
const int TABLE_HEIGHT = 20;

int headX = TABLE_WIDTH / 2;
int headY = TABLE_HEIGHT / 2;
vector<pair<int, int>> body;

int foodX = TABLE_WIDTH / 4;
int foodY = TABLE_HEIGHT / 4;

bool gamePlaying = true;

enum E_DIR
{
    e_DIR_UP = 1,
    e_DIR_DOWN,
    e_DIR_LEFT,
    e_DIR_RIGHT
};

int dir = e_DIR_RIGHT;

// Functions
void setCursorPosition(int x, int y);
void draw();
void input();
void move();

// Initialization
int main()
{
    body.push_back({headX, headY});
    body.push_back({headX - 1, headY});
    body.push_back({headX - 2, headY});

    while (gamePlaying)
    {
        setCursorPosition(0, 0);
        draw();
        input();
        move();
        Sleep(200);
        system("cls");
    }
    return 0;
}

// Define functions
void setCursorPosition(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw()
{
    string screen;
    
    // Top wall
    screen.append(TABLE_WIDTH, '#');
    screen += "\n";

    // Side walls
    for (int j = 0; j < TABLE_HEIGHT; j++)
    {
        screen += '#';

        // Inside the table
        for (int k = 0; k < TABLE_WIDTH - 2; k++)
        {
            char ch = ' ';
            // Draw snake head
            if (headX == k + 1 && headY == j)
                ch = 219; // head char
            else
            {
                bool isSnake = false;

                for (auto &segment: body)
                {
                    if (segment.first == k + 1 && segment.second == j)
                    {
                        isSnake = true;
                        break;
                    }
                }

                if (isSnake)
                    ch = 240; // body char
                else if (foodX == k + 1 && foodY == j)
                    ch = 254; // food char
            }

            screen += ch;
        }
        // Right wall
        screen += "#\n";
    }

    screen.append(TABLE_WIDTH, '#');
    screen += '\n';

    cout << screen;
}

void input()
{
    if (_kbhit())
    {
        char ch = _getch();
        if (ch == 'w') dir = e_DIR_UP;
        else if (ch == 'a') dir = e_DIR_LEFT;
        else if (ch == 'd') dir = e_DIR_RIGHT;
        else if (ch == 's') dir = e_DIR_DOWN;
    }
}

void move()
{
    if (dir == e_DIR_UP) headY--;
    else if (dir == e_DIR_DOWN) headY++;
    else if (dir == e_DIR_LEFT) headX--;
    else if (dir == e_DIR_RIGHT) headX++;

    body.insert(body.begin(), {headX, headY});

    if (headX >= (TABLE_WIDTH - 1) || headX == 0 || headY >= TABLE_HEIGHT || headY == -1)
    {
        gamePlaying = false;
        cout << "Game over!\n";
        system("pause");
    }

    if (headX == foodX && headY == foodY)
    {
        foodX = rand() % (TABLE_WIDTH - 2) + 1;
        foodY = rand() % (TABLE_HEIGHT - 2);
    }
    else
        body.pop_back();
}