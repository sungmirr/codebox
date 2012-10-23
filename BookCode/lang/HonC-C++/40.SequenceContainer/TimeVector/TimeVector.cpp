/*++
    2012.10.20

    40.시퀀스컨테이너, 사용자정의요소(743p)

    vector<Time>
     - 일반적인 객체는 대단히 클 수 있으므로
       벡터에 직접 객체를 저장하는 것보다 객체의 포인터를 저장하는것이 성능상 유리하며 일반적
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

/*
template<typename C> 
void dump(const char *desc, const C& c) 
{ 
    cout.width(12);
    cout << left << desc << "==> ";
    copy(c.begin(),c.end(),ostream_iterator<typename C::value_type>(cout," ")); 
    cout << endl; 
}
*/

template <typename C>
void dump(const char *desc, C& c)
{
    cout.width(12);
    cout << left << desc << "==>";
#if 0
    for(int i=0; i < c.size(); ++i)
        c[i].OutTime();
#else
    typename C::iterator it;
    for(it=c.begin(); it!=c.end(); ++it)
        it->OutTime();
#endif
    cout << endl;
}


void main()
{
    vector<Time> vt;
    vt.push_back(Time(1,1,1));
    vt.push_back(Time(2,2,2));
    dump("요소 2개", vt);
}