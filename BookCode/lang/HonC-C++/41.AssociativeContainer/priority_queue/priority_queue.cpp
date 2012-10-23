/*++
    2012.10.24

    41.3 컨테이너 어댑터, 우선순위큐 (813p)

    priority_queue
    - 벡터와 유사하되 값을 빼 낼 때 가장 큰 값을 리턴
    - 우선순위가 있는 자료를 다룰 때 편리
      
    
    priority_queue의 멤버함수
    - push  // 삽입
    - pop   // 가장 큰 값 제거
    - top   // 가장 큰 값 읽음
    - size
    - empty

--*/

#include <iostream>
#include <queue>
using namespace std;

void main()
{
    priority_queue<int> q;

    q.push(1);
    q.push(10);
    q.push(5);

    while(!q.empty())
    {
        cout << q.top() << endl;
        q.pop();
    }
}