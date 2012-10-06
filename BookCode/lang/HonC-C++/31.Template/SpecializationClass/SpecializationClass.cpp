/*++
    2012.10.06

    31.2 SpecializationClass(378p)
     - PosValue를 tag_friend 자료형 전용으로 특수화 (정석은 tag_friend에 <<연산자함수 정의)
     - tempalte <> class PosValue<tag_Friend>
     - 특수화된 클래스는 객체를 선언하지 않더라도 자동으로 구체화된다.
       즉, 클래스가 정의가 만들어지고 멤버 함수들은 컴파일 되어 실행파일에 포함된다
       따라서 특수화된 클래스에 대한 정의는 일반적인 템플릿 클래스와는 달리 
       헤더 파일에 작성해서는 안되며 구현 파일에 작성해야 한다
     
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
    void OutValue();
};

template <typename T>
void PosValue<T>::OutValue()
{
    gotoxy(x,y);
    cout << value << endl;
}

struct tag_Friend
{
    char name[10];
    int age;
    double height;
};

// 특수화
template <> class PosValue<tag_Friend>
{
private:
    int x,y;
    tag_Friend value;
public:
    PosValue(int x_, int y_, tag_Friend v_) : x(x_), y(y_), value(v_) {}
    void OutValue();
};

void PosValue<tag_Friend>::OutValue()
{
    gotoxy(x,y);
    cout << "이름" << value.name << " 나이" << value.age << " 키" << value.height << endl;
}

void main()
{
    PosValue<int> iv(1,5,10);
    tag_Friend tf ={"아무개", 25, 177.7};
    PosValue<tag_Friend> tv(5, 6, tf);
    iv.OutValue();
    tv.OutValue();;
}
