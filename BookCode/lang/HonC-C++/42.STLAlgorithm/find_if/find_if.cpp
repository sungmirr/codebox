/*++
    2012. 10. 24

    InIt find_if(InIt first, InIt last, UniPred F);
    - find는 ==연산자 이용, find_if는 단항함수 객체 F로 비교
 --*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct HasYoung 
{
    bool operator()(string who) const
    {
        return (who.find("영") != string::npos);
    }
};

void main()
{
    string names[]={"김정수","구홍녀","문병대",
        "김영주","임재임","박미영","박윤자"};
    vector<string> as(&names[0],&names[7]);
    vector<string>::iterator it;

    for(it=as.begin();;++it)
    {
        it=find_if(it, as.end(), HasYoung());
        if(it==as.end())
            break;
        cout << *it << "이(가) 있다." << endl;
    }
}