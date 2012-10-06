/*++
    2012.10.06

    31.1 Specialization, 특수화(364p)
        - template함수에서 특정 타입에 대해서만 다르게 동작하도록 하고싶을 때 사용
        - ex)Swap 템플릿 함수에서 double에 대해서는 정수부분만 교환하게 정의
          ex)Add 템플릿 함수에서 char *에 대해서는 문자열을 연결하게 정의

        - 템플릿 함수보다 특수화된 함수가 우선순위가 앞선다
        - 선언법
          template <> void Swap<double>(double &a, double &b)
          template <> void Swap<>(double &a, double &b)
          template <> void Swap(double &a, double &b)

          void Swap<double>(double &a, double &b)  // 비표준..
          void Swap(double &a, double &b) // 일반 함수를 Swap으로 정의... 우선순위에 문제가 생길 수 있다
 --*/

#include "Turboc.h"

template <typename T>
void Swap(T &a, T &b)
{
    T t;
    t=a; a=b; b=t;
}

template <> void Swap<double>(double &a, double &b)
{
    int i,j;

    i = (int)a;
    j = (int)b;

    a=a-i+j;
    b=b-j+i;
}

void main()
{
    double a=1.2, b=3.4;
    printf("a=%f, b=%f\n", a, b);
    Swap(a,b);
    printf("a=%f, b=%f\n", a, b);
}