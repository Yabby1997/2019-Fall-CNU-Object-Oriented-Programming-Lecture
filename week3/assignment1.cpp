#include<iostream>

using namespace std;

void test(){									//code영역에 할당되는 주소를 위해 함수를 선언했다.
	cout<<"TEST!"<<endl;
}

const int test2 = 999;							//rodata영역에 할당되는 주소를 위해 상수를 선언했다.
int test3 = 999;								//data영역에 할당되는 주소를 위해 전역변수를 선언했다.
int test4;										//bss영역에 할당되는 주소를 위해 전역변수를 선언하고 초기화하지 않았다.
	
int main(void){
	int * test5 = new int(3);					//heap영역에 할당되는 주소를 위해 new 키워드를 통해 메모리 동적할당했다.
	int test6 = 999;							//stack영역에 할당되는 주소를 위해 지역변수를 선언했다.
	cout<<"code\t"<<(void *)test<<endl;
	cout<<"rodata\t"<<&test2<<endl;
	cout<<"data\t"<<&test3<<endl;
	cout<<"bss\t"<<&test4<<endl;
	cout<<"heap\t"<<test5<<endl;
	cout<<"stack\t"<<&test6<<endl;
	return 0;
}
