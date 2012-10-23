/*++
    2012.10.24

    41.3 �����̳� �����, ť (812p)

    queue�� ����Լ�
    - push : �ڿ� �߰�
    - pop  : �տ���� ����
    - front : �տ�� �б�
    - back : �ڿ�� �ϱ�
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

    // (��) 3,2,1 (��)
    cout << "��" << q.front() << "��" << q.back() << endl;

    while(!q.empty())
    {
        cout << q.front() << endl;
        q.pop();
    }
}