#include<iostream>

int main(){
	char * a = "ABCDEFGHIJKLMNOP";
	char b[] = "ABCDEFGHIJKLMNOP";				//사이즈 17bite의 char 배열

	//a[0] = 'b';
	//std::cout<<a<<std::endl;
	//std::cout<<b<<std::endl;
	std::cout<<sizeof(a)<<std::endl;			//사이즈를 확인해보기 위해 sizeof함수를 이용, 두 변수의 사이즈를 확인해본다.
	std::cout<<sizeof(b)<<std::endl;
}
