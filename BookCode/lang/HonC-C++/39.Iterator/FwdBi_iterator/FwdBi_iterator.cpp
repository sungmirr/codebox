/*++
    2012.10.19

    39.반복자, 순방향반복자, 양방향반복자 (701p)
    
    Foward Iterator
    - 입출력 모두 가능
    - ++연산 가능
    - --연산 불가능
    - 입출력반복자와 다른점은 같은 위치를 여러번 읽고 쓸수 있다
    - ex) search알고리즘, 검색대상구간과 완전히 일치하는 부분을 찾을 떄까지 컨터이너의 각 요소를 여러번 읽음
          strstr함수와 동작이 유사
    - 모든 STL 컨테이너가 지원
    

    Bidirectional Iterator
    - ++연산, --연산 가능
    - list가 양방향반복자 제공

    void replace(FwdIt first, FwdIt last, const Type& Old, const Type& New);
    void reverse(BiIt first, BiIt last);

--*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename C>
void dump(const char *desc, C &c)
{
    cout.width(12);
    cout << left << desc << "==>";
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout," "));
    cout << endl;
}

void main()
{
    int ari[]={78,85,95,93,86,60,72,99,56,85};
    vector<int> vi(&ari[0],&ari[10]);

    dump("원본", vi);
    replace(vi.begin(), vi.end(), 85, 100);
    dump("대체후",vi);
    reverse(vi.begin(), vi.end());
    dump("뒤집은후",vi);
}