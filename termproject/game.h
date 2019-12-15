#ifndef GAME_H
#define GAME_H

#include<vector>

#define WIDTH 7                                                                 //게임맵의 크기. 벽을 포함한 크기이고 HEIGHT의 경우 블럭의 생성을 위해 조금 더 크게줬다.
#define HEIGHT 16

//변수
bool gameover = false;
int x = 2, y = 0;
int score = 0;
int combo = 1;
int comboInterval = 0;
int comboRecord = 0;
std::vector<int> foundX;                                                        //scan시 폭파될 블럭의 X와 Y좌표를 저장할 벡터
std::vector<int> foundY;

bool visited[HEIGHT][WIDTH];                                                    //scan시 방문여부 확인할 배열
std::vector<std::vector<int>> gameMap(16, std::vector<int>(7, 0));              //display할 맵
std::vector<std::vector<int>> collisionMap(16, std::vector<int>(7, 0));         //collision을 체크하기 위한 맵
std::vector<std::vector<int>> blockMap(16, std::vector<int>(7, 0));             //비활성화되지 않은 블럭 공중에 떠있는 블럭은 제외한 맵

std::vector<std::vector<int>> pattern = {                                       //현재 패턴정보를 저장할 벡터
    { 0, 0, 0},
    { 0, 0, 0},
    { 0, 0, 0},
};

std::vector<std::vector<std::vector<int>>> patternList = {                      //3가지 종류의 패턴의 벡터
    {
        { 0, 1, 0},
        { 0, 1, 0},
        { 0, 1, 0},
    },
    {
        { 0, 1, 0},
        { 1, 1, 1},
        { 0, 1, 0},
    },
    {
        { 0, 0, 0},
        { 0, 1, 0},
        { 1, 1, 0},
    }
};

char getch();
void debugMessage(std::string msg);

void update();
void draw();

void gameStart();
void gameOver();

void initGame();
void setCoordinate();

void updateBlocks();
bool isCollide(int, int);

void userInput();

void patternGenerate();
void movePattern(int, int);
void rotatePattern();
void spawnPattern();

void inactivate();
void gravitate();

void clearVisited();
void clearFound();
void scan();
void sameColorChecker(int currentI, int currentJ, int checkingColor);
void adjacentGreyChecker(int currentI, int currentJ);
void explode(int targetX, int targetY);

#endif
