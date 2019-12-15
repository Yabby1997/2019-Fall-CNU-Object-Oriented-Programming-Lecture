#include<iomanip>
#include<iostream>
#include<vector>
#include<stdio.h>
#include<ctime>
#include<cstdlib>
#include<string>
#include"color.h"
#include"gameIO.h"
#include"game.h"

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
	for (int i = 3; i < HEIGHT; i++){  
		for (int j = 0; j < WIDTH; j++){
            switch (gameMap[i][j]){                                       //gameMap에서 읽어온 블럭정보에 따라 출력해준다. 
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

void initGame(){															//게임 초기설정. 벽을 만들고 패턴생
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

void setCoordinate(int newX, int newY){                                     //게임 좌표를 인자로 설정
    x = newX;
    y = newY;
}

void movePattern(int x2, int y2){                                            //이동할 위치를 인자로 받는다.
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            gameMap[y + i][x + j] -= pattern[i][j];                         //블럭은 현재좌표에 위치해 있을 것이므로 현좌표 기준으로 패턴을 빼주어서 제거한다.
        }
    }
    
    setCoordinate(x2, y2);                                                  //인자로 받아진 새로운 좌표로 좌표를 업데이트 해준다.
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            gameMap[y + i][x + j] += pattern[i][j];                         //인자로 받아진 새 위치의 3*3을 블럭 3*3으로 더해주어 새로운 위치에 쓴다.
        }
    }
    draw();                                                                 //지우기, 쓰기가 완료되면 그린다.
}

void updateBlocks(){                                                        //각 라인에 제거될 수 있는 블럭들, 공중에 떠있지 않은 블럭들을 업데이트해준다.
    for(int i = 0; i < HEIGHT; i++){                                        //매번 업데이트를 위해 0으로 초기화먼저 해준다.
        for(int j = 0; j < WIDTH; j++){
            blockMap[i][j] = 0;
        }
    }
    
    for (int i = 14; i > 1; i--){                                           //5개의 열에 대해서 모두 수행해준다. 게임맵의 아래부터 훑어서 0, 즉 빈공간이 생기면 탐색을 멈춘다.
        int colorOfBlock = gameMap[i][1];                                   //이렇게해서 공중에 떠있지 않은 블럭들만을 찾아내 blockMap에 써준다.
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

bool isCollide(int x2, int y2){                                             //인자로 전달된 좌표가 패턴과 충돌하는지를 확인
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (pattern[i][j] && collisionMap[y2 + i][x2 + j] != 0){        //현재 패턴과 현재 좌표사이에 충돌하는 부분이 있는지 확인해서 있다면 true반환
                return true;
            }
        }
    }
    return false;
}

void gravitate(){                                                           //비활성화된 개별 블럭들에 중력을 적용해 아래로 내려가게 만든다.
    for(int i = 14; i > 0; i--){
        for(int j = 1; j < 6; j++){
            if(gameMap[i][j] == 0 && gameMap[i - 1][j] > 4 && gameMap[i-1][j] < 9){     //5~8은 비활성화된 블럭이다. 비활성 블럭의 아래에 빈공간이 있다면 중력을 적용한다.
                gameMap[i][j] = collisionMap[i][j] = gameMap[i - 1][j];
                gameMap[i - 1][j] = collisionMap[i - 1][j] = 0;
            }
        }
    }
}

void userInput(){
    char key = getch();                                                     //getch로 유저의 입력을 받는다.
    switch (key){
        case 'd':
            if(!isCollide(x + 1, y))                                        //wasd에 대하여 대응하는 위치에 충돌하는 블럭이 없다면 그 좌표로 이동시킨다.
                movePattern(x + 1, y);
            break;
        case 'a':
            if (!isCollide(x - 1, y))
                movePattern(x - 1, y);
            break;
        case 's':
            if (!isCollide(x, y + 1))
                movePattern(x, y + 1);
            break;
        case 'e':                                                           //e키로 90도 회전시킬 수 있다.
            rotatePattern();
            break;
    }
}

void rotatePattern(){
    std::vector<std::vector<int>> tmp = {                                   //패턴의 회전에 필요한 임시 벡터
        { 0, 0, 0},
        { 0, 0, 0},
        { 0, 0, 0},
    };
    
    for (int i = 0; i < 3; i++){                                            //temp에 현재 pattern을 복제한다.
        for (int j = 0; j < 3; j++){
            tmp[i][j] = pattern[i][j];
        }
    }
                                                                            //  temp를 이용해 pattern을 우로 90도 회전시킨다
    for (int i = 0; i < 3; i++){                                            //  1 2 3       7 4 1
        for (int j = 0; j < 3; j++){                                        //  4 5 6   ->  8 5 2
            pattern[i][j] = tmp[2 - j][i];                                  //  7 8 9       9 6 3
        }
    }
    
    if (isCollide(x, y)){                                                   //변경된 pattern에 대해 충돌이 발생하는지를 확인한다.
        for (int i = 0; i < 3; i++){                                        //발생한다면 회전이 불가능하니까 원본인 temp로 pattern을 복구시킨다.
            for (int j = 0; j < 3; j++){
                pattern[i][j] = tmp[i][j];
            }
        }
    }
    
    for (int i = 0; i < 3; i++){                                            //그렇지 않다면 게임맵에서 temp를 빼고 (원본을 지우고)
        for (int j = 0; j < 3; j++){                                        //새로운 pattern을 쓴다 (회전된 걸 쓴다)
            gameMap[y + i][x + j] -= tmp[i][j];
            gameMap[y + i][x + j] += pattern[i][j];
        }
    }
}

