#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include <unistd.h>
#include <termios.h>
#include <stropts.h>
#include <sys/select.h>
#include <stdio.h>

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

/*============================================*/
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
/*============================================*/

class block{
};

class voidBlock : public(block){
};

class wallBlock : public(block){
};

class ppuyoBlock : public(block){
    private :
    int color;
    public :
    ppuyoBlock();
    void setColor(int newColor);
    int color();
};

ppuyoBlock::ppuyoBlock(){
    this->setColor(Random::get(0, 4));
}

void ppuyoBlock::setColor(int newColor){
    this->color = newColor;
}

int ppuyoBlock::color(){
    return this->color;
}


int y = 0;
int x = 4;
bool gameover = false;
bool collideFlag = false;
int score = 0;

struct Random{
    Random(int min, int max)
    : mUniformDistribution(min, max)
    {}
    
    int operator()(){
        return mUniformDistribution(mEngine);
    }
    
    std::default_random_engine mEngine{ std::random_device()() };
    std::uniform_int_distribution<int> mUniformDistribution;
};

std::vector<std::vector<int>> stage(14, std::vector<int>(8, 0));
std::vector<std::vector<int>> field(14, std::vector<int>(8, 0));
Random getRandom{ 0, 2 };

//blocks
std::vector<std::vector<int>> block =
{
    { 0, 0, 0},
    { 0, 0, 0},
    { 0, 0, 0},
};

std::vector<std::vector<std::vector<int>>> block_list =
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
//end of blocks

char getch();
void title();
void update();
void draw();
bool makeBlocks();
void initGame();
void moveBlock(int, int);
void collidable();
bool isCollide(int, int);
void userInput();
bool rotateBolck();
void spwanBlock();

int main()
{
    initGame();
    update();
    return 0;
}

void update(){
    while(!gameover){
		userInput();
	}
}

void draw(){
	std::cout<<"score : "<<score<<std::endl;
    std::cout<<"============="<<std::endl;
	for (size_t i = 0; i < 13; i++){
        for (size_t j = 0; j < 7; j++){
            switch (field[i][j]){
                case 0:
                    std::cout << "  " << std::flush;
                    break;
                case 9:
                    std::cout <<BOLD("X ")<< std::flush;
                    break;
                default :
                    std::cout <<BOLD(FRED("⚉ "))<< std::flush;
                    break;
            }
        }
        std::cout << std::endl;
    }
}

void initGame(){
    for (size_t i = 0; i <= 13; i++){
        for (size_t j = 0; j <= 6; j++){
            if ((j == 0) || (j == 6) || (i == 12))
                field[i][j] = stage[i][j] = 9;
            else
                field[i][j] = stage[i][j] = 0;
        }
    }
    makeBlocks();
    draw();
}

bool makeBlocks(){
    x = 3;
    y = 0;
   
    int blockType = getRandom();

    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            block[i][j] = 0;
            block[i][j] = block_list[blockType][i][j];
        }
    }
    
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            field[i][j + 3] = stage[i][j + 3] + block[i][j];
            if (field[i][j + 3] > 1){
                gameover = true;
                return true;
            }
        }
    }
    return false;
}

void moveBlock(int x2, int y2){
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            field[y + i][x + j] -= block[i][j];     //현위치의 3*3을 블럭 3*3으로 뺀다 => 제거
        }
    }
    
    x = x2;                                         //인자로 받아진 새로운 좌표로 좌표를 업데이트 해준다.
    y = y2;
    
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            field[y + i][x + j] += block[i][j];     //인자로 받아진 새 위치의 3*3을 블럭 3*3으로 더한다 => 새로쓰기
        }
    }
    draw();                                         //지우기, 쓰기가 완료되면 그린다.
}

void collidable(){
    for (size_t i = 0; i<21; i++){
        for (size_t j = 0; j<12; j++){
            stage[i][j] = field[i][j];                          //stage가 collidable들?
        }
    }
}

bool isCollide(int x2, int y2){                                 //인자로 전달된 좌표와 충돌하는지를 확인
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            if (block[i][j] && stage[y2 + i][x2 + j] != 0)      //collidable의 좌표와 충돌하는 부분이 있는지 확인해서 있다면 충돌반환
                return true;
        }
    }
    return false;
}                                                               //없으면 ㄱㅊ

void userInput(){
    if (!isCollide(x, y + 1))                                   //일단 한번 떨어져야함
        moveBlock(x, y + 1);
    
    char key = getch();
    switch (key){
        case 'd':
            if(!isCollide(x + 1, y))                            //현 위치로부터 오른쪽에 충돌하는게 있는지 확인해서 괜찮으면 옮긴다.
                moveBlock(x + 1, y);
            break;
        case 'a':
            if (!isCollide(x - 1, y))                           //현 위치로부터 왼쪽에 충돌하는게 있는지 확인해서 괜찮으면 옮긴다.
                moveBlock(x - 1, y);
            break;
        case 's':
            if (!isCollide(x, y + 1))                           //마찬가지로 밑도 해줌
                moveBlock(x, y + 1);
            break;
        case 'e':
            rotateBolck();
    }
}

bool rotateBolck(){
    std::vector<std::vector<int>> tmp(4, std::vector<int>(4, 0));

    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            tmp[i][j] = block[i][j];
        }
    }
    
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            block[i][j] = tmp[3 - j][i];
        }
    }
    
    if (isCollide(x, y)){
        for (size_t i = 0; i < 3; i++){
            for (size_t j = 0; j < 3; j++){
                block[i][j] = tmp[i][j];
            }
        }
        collideFlag = true;
        return true;
    }
    
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            field[y + i][x + j] -= tmp[i][j];
            field[y + i][x + j] += block[i][j];
        }
    }
    
    draw();
    return false;
}

void spwanBlock(){
    if (!isCollide(x, y + 1)){
        moveBlock(x, y + 1);
    }
    else{
        collidable();
        makeBlocks();
        draw();
    }
}

