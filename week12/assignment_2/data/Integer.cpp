#include<iostream>
#include<string>
#include<cstring>
#include"Integer.h"
#include<vector>

Integer::Integer(int value){
	this->set_val(value);
}

json_object* Integer::parse(const char* inputArray, int length){
	std::vector<char> a = {};
	while(inputArray[json_object::_index] >= 48 && inputArray[json_object::_index] <= 57){
		a.push_back(inputArray[json_object::_index]);
		json_object::_index++;
	}
	json_object::_index--;
	std::string output(a.begin(), a.end());
	//std::cout<<"INTEGER -> "<<output<<"\t"<<json_object::_index<<std::endl;
	return new Integer(atoi(output.c_str()));
}

int Integer::val(){
	return this->_val;
}

void Integer::set_val(const int& value){
	this->_val = value;
}

json_object::_type Integer::type(){
	return INT;
}

std::string Integer::to_string(){
	return std::to_string(this->val());
}
