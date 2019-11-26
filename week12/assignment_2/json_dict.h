//
// Created by 김혁진 on 2019/11/19.
//

#ifndef JSON_DICT_H
#define JSON_DICT_H

#include "json_object.h"
#include <vector>

class json_dict : public json_object {
private:
    std::vector<std::pair<json_object*, json_object*> > v;
    void put(json_object* key, json_object* val);
    int find(json_object* key);
public:
    json_dict();
    static json_object* parse(const char *, int length);	//key value를 유의하면서 파싱?작은따옴표 혹은 큰따옴표 -> string parse, spacebar 는 continue처리 파싱하다 콜론나오면 파싱된게 key가됨을 알 수 있음 
    json_object* operator[](json_object* key) const;
    json_object* operator[](const std::string& key) const;
    json_object* operator[](int key) const;
	//다양한 key값으로 요소를 찾기위한것

    _type type();
    std::string to_string();
};


#endif // JSON_DICT_H
