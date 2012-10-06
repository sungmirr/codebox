/*++
    2012.10.06

    31.2 Class Template(367p, PosValueTemp)
     - 클래스 템플릿에서 멤버함수 정의
     - 클래스 템블릿의 객체 생성
        템플릿 클래스의 클래스명은 <>을 붙혀준다. 단 생성자 예외
        class PosValue2 : public PosValue<int> { ... }
     - 클래스 템플릿의 경우 선언부(*.h)와 구현부(*.cpp)를 따로 정의하면 안된다, 같이(*.h)에 정의
       main.cpp에서 선언부만 include하는 경우 컴파일 단계에 구체화되지 못함

       일반 함수: 컴파일시 원형만 선언한 후 컴파일 가능하고, 링크할 때 바인딩
       템플릿 : 컴파일 할때 완변하게 구체화되야함
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
    // 클래스 템플릿 멤버함수의 내부선언
    /*        
    void OutValue()
    {
        gotoxy(x,y);
        cout << value << endl;
    }
    */

};

// 클래스 템플릿 멤버함수의 외부선언
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