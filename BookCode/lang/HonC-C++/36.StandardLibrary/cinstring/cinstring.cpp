/*++
    2012.10.7

    36.표준라이브러리, 입력스트림(585p)

    cin, >>연산자의 공백(스페이스,텝,개행문자) 입력못받는 특징을 보완하기 위해
    basic_istream& get(char& c);
    basic_istream& getline(char *s, streamsize, n, char delim='\n');
--*/

#include "Turboc.h"
#include <iostream>
using namespace std;

void main()
{
    char ch;
    char str[128];

    cin.get(ch);
    cout << showbase << hex <<  (int)ch << endl;
    cin.get(ch);

    cin.getline(str, sizeof(str));
    cout << str << endl;
}