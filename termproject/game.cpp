#include<iomanip>
#include<iostream>
#include<vector>
#include<stdio.h>
#include<ctime>
#include<cstdlib>
#include<string>
#include"color.h"
#include"gameIO.h"

#define WIDTH 7
#define HEIGHT 16

//변수
bool gameover = false;
int x = 2, y = 0;
int score = 0;
int combo = 1;
int comboInterval = 0;
int comboRecord = 0;
std::vector<int> foundX;
std::vector<int> foundY;

bool visited[HEIGHT][WIDTH];                                                    //scan시 방문여부 확인할 배열
std::vector<std::vector<int>> gameMap(16, std::vector<int>(7, 0));              //display할 맵
std::vector<std::vector<int>> collisionMap(16, std::vector<int>(7, 0));         //collision을 체크하기 위한 맵
std::vector<std::vector<int>> blockMap(16, std::vector<int>(7, 0));             //비활성화되지 않은 블럭 공중에 떠있는 블럭은 제외한 맵

std::vector<std::vector<int>> pattern = {                                       //패턴으로 이름 바꾸고 블럭의 배열로
    { 0, 0, 0},
    { 0, 0, 0},
    { 0, 0, 0},
};

std::vector<std::vector<std::vector<int>>> patternList = {
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

//함수선언부
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

bool patternGenerate();
void movePattern(int, int);
bool rotatePattern();
void spawnPattern();

void inactivate();
void gravitate();

void clearVisited();
void clearFound();
void scan();
void sameColorChecker(int currentI, int currentJ, int checkingColor);
void adjacentGreyChecker(int currentI, int currentJ);
void explode(int targetX, int targetY);

//함수구현부
int main(){
    srand((unsigned int)time(NULL));
    initGame();
    gameStart();
    update();
    gameOver();
    return 0;
}

void update(){
    while(!gameover){
        gravitate();
		userInput();
        spawnPattern();
        updateBlocks();
        scan();
	}
}

void gameStart(){
    std::system("clear");
    std::cout<<""<<std::endl;
    std::cout<<BOLD(FCYN("====PPUYO PPUYO===="))<<std::endl;
    std::cout<<BOLD(FWHT("   PRESS ANY KEY   "))<<std::endl;
    std::cout<<BOLD(FCYN("==================="))<<std::endl;
    std::cout<<""<<std::endl;
}

void gameOver(){
    std::system("clear");
    std::cout<<""<<std::endl;
    std::cout<<BOLD(FRED("=====GAME OVER====="))<<std::endl;
    std::cout<<BOLD(FYEL(" + YOUR SCORE : "))<<score<<std::endl;
    std::cout<<BOLD(FYEL(" + BEST COMBO : "))<<comboRecord<<std::endl;
    std::cout<<BOLD(FRED("==================="))<<std::endl;
    std::cout<<""<<std::endl;
}

/*
 *  0 : empty space
 *  1 : red ppuyo
 *  2 : green ppuyo
 *  3 : blue ppuyo
 *  4 : gray ppuyo (actually, white in game)
 *  5 : inactivated version of 1
 *  6 : inactivated version of 2
 *  7 : inactivated version of 3
 *  8 : inactivated version of 4
 *  9 : wall
 */

void draw(){
    std::system("clear");
	std::cout<<BOLD(FYEL("score : "))<<score<<std::endl;
    std::cout<<BOLD(FMAG("============="))<<std::endl;
	for (int i = 3; i < HEIGHT; i++){                                    //0은 디버그용
        for (int j = 0; j < WIDTH; j++){
            switch (gameMap[i][j]){                                       //읽어들인 블럭이 void인지 wall인지 ppuyo인지 확인, ppuyo면 색에 맞춰 출력
                case 0:
                    std::cout << "  ";
                    break;
                case 1:
                    std::cout <<BOLD(FRED("⚉ "));
                    break;
                case 2:
                    std::cout <<BOLD(FGRN("⚉ "));
                    break;
                case 3:
                    std::cout <<BOLD(FBLU("⚉ "));
                    break;
                case 4:
                    std::cout <<BOLD(FWHT("⚉ "));
                    break;
                case 5:
                    std::cout <<BOLD(FRED("⚉ "));
                    break;
                case 6:
                    std::cout <<BOLD(FGRN("⚉ "));
                    break;
                case 7:
                    std::cout <<BOLD(FBLU("⚉ "));
                    break;
                case 8:
                    std::cout <<BOLD(FWHT("⚉ "));
                    break;
                case 9:
                    std::cout <<BOLD(FMAG("X "));
                    break;
            }
        }
        std::cout << std::endl;
    }
}

void initGame(){
    score = 0;
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            if ((j == 0) || (j == 6) || (i == 15))
                gameMap[i][j] = collisionMap[i][j] = 9;
            else
                gameMap[i][j] = collisionMap[i][j] = 0;
        }
    }
    patternGenerate();
}

