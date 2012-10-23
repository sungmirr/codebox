/*++
    2012.10.23

    40.�����������̳�, ����Ʈ(756p)

    1.����Ʈ
    - ���߿��Ḯ��Ʈ�� ���ø����� �߻�ȭ�� ����
    - ����Ʈ�� �����ϴ� ����Ÿ��, ���Ϳ� ����
      value_type         : �����̳� ����� Ÿ��
      (const_) pointer   : ��Ҹ� ����Ű�� ������ Ÿ��
      (const_) reference : ����� ���۷��� Ÿ��
      (const_) iterator  : �츮�� iteratorŸ������ ������ ������ ���
      (const_) reverse_iterator
      difference_type    : �� �ݺ����� ���� ǥ���ϴ� Ÿ��, ��� int
      size_type          : ũ�⸦ ǥ���ϴ� Ÿ��, ��� unsigned

    2. ����Ʈ�� ������ ������
    - �ݺ��ڷ���, ���� RanIt, ����Ʈ BiIt, �ݵ�� ��ȸ�� ���ϴ� ��� ����(+n,[]����Ұ���)
    - ����ð��� ������ ��ġ�� ����,��������
      push_front, pop_front ����
      capacity, reserve���ʿ�
    - ���Ϳ� ���� ��ũ��Ҷ����� �޸� ��뷮�� ũ��, �޸� ����ȭ�� ���ϴ�
    - �ݺ��� ��ȿȭ�� ���.. ����Ű�� ��Ұ� �����ø� �߻�
    => ���ʹ� �ϱ⿡ ���ϰ� ����Ʈ�� ���⿡ ���ϴ�
       �бⰡ ����ϸ� ����, ����,������ ����ϸ� ����Ʈ�� ����

    3. ����Ʈ�� ������(���Ϳ� ����)
    explicit list();
    explicit list(size_type n, const T& v = T());
    list(const vector& x);    //���������
    list(const_iterator first, const_iterator last);

    4. ����,����(���Ϳ� ����)
    iterator insert(iterator it, const T& x=T());
    void insert(iterator it, size_type n, const T& x);
    void insert(iterator it, const_iterator first, const_iterator last);
    iterator erase(iterator it);
    iterator erase(iterator first, iterator last);

    5. Ư������ ������ ��� ��� ����
    void remove(const Type& val);
    void remove_if(UniPred F);
    cf)���� remove�˰����Լ�.. ���۹���� �ٸ���

    6. �̿� ����Լ�
    void swap(list& Right);
    void reverse();
    void merge(list& Right);
    cf)���� �˰��� ����, but ����Ʈ�� ����Լ��� ����ϸ� ����Ʈ�� ��ũ�� �̿�..�����Ե���

    7. splice
    void splice(iterator it, list& x);
    void splice(iterator it, list& x, iterator first);
    void splice(iterator it, list& x, iterator first, iterator last);

    8. unique, �ι��̻� �ߺ��� �ߺ���� ���� (ListSort������Ʈ�� ��������)
    void unique();
    void unique(UniPred op);

--*/ 

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

template <typename C>
void dump(const char *dest, C &c)
{
    cout.width(12);
    cout << left << dest << "==>";
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " "));
    cout << endl;
}

void main()
{
    // ���� �󸮽�Ʈ�� ���� ��, push(pop)_front(back)�Լ��� ��� ��� ÷��
    list<int> li;
    list<int>::iterator it;

    li.push_back(8);
    li.push_back(9);
    li.push_front(2);
    li.push_front(1);

    for(it=li.begin(); it!=li.end(); ++it)
        printf("%d\n", *it);

    cout << "--------------------------------------" << endl;
    const char *str = "abcdefghij";
    list<char> lc(&str[0], &str[10]);
    list<char>::iterator it2;

    dump("����", lc);
    it2=lc.begin(); 
    //it2++;it2++;it2++;it2++;it2++;      // advance
    advance(it2,5);
    lc.insert(it2, 'Z');
    dump("Z����", lc);
    it2=lc.end();
    it2--;it2--;it2--;
    lc.erase(it2);
    dump("h����", lc);


    cout << "--------------------------------------" << endl;
    const char *str3="double linked list class";
    list<char> li3(&str3[0],&str3[strlen(str3)]);

    dump("����", li3);
    li3.remove('l');
    dump("l����",li3);
}

