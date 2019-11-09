#ifndef CAR_H
#define CAR_H

#include<iostream>
#include "vehicle.h"

class car : public vehicle{
private : 
	char* car_name;
public :
	car();
	car(int given_wheel_number, int given_max_speed);
	car(int given_wheel_number, int given_max_speed, char* given_car_name);
	car(int given_wheel_number, int given_max_speed, char* given_car_name, bool given_has_name);
	char* get_car_name();
	void set_car_name(char* new_car_name);
	const char* get_class_name() override;
};

#endif
