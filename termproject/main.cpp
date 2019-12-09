#include<iostream>
#include"game.h"

int main(){
	game *newGame = new game();
	while(newGame->getValidity()){
		newGame->refreshGame();	
		if(newGame->getNumberOfInputs() == 5)
			newGame->setValidity(false);
	}
	std::cout<<"GAME OVER"<<std::endl;
	return 0;
}
