/*++
    2012.10.17

    38.함수객체, 알고리즘의 변형(658p) 

    - find는 반복자값과 세 번째 인수로 지정한 값을 ==연산자로 비교
    - find_if는 함수객체로 요소를 직접 비교
      InIt find_if(InIt first, InIt last, UniPred F);
      bool을 리턴하는 함수객체를 조건자(Predicate)라고 한다
--*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct IsKim
{
    bool operator()(const string &name) const       // stirng은 큰 객체이므로 값으로 복사 받으면 오버헤드가 크다
    {                                               // 그래서 레퍼런스로 전달받는다, int같은 단순 타입은 값전달이나 레퍼런스전달이나 별차이없다
        //return (strncmp(name.c_str(),"김",2) == 0 );
        return (name.compare(0,2,"김",2)==0);
    }
};

void main()
{
    string names[]={"이순신","성삼문","장보고","조광조",
        "신숙주","김홍도","정도전","이성계","정몽주","김유신"};
    vector<string> vs(&names[0],&names[10]);
    vector<string>::iterator it;

    it = find_if(vs.begin(), vs.end(), IsKim());
    if (it==vs.end()) 
        cout << "없다." << endl;
    else 
        cout << *it << "이(가) 있다." << endl;

 
    // 모든 김가 찾기
    cout << "------------------------------\n";
    for(it=vs.begin(); ; ++it)
    {
        it=find_if(it, vs.end(), IsKim());
        if(it==vs.end())    break;
        cout << *it << endl;
    }
}