#ifndef BIKE_H
#define BIKE_H

#include<iostream>
#include "vehicle.h"

class bike : public vehicle{
private : 
	char* bike_name;
	int bike_number;
public :
	bike();
	bike(int given_wheel_number, int given_max_speed);
	bike(int given_wheel_number, int given_max_speed, char* given_bike_name);
	bike(int given_wheel_numver, int given_max_speed, char* given_bike_name, int given_bike_number);
	bike(int given_wheel_number, int given_max_speed, char* given_bike_name, int given_bike_number, bool given_has_name);
	char* get_bike_name();
	int get_bike_number();
	void set_bike_name(char* new_bike_name);
	void set_bike_number(int new_bike_number);
	const char* get_class_name() override;
};

#endif
