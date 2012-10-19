/*++
    2012.10.17

    38.함수객체, 함수객체의 종류 (666p)  
    
    Gen     : 인수없음, bool이 아닌 리턴값, Generator.. 예를들어 난수 생성하는 함수객체가 생성기
    UniOp   : 단항, bool이 아닌 리턴값
    BinOP   : 이항, bool이 아닌 리턴값
    UniPred : 단한, bool리턴   ex) bool Pred(T &val) {}
    BinPred : 이항, bool리턴

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