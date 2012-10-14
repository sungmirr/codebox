/*++
    2012.10.14

    36.표준라이브러리, string(612p)

    compare
    int __CLR_OR_THIS_CALL compare(const _Myt& _Right) const
    int __CLR_OR_THIS_CALL compare(size_type _Off, size_type _N0,const _Myt& _Right) const
    int __CLR_OR_THIS_CALL compare(size_type _Off,
                size_type _N0, const _Myt& _Right,
                size_type _Roff, size_type _Count) const
--*/

#include <iostream>
#include <string>
using namespace std;

void main()
{
    string s1("aaa");
    string s2("bbb");
    cout << (s1==s1 ? "같다" : "다르다") << endl;
    cout << (s1==s2 ? "같다" : "다르다") << endl;
    cout << (s1>s2 ? "크다" : "안크다") << endl;

    string s3("1234567");
    string s4("1234999");
    cout << (s3.compare(s4)==0 ? "같다":"다르다") << endl;
    cout << (s3.compare(0,4,s4,0,4)==0 ? "같다":"다르다") << endl;

    string s5("hongkildong");
    cout << (s5=="hongkildong"?"같다":"다르다") << endl;
    // ==연산자는 전역 연산자 함수로 정의되있다
    // cout << ("hongkildong"==s5?"같다":"다르다") << endl;
}