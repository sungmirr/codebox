/*++
    2012.10.23

    40.시퀀스컨테이너, 데크(765p)
    
    deque
    - 양쪽 끝이 있는 큐이며 양 끝에서 자료를 삽입, 삭제할 수 있다
    - 벡터에 비해 앞쪽에서도 삽입, 삭제가 빠르다, 대신 나머지 연산들은 벡터보다 느리다
    - push_front, pop_front함수 추가로 제공
    - reserv,capacity 불필요

--*/ 

#include <iostream>
#include <deque>
using namespace std;

void main()
{
    deque<int> dq;

    dq.push_back(8);
    dq.push_back(9);
    dq.push_front(2);
    dq.push_front(1);

    for(unsigned i=0; i<dq.size(); ++i)
        cout << dq[i];
    cout << endl;
}