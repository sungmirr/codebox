/*++
    2012.10.14

    36.표준라이브러리, string(594p)

    <string>
    typedef basic_string<char> string;
    typedef basic_string<wchar_t> wstring;

    string:: 
    size,length,capacity,resize,reserve,clear,empty,data,c_str
--*/

#include "Turboc.h"
#include <iostream>
#include <string>
using namespace std;

void main()
{
    // string의 생성자
    string s1("test");
    string s2(s1);
    string s3;
    s3=s1+"ing";
    string s4(32, 'S');
    string s5("very nicde day", 8);
    char *str ="abcdefghijklmnopqrstuvwxyz";
    string s6(str+5, str+10);       // str+5에서 str+9까지 포함, 끝점은 포함안된다

    cout << "s1=" << s1 << endl;
    cout << "s2=" << s2 << endl;
    cout << "s3=" << s3 << endl;
    cout << "s4=" << s4 << endl;
    cout << "s5=" << s5 << endl;
    cout << "s6=" << s6 << endl;


    // string개체의 버퍼 사이즈
    cout << "-----------------------------\n";
    string s("C++ string");

    cout << s << " 문자열의 길이=" << s.size() << endl;     // stl과 호환을 위해 size함수 정의
    cout << s << " 문자열의 길이=" << s.length() << endl;
    cout << s << " 문자열의 할당 크기=" << s.capacity() << endl;
    cout << s << " 문자열의 최대 크기" << s.max_size() << endl; // string::npos, (unsigned)-1을 리턴
                                                                // 검색실패를 나타내는 플래그로도 쓰임

    s.resize(6);
    cout << s << " 길이=" << s.size() << ", 할당크기" << s.capacity() << endl;
    s.resize(30,'*');
    cout << s << " 길이=" << s.size() << ", 할당크기" << s.capacity() << endl;
    s.reserve(100);
    cout << s << " 길이=" << s.size() << ", 할당크기" << s.capacity() << endl;


    // string개체의 초기화
    cout << "-----------------------------\n";
    s.clear();
    cout << "s.empty() is " << boolalpha << s.empty() << endl;


    // string 문자열 내용 얻기
    cout << "-----------------------------\n";
    s="C++ Standard Library";
    cout << s.data() << endl;       // s객체의 내부 데이터를 그대로 리턴
    cout << s.c_str() << endl;      // 널종료 문자열이 아닌경우 사본을 복사한 후 널 종료 문자열로 바꿔서 리턴

    char *p = new char[s.size()+1];
    strcpy(p, s.c_str());
    printf("p = %s\n", p);
    delete [] p;
}