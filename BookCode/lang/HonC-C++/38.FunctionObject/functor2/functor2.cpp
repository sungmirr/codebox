/*++
    2012.10.17

    38.�Լ���ü (657p)  
    - �Լ���ü�� Ÿ���̹Ƿ� ���ø��� �μ��� ���� �� ������, 
      �Լ������ʹ� �ܼ��� ���ϻ��̹Ƿ� ���ø��� �μ��� ����� �� ����

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
    SomeClass<print> s1; // ����
//  SomeClass<func> s2;  // �Ұ���
}