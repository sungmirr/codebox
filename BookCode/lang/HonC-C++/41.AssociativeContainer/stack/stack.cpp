/*++
    2012.10.24

    41.3 컨테이너 어댑터, 스택 (808p)

    컨테이너어댑터
    - 기존 컨테이너의 기능 중 일부만을 공개하여 기능이 제한되거나 변형된 컨테이너를 만든다
    - 스택,큐,우선 순위 큐

    스택
    - template<class T, class Cont=deque<T> >
      class stack { ... }
      // 디폴트로 데크.. 벡터나 리스트로 변경가능

    스택이 제공하는 내부타입
    - size_type, value_type
      container_type : 스택의 자료 관리를 위해 사용되는 기본 컨테이너의 타입(Cont)

    생성자
    - explicit stack(const allocator_type& al = allocator_type());
      ex) stack<T> s;

    멤버함수
    - void push(const T& x);
    - void pop();                       // 제거
    - value_type& top();                // 최상단의 값을 읽어 레퍼런스로 리턴
    - const value_type& top() const;    // const버전
    - size()
    - empty()
    cf) STL의 스택은 읽는 함수와 제거하는 함수가 분리되 있다

--*/
#include <iostream>
#include <stack>
using namespace std;

void main()
{
    stack<int> s;

    s.push(4);
    s.push(7);
    s.push(2);

    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
}