/*++
    2012.10.19

    38.�Լ���ü, ����Լ������ (687p)  

    mem_fun
    - Ŭ������ ����Լ��� ��ü�� ����� cf) ptr_fun�� �Ϲ��Լ��� ��ü�� �����
    - ����Լ� �����͸� ĸ��ȭ�Ͽ� �Լ� ��ü�� ����� ��ü�� �����ϸ� 
      �� ��ü��()�����ڸ� ���� �����̳ʿ� ����� �� ��ü ������(this)�� �Բ� ����Լ��� ȣ��ȴ�
    - ����Լ��� ���� ���۴� �μ��� ������ �ʴ� ����Լ�, �μ� �ϳ��� ���ϴ� ����Լ��� ���� ���� �ۼ��� �ִ�
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
        // mem_fun(����Լ�������)
        it = find_if(it, vn.end(), mem_fun(&Natural::IsEven));
        //it = find_if(it, vn.end(), Natural());
        //it = find_if(it, vn.end(), Natural::functor_even());
        if(it == vn.end()) break;
        cout << (*it)->GetNum() << "��(��) �ִ�" << endl;
    }

    for_each(vn.begin(), vn.end(), delnatural);
}