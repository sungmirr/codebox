/*++
    2012.10.20

    40.�����������̳�, ����(730p)

    =====================================================================================================
    ������ ���Ի��� ��� �Լ�
        void push_back(const T& x); 
        void pop_back();            //����
        iterator insert(iterator it, const T& x=T());
        void insert(iterator it, size_type n, const T& x);
        void insert(iterator it, const_iterator first, const_iterator last);
        iterator erase(iterator it);
        iterator erase(iterator first, iterator last);

    cf) �����̳� ������ �����ϱ� ������ ����, ���� ��ĵ� �����̳ʺ��� �ٸ���
        ����,���� �Լ��� �Ϲ� �˰������� �����Ǳ� ���� �����̳��� ��� �Լ��� ����
        insert, erase�� ��Ҹ� �����ϴ� �⺻ �����̹Ƿ� ��κ��� �����̳ʿ��� ������ �̸��� �������� ���� 
    =====================================================================================================

    ������ ������ �ϳ��� �߰�,����,���� 
    => �޸� ���Ҵ�, �޸��̵� ������ �Ͼ
    �������������� �Ѳ����� �߰�,����,����
    => �޸� ���Ҵ�, �޸��̵��� �� �ѹ� �Ͼ

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
    dump("���� ����", vc);

    vc.push_back('A');
    dump("A �߰�", vc);

    vc.insert(vc.begin()+3, 'B');
    dump("B ����", vc);

    vc.pop_back();
    dump("�� ��� ����", vc);

    // ��������
    vc.erase(vc.begin()+5, vc.begin()+8);
    dump("[5~8) ����", vc);

    // �����Ҵ�� �ѹ����Ҵ�
    cout << "---------------------------\n";
    vector<char> vc1;
    for(int i=0; i<10; ++i)
        vc1.insert(vc1.begin(), 'Z');
    dump("���� �߰�", vc1);

    vector<char> vc2;
    vc2.insert(vc2.begin(), 10, 'Z');
    dump("�Ѳ����� �߰�", vc2);

    // ����Ʈ�� ��Ҹ� ���Ϳ� ����
    cout << "---------------------------\n";
    list<int> li;
    for(int i=0; i<100; ++i)
        li.push_back(i);

    vector<int> vi;
    vi.insert(vi.begin(), find(li.begin(), li.end(), 8), find(li.begin(), li.end(), 25)); // find���ϰ��� li.end() üũ����
    dump("����Ʈ��� �߰���", vi);
}