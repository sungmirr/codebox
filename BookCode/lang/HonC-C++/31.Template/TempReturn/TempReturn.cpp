/*++
    2012.10.06

    31.1.2 명시적 인수지정(354p)

    - 인수가 고정된 타입의 템플릿 함수의 경우 
      명시적으로 타입을 지정해줘야한다

    - 호환되는 타입의 템플릿 함수의 구체화를 줄일때
      산술 변환 되어도 상관없는 실인수만 가능

    - 템플릿함수의 명시적구체화
      당장 사용하진 않지만 캄파일된 라이브러리로 제공하고 싶을때
      템플릿 선언 보다 뒤에
--*/

#include "turboc.h"
#include <iostream>

using namespace std;

template <typename T>
T cast(int s)
{
    return (T)s;
}

template <typename T>
void func(void)
{
    T v;

    cin >> v;
    cout << v << endl;
}

template <typename T>
void LongFunc(T a)
{
    //... 긴 본체
    cout << a;
}

// 템플릿 함수의 명시적 구체화
template void LongFunc<float>(float);
// 템플릿 클래스의 명시적 구체화
// template class PosValue<float>;

void main()
{
    // 1.
    unsigned i = cast<unsigned>(1234);
    double d = cast<double>(5678);

    printf("i=%d, d=%f\n", i, d);
    func<int>();

    //2 .
    int ii=1;
    unsigned u=2;
    long l=3;

    LongFunc<int>(ii);
    LongFunc<int>(u);
    LongFunc<int>(l);
}