/*++
    2012.10.06

    31.1.2 ����� �μ�����(354p)

    - �μ��� ������ Ÿ���� ���ø� �Լ��� ��� 
      ��������� Ÿ���� ����������Ѵ�

    - ȣȯ�Ǵ� Ÿ���� ���ø� �Լ��� ��üȭ�� ���϶�
      ��� ��ȯ �Ǿ ������� ���μ��� ����

    - ���ø��Լ��� �������üȭ
      ���� ������� ������ į���ϵ� ���̺귯���� �����ϰ� ������
      ���ø� ���� ���� �ڿ�
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
    //... �� ��ü
    cout << a;
}

// ���ø� �Լ��� ����� ��üȭ
template void LongFunc<float>(float);
// ���ø� Ŭ������ ����� ��üȭ
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