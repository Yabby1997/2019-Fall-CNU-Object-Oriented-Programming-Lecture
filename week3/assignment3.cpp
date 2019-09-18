#include<iostream>

int main(){
	char target[] = "Yang Seunghun";
	long b[22];									//long 자료형 8bite. 학번 201602022 -> 끝자리 3개는 022 
	int a = 17;									//int 자료형 4bite
	int i = 210;								//int 자료형 4bite
	int *c = new int[602];						//pointer 8bite
	char * copy = "is no no";					//pointer 8bite
	char name = 'a';							//char 자료형 1bite
	std::cout << &name+i << std::endl;			//배열의 이름은 배열의 첫번째 원소의 주소와 같다.
	return 0;
}

