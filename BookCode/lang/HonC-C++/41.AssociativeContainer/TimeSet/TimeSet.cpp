/*++
    2012.10.23

    40. 연관컨테이너, 객체의 집합(783p)

    set 디폴트 비교 함수 객체가 less(<)로 지정되 있다
    set에서 사용하는 비교 삼수 객체의 연산자를 제공해줘야 한다 
    (ex..greater일 경우 >연산자)

--*/

#include <iostream>
#include <set>
#include <functional>
using namespace std;

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
    bool operator>(const Time &T) const
    {
        return (hour*3600+min*60+sec > T.hour*3600+T.min*60+T.sec);
    }
};

void main()
{
    set<Time> Times;
    set<Time>::iterator it;

    Times.insert(Time(1,1,1));
    Times.insert(Time(9,8,7));
    Times.insert(Time(2,3,4));

    for(it=Times.begin(); it!=Times.end(); ++it)
        (*it).OutTime();


    cout << "-------------------------------------------------" << endl;
    set<Time, greater<Time> > GTimes;
    set<Time, greater<Time> >::iterator git;
    GTimes.insert(Time(1,1,1));
    GTimes.insert(Time(9,8,7));
    GTimes.insert(Time(2,3,4));

    for(git=GTimes.begin(); git!=GTimes.end(); ++git)
        (*git).OutTime();
}