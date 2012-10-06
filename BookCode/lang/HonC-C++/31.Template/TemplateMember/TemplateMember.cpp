/*++
    2012.10.06

    31.2 Template Member (370p, TempMember)
      클래스의 템플릿 멤버함수 정의
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
    // 템플릿 멤버 함수
#if 0
    template <typename T>
    void memfunc(T a)
    {
        cout << "템플릿인수 =" << a << " mem = " << mem << endl;
    }
#endif
    template <typename T>
    void memfunc(T a);
};

template <typename T>
void Some::memfunc(T a)
{
    cout << "템플릿인수 =" << a << " mem = " << mem << endl;
}

void main()
{
    Some s(9999);

    s.memfunc(1234);
    s.memfunc(1.2345);
    s.memfunc("string");
}
