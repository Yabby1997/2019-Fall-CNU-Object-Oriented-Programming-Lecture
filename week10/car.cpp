#include<iostream>
#include "car.h"

car::car() : vehicle() {
	this->set_car_name("NO NAME");
}

car::car(int given_wheel_number, int given_max_speed) : vehicle(given_wheel_number, given_max_speed){
	this->set_car_name("NO NAME");
}

car::car(int given_wheel_number, int given_max_speed, char* given_car_name) : vehicle(given_wheel_number, given_max_speed){
	this->set_car_name(given_car_name);
}

car::car(int given_wheel_number, int given_max_speed, char* given_car_name, bool given_has_name) : vehicle(given_wheel_number, given_max_speed, given_has_name){
	this->set_car_name(given_car_name);
}

const char* car::get_class_name(){
	return "car";
}

char* car::get_car_name(){
	return this->car_name;
}

void car::set_car_name(char* new_car_name){
	this->car_name = new_car_name;
}
