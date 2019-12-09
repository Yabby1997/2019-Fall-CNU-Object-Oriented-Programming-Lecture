#include<stdio.h>
#include<iostream>
#include<unistd.h>
#include<termios.h>
#include"game.h"

//constructor
game::game(){
	this->gameMap = new map();
	this->gameScore = 0;
	this->numberOfInputs = 0;
	this->isValid = true;
}

//getter & setter
int game::getScore(){
	return this->gameScore;
}

int game::getNumberOfInputs(){
	return this->numberOfInputs;
}

bool game::getValidity(){
	return this->isValid;
}

void game::setValidity(bool newValidity){
	this->isValid = newValidity;
}
//end of getter & setter

void game::refreshGame(){
    this->showSeparator();
    char inputChar = this->inputCommand();
    this->showInfo(inputChar);
    this->showSeparator();
    this->gameMap->generateBlock(inputChar, 3); 
    this->gameMap->printMap();
    this->showSeparator();
}

void game::showInfo(char inputChar){
	std::cout<<"score : "<<this->getScore()<<std::endl;
	std::cout<<"log   : ["<<this->getNumberOfInputs()<<"] input ["<<inputChar<<"]"<<std::endl;
}

void game::showSeparator(){
	std::cout<<"=================================="<<std::endl;
}

char game::inputCommand(){
	this->numberOfInputs++;
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
