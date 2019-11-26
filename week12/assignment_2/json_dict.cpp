#include<iostream>
#include<string>
#include<cstring>
#include"json_object.h"
#include"json_dict.h"
#include"data/String.h"
#include"data/Integer.h"

json_dict::json_dict(){
}

void json_dict::put(json_object* key, json_object* val){
	if(this->find(key) == -1){
		v.push_back(std::make_pair(key, val));
	}
	else{
		v.at(this->find(key)).second = val;
	}
}

int json_dict::find(json_object* key){
	for(int index = 0; index < v.size(); index++){
		//std::cout<<"! CHECKING INDEX "<<index<<std::endl;
		if(strcmp((v.at(index).first->to_string()).c_str(), (key->to_string()).c_str()) == 0){
			//std::cout<<"! SAME KEY FOUND AT "<<index<<std::endl;
			return index;
		}
	}
	//std::cout<<"! SAME KEY NOT FOUND"<<std::endl;
	return -1;
}

json_object::_type json_dict::type(){
   return DICT;
}

std::string json_dict::to_string(){
	std::string returnString = "{";
	for(auto iter = v.begin(); iter < v.end(); iter++){
        returnString = returnString + (iter->first->to_string() + ":" + iter->second->to_string());
		if(iter + 1 != v.end())
			returnString = returnString + ", ";
    }
	returnString = returnString + "}";
	return returnString;
}

json_object* json_dict::parse(const char* inputArray, int length){
	json_dict* newDict = new json_dict();
    for(json_object::_index; inputArray[json_object::_index] != 125; json_object::_index++){
		json_object* newKey = json_object::parse(inputArray, length);
		//std::cout<<"! DICT KEY FOUND\t"<<json_object::_index<<std::endl;
		json_object::_index++;
		json_object* newVal = json_object::parse(inputArray, length);
		//std::cout<<"! DICT VAL FOUND\t"<<json_object::_index<<std::endl;
		newDict->put(newKey, newVal);
	}
	//std::cout<<"! END OF DICT"<<std::endl;
	return newDict;
}
                    
json_object* json_dict::operator[](json_object* key) const{
	for(auto iter = v.begin(); iter < v.end(); iter++){
		if(strcmp(iter->first->to_string().c_str(), key->to_string().c_str()) == 0){
			return iter->second;
		}
	}
	return nullptr;
}

json_object* json_dict::operator[](const std::string& key) const{
	json_object* temp = new String(key);
	for(auto iter = v.begin(); iter< v.end(); iter++){
		if(strcmp(iter->first->to_string().c_str(), temp->to_string().c_str()) == 0){
			return iter->second;
		}
	}
	return nullptr;
}

json_object* json_dict::operator[](int key) const{
	json_object* a = new Integer(key);
	for(auto iter = v.begin(); iter < v.end(); iter++){
		if(strcmp(iter->first->to_string().c_str(), std::to_string(key).c_str()) == 0){
			return iter->second;
		}
	}
	return nullptr;
}
