/*++
    2012.10.06

    31.2 Template Member (370p, TempMember)
      Ŭ������ ���ø� ����Լ� ����
 --*/

#include "Turboc.h"
#include <iostream>

using namespace std;

class Some
{
private:
    int mem;

public:
    Some(int m) : mem(m) {}
    // ���ø� ��� �Լ�
#if 0
    template <typename T>
    void memfunc(T a)
    {
        cout << "���ø��μ� =" << a << " mem = " << mem << endl;
    }
#endif
    template <typename T>
    void memfunc(T a);
};

template <typename T>
void Some::memfunc(T a)
{
    cout << "���ø��μ� =" << a << " mem = " << mem << endl;
}

void main()
{
    Some s(9999);

    s.memfunc(1234);
    s.memfunc(1.2345);
    s.memfunc("string");
}
