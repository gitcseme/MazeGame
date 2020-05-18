#include<bits/stdc++.h>
#include <graphics.h>
#include <chrono>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
using namespace std;

/** SETTINGS
    The Game is written using C++11.
    [settings -> compiler -> -std=c++11]
	
	Library: graphics.h
*/

const int BOARD_COLOR = CYAN;
const int BALLBORDER_COLOR = YELLOW;
const int POINT_COLOR = RED;
const int BG_COLOR = BLACK;
const int BALLFILL_COLOR = LIGHTRED;
const int BALL_RADIUS = 14;

int globalMoveCount;

struct Dir {
    int LEFT = 1, RIGHT = 2, TOP = 3, BOTTOM = 4;
};

struct Ball {
    int x, y;
    Ball(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

Ball ball = Ball(20, 250);
Dir dir;

void DrawMaze() {
    setcolor(BOARD_COLOR);
    line(0,100,450,100);  //horizontal line
    line(50,130,400,130);
    line(100,160,450,160);
    line(150,190,300,190);
    line(100,220,250,220);
    line(50,250,200,250);
    line(0,400,500,400);
    line(450,370,500,370);
    line(0,100,0,400); //vertical line
    line(50,130,50,370);
    line(100,160,100,220);
    line(100,280,100,400);
    line(150,250,150,370);
    line(200,280,200,400);
    line(250,220,250,370);
    line(300,190,300,400);
    line(350,160,350,370);
    line(400,190,400,400);
    line(450,100,450,370);

    setcolor(WHITE);
    line(493, 370, 493, 400);
    line(494, 370, 494, 400);
    setcolor(YELLOW);
    line(495, 370, 495, 400);
    line(496, 370, 496, 400);
    setcolor(DARKGRAY);
    line(497, 370, 497, 400);
    line(498, 370, 498, 400);
    setcolor(RED);
    line(499, 370, 499, 400);
    line(500, 370, 500, 400);

}

bool uCheck(int x, int y) {
    for (int i = x - BALL_RADIUS; i <= x + BALL_RADIUS; ++i) {
        int c = getpixel(i, y - BALL_RADIUS);
        if (c != BG_COLOR && c != BALLBORDER_COLOR)
            return false;
    }
    return true;
}
bool lCheck(int x, int y) {
    for (int j = y - BALL_RADIUS; j <= y + BALL_RADIUS; ++j) {
        int c = getpixel(x - BALL_RADIUS, j);
        if (c != BG_COLOR && c != BALLBORDER_COLOR)
            return false;
    }
    return true;
}
bool dCheck(int x, int y) {
    for (int i = x - BALL_RADIUS; i <= x + BALL_RADIUS; ++i) {
        int c = getpixel(i, y + BALL_RADIUS);
        if (c != BG_COLOR && c != BALLBORDER_COLOR) {
            return false;
        }
    }
    return true;
}
bool rCheck(int x, int y) {
    for (int j = y - BALL_RADIUS; j <= y + BALL_RADIUS; ++j) {
        int c = getpixel(x + BALL_RADIUS, j);
        if (c != BG_COLOR && c != BALLBORDER_COLOR) {
            return false;
        }
    }
    return true;
}

// Need to re-write
bool WIN() {
    for (int i = ball.x + BALL_RADIUS; i <= ball.x + BALL_RADIUS + 3; ++i)
        if(getpixel(i, ball.y) == WHITE)
            return true;

    return false;
}

void drawBall() {
    setcolor(BALLBORDER_COLOR);
    circle(ball.x, ball.y, BALL_RADIUS);
    setfillstyle(SOLID_FILL,12);
    floodfill(ball.x, ball.y, BALLBORDER_COLOR);
}

void InitGame() {
    int direc = dir.BOTTOM, mov;
    globalMoveCount = 0;
    char msg[200];

    while (true) {

        if (kbhit()) {
            for (int i = 0; i < 2; ++i) mov = getch();

            if (mov == KEY_UP) direc = dir.TOP;
            else if (mov == KEY_DOWN) direc = dir.BOTTOM;
            else if (mov == KEY_LEFT) direc = dir.LEFT;
            else if (mov == KEY_RIGHT) direc = dir.RIGHT;
        }

        if (direc == dir.TOP && uCheck(ball.x, ball.y - 1)) --ball.y, ++globalMoveCount;
        else if (direc == dir.BOTTOM && dCheck(ball.x, ball.y + 1)) ++ball.y, ++globalMoveCount;
        else if (direc == dir.LEFT && lCheck(ball.x - 1, ball.y)) --ball.x, ++globalMoveCount;
        else if (direc == dir.RIGHT && rCheck(ball.x + 1, ball.y)) ++ball.x, ++globalMoveCount;

        cleardevice();
        sprintf(msg, "Move count %d", globalMoveCount);
        outtextxy(300, 50, msg);
        DrawMaze();
        setcolor(BALLBORDER_COLOR);
        drawBall();

        delay(1);

        if (WIN()) {
            cleardevice();
            outtextxy(300, 50, msg);
            outtextxy(300, 70, "YOU WON");
            break;
        }
    }
}

int main() {
    int gDriver = DETECT;
    int gMode;
    initgraph(&gDriver, &gMode, "C:\\TC\\BGI");
    //initwindow(800, 700);
    /* ************** settings ***************/

    auto startTime = chrono::steady_clock::now();
    InitGame();
    auto endTime = chrono::steady_clock::now();

    char c[200];
    int d = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
    sprintf(c, "Elapsed Time:  %d sec.", d);
    outtextxy(200, 250, c);

    cout << "Elapsed time: " << d << "\n";


    /* ************** settings ***************/
    getch();
    closegraph();
    return 0;
}
