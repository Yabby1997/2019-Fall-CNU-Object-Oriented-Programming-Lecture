#include<iomanip>
#include<iostream>
#include<vector>
#include<unistd.h>
#include<termios.h>
#include<stropts.h>
#include<sys/select.h>
#include<stdio.h>
#include<ctime>
#include<cstdlib>
#include<string>

/*===============COLORS=================*/
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST
#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST
/*===============COLORS=================*/

/*================DEBUG=================*/
#define DEBUG_MODE false
void debugMessage(std::string msg){
    if(DEBUG_MODE)
        std::cout<<BOLD(FCYN("[DEBUG] "))<<msg<<std::endl;
}
/*================DEBUG=================*/

/*===============INPUT==================*/
char getch(){
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
}
/*===============INPUT==================*/

/*===============BLOCK==================*/
class block{
public:
    block();
};

block::block(){}
/*===============BLOCK==================*/

/*============VOID BLOCK================*/
class voidBlock : public block{
public:
    voidBlock();
};

voidBlock::voidBlock(){}
/*============VOID BLOCK================*/

/*============WALL BLOCK================*/
class wallBlock : public block{
public:
    wallBlock();
};

wallBlock::wallBlock(){}
/*============WALL BLOCK================*/

/*===========PPUYO BLOCK================*/
class ppuyoBlock : public block{
    private :
    int color;
    
    public :
    ppuyoBlock();
    void setColor(int newColor);
    int getColor();
};

ppuyoBlock::ppuyoBlock(){
    this->setColor(rand()%4);                                                  //랜덤으로 처리해서 랜덤색의 블럭이 생성되도록 하면될듯
}

void ppuyoBlock::setColor(int newColor){
    this->color = newColor;
}

int ppuyoBlock::getColor(){
    return this->color;
}
/*===========PPUYO BLOCK================*/

/*=============VARIABLES================*/
int y = 0;
int x = 4;
bool gameover = false;
bool collideFlag = false;
int score = 0;

#define RED 0
#define GRN 1
#define BLU 2
#define ASH 3

std::vector<std::vector<int>> collisionMap(16, std::vector<int>(7, 0));         //맵도 블럭의 배열로 바꾸고 void랑 wall로 처리하기
std::vector<std::vector<int>> gameMap(16, std::vector<int>(7, 0));         //collisionMap랑 gameMap를 따로 둔 이유가?
/*=============VARIABLES================*/

/*==============PATTERNS================*/
std::vector<std::vector<int>> pattern =                                   //패턴으로 이름 바꾸고 블럭의 배열로
{
    { 0, 0, 0},
    { 0, 0, 0},
    { 0, 0, 0},
};

