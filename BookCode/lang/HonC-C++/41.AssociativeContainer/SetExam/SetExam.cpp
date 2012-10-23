/*++
    2012.10.23

    40. 연관컨테이너, 셋의활용(780p)

    set의 insert,erase,find활용

    set의 모든 요소 순회
    => begin부터 end까지 순회하며 반복
       for_each사용
--*/ 

#include <iostream>
#include <set>
#include <string>
using namespace std;

void main()
{
    set<string> s;
    set<string>::iterator it;
    string name;
    char ch;

    for(;;) 
    {
        cout << "1:삽입, 2:삭제, 3:보기, 4:검색, 5:종료 => ";
        cin >> ch;
        switch (ch) 
        {
        case '1':
            cout << "새 이름을 입력 하시오 : ";
            cin >> name;
            s.insert(name);
            break;
        case '2':
            cout << "삭제할 이름을 입력 하시오 : ";
            cin >> name;
            s.erase(name);
            break;
        case '3':
            for(it=s.begin(); it!=s.end(); ++it)
                cout << *it << endl;
            break;
        case '4':
            cout << "검색할 이름을 입력 하시오 : ";
            cin >> name;
            cout << name << "이(가) " << (s.find(name) != s.end() ? "있":"없")
                     << "습니다." << endl;
            break;
        case '5':
            return;
        }
    }
}