/*++
    2012.10.17

    38.함수객체 (651p)
    - 알고리즘 함수는 동작 중에 사용자의 개입이 필요한 부분에 대해 함수 객체를 호출하여 의사를 결정
    - 함수객체(FunctionObject or Functor)는 함수포인터나 함수객체일 수 있다
    - 함수객체는 함수 호출연산자인()를 오버로딩한 객체를 의미, 이 연산자를 통해 마치 함수를 호출하듯이 객체를 호출

    함수포인터에 비해 함수객체가 가지는 장점
    - 인라인이 가능해서 처리속도가 빠르다(클래스 내부에선언된 멤버함수는 자동으로 인라인 되며 호출부에 본체 코드가 삽입)
    - 연산자함수()뿐 아니라 다른 멤버변수,멤버함수, 생성자, 파괴자를 가질 수 있다
    - 함수객체는 타입이므로 템플릿의 인수로 사용될 수 있지만, 함수 포인터는 단순한 값일뿐이므로 템플릿의 인수로 사용할 수 없다

    _Fn1 for_each(_InIt _First, _InIt _Last, _Fn1 _Func)
    UniOp for_each(InIt first, InIt last, UniOp op);
    
--*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// 1. 함수포인터
void print(int a)
{
    printf("%d\n", a);
}


// 2. 함수객체
struct fo_print
{
    void operator()(const int a) const
    {
        printf("%d\n", a);
    }
};

// 3. 함수객체의 멤버함수 활용
struct accum
{
    int sum;
    accum() : sum(0) {}
    void operator()(const int a) 
    {
        sum+=a;
    }

};

// 4. 함수객체의 생성자 활용
struct fo_print_ct
{
    string mes;
    fo_print_ct(const string &m) : mes(m) {} 
    void operator()(int a) const
    {
        cout << mes << a << endl;
    }
};


void main()
{
    int ari[]={2,3,5,1,9};
    vector<int> vi(&ari[0], &ari[5]);
    
    sort(vi.begin(), vi.end());

    // 1. 함수객체로 함수포인터 사용
    for_each(vi.begin(), vi.end(), print);

    // 2. 함수객체 사용
    //fo_print f;                               // 함수객체를 f를 생성한 후  for_each에 전달
    //for_each(vi.begin(), vi.end(), f);        // for_each함수 내부에서 f의 ()연산자를 호출     
    for_each(vi.begin(), vi.end(), fo_print()); // fo_print()는 객체를 호출하는것이 아니라, 임시객체를 생성하는 문장

    // 3.
    accum ac;
    ac = for_each(vi.begin(), vi.end(), ac);
    printf("총합=%d\n", ac.sum);

    // 4.
    for_each(vi.begin(), vi.end(), fo_print_ct(string("요소값은")));
    for_each(vi.begin(), vi.end(), fo_print_ct(string("다른 메시지")));
}