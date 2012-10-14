/*++
    2012.10.14

    36.표준라이브러리, string(612p)

    find - 발견되지 않을 경우 string::npos(string의끝) 리턴    
        size_type __CLR_OR_THIS_CALL find(const _Elem *_Ptr,
            size_type _Off, size_type _Count) const
            {	// look for [_Ptr, _Ptr + _Count) beginnng at or after _Off  
    rfind - 역방향 검색
    find_first_of
    find_last_of
    find_first_not_of
    find_last_not_of
--*/
#include <iostream>
#include <string>
using namespace std;

void main()
{
    string s1("string class find function");
    string s2("func");

    cout << s1 << endl;
    cout << "i:" << s1.find('i') << "번째" << endl;
    cout << "i:" << s1.find('i',10) << "번째" << endl;
    cout << "ass:" << s1.find("ass") << "번째" << endl;
    cout << "finding의 앞4:" << s1.find("finding",0,4) << "번째" << endl;  //
    cout << "kiss:" << s1.find("kiss") << "번째" << endl;
    unsigned ret = s1.find("kiss");
    if(ret != string::npos)
        cout << "kiss:" << ret << "번째" << endl;
    else
        cout << "kiss:" << "발견되지않음" << endl;
    

    cout << "----------------------------" << endl;
    string s3("starcraft");
    string s4("123abc456");
    string moum("aeiou");
    string num("0123456789");
    
    cout << s3 << endl;
    cout << "순방향 t:" << s3.find('t') << "번째" << endl;
    cout << "역방향 t:" << s3.rfind('t') << "번째" << endl;
    cout << "역방향 cra:" << s3.rfind("cra") << "번째" << endl;
    cout << "최초의 모음" << s3.find_first_of(moum) << "번쨰" << endl;
    cout << "최후의 모음" << s3.find_last_of(moum) << "번쨰" << endl;

    cout << s4 << endl;
    cout << "최초의 비숫자" << s4.find_first_not_of(num) << "번째" << endl;
    cout << "최후의 비숫자" << s4.find_last_not_of(num) << "번째" << endl;
}