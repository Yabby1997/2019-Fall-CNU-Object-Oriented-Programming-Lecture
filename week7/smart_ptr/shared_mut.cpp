//
// Created by 김혁진 on 14/10/2019.
//

#include "shared_mut.h"

namespace ptr {

void shared_mut::increase(){
	this->_mgr->count++;
}

shared_mut::shared_mut(const shared_mut &shared){
	_mgr = shared._mgr;
	increase();
}

shared_mut::shared_mut() {
    _mgr = new mgr();
}

shared_mut::shared_mut(Object* obj){
	_mgr = new mgr(obj);
}

shared_mut::~shared_mut(){
	this->release();
}

Object* shared_mut::get() const{
	return this->_mgr->ptr;
}

void shared_mut::release(){
	this->_mgr->count--;
	if(this->_mgr->count == 0){
		this->_mgr->~mgr();
	}
	this->_mgr = new mgr();
}

int shared_mut::count(){
	return this->_mgr->count;
}

shared_mut shared_mut::operator+(const shared_mut &shared){
	int value = this->_mgr->ptr->get();
	value = value + shared._mgr->ptr->get();
	return shared_mut(new Object(value));
}

shared_mut shared_mut::operator-(const shared_mut &shared){
	int value = this->_mgr->ptr->get();
	value = value - shared._mgr->ptr->get();
	return shared_mut(new Object(value));
}

shared_mut shared_mut::operator*(const shared_mut &shared){
	int value = this->_mgr->ptr->get();
	value = value * shared._mgr->ptr->get();
	return shared_mut(new Object(value));
}

shared_mut shared_mut::operator/(const shared_mut &shared){
	int value = this->_mgr->ptr->get();
	value = value / shared._mgr->ptr->get();
	return shared_mut(new Object(value));
}

shared_mut& shared_mut::operator=(const shared_mut &shared){
	this->release();
	this->_mgr = shared._mgr;
	this->increase();
	return *this;
}

Object* shared_mut::operator->(){
	return this->_mgr->ptr;
}

}
