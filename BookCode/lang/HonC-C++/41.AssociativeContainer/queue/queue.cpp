/*++
    2012.10.24

    41.3 컨테이너 어댑터, 큐 (812p)

    queue의 멤버함수
    - push : 뒤에 추가
    - pop  : 앞에요소 제거
    - front : 앞요소 읽기
    - back : 뒤요소 일기
    - size
    - empty

--*/

#include <iostream>
#include <queue>
using namespace std;

void main()
{
    queue<int> q;

    
    q.push(1);
    q.push(2);
    q.push(3);

    // (뒤) 3,2,1 (앞)
    cout << "앞" << q.front() << "뒤" << q.back() << endl;

    while(!q.empty())
    {
        cout << q.front() << endl;
        q.pop();
    }
}