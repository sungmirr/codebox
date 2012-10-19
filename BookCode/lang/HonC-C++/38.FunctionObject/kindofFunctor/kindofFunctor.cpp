/*++
    2012.10.17

    38.�Լ���ü, �Լ���ü�� ���� (666p)  
    
    Gen     : �μ�����, bool�� �ƴ� ���ϰ�, Generator.. ������� ���� �����ϴ� �Լ���ü�� ������
    UniOp   : ����, bool�� �ƴ� ���ϰ�
    BinOP   : ����, bool�� �ƴ� ���ϰ�
    UniPred : ����, bool����   ex) bool Pred(T &val) {}
    BinPred : ����, bool����

--*/

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

// UniOp
void functor1(int a)
{
    printf("%d ", a);
}

// UniOp
struct functor2
{
    void operator()(double a) const
    {
        printf("%f\n", a);
    }
};

void main()
{
    int ari[]={1,2,3,4,5};
    vector<int> vi(&ari[0], &ari[5]);
    double ard[]={1.2, 3.4, 5.6, 7.8, 9.9};
    list<double> ld(&ard[0], &ard[5]);

    for_each(vi.begin(), vi.end(), functor1);
    cout << endl;
    for_each(ld.begin(), ld.end(), functor2());
}