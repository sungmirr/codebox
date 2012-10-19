/*++
    2012.10.17

    38.함수객체, 미리 정의된 함수객체(662p) 
    - functional 헤더파일에 함수객체와 그 지원 매크로, 타입등이 정의

    <미리 정의된 함수객체의 리스트>
    plus            두 인수의 합을 계산 후 리턴
    minus           
    multiplies
    divides
    modulus
    negate          인수 하나를 전달받아 부호를 반대로
    eqaul_to        두 안수가 같인지 비교하여 결과를 bool타입으로 리턴
    not_eqaul_to    
    greater         첫번째 인수가 두번째 인수보다 큰지 조사
    less
    greater_equal
    less_eaual
    logical_and     두 인수의 논리곱(&&) 결과를 리턴
    logical_or
    logical_not     인수 하나를 전달받아 논리부정(!)을 리턴


    void sort(RanIt first, RanIt last);         // <연산자로 대소를 비교하므로 올림차순 정렬
    void sort(RanIt first, RanIt last, BinPred F);  // BinPred : bool리턴, 이항

--*/
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;


// 대소문자 구분없이 알파벳순으로 문자열을 오름차순으로 정렬
struct compare
{
    bool operator()(const string &a, const string &b) const
    {
        return stricmp(a.c_str(), b.c_str()) < 0;
    }
};

void main()
{
    int a=1,b=2;
    int c;

    // plus<int> P;
    // c = P(a,b);
    c = plus<int>()(a,b);   // 디폴트생성자 호출문으로 임시객체를 생성
                            // 생성된 임시객체에서 ()연산자 호출
    cout << c << endl;
    

    cout << "--------------------------------" << endl;
    string names[]={"STL","MFC","owl","html","pascal","Ada",
        "Delphi","C/C++","Python","basic"};
    vector<string> vs(&names[0],&names[10]);

    //sort(vs.begin(), vs.end());                       // <연산자.. 오름차순
    sort(vs.begin(), vs.end(), greater<string>());      // >연산자.. 내림차순

    vector<string>::iterator it;
    for(it=vs.begin(); it!=vs.end(); ++it)
        cout << *it << endl;


    cout << "--------------------------------" << endl;
    sort(vs.begin(), vs.end(), compare());
    for(it=vs.begin(); it!=vs.end(); ++it)
        cout << *it << endl;
}