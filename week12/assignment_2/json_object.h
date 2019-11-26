//
// Created by 김혁진 on 2019/11/19.
//

#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <string>
#include <iostream>

class json_object {
protected:
    enum _type {
        // Structure type
        DICT,
        LIST,

        // Data type
        INT,
        STRING
    };

    static int _index;
	static json_object* parse(const char * inputArray, int length);		//char	배열로 만들고 길이를 전달해서 얘로 보냄 각각의 parse를 호출만해주는애? 확인하고있는 인덱스를 공유하기위해 static index를 만든것? string이 새로 들어올때마다 인덱스는 초기화가 되어야한다. 
public:
    static json_object* parse(const std::string& inputString);				//얘가 스트링을 받는다. 그리고 프로텍티드 parse로 옮김 
    virtual _type type() = 0;
    virtual std::string to_string() = 0;
};

#endif // JSON_OBJECT_H
