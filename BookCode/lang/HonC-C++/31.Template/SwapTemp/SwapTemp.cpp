/*++
    2012.10.06

    31.1 함수템플릿(348p)
        - 함수템플릿 선언
 --*/

#include "Turboc.h"

// swap함수에 지역적으로 선언된 변수에 대해서는 사용할수없다.
// 그래서 tag_st를 전역으로 선언
struct tag_st
{
    int i; 
    double d;
};


// 매크로 함수는 전처리기가 처리
#define MakeSwap(T) \
void swap(T &a, T &b) \
{ \
    T t; \
    t=a,a=b,b=t; \
}

MakeSwap(int)
MakeSwap(double)
MakeSwap(char)
MakeSwap(tag_st)


// 템플릿은 컴파일러가 처리
//template <typename T>
//void swap(T &a, T &b);  // 템플릿 함수의 선언
template <typename T>
void swap(T &a, T &b)
{
    T t;
    t=a;
    a=b;
    b=t;
}

void main()
{
    int a=3, b=4;
    double c=1.2, d=3.4;
    char e='e', f='f';
    tag_st g={1, 2.3}, h={4, 5.6};

    swap(a,b);
    swap(c,d);
    swap(e,f);
    printf("g={%d, %f}, h={%d, %f}\n", g.i, g.d, h.i, h.d);
    swap(g,h);
    printf("g={%d, %f}, h={%d, %f}\n", g.i, g.d, h.i, h.d);
    
}
