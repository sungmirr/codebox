/*++
    2012.10.7

    36.표준라이브러리, 파일입출력(589p)

    <fstream>
    typedef basic_ifstream<char, char_traits<char> > ifstream;
    typedef basic_ofstream<char, char_traits<char> > ofstream;
    typedef basic_ifstream<wchar_t, char_traits<wchar_t> > wifstream;
    typedef basic_ofstream<wchar_t, char_traits<wchar_t> > wofstream;

    ofstream, ifstream은 
    - open(), close()로 스트림연결/종료 
    - 이진모드가 아니므로 <<, >> 연산자로 입출력 가능
    - is_open
--*/

#include "Turboc.h"
#include <iostream>
#include <fstream>
using namespace std;

void main()
{
    //////////////////////// 파일 쓰기
    ofstream f;

    // 상대경로 가능, 이미 존재하면 덮어쓴다
    // ofstream f("C:\\cpptest.txt");
    f.open("C:\\cpptest.txt");      
    f << "String " << 1234 << endl;
    f.close();


    //////////////////////  파일 읽기
    ifstream ifs;
    char str[128];
    int i;

    ifs.open("C:\\cpptest.txt");   

    if(ifs.is_open())
    {
        cout << "파일 열기 성공" << endl;
    }
    else
    {
        cout << "파일 열기 실패" << endl;
        return;
    }

    ifs >> str >> i;
    cout << str << " " << i << endl;
    ifs.close();
}