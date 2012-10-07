/*++
    2012.10.7

    36.표준라이브러리, cout 에러체크(587p)

    cin객체는 내부적으로 에러 발생여부를 표시하는 세개의 플래그 유지
    - failbit : 입력 실패, 정수를 입력받는데 문자가 입력된 경우, fail()
    - eofbit : 파일 끝, eof()
    - badbit : 스트림이 물리적으로 손상되어 읽을 수 없다, bad()
    - goodbit : 상기 세에러가 발생하지 않았다는 뜻, good()

    cin은 일단 에러가 발생하면 계속 에러 상태 유지, 별도로 에러상태 리셋
    rdstate, setstate, clear 사용
--*/

#include "Turboc.h"
#include <iostream>
#include <string>
using namespace std;

void main()
{
    int i;
    string discard;

    if(cin >> i)
        cout << i << endl;
    else
        cout << "실패" << endl;

    // 버퍼비우기.. 잘안되네...
    //cin.ignore(100);
    //cin.ignore(cin.rdbuf()->in_avail());
    cin.clear();            // 
    cin >> discard;


    cin >> i;
    if(cin.good())
        cout << i << endl;
    else
        cout << "실패" << endl;
}