/*++
    2012.10.23

    40. 연관컨테이너, 객체의 포인터 집합(786p)

    셋에 객체의 포인터 저장
    - 디폴트 셋은 정렬할때 포인터를 기준으로 less 비교..정렬되기때문에 의미가 없다
    - <연산자를 오버로딩 할 경우 클래스의 기본구조가 변경되므로 비추
    - 함수객체를 정의해서 set<PtrObject *, 이항함수객체>로 객체 정렬
    

    cf)
    객체의 포인터를 컨테이너에 적용시 컨테이너가 제공하는 알고리즘에
    적용가능한 연산자를 제공해줘야한다.. 이 때 멤버함수의연산자오버라이딩은
    일반 클래스의 구조를 변경해야 하므로 함수객체로 필요한 연산자 제공

--*/


#include <iostream>
#include <set>
#include <functional>
using namespace std;


// set<Time>에 적용가능하게 제너럴하게 구성
class Time
{
protected:
    int hour, min, sec;
public:
    Time(int h, int m, int s) : hour(h), min(m), sec(s) {}
    void OutTime()
    {
        printf("%d:%d:%d\n", hour, min, sec);
    }
    bool operator<(const Time &T) const
    {
        return (hour*3600+min*60+sec < T.hour*3600+T.min*60+T.sec);
    }
};

struct Timeless : public binary_function<const Time*, const Time*, bool>
{
    bool operator()(const Time* A, const Time* B)
    {
        return *A < *B;
    }
};

void main()
{
    set<Time *, Timeless> Times;
    set<Time *, Timeless>::iterator it;

    Times.insert(new Time(1,1,1));
    Times.insert(new Time(9,8,7));
    Times.insert(new Time(2,3,4));

    for(it=Times.begin(); it!=Times.end(); ++it)
        *it->OutTime();         //(**it).OutTime();

    for(it=Times.begin(); it!=Times.end(); ++it)
        delete *it;
}