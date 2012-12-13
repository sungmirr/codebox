/*++
    2012. 10. 24

    InIt find(InIt first, InIt last, const T&val);
    - 입력 반복자 두 개로 검색 대상 구간을 지정하여 검색
    - 검색할 값을 세번째 인수로 전달
    - ==연산자 사용
    - val이 발견되지 않으면 last가 리턴
 --*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void main()
{
    string names[]={"김정수","구홍녀","문병대",
        "김영주","임재임","박미영","박윤자"};
    vector<string> as(&names[0],&names[7]);
    vector<string>::iterator it;

    it=find(as.begin(),as.end(),"안순자");
    if (it==as.end()) 
        cout << "없다" << endl;
    else 
        cout << "있다" << endl;

    for(it=as.begin();; ++it)
    {
        it=find(it, as.end(), "김정수");
        if(it==as.end()) break;
        cout << *it << endl;
    }
}