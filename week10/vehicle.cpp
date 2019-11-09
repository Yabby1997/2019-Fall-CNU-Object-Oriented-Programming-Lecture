#include<iostream>
#include "vehicle.h"

vehicle::vehicle(){
	this->set_wheel_number(0);
	this->set_max_speed(0);
	this->set_has_name(false);
}

vehicle::vehicle(int given_wheel_number, int given_max_speed){
	this->set_wheel_number(given_wheel_number);
	this->set_max_speed(given_max_speed);
	this->set_has_name(false);
}

vehicle::vehicle(int given_wheel_number, int given_max_speed, bool given_has_name){
	this->set_wheel_number(given_wheel_number);
	this->set_max_speed(given_max_speed);
	this->set_has_name(given_has_name);
}

int vehicle::get_wheel_number(){
	return this->wheel_number;
}

int vehicle::get_max_speed(){
	return this->max_speed;
}

bool vehicle::get_has_name(){
	return this->has_name;
}

const char* vehicle::get_class_name(){
	return "vehicle";
}

void vehicle::set_wheel_number(int new_wheel_number){
	this->wheel_number = new_wheel_number;
}

void vehicle::set_max_speed(int new_max_speed){
	this->max_speed = new_max_speed;
}

void vehicle::set_has_name(bool new_has_name){
	this->has_name = new_has_name;
}

