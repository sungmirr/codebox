/*++
    2012.10.20

    40.시퀀스컨테이너, 사용자정의요소(745p)

    vector<Time *>
     - 일반적인 객체는 대단히 클 수 있으므로
       벡터에 직접 객체를 저장하는 것보다 객체의 포인터를 저장하는것이 성능상 유리하며 일반적
     - 포인터 벡터의 구성.. [Time* eletment, Time* element]
     - 종료전 벡터의 요소를 해제
--*/ 

#include <iostream>
#include <vector>
using namespace std;

class Time
{
protected:
    int hour,min,sec;
public:
    Time(int h, int m, int s) : hour(h), min(m),sec(s) {}
    void OutTime()
    {
        printf("%d:%d:%d ", hour, min, sec);
    }
/* <<연산자를 정의해 일반적으로 사용한 dump함수가 가능하게 해라
    void operator<<()
    {
        OutTime();
    }
    */
};

template <typename C>
void dump(const char *desc, C& c)
{
    cout.width(12);
    cout << left << desc << "==>";
#if 0
    for(int i=0; i < c.size(); ++i)
        c[i]->OutTime();            // 벡터요소가 포인터라 포인터연산
#else
    typename C::iterator it;
    for(it=c.begin(); it!=c.end(); ++it)
        (*it)->OutTime();           // 벡터요소가 포인터라 포인터연산
#endif
    cout << endl;
}


void main()
{
    vector<Time *> vt;

    vt.push_back(new Time(1,1,1));
    vt.push_back(new Time(2,2,2));
    dump("요소2개", vt);

    vector<Time *>::iterator it;
    for(it=vt.begin(); it!=vt.end(); ++it)
        delete *it;                // 벡터요소를 해체, *it가 포인터다.... [Time *element1, Time *element2]
}