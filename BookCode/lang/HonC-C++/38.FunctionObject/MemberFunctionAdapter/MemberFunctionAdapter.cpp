/*++
    2012.10.19

    38.함수객체, 멤버함수어댑터 (687p)  

    mem_fun
    - 클래스의 멤버함수를 객체로 만든다 cf) ptr_fun은 일반함수를 객체로 만든다
    - 멤버함수 포인터를 캡슐화하여 함수 객체로 만드는 개체를 생성하며 
      이 객체의()연산자를 통해 컨테이너에 저장된 각 객체 포인터(this)와 함께 멤버함수가 호출된다
    - 멤버함수에 대한 래퍼는 인수를 취하지 않는 멤버함수, 인수 하나를 취하는 멤버함수에 대해 각각 작성되 있다
--*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Natural
{
private:
    int num;

public:
    Natural() {}
    Natural(int anum) : num(anum)
    {
        SetNum(anum);
    }

    void SetNum(int anum)
    {
        if(anum >=0)
            num=anum;
    }

    int GetNum() { return num; }
    bool IsEven() { return num%2==0; }
    bool operator()(Natural *n) const
    {
        return n->num%2 == 0;
    }

    struct functor_even
    {
        bool operator()(const Natural *n) const
        {
            return n->num%2 == 0;
        }
    };
};

void delnatural(Natural* pn)
{
    delete pn;
}

void main()
{
    vector<Natural *> vn;
    vn.push_back(new Natural(1));
    vn.push_back(new Natural(2));
    vn.push_back(new Natural(3));
    vn.push_back(new Natural(4));

    vector<Natural *>::iterator it;
    for(it=vn.begin();; ++it)
    {
        // mem_fun(멤버함수포인터)
        it = find_if(it, vn.end(), mem_fun(&Natural::IsEven));
        //it = find_if(it, vn.end(), Natural());
        //it = find_if(it, vn.end(), Natural::functor_even());
        if(it == vn.end()) break;
        cout << (*it)->GetNum() << "이(가) 있다" << endl;
    }

    for_each(vn.begin(), vn.end(), delnatural);
}