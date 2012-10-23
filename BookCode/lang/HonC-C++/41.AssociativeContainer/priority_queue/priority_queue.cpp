/*++
    2012.10.24

    41.3 �����̳� �����, �켱����ť (813p)

    priority_queue
    - ���Ϳ� �����ϵ� ���� �� �� �� ���� ū ���� ����
    - �켱������ �ִ� �ڷḦ �ٷ� �� ��
      
    
    priority_queue�� ����Լ�
    - push  // ����
    - pop   // ���� ū �� ����
    - top   // ���� ū �� ����
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