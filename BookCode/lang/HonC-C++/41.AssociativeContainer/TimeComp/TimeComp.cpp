/*++
    2012.10.23

    40. 연관컨테이너, 사용자정의 함수 객체 사용(785p)

    
    set에 사용자정의 함수 객체(BinPred)를 사용하여 정렬

    template<class _Kty, class _Pr = less<_Kty>, class _Alloc = allocator<_Kty> >
    class set

--*/

#include <iostream>
#include <set>
#include <functional>
using namespace std;

class Time
{
    friend struct TimeComp;
protected:
    int hour,min,sec;
public:
    Time(int h,int m,int s) { hour=h;min=m;sec=s; }
    void OutTime() 
    { 
        printf("%d:%d:%d\n",hour,min,sec); 
    }
};

struct TimeComp : binary_function<Time, Time, bool>
{
    bool operator()(const Time& a, const Time& b) const
    {
        return (a.hour*3600+a.min*60+a.sec < b.hour*3600+b.min*60+b.sec);
    }
};

void main()
{
    // set의 디폴트 생성자는 
    // TimeComp의 디폴트생성자를 호출하여 비교객체를 만들고 
    // 비교가 필요할때마다 ()연산자를 호출
    set<Time, TimeComp> Times;              
    set<Time, TimeComp>::iterator it;

    Times.insert(Time(1,1,1));
    Times.insert(Time(9,8,7));
    Times.insert(Time(2,3,4));

    for(it=Times.begin(); it!=Times.end(); ++it)
        (*it).OutTime();
}

