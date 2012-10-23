/*++
    2012.10.20

    40.�����������̳�, ��������ǿ��(743p)

    vector<Time>
     - �Ϲ����� ��ü�� ����� Ŭ �� �����Ƿ�
       ���Ϳ� ���� ��ü�� �����ϴ� �ͺ��� ��ü�� �����͸� �����ϴ°��� ���ɻ� �����ϸ� �Ϲ���
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
/* <<�����ڸ� ������ �Ϲ������� ����� dump�Լ��� �����ϰ� �ض�
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
    dump("��� 2��", vt);
}