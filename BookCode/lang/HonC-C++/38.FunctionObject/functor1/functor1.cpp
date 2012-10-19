/*++
    2012.10.17

    38.�Լ���ü (651p)
    - �˰��� �Լ��� ���� �߿� ������� ������ �ʿ��� �κп� ���� �Լ� ��ü�� ȣ���Ͽ� �ǻ縦 ����
    - �Լ���ü(FunctionObject or Functor)�� �Լ������ͳ� �Լ���ü�� �� �ִ�
    - �Լ���ü�� �Լ� ȣ�⿬������()�� �����ε��� ��ü�� �ǹ�, �� �����ڸ� ���� ��ġ �Լ��� ȣ���ϵ��� ��ü�� ȣ��

    �Լ������Ϳ� ���� �Լ���ü�� ������ ����
    - �ζ����� �����ؼ� ó���ӵ��� ������(Ŭ���� ���ο������ ����Լ��� �ڵ����� �ζ��� �Ǹ� ȣ��ο� ��ü �ڵ尡 ����)
    - �������Լ�()�� �ƴ϶� �ٸ� �������,����Լ�, ������, �ı��ڸ� ���� �� �ִ�
    - �Լ���ü�� Ÿ���̹Ƿ� ���ø��� �μ��� ���� �� ������, �Լ� �����ʹ� �ܼ��� ���ϻ��̹Ƿ� ���ø��� �μ��� ����� �� ����

    _Fn1 for_each(_InIt _First, _InIt _Last, _Fn1 _Func)
    UniOp for_each(InIt first, InIt last, UniOp op);
    
--*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// 1. �Լ�������
void print(int a)
{
    printf("%d\n", a);
}


// 2. �Լ���ü
struct fo_print
{
    void operator()(const int a) const
    {
        printf("%d\n", a);
    }
};

// 3. �Լ���ü�� ����Լ� Ȱ��
struct accum
{
    int sum;
    accum() : sum(0) {}
    void operator()(const int a) 
    {
        sum+=a;
    }

};

// 4. �Լ���ü�� ������ Ȱ��
struct fo_print_ct
{
    string mes;
    fo_print_ct(const string &m) : mes(m) {} 
    void operator()(int a) const
    {
        cout << mes << a << endl;
    }
};


void main()
{
    int ari[]={2,3,5,1,9};
    vector<int> vi(&ari[0], &ari[5]);
    
    sort(vi.begin(), vi.end());

    // 1. �Լ���ü�� �Լ������� ���
    for_each(vi.begin(), vi.end(), print);

    // 2. �Լ���ü ���
    //fo_print f;                               // �Լ���ü�� f�� ������ ��  for_each�� ����
    //for_each(vi.begin(), vi.end(), f);        // for_each�Լ� ���ο��� f�� ()�����ڸ� ȣ��     
    for_each(vi.begin(), vi.end(), fo_print()); // fo_print()�� ��ü�� ȣ���ϴ°��� �ƴ϶�, �ӽð�ü�� �����ϴ� ����

    // 3.
    accum ac;
    ac = for_each(vi.begin(), vi.end(), ac);
    printf("����=%d\n", ac.sum);

    // 4.
    for_each(vi.begin(), vi.end(), fo_print_ct(string("��Ұ���")));
    for_each(vi.begin(), vi.end(), fo_print_ct(string("�ٸ� �޽���")));
}