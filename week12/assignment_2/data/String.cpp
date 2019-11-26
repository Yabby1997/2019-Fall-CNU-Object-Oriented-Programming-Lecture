#include<iostream>
#include<string>
#include<cstring>
#include"String.h"
#include<vector>

String::String(const std::string& str){
	this->set_val(str);
}

std::string String::val(){
	return this->_val;
}

void String::set_val(const std::string& str){
	this->_val = str;
}

json_object::_type String::type(){
	return STRING;
}

std::string String::to_string(){
	std::string returnString = "\'";
	returnString = returnString + this->val() + "\'";
	return returnString;
}

json_object* String::parse(const char* inputArray, int length, char base){
	std::vector<char> a = {};
	while(inputArray[json_object::_index] != base){
		a.push_back(inputArray[json_object::_index]);
		json_object::_index++;
	}
	std::string output(a.begin(), a.end());
	//std::cout<<"STRING -> "<<output<<"\t"<<json_object::_index<<std::endl;
	return new String(output);
}
