#include<iostream>
#include<string>
#include"json_object.h"
#include"json_list.h"
#include"json_dict.h"
#include"data/Integer.h"
#include"data/String.h"
#include<vector>

json_list::json_list(){
}

json_object::_type json_list::type(){
	return json_object::LIST;
}

std::string json_list::to_string(){
	std::string returnString = "[";
	for(auto iter = v.begin(); iter < v.end(); iter++){
		returnString = returnString + (*iter)->to_string();
		if(iter + 1 != v.end())
			returnString = returnString + ", ";
	}
	returnString = returnString + "]";
	return returnString;
}

json_object* json_list::parse(const char* inputArray, int length){
	json_list* newList = new json_list();
	for(json_object::_index; inputArray[json_object::_index] != 93; json_object::_index++){
		while(inputArray[json_object::_index] == 32 || inputArray[json_object::_index] == 44)
			json_object::_index++;
		if(inputArray[json_object::_index] == 93)
			break;
		json_object* newElement = json_object::parse(inputArray, length);
		//std::cout<<"! LIST ELEMENT FOUND\t"<<json_object::_index<<"\t"<<inputArray[json_object::_index]<<std::endl;
		newList->v.push_back(newElement);
	}
	//std::cout<<"! END OF LIST\t"<<json_object::_index<<std::endl;
	return newList;
}

json_object* json_list::operator[](int key) const{
	return v.at(key);
}
