/*++
    2012.10.17

    38.함수객체 (657p)  
    - 함수객체는 타입이므로 템플릿의 인수로 사용될 수 있지만, 
      함수포인터는 단순한 값일뿐이므로 템플릿의 인수로 사용할 수 없다

--*/

#include <iostream>
using namespace std;

template <typename T>
class SomeClass {};

struct print
{
    void operator()(int a) const
    {
        printf("%d\n", a);
    }
};

void func(int a)
{
    printf("%d\n", a);
}

void main()
{
    SomeClass<print> s1; // 가능
//  SomeClass<func> s2;  // 불가능
}