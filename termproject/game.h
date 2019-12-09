#ifndef GAME_H
#define GAME_H
#include"map.h"

class game{
private : 
	map *gameMap;
	int gameScore;
	int numberOfInputs;
	bool isValid;

public :
	game();
	int getScore();
	int getNumberOfInputs();
	bool getValidity();
	void setValidity(bool newValidity);
	void refreshGame();
	char inputCommand();
	void showInfo(char inputChar);
	void showSeparator();
};

#endif
