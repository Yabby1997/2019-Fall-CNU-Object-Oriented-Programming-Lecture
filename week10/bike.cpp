#include<iostream>
#include "bike.h"

bike::bike() : vehicle() {
	this->set_bike_name("NO NAME");
	this->set_bike_number(0);
}

bike::bike(int given_wheel_number, int given_max_speed) : vehicle(given_wheel_number, given_max_speed){
	this->set_bike_name("NO NAME");
	this->set_bike_number(0);
}

bike::bike(int given_wheel_number, int given_max_speed, char* given_bike_name) : vehicle(given_wheel_number, given_max_speed){
	this->set_bike_name(given_bike_name);
	this->set_bike_number(0);
}

bike::bike(int given_wheel_number, int given_max_speed, char* given_bike_name, int given_bike_number) : vehicle(given_wheel_number, given_max_speed){
	this->set_bike_name(given_bike_name);
	this->set_bike_number(given_bike_number);
}

bike::bike(int given_wheel_number, int given_max_speed, char* given_bike_name, int given_bike_number, bool given_has_name) : vehicle(given_wheel_number, given_max_speed, given_has_name){
	this->set_bike_name(given_bike_name);
	this->set_bike_number(given_bike_number);
}

const char* bike::get_class_name(){
	return "bike";
}

char* bike::get_bike_name(){
	return this->bike_name;
}

int bike::get_bike_number(){
	return this->bike_number;
}

void bike::set_bike_name(char* new_bike_name){
	this->bike_name = new_bike_name;
}

void bike::set_bike_number(int new_bike_number){
	this->bike_number = new_bike_number;
}
