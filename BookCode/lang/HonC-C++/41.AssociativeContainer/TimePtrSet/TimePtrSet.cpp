/*++
    2012.10.23

    40. ���������̳�, ��ü�� ������ ����(786p)

    �¿� ��ü�� ������ ����
    - ����Ʈ ���� �����Ҷ� �����͸� �������� less ��..���ĵǱ⶧���� �ǹ̰� ����
    - <�����ڸ� �����ε� �� ��� Ŭ������ �⺻������ ����ǹǷ� ����
    - �Լ���ü�� �����ؼ� set<PtrObject *, �����Լ���ü>�� ��ü ����
    

    cf)
    ��ü�� �����͸� �����̳ʿ� ����� �����̳ʰ� �����ϴ� �˰���
    ���밡���� �����ڸ� ����������Ѵ�.. �� �� ����Լ��ǿ����ڿ������̵���
    �Ϲ� Ŭ������ ������ �����ؾ� �ϹǷ� �Լ���ü�� �ʿ��� ������ ����

--*/


#include <iostream>
#include <set>
#include <functional>
using namespace std;


// set<Time>�� ���밡���ϰ� ���ʷ��ϰ� ����
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