void inactivate(){                                                          //활성 블럭(1, 2, 3, 4)를 비활성블럭(5, 6, 7, 8)로 만들어준다.
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 6; j++){
            if(gameMap[i][j] > 0 && gameMap[i][j] < 5){
                gameMap[i][j] += 4;
                collisionMap[i][j] = gameMap[i][j];                         //활성블럭이 되면 충돌판정을 받는 블럭이된다. 따라서 collisionMap을 업데이트해준다.
            }
        }
    }
}

void patternGenerate(){
    setCoordinate(2, 0);                                                    //패턴이 생성되면 생성된 위치로 옮겨간다.
    
    int blockType = rand()%3;                                               //패턴이 3가지중 랜덤하게 타입이 결정된다.
    
    for (int i = 0; i < 3; i++){                                            //패턴이결정되면 패턴배열에 가져온다.
        for (int j = 0; j < 3; j++){
            pattern[i][j] = 0;
            pattern[i][j] = patternList[blockType][i][j] * (rand()%4 + 1);  //패턴의 각 블럭들은 빨강, 초록, 파랑, 회색에서 랜덤하게 결정됨
        }
    }
    
    for (int i = 0; i < 3; i++){                                             //생성된 패턴을 게임맵 위에 올린다.
        for (int j = 0; j < 3; j++){
            if (gameMap[i][j + 2] >= 1)                                      //배치 가능한지 검사해서 이미 블럭이 배치되어있다면, 즉 놓을 수 없다면 gameover
                gameover = true;
            gameMap[i][j + 2] = collisionMap[i][j + 2] + pattern[i][j];      //그게 아니라면 패턴으로 만들어진걸 배치한다.
        }
    }
}

void spawnPattern(){
    if (!isCollide(x, y + 1)){                                               //현재 블럭의 좌표 밑에 충돌할게없다면 기본적으로 그 패턴은 내려가야한다.
        movePattern(x, y + 1);
    }
    else{                                                                    //그러나 충돌할 게 있다면 현재 패턴을 비활성화시키고 새로운 블럭을 생성시킨다.
        inactivate();                                                        //충돌하여 비활성화되면 이후로 개별 블럭들이 중력의 영향을 받아 움직이게된다.
        patternGenerate();                                                   //patternGenerate가 되면 새로운 패턴이 초기 좌표에 만들어지고 이후 입력에 의해 움직이는건 그 패턴이다.
    }
}

void clearVisited(){                                                        //방문한 블럭 배열을 false로 초기화한다.
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            visited[i][j] = false;
        }
    }
}

void clearFound(){                                                          //찾아진 x와 y좌표의 벡터를 비운다.
    while(!foundX.empty()){
        foundX.pop_back();
        foundY.pop_back();
    }
}


