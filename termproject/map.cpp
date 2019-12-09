#include<iostream>
#include"map.h"

map::map(){
	this->initMap();
}

void map::printMap(){
	std::cout<<""<<std::endl;
	for(int height = 0; height < MAP_HEIGHT; height++){
		for(int width = 0; width < MAP_WIDTH; width++){
			std::cout<<this->tileMap[width][height]<<"\t";
		}
		std::cout<<""<<std::endl;
	}
}

void map::initMap(){
	for(int height = 0; height < MAP_HEIGHT; height++){
		for(int width = 0; width < MAP_WIDTH; width++){
			this->tileMap[width][height] = 'x';
		}
	}
}

bool map::generateBlock(char newBlock, int xCoordinate){
	this->tileMap[xCoordinate][0] = newBlock;
}
