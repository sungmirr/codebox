/*++
    2012.10.20

    40.�����������̳�, ����(725p)

    1. ���� Ŭ���� ���ø��� ���ǵ� Ÿ��(typedef)
    - ��� �����̳ʴ� �ڽ��� �����ϴ� Ÿ���� ��ӵ� �̸����� �����ؾ� 
      �ݺ��ڳ� �˰��򿡼� �����̳ʸ� �����ϱ� ���� �̸� ���ǵ� Ÿ���� ���  

    - value_type         : �����̳� ����� Ÿ��
      (const_) pointer   : ��Ҹ� ����Ű�� ������ Ÿ��
      (const_) reference : ����� ���۷��� Ÿ��
      (const_) iterator  : �츮�� iteratorŸ������ ������ ������ ���
      (const_) reverse_iterator
      difference_type    : �� �ݺ����� ���� ǥ���ϴ� Ÿ��, ��� int
      size_type          : ũ�⸦ ǥ���ϴ� Ÿ��, ��� unsigned


    2. ������ ������
    explicit vector();
    explicit vector(size_type n, const T& v = T());
    vector(const vector& x);    //���������
    vector(const_iterator first, const_iterator last);

    3. ������ �޸� ���� ����Լ�
    size        : ��� ����
    max_size    : ���Ͱ� ���� �� �� �ִ� �ִ� ��� ����
    capacity    : �Ҵ�� ��Ұ���(�޸��� ũ��)
    resize(n)   : ũ�⸦ ����, ��ũ�Ⱑ �� Ŭ��� �����Ҵ�� ��Ҵ� ����Ʈ������ �ʱ�ȭ
    reserve(n)  : �ּ����� ũ�⸦ �����ϸ�, �޸𸮸� �̸� �Ҵ�
    clear       : ��� ��Ҹ� ����
    empty       : ��� �ִ��� ����
    
    cf) empty�� size()==0
        ��Ұ� ���� ��� size()�� ������ �����.. ������尡 ũ��
        empty�� 0���� �ƴ����� üũ

    4. ������ ���Ի��� ��� �Լ�
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

    5. ������ ������
    ���� : =(��ü), assign(�Ϻα����� ����)
    ��ȯ : swap
    �� : ==,!=, <,>,<=,>=
    ������� : [], at
--*/ 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<typename C>
void dump(const char *desc, const C &c)
{
    cout.width(12);
    cout << left << desc << "==>";
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " "));
    cout << endl;
}

void main()
{
    vector<string> v1;
    dump("v1", v1);

    vector<double> v2(10);
    dump("v2", v2);

    vector<int> v3(10,7);
    dump("v3", v3);

    vector<int> v4(v3);
    dump("v4", v4);

    v4.clear();
    dump("v4 clear", v4);

    if(v4.empty())
        cout << "v4�� ��Ұ� ����"  << endl;

    int ar[]={1,2,3,4,5,6,7,8};
    vector<int> v5(&ar[2], &ar[5]);
    dump("v5", v5);

    
}