void scan(){                                                                //map을 스캔하며 폭발 조건을 만족하는 블럭들이 있는지 확인, 있다면 제거하고 점수를 준다.
    if(comboInterval == 0)                                                  //콤보인터벌이 0에 도달하면 기본점수만 얻을 수 있다.
        combo = 1;
    
    bool exploded = false;                                                  //폭발할 블럭이 있는지를 확인할 bool 변수
    
    for(int i = 2; i < HEIGHT - 1; i++){
        for(int j = 1; j < WIDTH - 1; j++){                                 //blockMap을 순회한다. 터질 수 있는 블럭의 맵인 blockMap을 확인하도록 한다.
            
            if(blockMap[i][j] != 8)                                         //8은 회색블럭이다. 회색블럭은 다른 블럭이 터질 때 함께 터질수는 있지만 개별적으로 터질수는 없으므로 제외한다.
                sameColorChecker(i, j, blockMap[i][j]);                     //해당위치의 블럭과 좌표로 재귀적으로 근처 블럭들을 확인하도록 한다.
            
            if(foundX.size() >= 4){                                         //해당 좌표에 대한 인접 블럭들의 스캔이 끝났을 때 찾아진 블럭의 수가 4개 이상이라면 폭발 조건을 만족한다.
                for(int i = 0; i < foundX.size(); i++){                     //이후엔 폭발하게될 블럭들 주위의 인접한 회색블럭을 찾아준다. 이 회색 블럭들도 재귀적으로 찾아준다.
                    adjacentGreyChecker(foundY.at(i) + 1, foundX.at(i));
                    adjacentGreyChecker(foundY.at(i) - 1, foundX.at(i));
                    adjacentGreyChecker(foundY.at(i), foundX.at(i) + 1);
                    adjacentGreyChecker(foundY.at(i), foundX.at(i) - 1);
                }
                
                for(int i = 0; i < foundX.size(); i++){
                    debugMessage("EXPLODE " + std::to_string(foundX.at(i)) + ", " + std::to_string(foundY.at(i)));
                }
                
                while(!foundX.empty()){                                     //회색블럭까지 찾아졌다면 찾아진 좌표 벡터가 비워질때까지 좌표를 비워내며 해 좌표의 블럭을 폭파시킨다.
                    int targetX = foundX.back();
                    int targetY = foundY.back();
                    foundX.pop_back();
                    foundY.pop_back();
                    explode(targetX, targetY);                              //찾아진 블럭들을 폭파시킨다.
                }
                exploded = true;                                            //조건을 만족하여 블럭을 제거했기 때문에 exploded 는 true로 값이 변경된다.
            }
            clearFound();                                                   //만약 4개 미만의 좌표만 찾아졌다면 좌표 벡터에 값이 남아있게된다. 따라서 다음 탐색에서 찾을 좌표들을 위해 비워준다.
        }
    }                                                                       //모든 블럭들에 대해서 순회를 마치면 해당 턴에서 폭파되어야할 블럭은 모두 폭파가 된 상태다.
    clearVisited();                                                         //다음 스캔을 위해 방문 여부 배열을 초기화해준다.
    
    if(exploded){                                                           //만약 폭파된 블럭이 있었다면
        comboInterval = 5;                                                  //이후 5턴 안에 다른 폭발이 있다면 콤보로 인정되도록 인터벌을 설정해준다.
        score += combo;                                                     //현재 콤보 횟수만큼 점수에 추가해준다.
        std::cout<<BOLD(FCYN("COMBO ")) + std::to_string(combo)<<std::endl;
        if(comboRecord < combo){                                            //현재 콤보가 콤보 기록을 넘어섰다면 새로운 콤보 기록으로 설정해준다.
            comboRecord = combo;
            std::cout<<BOLD(FCYN("NEW RECORD!"))<<std::endl;
        }
        combo++;                                                            //다음 콤보를 위해 콤보를 증가시켜준다.
    }
    else                                                                    //콤보를 성공시키지 못했다면 인터벌을 하나씩 줄여준다.
        comboInterval--;
}

void explode(int targetX, int targetY){                                     //맵에서 인자로 주어진 좌표에 해당하는 블럭을 제거해버린다.
    gameMap[targetY][targetX] = collisionMap[targetY][targetX] = blockMap[targetY][targetX] = 0;
}

void adjacentGreyChecker(int currentI, int currentJ){                       //인접한 회색 블럭을 찾아준다.
    int currentValue = blockMap[currentI][currentJ];
    if(visited[currentI][currentJ] == false && currentValue == 8){          //현재블럭이 찾아진블럭이 아니고 값이 8이라면(회색블럭이라면)
        visited[currentI][currentJ] = true;                                 //찾아진것으로 표시해주고
        debugMessage("ADJACENT GREY FOUND ... I : " + std::to_string(currentI) + ", J : " + std::to_string(currentJ) + ", COLOR : " + std::to_string(blockMap[currentI][currentJ]));
        foundX.push_back(currentJ);                                         //폭파될 블럭좌표로 추가해준다.
        foundY.push_back(currentI);
        adjacentGreyChecker(currentI + 1, currentJ);                        //추가로 회색 주변에 회색이 더 있다면 함께 터지도록 재귀적으로 상하좌우를 확인하도록 한다.
        adjacentGreyChecker(currentI -1, currentJ);
        adjacentGreyChecker(currentI, currentJ + 1);
        adjacentGreyChecker(currentI, currentJ - 1);
    }
}

void sameColorChecker(int currentI, int currentJ, int checkingColor){       //해당 좌표오 색으로 근처에 폭파시킬 블럭이 있는지 확인한다.
    int currentValue = blockMap[currentI][currentJ];                        //찾아지지 않았으며 비활성화블럭이면서 확인하는 색상과 동일한 색상의 블럭이 찾아지면
    if(visited[currentI][currentJ] == false && (currentValue > 4 && currentValue < 9) && currentValue == checkingColor){
        visited[currentI][currentJ] = true;                                 //찾아진것으로 표시하고
        debugMessage("SAME COLOR FOUND ... I : " + std::to_string(currentI) + ", J : " + std::to_string(currentJ) + ", COLOR : " + std::to_string(blockMap[currentI][currentJ]));
        foundX.push_back(currentJ);                                         //폭파될 블럭좌표로 추가해준다.
        foundY.push_back(currentI);
        sameColorChecker(currentI + 1, currentJ, checkingColor);            //추가로 인접한 블럭중 동일한 색의 블럭이 있는지 재귀적으로 확인하도록 한다.
        sameColorChecker(currentI - 1, currentJ, checkingColor);
        sameColorChecker(currentI, currentJ + 1, checkingColor);
        sameColorChecker(currentI, currentJ - 1, checkingColor);
    }
}
