/*++
    2012.10.7

    36.표준라이브러리, iostream

    // ostream은 char 타입의 문자열을 출력, char_traits<char>객체는 널 종료문자열을 관리하는 객체
    typedef basic_ostream<char, char_traits<char> > ostream;
    typedef basic_ostream<wchar_t, char_traits<wchar_t> > wostream;

    <iostream>
    extern istream cin;
    extern ostream cout;
    extern ostream cerr;
    extern ostream clog;
    extern wistrem wcin;
    extern wostream wcout;

    출력 객체는 폭이나 정밀도, 정렬방식, 채움문자, 진법 등에 대한 옵션을
    기억하는 플래그들을 가지며 조정자들은 이 플래그를 변경하는 역활 수행
    조정자 외에 플래그를 직접 변경 : setf.unsetf멤버함수 이용, 출력양식 일괄적으로 변경, 조사
--*/


#include "Turboc.h"
#include <iostream>
using namespace std;


void main()
{
    int i=1234;
    int j=-567;

    hex(cout);
    cout << i << endl;
    dec(cout);
    cout << i << endl;

    cout << "-----------------------------\n";
    cout.width(10);                 // 한번 사용후 자동 해제
    cout << oct << i << endl;       // oct, hex, dex한번 지정후 계속 유효
    cout << hex << i << endl;
    cout << dec << i << endl;

    cout << "-----------------------------\n";
    cout.width(2);
    cout << oct << i << endl;
    cout << hex << i << endl;
    cout << dec << i << endl;

    cout << "-----------------------------\n";
    cout.width(10);
    cout.fill('_');                 // cout.fill 한번 지정후 계속 유효
    cout << oct << i << endl;
    cout.width(10);
    cout << hex << i << endl;
    cout.fill(' ');                 // cout.fill 해제
    cout.width(10);
    cout << dec << i << endl;

    cout << "-----------------------------\n";
    cout.width(10);
    cout << left << oct << i << endl;
    cout.width(10);
    cout << right << hex << i << endl;
    cout.width(10);
    cout << internal << dec << j << endl;       // internal 부호(-, 0x)는 왼쪽, 숫자 오른쪽

    cout << "float-----------------------------\n";
    double d = 1.234;
    cout << d << endl;
    cout.precision(3); // 실수의 정밀도 지정
    cout << d << endl;
    cout.precision(10);
    cout << showpoint << d << endl;
    cout.precision(6);

    cout << fixed << d << endl; // 실수 출력방식( fixed, scientific의 조정자로 변경)
    cout << scientific << d << endl;

    cout << "----------------------------\n";
    bool b = true;
    cout << b << endl;
    cout << boolalpha << b << endl;
    cout << hex << i << endl;       // 4d2
    cout << showbase << i << endl;  // 0x4d2
    cout << uppercase << i << endl; // 0X4d2
    cout << dec << showpos << i << endl;

}