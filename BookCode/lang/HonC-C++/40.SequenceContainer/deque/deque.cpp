/*++
    2012.10.23

    40.�����������̳�, ��ũ(765p)
    
    deque
    - ���� ���� �ִ� ť�̸� �� ������ �ڷḦ ����, ������ �� �ִ�
    - ���Ϳ� ���� ���ʿ����� ����, ������ ������, ��� ������ ������� ���ͺ��� ������
    - push_front, pop_front�Լ� �߰��� ����
    - reserv,capacity ���ʿ�

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