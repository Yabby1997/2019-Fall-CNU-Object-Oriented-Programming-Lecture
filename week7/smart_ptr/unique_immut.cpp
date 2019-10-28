//
// Created by 김혁진 on 14/10/2019.
//

#include "unique_immut.h"

namespace ptr {
unique_immut::unique_immut() {
    _mgr = new mgr();
}

unique_immut::unique_immut(Object *obj) {
    _mgr = new mgr(obj);
}

unique_immut::unique_immut(const unique_immut &immut) {
    if (immut._mgr) {
        int val = immut._mgr->ptr->get();
        _mgr = new mgr(val);
    }
}

unique_immut::~unique_immut(){
	this->release();
}

Object* unique_immut::get() const{
	return this->_mgr->ptr;
}

void unique_immut::release(){
	this->_mgr->count--;
	if(this->_mgr->count == 0){
		this->_mgr->~mgr();
	}
}

unique_immut unique_immut::operator+(unique_immut &unique){
	int value = this->_mgr->ptr->get();
	value = value + unique._mgr->ptr->get();
	this->release();
	unique.release();
	return unique_immut(new Object(value));
}

unique_immut unique_immut::operator-(unique_immut &unique){
	int value = this->_mgr->ptr->get();
	value = value - unique._mgr->ptr->get();
	this->release();
	unique.release();
	return unique_immut(new Object(value));
}

unique_immut unique_immut::operator*(unique_immut &unique){
     int value = this->_mgr->ptr->get();
     value = value * unique._mgr->ptr->get();
     this->release();
     unique.release();
     return unique_immut(new Object(value));
}

unique_immut unique_immut::operator/(unique_immut &unique){
     int value = this->_mgr->ptr->get();
     value = value / unique._mgr->ptr->get();
     this->release();
     unique.release();
     return unique_immut(new Object(value));
}

unique_immut& unique_immut::operator=(unique_immut& r){
     this->release();
     this->_mgr = r._mgr;
     return *this;
}

Object* unique_immut::operator->(){
    return this->_mgr->ptr;
}

} // end of namespace ptr