void setCoordinate(int newX, int newY){
    x = newX;
    y = newY;
}

bool patternGenerate(){
    setCoordinate(2, 0);                                               //좌표 초기화
    
    int blockType = rand()%3;                                       //블럭타입 결정, 3가지 타입중 랜덤하게 결정됨
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            pattern[i][j] = 0;
            pattern[i][j] = patternList[blockType][i][j] * (rand()%4 + 1);           //패턴리스트에서 랜덤결정된 패턴을 패턴 배열로 가져온다.
        }
    }
    
    for (int i = 0; i < 3; i++){                                                         //실제 필드에 배치
        for (int j = 0; j < 3; j++){
            if (gameMap[i][j + 2] >= 1){                                                      //배치 가능한지 검사해서 이미 블럭이 배치되어있다면, 즉 놓을 수 없다면 gameover
                gameover = true;
                return true;
            }
            gameMap[i][j + 2] = collisionMap[i][j + 2] + pattern[i][j];                              //그게 아니라면 패턴으로 만들어진걸 배치한다.
        }
    }
    return false;
}

void movePattern(int x2, int y2){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            gameMap[y + i][x + j] -= pattern[i][j];     //현위치의 3*3을 블럭 3*3으로 뺀다 => 제거
        }
    }
    
    setCoordinate(x2, y2);                                       //인자로 받아진 새로운 좌표로 좌표를 업데이트 해준다.
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            gameMap[y + i][x + j] += pattern[i][j];     //인자로 받아진 새 위치의 3*3을 블럭 3*3으로 더한다 => 새로쓰기
        }
    }
    draw();                                         //지우기, 쓰기가 완료되면 그린다.
}

void updateBlocks(){                                                    //각 라인별 안착한 블럭들 확인하여 업데이트해준다.
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            blockMap[i][j] = 0;
        }
    }
    
    for (int i = 14; i > 1; i--){
        int colorOfBlock = gameMap[i][1];
        if(colorOfBlock == 0)
            break;
        blockMap[i][1] = gameMap[i][1];
    }
    
    for (int i = 14; i > 1; i--){
        int colorOfBlock = gameMap[i][2];
        if(colorOfBlock == 0)
            break;
        blockMap[i][2] = gameMap[i][2];
    }
    
    for (int i = 14; i > 1; i--){
        int colorOfBlock = gameMap[i][3];
        if(colorOfBlock == 0)
            break;
        blockMap[i][3] = gameMap[i][3];
    }
    
    for (int i = 14; i > 1; i--){
        int colorOfBlock = gameMap[i][4];
        if(colorOfBlock == 0)
            break;
        blockMap[i][4] = gameMap[i][4];
    }
    
    for (int i = 14; i > 1; i--){
        int colorOfBlock = gameMap[i][5];
        if(colorOfBlock == 0)
            break;
        blockMap[i][5] = gameMap[i][5];
    }
}

bool isCollide(int x2, int y2){                                 //인자로 전달된 좌표와 충돌하는지를 확인
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (pattern[i][j] && collisionMap[y2 + i][x2 + j] != 0){      //현재 패턴과 현재 좌표사이에 충돌하는 부분이 있는지 확인해서 있다면 true반환
                return true;
            }
        }
    }
    return false;
}

void gravitate(){                                                                   //개별블럭들을 아래로 내린다.
    for(int i = 14; i > 0; i--){
        for(int j = 1; j < 6; j++){
            if(gameMap[i][j] == 0 && gameMap[i - 1][j] > 4 && gameMap[i-1][j] < 9){
                gameMap[i][j] = collisionMap[i][j] = gameMap[i - 1][j];
                gameMap[i - 1][j] = collisionMap[i - 1][j] = 0;
            }
        }
    }
}

void userInput(){
    char key = getch();
    switch (key){
        case 'd':
            if(!isCollide(x + 1, y))                            //현 위치로부터 오른쪽에 충돌하는게 있는지 확인해서 괜찮으면 옮긴다.
                movePattern(x + 1, y);
            break;
        case 'a':
            if (!isCollide(x - 1, y))                           //현 위치로부터 왼쪽에 충돌하는게 있는지 확인해서 괜찮으면 옮긴다.
                movePattern(x - 1, y);
            break;
        case 's':
            if (!isCollide(x, y + 1))                           //마찬가지로 밑도 해줌
                movePattern(x, y + 1);
            break;
        case 'e':
            rotatePattern();
            break;
    }
}

