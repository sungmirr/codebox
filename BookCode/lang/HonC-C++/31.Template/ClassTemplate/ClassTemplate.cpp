/*++
    2012.10.06

    31.2 Class Template(367p, PosValueTemp)
     - Ŭ���� ���ø����� ����Լ� ����
     - Ŭ���� �ۺ��� ��ü ����
        ���ø� Ŭ������ Ŭ�������� <>�� �����ش�. �� ������ ����
        class PosValue2 : public PosValue<int> { ... }
     - Ŭ���� ���ø��� ��� �����(*.h)�� ������(*.cpp)�� ���� �����ϸ� �ȵȴ�, ����(*.h)�� ����
       main.cpp���� ����θ� include�ϴ� ��� ������ �ܰ迡 ��üȭ���� ����

       �Ϲ� �Լ�: �����Ͻ� ������ ������ �� ������ �����ϰ�, ��ũ�� �� ���ε�
       ���ø� : ������ �Ҷ� �Ϻ��ϰ� ��üȭ�Ǿ���
 --*/

#include "Turboc.h"
#include <iostream>

using namespace std;

template <typename T>
class PosValue
{
private:
    int x,y;
    T value;

public:
    PosValue(int x_, int y_, T v_) : x(x_), y(y_), value(v_) {}
    //PosValue<T>(int x_, int y_, T v_) : x(x_), y(y_), value(v_) {}
    void OutValue();
    // Ŭ���� ���ø� ����Լ��� ���μ���
    /*        
    void OutValue()
    {
        gotoxy(x,y);
        cout << value << endl;
    }
    */

};

// Ŭ���� ���ø� ����Լ��� �ܺμ���
template <typename T>
void PosValue<T>::OutValue()
{
    gotoxy(x,y);
    cout << value << endl;
}

/////
typedef PosValue<long> LongPosValue;

void main()
{
    PosValue<int> iv(1, 1, 2);
    PosValue<char> cv(5, 1, 'C');
    PosValue<double> dv(20, 3, 3.14);

    LongPosValue lv(30, 4, 100);

    iv.OutValue();
    cv.OutValue();
    dv.OutValue();
    lv.OutValue();
}