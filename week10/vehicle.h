#ifndef VEHICLE_H
#define VEHICLE_H

#include<iostream>

class vehicle{
protected:
	bool has_name;
	int wheel_number;
	int max_speed;
public :
	vehicle();
	vehicle(int given_wheel_number, int given_max_speed);
	vehicle(int given_wheel_number, int given_max_speed, bool given_has_name);
	int get_wheel_number();
	int get_max_speed();
	bool get_has_name();
	virtual const char* get_class_name();
	void set_wheel_number(int new_wheel_number);
	void set_max_speed(int new_max_speed);
	void set_has_name(bool new_has_name);
};

#endif