bool rotatePattern(){
    std::vector<std::vector<int>> tmp =
    {
        { 0, 0, 0},
        { 0, 0, 0},
        { 0, 0, 0},
    };
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            tmp[i][j] = pattern[i][j];
        }
    }
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            pattern[i][j] = tmp[2 - j][i];
        }
    }
    
    if (isCollide(x, y)){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                pattern[i][j] = tmp[i][j];
            }
        }
        return true;
    }
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            gameMap[y + i][x + j] -= tmp[i][j];
            gameMap[y + i][x + j] += pattern[i][j];
        }
    }
    return false;
}

void inactivate(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 6; j++){
            if(gameMap[i][j] > 0 && gameMap[i][j] < 5){
                gameMap[i][j] += 4;
                collisionMap[i][j] = gameMap[i][j];
            }
        }
    }
}

void spawnPattern(){
    if (!isCollide(x, y + 1)){
        movePattern(x, y + 1);
    }
    else{
        inactivate();
        patternGenerate();
    }
}
void clearVisited(){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            visited[i][j] = false;
        }
    }
}

void clearFound(){
    while(!foundX.empty()){
        foundX.pop_back();
        foundY.pop_back();
    }
}


void scan(){
    if(comboInterval == 0)
        combo = 1;
    
    bool exploded = false;
    
    for(int i = 2; i < HEIGHT - 1; i++){
        for(int j = 1; j < WIDTH - 1; j++){
            if(blockMap[i][j] != 8){
                sameColorChecker(i, j, blockMap[i][j]);
            }
            if(foundX.size() >= 4){
                for(int i = 0; i < foundX.size(); i++){
                    adjacentGreyChecker(foundY.at(i) + 1, foundX.at(i));
                    adjacentGreyChecker(foundY.at(i) - 1, foundX.at(i));
                    adjacentGreyChecker(foundY.at(i), foundX.at(i) + 1);
                    adjacentGreyChecker(foundY.at(i), foundX.at(i) - 1);
                }
                
                for(int i = 0; i < foundX.size(); i++){
                    debugMessage("EXPLODE " + std::to_string(foundX.at(i)) + ", " + std::to_string(foundY.at(i)));
                }
                
                while(!foundX.empty()){
                    int targetX = foundX.back();
                    int targetY = foundY.back();
                    foundX.pop_back();
                    foundY.pop_back();
                    explode(targetX, targetY);
                }
                exploded = true;
            }
            clearFound();
        }
    }
    clearVisited();
    
    if(exploded){
        comboInterval = 5;
        score += combo;
        std::cout<<BOLD(FCYN("COMBO ")) + std::to_string(combo)<<std::endl;
        if(comboRecord < combo){
            comboRecord = combo;
            std::cout<<BOLD(FCYN("NEW RECORD!"))<<std::endl;
        }
        combo++;
    }
    else
        comboInterval--;
}

void explode(int targetX, int targetY){
    gameMap[targetY][targetX] = collisionMap[targetY][targetX] = blockMap[targetY][targetX] = 0;
}

void adjacentGreyChecker(int currentI, int currentJ){
    int currentValue = blockMap[currentI][currentJ];
    if(visited[currentI][currentJ] == false && currentValue == 8){
        visited[currentI][currentJ] = true;
        debugMessage("ADJACENT GREY FOUND ... I : " + std::to_string(currentI) + ", J : " + std::to_string(currentJ) + ", COLOR : " + std::to_string(blockMap[currentI][currentJ]));
        foundX.push_back(currentJ);
        foundY.push_back(currentI);
        adjacentGreyChecker(currentI + 1, currentJ);
        adjacentGreyChecker(currentI -1, currentJ);
        adjacentGreyChecker(currentI, currentJ + 1);
        adjacentGreyChecker(currentI, currentJ - 1);
    }
}

void sameColorChecker(int currentI, int currentJ, int checkingColor){
    int currentValue = blockMap[currentI][currentJ];
    if(visited[currentI][currentJ] == false && (currentValue > 4 && currentValue < 9) && currentValue == checkingColor){
        debugMessage("SAME COLOR FOUND ... I : " + std::to_string(currentI) + ", J : " + std::to_string(currentJ) + ", COLOR : " + std::to_string(blockMap[currentI][currentJ]));
        visited[currentI][currentJ] = true;
        foundX.push_back(currentJ);
        foundY.push_back(currentI);
        sameColorChecker(currentI + 1, currentJ, checkingColor);
        sameColorChecker(currentI - 1, currentJ, checkingColor);
        sameColorChecker(currentI, currentJ + 1, checkingColor);
        sameColorChecker(currentI, currentJ - 1, checkingColor);
    }
}
