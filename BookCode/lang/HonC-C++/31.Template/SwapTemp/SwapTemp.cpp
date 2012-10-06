/*++
    2012.10.06

    31.1 �Լ����ø�(348p)
        - �Լ����ø� ����
 --*/

#include "Turboc.h"

// swap�Լ��� ���������� ����� ������ ���ؼ��� ����Ҽ�����.
// �׷��� tag_st�� �������� ����
struct tag_st
{
    int i; 
    double d;
};


// ��ũ�� �Լ��� ��ó���Ⱑ ó��
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


// ���ø��� �����Ϸ��� ó��
//template <typename T>
//void swap(T &a, T &b);  // ���ø� �Լ��� ����
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
