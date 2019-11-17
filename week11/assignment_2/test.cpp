//
// Created by 김혁진 on 2019/11/12.
//

#include "Integer.h"
#include "Float.h"
#include "Complex.h"
#include <iostream>

int main() {
    // 이번 과제는 테스트 코드를 주지 않습니다.
    // 직접 코드를 작성해보면서 확인해보세요
    {
        Number *a = new Integer(13);
        Number *result = a->add(new Float(3.14));

        std::cout << dynamic_cast<Float *>(result)->val() << std::endl; // 16.14
    }
    {
        Number *a = new Integer(3);
        Number *result = a
                ->add(new Float(3.14))
                ->sub(new Integer(1))
                ->mul(new Integer(7))
                ->sub(new Complex(11, 5));

        std::cout << dynamic_cast<Complex *>(result)->to_string() << std::endl; // 24.980000 - 5.000000i
    }
	{
		Number *a = new Integer(3);
		Number * result = a
				->add(new Integer(1))			//4
				->sub(new Integer(2))			//2
				->mul(new Integer(5))			//7
				->div(new Integer(7))			//1
				->add(new Float(1.1))			//2.1 (Float으로 변환)
				->sub(new Float(0.1))			//2.0
				->mul(new Integer(3))			//6.0 (여전히 Float)
				->mul(new Float(5.5))			//33.0
				->div(new Float(1.1))			//30.0
				->add(new Complex(3.3, 2.5))	//33.3 + 2.5i (Complex로 변환)
				->sub(new Complex(3.3, 1.25))	//30.0 + 1.25i
				->mul(new Complex(3.3, 1.25))	//97.4375 + 41.625i
				->div(new Complex(3.3, 1.25));	//30.0 + 1.25i
		std::cout<<dynamic_cast<Complex*>(result) ->to_string()<<std::endl;
	}
    // 테스트 코드 작성해보고 확인해보세요
    // 채점은 임의의 테스트코드로 진행할 예정입니다

    return 0;
}
