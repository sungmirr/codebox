/*++
    2012.10.14

    36.표준라이브러리, string(602p)

    string의 입력, 출력
     - ignore : 남아있는 버퍼(ex..개행코드)를 비운다\
    string의 원소 접근
     - [] or at()

--*/
#include <iostream>
#include <string>
using namespace std;

void main()
{
    string name, addr;
    cout << "이름을 입력하시오: ";
    cin >> name;
    cout << "입력한 이름은 " << name << "입니다." << endl;
    cin.ignore();       // 남아있는 개행코드(엔터문자)를 비운다.. 

    cout << "주소를 입력하시오: ";
    getline(cin, addr);
    cout << "입력한 주소는 " << addr << "입니다." << endl;

    cout << "----------------------------\n";
    string s("korea");
    size_t len, i;

    len = s.size();
    for(i=0; i<len; ++i)
        cout << s[i];       // 경계점검하지않는다, 대신 빠르다, size로 범위안넘으므로 추천
    cout << endl;
    s[0] = 'c';

    for(i=0; i<len; ++i)
        cout << s.at(i);    // 경계점검한다.
    cout << endl;
}