/*
 *	2019 Fall OOP Term Project
 *	201602022 SEUNGHUN YANG
 */

#ifndef MAP_H
#define MAP_H

#define MAP_HEIGHT 12
#define MAP_WIDTH 5

class map{
public :	
	char tileMap[MAP_WIDTH][MAP_HEIGHT] = {0, };
	map();
	void printMap();
	void initMap();
	bool generateBlock(char newBlock, int xCoordinate);
};

#endif
