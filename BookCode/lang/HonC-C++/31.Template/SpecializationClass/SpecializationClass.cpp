/*++
    2012.10.06

    31.2 SpecializationClass(378p)
     - PosValue�� tag_friend �ڷ��� �������� Ư��ȭ (������ tag_friend�� <<�������Լ� ����)
     - tempalte <> class PosValue<tag_Friend>
     - Ư��ȭ�� Ŭ������ ��ü�� �������� �ʴ��� �ڵ����� ��üȭ�ȴ�.
       ��, Ŭ������ ���ǰ� ��������� ��� �Լ����� ������ �Ǿ� �������Ͽ� ���Եȴ�
       ���� Ư��ȭ�� Ŭ������ ���� ���Ǵ� �Ϲ����� ���ø� Ŭ�����ʹ� �޸� 
       ��� ���Ͽ� �ۼ��ؼ��� �ȵǸ� ���� ���Ͽ� �ۼ��ؾ� �Ѵ�
     
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

// Ư��ȭ
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
    cout << "�̸�" << value.name << " ����" << value.age << " Ű" << value.height << endl;
}

void main()
{
    PosValue<int> iv(1,5,10);
    tag_Friend tf ={"�ƹ���", 25, 177.7};
    PosValue<tag_Friend> tv(5, 6, tf);
    iv.OutValue();
    tv.OutValue();;
}
