/*++
    2012.10.06

    31.1 Specialization, Ư��ȭ(364p)
        - template�Լ����� Ư�� Ÿ�Կ� ���ؼ��� �ٸ��� �����ϵ��� �ϰ���� �� ���
        - ex)Swap ���ø� �Լ����� double�� ���ؼ��� �����κи� ��ȯ�ϰ� ����
          ex)Add ���ø� �Լ����� char *�� ���ؼ��� ���ڿ��� �����ϰ� ����

        - ���ø� �Լ����� Ư��ȭ�� �Լ��� �켱������ �ռ���
        - �����
          template <> void Swap<double>(double &a, double &b)
          template <> void Swap<>(double &a, double &b)
          template <> void Swap(double &a, double &b)

          void Swap<double>(double &a, double &b)  // ��ǥ��..
          void Swap(double &a, double &b) // �Ϲ� �Լ��� Swap���� ����... �켱������ ������ ���� �� �ִ�
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