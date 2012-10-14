/*++
    2012.10.14

    36.표준라이브러리, string(605p)

    string의 
    operator= , operator+=, operator+ 연산자
    assign, append
        _Myt& __CLR_OR_THIS_CALL assign(const _Myt& _Right,size_type _Roff, size_type _Count)
        _Myt& __CLR_OR_THIS_CALL append(const _Myt& _Right,size_type _Roff, size_type _Count)
    copy, swap
        size_type __CLR_OR_THIS_CALL copy(_Elem *_Dest,size_type _Count, size_type _Off = 0) const
    insert, erase
        string의 임의의 위치에 문자열, string을 삽입한다. cf)append는 첫번째 인수가 size()인 insert함수
        _Myt& __CLR_OR_THIS_CALL erase(size_type _Off = 0, size_type _Count = npos)
    replace
        _Myt& __CLR_OR_THIS_CALL replace(size_type _Off, size_type _N0, const _Elem *_Ptr)
    substr
        _Myt __CLR_OR_THIS_CALL substr(size_type _Off = 0, size_type _Count = npos) const  
--*/

#include "Turboc.h"
#include <iostream>
#include <string>
using namespace std;

void main()
{
    string s1("야호 신난다.");
    string s2;

    // operator=연산자
    s2="임의의 문자열";
    cout << s2 << endl;
    s2=s1;
    cout << s2 << endl;
    s2='A';
    cout << s2 << endl;

    // operator+=
    cout << "-------------------------\n";
    s1+="문자열 연결.";
    cout << s1 << endl;
    s1+=s2;
    cout << s1 << endl;
    s1+='!';
    cout << s1 << endl;

    // operator+
    cout << "-------------------------\n";
    string s3;
    s3 = "s1:"+s1+"s2:"+s2+".";
    cout << s3 << endl;

    // assign, append
    cout << "-------------------------\n";
    string st1("1234567890");
    string st2("abcdefghijklmnopqrstuvwxyz");
    string st3;
    st3.assign(st1,3,4);
    cout << st3 << endl;
    st3.append(st2,10,7);
    cout << st3 << endl;

    // copy, swap
    cout << "-------------------------\n";
    string ss("1234567890");
    char str[128]="abcdefghijklmnopqrstuvwxyz";
    ss.copy(str, 5, 3);     // 첫번째 인자값인 문자열포인터의 문자열에 복사된다 ex) ss.copy(str+5,5,3)
    cout << str << endl;
    cout << "st1:" << st1 << " st2:" << st2 << endl;
    st1.swap(st2);             // st2.swap(st1);
    cout << "st1:" << st1 << " st2:" << st2 << endl;

    // insert, erase
    cout << "-------------------------\n";
    string a("1234567890");
    string b("^_^");
    cout << a << endl;
    a.insert(5,"XXX");
    cout << a << endl;
    a.insert(5, b);
    cout << a << endl;
    a.erase(5,6);
    cout << a << endl;

    // replace
    cout << "-------------------------\n";
    string c="독도는 일본땅";
    cout << c << endl;
    c.replace(7,4,"대한민국");
    cout << c << endl;

    // substr
    string d("1234567890");
    string e=d.substr(3,4);
    cout << e << endl;
}