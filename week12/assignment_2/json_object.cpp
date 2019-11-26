#include<iostream>
#include<string.h>
#include"json_object.h"
#include"json_dict.h"
#include"json_list.h"
#include"data/String.h"
#include"data/Integer.h"

int json_object::_index = 0;

json_object* json_object::parse(const std::string& inputString){
	json_object::_index = 0;
	char inputArray[inputString.size() + 1];
	strcpy(inputArray, inputString.c_str());
	return json_object::parse(inputArray, inputString.size());
}

json_object* json_object::parse(const char * inputArray, int length){
	json_object* returnObject;
	for(json_object::_index; json_object::_index < length; json_object::_index++){
		char target = inputArray[json_object::_index];
		if(target == 123){
			//std::cout<<"DICT CALLED\t"<<json_object::_index<<std::endl;
			json_object::_index++;
			return json_dict::parse(inputArray, length);
		}
		else if(target == 91){
			//std::cout<<"LIST CALLED\t"<<json_object::_index<<std::endl;
			json_object::_index++;
			return json_list::parse(inputArray, length);
		}
		else if(target == 32){
			//std::cout<<"BLANK CALLED\t"<<json_object::_index<<std::endl;
			json_object::_index++;
			return json_object::parse(inputArray, length);
		}
		else if(target == 44){
			//std::cout<<"COMMA CALLED\t"<<json_object::_index<<std::endl;
			json_object::_index++;
			return json_object::parse(inputArray, length);
		}
		else if(target == 58){
			//std::cout<<"COLLON CALLED\t"<<json_object::_index<<std::endl;
			json_object::_index++;
			return json_object::parse(inputArray, length);
		}
		else if(target == 39){
			//std::cout<<"STRING CALLED\t"<<json_object::_index<<std::endl;
			json_object::_index++;
			return String::parse(inputArray, length, 39);
		}
		else if(target == 34){
			//std::cout<<"STRING CALLED\t"<<json_object::_index<<std::endl;
			json_object::_index++;
			return String::parse(inputArray, length, 34);
		}
		else{
			//std::cout<<"INTEGER CALLED\t"<<json_object::_index<<std::endl;
			return Integer::parse(inputArray, length);
		}
	}
	return nullptr;
}