std::vector<std::vector<std::vector<int>>> patternList =
{
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
/*==============PATTERNS================*/

/*==============FUNCTIONS===============*/
char getch();
void debugMessage(std::string msg);

void update();
void draw();

void initGame();
void initCoordinate();

void collidable();
bool isCollide(int, int);

void userInput();

bool patternGenerate();
void movePattern(int, int);
bool rotatePattern();
void spawnPattern();

void inactivate();
void gravitate();

/*==============FUNCTIONS===============*/

/*================GAME==================*/
int main(){
    srand((unsigned int)time(NULL));
    initGame();
    update();
    return 0;
}

void update(){
    while(!gameover){
        gravitate();
		userInput();
        spawnPattern();
	}
    std::cout<<""<<std::endl;
    std::cout<<BOLD(FRED("===GAME OVER==="))<<std::endl;
    std::cout<<BOLD(FYEL("YOUR SCORE IS "))<<score<<std::endl;
    std::cout<<BOLD(FRED("==============="))s<<std::endl;
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
	std::cout<<BOLD(FYEL("score : "))<<score<<std::endl;
    std::cout<<BOLD(UNDL("============="))<<std::endl;
	for (size_t i = 0; i < 16; i++){                                    //0은 디버그용
        for (size_t j = 0; j < 7; j++){
            switch (gameMap[i][j]){                                       //읽어들인 블럭이 void인지 wall인지 ppuyo인지 확인, ppuyo면 색에 맞춰 출력
                case 0:
                    std::cout << "  " << std::flush;
                    break;
                case 9:
                    std::cout <<BOLD("X ")<< std::flush;
                    break;
                case 1:
                    std::cout <<BOLD(FRED("⚉ "))<< std::flush;
                    break;
                case 2:
                    std::cout <<BOLD(FGRN("⚉ "))<< std::flush;
                    break;
                case 3:
                    std::cout <<BOLD(FBLU("⚉ "))<< std::flush;
                    break;
                case 4:
                    std::cout <<BOLD(FWHT("⚉ "))<< std::flush;
                    break;
                case 5:
                    std::cout <<BOLD(FRED("⚉ "))<< std::flush;
                    break;
                case 6:
                    std::cout <<BOLD(FGRN("⚉ "))<< std::flush;
                    break;
                case 7:
                    std::cout <<BOLD(FBLU("⚉ "))<< std::flush;
                    break;
                case 8:
                    std::cout <<BOLD(FWHT("⚉ "))<< std::flush;
                    break;
                default:
                    std::cout <<gameMap[i][j]<< std::flush;
                    break;
            }
        }
        std::cout << std::endl;
    }
}

void initGame(){
    for (size_t i = 0; i < 16; i++){
        for (size_t j = 0; j < 7; j++){
            if ((j == 0) || (j == 6) || (i == 15))
                gameMap[i][j] = collisionMap[i][j] = 9;
            else
                gameMap[i][j] = collisionMap[i][j] = 0;
        }
    }
    patternGenerate();
    draw();
}

void initCoordinate(){
    x = 2;
    y = 0;
}

bool patternGenerate(){
    initCoordinate();                                               //좌표 초기화
    
    int blockType = rand()%3;                                       //블럭타입 결정, 3가지 타입중 결정됨
    
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            pattern[i][j] = 0;
            pattern[i][j] = patternList[blockType][i][j] * (rand()%4 + 1);           //패턴리스트에서 랜덤결정된 패턴을 패턴 배열로 가져온다.
        }
    }
    
    for (size_t i = 0; i < 3; i++){                                                         //실제 필드에 배치
        for (size_t j = 0; j < 3; j++){
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
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            gameMap[y + i][x + j] -= pattern[i][j];     //현위치의 3*3을 블럭 3*3으로 뺀다 => 제거
        }
    }
    
    x = x2;                                         //인자로 받아진 새로운 좌표로 좌표를 업데이트 해준다.
    y = y2;
    
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            gameMap[y + i][x + j] += pattern[i][j];     //인자로 받아진 새 위치의 3*3을 블럭 3*3으로 더한다 => 새로쓰기
        }
    }
    draw();                                         //지우기, 쓰기가 완료되면 그린다.
}

void collidable(){
    for (size_t i = 3; i<16; i++){
        for (size_t j = 0; j<7; j++){
            collisionMap[i][j] = gameMap[i][j];                          //collisionMap가 collidable들?
        }
    }
}

bool isCollide(int x2, int y2){                                 //인자로 전달된 좌표와 충돌하는지를 확인
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            if (pattern[i][j] && collisionMap[y2 + i][x2 + j] != 0){      //현재 패턴과 현재 좌표사이에 충돌하는 부분이 있는지 확인해서 있다면 true반환
                debugMessage("HIT DETECTION!");
                return true;
            }
        }
    }
    return false;
}                                                               //없으면 ㄱㅊ

void gravitate(){
    for(int i = 14; i > 0; i--){
        for(int j = 1; j < 6; j++){
            if(gameMap[i][j] == 0 && gameMap[i - 1][j] > 4 && gameMap[i-1][j] < 9){
                debugMessage("gravitate " + std::to_string(i) + ", " + std::to_string(j) + " : " +std::to_string(gameMap[i][j]));
                gameMap[i][j] = gameMap[i - 1][j];
                gameMap[i - 1][j] = 0;
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
    
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            tmp[i][j] = pattern[i][j];
        }
    }
    
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            pattern[i][j] = tmp[2 - j][i];
        }
    }
    
    if (isCollide(x, y)){
        for (size_t i = 0; i < 3; i++){
            for (size_t j = 0; j < 3; j++){
                pattern[i][j] = tmp[i][j];
            }
        }
        return true;
    }
    
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            gameMap[y + i][x + j] -= tmp[i][j];
            gameMap[y + i][x + j] += pattern[i][j];
        }
    }
    
    draw();
    return false;
}

void inactivate(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 6; j++){
            if(gameMap[i][j] > 0 && gameMap[i][j] < 5){
                gameMap[i][j] += 4;
            }
        }
    }
}

void spawnPattern(){
    if (!isCollide(x, y + 1)){
        movePattern(x, y + 1);
    }
    else{
        collidable();
        inactivate();
        patternGenerate();
        draw();
    }
}
