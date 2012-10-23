/*++
    2012.10.20

    40.시퀀스컨테이너, 벡터(730p)

    =====================================================================================================
    벡터의 삽입삭제 멤버 함수
        void push_back(const T& x); 
        void pop_back();            //제거
        iterator insert(iterator it, const T& x=T());
        void insert(iterator it, size_type n, const T& x);
        void insert(iterator it, const_iterator first, const_iterator last);
        iterator erase(iterator it);
        iterator erase(iterator first, iterator last);

    cf) 컨테이너 구조가 상이하기 때문에 삽입, 삭제 방식도 컨테이너별로 다르다
        삽입,삭제 함수는 일반 알고리즘으로 제공되기 보다 컨테이너의 멤버 함수로 제공
        insert, erase는 요소를 관리하는 기본 동작이므로 대부분의 컨테이너에서 동일한 이름과 형식으로 존재 
    =====================================================================================================

    루프를 돌리며 하나씩 추가,삽입,삭제 
    => 메모리 재할당, 메모리이동 여러번 일어남
    구간으로지정해 한꺼번에 추가,삽입,삭제
    => 메모리 재할당, 메모리이동이 딱 한번 일어남

--*/ 
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

template<typename C>
void dump(const char *desc, const C& c)
{
    cout.width(12);
    cout << left << desc << "==>";
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " "));
    cout << endl;
}

void main()
{
    const char *str = "0123456789";
    vector<char> vc(&str[0], &str[10]);
    dump("생성 직후", vc);

    vc.push_back('A');
    dump("A 추가", vc);

    vc.insert(vc.begin()+3, 'B');
    dump("B 삽입", vc);

    vc.pop_back();
    dump("끝 요소 삭제", vc);

    // 구간삭제
    vc.erase(vc.begin()+5, vc.begin()+8);
    dump("[5~8) 삭제", vc);

    // 개별할당과 한번에할당
    cout << "---------------------------\n";
    vector<char> vc1;
    for(int i=0; i<10; ++i)
        vc1.insert(vc1.begin(), 'Z');
    dump("개별 추가", vc1);

    vector<char> vc2;
    vc2.insert(vc2.begin(), 10, 'Z');
    dump("한꺼번에 추가", vc2);

    // 리스트의 요소를 벡터에 삽입
    cout << "---------------------------\n";
    list<int> li;
    for(int i=0; i<100; ++i)
        li.push_back(i);

    vector<int> vi;
    vi.insert(vi.begin(), find(li.begin(), li.end(), 8), find(li.begin(), li.end(), 25)); // find리턴값이 li.end() 체크생략
    dump("리스트요소 추가후", vi);
}