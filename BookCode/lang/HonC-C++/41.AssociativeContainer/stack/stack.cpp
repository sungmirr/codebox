/*++
    2012.10.24

    41.3 �����̳� �����, ���� (808p)

    �����̳ʾ����
    - ���� �����̳��� ��� �� �Ϻθ��� �����Ͽ� ����� ���ѵǰų� ������ �����̳ʸ� �����
    - ����,ť,�켱 ���� ť

    ����
    - template<class T, class Cont=deque<T> >
      class stack { ... }
      // ����Ʈ�� ��ũ.. ���ͳ� ����Ʈ�� ���氡��

    ������ �����ϴ� ����Ÿ��
    - size_type, value_type
      container_type : ������ �ڷ� ������ ���� ���Ǵ� �⺻ �����̳��� Ÿ��(Cont)

    ������
    - explicit stack(const allocator_type& al = allocator_type());
      ex) stack<T> s;

    ����Լ�
    - void push(const T& x);
    - void pop();                       // ����
    - value_type& top();                // �ֻ���� ���� �о� ���۷����� ����
    - const value_type& top() const;    // const����
    - size()
    - empty()
    cf) STL�� ������ �д� �Լ��� �����ϴ� �Լ��� �и��� �ִ�

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