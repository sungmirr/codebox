/*++
    2012.10.17

    38.함수객체, 어댑터 (671p)  
    
    ========================================================================================================
    어댑터의 종류
    - 컴포넌트 어댑터(component adapter) : 스택, 큐, 우선순위 큐
    - 반복자 어댑터(iterator adapter) : 역방향 반복자
    - 함수객체 어댑터(functor adapter) : 부정자, 바인더, 함수포인터어댑터

    함수객체 어댑터
    - 함수 객체의 기능을 변형하기 위해 인수타입과 반환값의 타입이 필요함
    - 그래서 STL에서는 functional 헤더 파일에 unary_function, binary_function 템플릿 클래스를 정의함
    - 어댑터블함수객체(Adaptable Functor)를 만들려면 적절한 템플릿 클래스를 상속받아 정의

    어댑터블 함수객체
    - 함수객체의 인수타입과 반환값을 argument_type과 result_type등의 이름으로 획일화하여 타입 정의
    - 아래 두 템플릿 클래스를 상속받으면 미리 약속된 이름으로 정의되어 어댑터는 약속된 이름으로 해당 
      정보를 쉽게 얻는다
    template<class Arg, class Result>
    struct unary_function
    {
        typedef Arg argument_type;
        typedef Result result_type;
    }
    template<class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    }

    plus, greater등의 미리 제공되는 함수객체들은 모두 어댑터블 함수객체이다
    ========================================================================================================

    부정자
    - bool을 리턴하는 조건자 함수 객체의 평가 결과를 반대로 뒤집는 함수객체
    - not1 : UniPred에 적용
      not2 : BinPred에 적용

    바인더
    - 사용하고자 하는 함수 객체의 항이 요구되는 함수 객체와 다를때 바인더 어댑터 사용
    - 이항 함수 객체의 나머지 한 인수를 특정한 값으로 고정하여 단항 함수 객체로 변환 
      bind1st(이항객체, 고정값)
      bind2nd(이항객체, 고정값)

    함수 포인터 어댑터
    - 일반 함수의 번지인 함수 포인터를 함수 객체처럼 포장
    - 함수포인터는 객체가 아니므로 어댑터에 적용할 수 없다
      ptr_fun

    cf>
    greater<int>() : 두값을 비교하여 앞의 값이 뒤의 값보다 더 큰지를 조사하는 이항 조건자
    less_equal<int>() : 단항 조건자로 이하의 조건을 점검
    

    책에 어댑터 구현 방식....확인!!!!
--*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

// unary adaptable functor
struct IsMulti3 : public unary_function<int, bool>
{
    // typedef int argument_type;
    // typedef bool result_type;
    bool operator()(const int a) const
    {
        return (a%3 == 0);
    }
};


// binary adaptable funtor
// string을 대소문자 구분없이 오름차순 정렬
struct compare : public binary_function<string, string, bool>
{
    bool operator()(const string &a, const string &b) const
    {
        return stricmp(a.c_str(), b.c_str()) < 0;
    }
};

// 이항조건자
struct IsMulti : public binary_function<int,int,bool>
{
    bool operator()(const int a, const int b) const
    {
        return (a%b == 0);
    }
};

// 함수포인터
bool IsMultiFunc(int a, int b)
{
    return (a%b == 0);
}


void main()
{
    int ari[]={1,2,3,4,5,6,7,8,9,10};
    vector<int> vi(&ari[0],&ari[10]);
    vector<int>::iterator it;

    for(it=vi.begin();;++it)
    {
        it = find_if(it, vi.end(), IsMulti3());
        if(it==vi.end()) break;
        cout << *it << "이(가) 있다" << endl;
    }

    // IsMulti3의 리턴값을 뒤집어 3의 배수가 아님 원소를 출력
    cout << "-------------------------------" << endl;
    for(it=vi.begin();;++it)
    {
        it = find_if(it, vi.end(), not1(IsMulti3()));
        if(it==vi.end()) break;
        cout << *it << "이(가) 있다" << endl;
    }

    // not2
    cout << "-------------------------------" << endl;
    string names[]={"STL","MFC","owl","html","pascal","Ada",
        "Delphi","C/C++","Python","basic"};
    vector<string> vs(&names[0],&names[10]);

    sort(vs.begin(), vs.end(), not2(compare()));
    vector<string>::iterator vIt;
    for(vIt=vs.begin(); vIt!=vs.end(); ++vIt)
        cout << *vIt << endl;

    // 이항객체 IsMulti
    cout << "-------------------------------" << endl;
    IsMulti IM;
    if(IM(6,3))
        cout << "6은 3의 배수이다." << endl;
    if(IM(9,2))
        cout << "9는 2의 배수이다." << endl;

    // bind2nd
    // 이상조건자를 단항조건자로 변경
    cout << "bind2nd-------------------------------" << endl;
    for(it=vi.begin();;++it)
    {
        // IsMulti의 두번째 인수를 3으로 고정하여 단항조건자로 변환 
        //it=find_if(it, vi.end(), bind2nd(IsMulti(), 3));
        //it=find_if(it, vi.end(), bind2nd(greater<int>(), 5));
        //it=find_if(it, vi.end(), bind2nd(less_equal<int>(),5));   // less_equal은 단항조건자
        it=find_if(it, vi.end(), not1(bind2nd(less_equal<int>(),5)));
        if(it==vi.end()) break;
        cout << *it << "이(가) 있다" << endl;
    }   

    // 함수포인터를 함수객체로 변환하는 어댑터
    cout << "ptr_fun-------------------------------" << endl;
    for(it=vi.begin();;++it)
    {
        it = find_if(it, vi.end(), bind2nd(ptr_fun(IsMultiFunc), 3));
        if(it == vi.end()) break;
        cout << *it << "이(가) 있다" << endl;
    }
}