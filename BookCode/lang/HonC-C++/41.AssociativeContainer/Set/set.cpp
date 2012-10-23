/*++
    2012.10.23

    40. ���������̳�, set(774p)
    
    ��
    - �����ϴ� ������ ��ü�� Ű�� ����ϸ� �����ʹ� ����ʴ´�
    - ���ĵ� ��ġ�� ���ԵǸ�, �˻� �ӵ��� ������
    - �ߺ� ��� �ʴ´�, multiset�� �ߺ����
    - ����Ʈ�� �̸� �񱳷� ����, �˻��� �����̸� ���Ĺ���� �ٲ��ʿ����
    
    ���� �����ڷ���
    value_type,iterator,const_iterator,refrence��..
    key_type        : Ű�� Ÿ��, value_type�� �����ϸ� ���� Ű�� ���� pairŸ������ ����
    key_compare     : Ű�� ���ϴ� �Լ� ��ü Ÿ��, ����Ʈ�� less
    value_compare   : ���� ���ϴ� �Լ� ��ü Ÿ��, ���� key_compare�� ������ Ÿ������ ����,
                      �ʿ����� pair�� ��

    ������
    explicit set(const BinPred& cmp = BinPred());
    set(const set& x);
    set(InIt first, InIt last, const BinPred& comp=BinPred());
    cf)multiset�� ����

    ����,����
    - set�� insert
      pair<iterator, bool> insert(const value_type& val);  // ������ġ�� ���� �������ΰ� pair�� ���� 
                                                           // set�� �ߺ�����ϹǷ� val�������Ұ�� ����
    - multiset�� insert
      iterator insert(const value_type& val);  // �ߺ�����ϹǷ� ������ �׻� ����, �ݺ��ڸ� ����
    - set,multiset insert(����)
      iterator insert(iterator it, const value_type& val);  // it�� ��ġ������ ��Ʈ�ϻ� �ƹ� ��ġ�� �����ص� ������ ������ ����
                                                            // set..�����Ұ�� �ߺ��� val�� ��ġ�� ����, ������ ��ġ ����
      void insert(iterator first, iterator last);      
    - iterator erase(iterator it);
    - iterator erase(iterator first, iterator last);
    - size_type erase(const Key& key);

    �˻�(�˻����н� end()����)
    - iterator find(const Key& val);
    - const_iterator find(const Key& val) const;
    cf)�˰����Լ� find���� ��� find�� ����Ʈ���˻��� ����ϹǷ� ������
       multiset�� ��� ����Ʈ���� Ư���� �ߺ��� Ű�� ����� �˻��� �� �� �� ����
       �˰����Լ� find�� �����˻��� �����ϹǷ� �ߺ��Ǵ� ���� ù��� �˻�

    multiset�� �ߺ��� �˻�
    [ 1, 2, 3, 4, 5, 7, 7, 7, 7, 7, 10, 13, 13 ]    
    - iterator lower_bound(const Key& key);     // �ߺ��Ǵ� ���� ù���
    - iterator upper_bound(const Key& key);     // �ߺ��Ǵ� ���� ����������� ����
    - pair<iterator, iterator> equal_range(const Key& key);  // ó���� ���� �ݺ��� ��

--*/

#include <iostream>
#include <set>
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
    int ar[]={1,4,8,1,9,6,3};

    set<int> s;
    for(int i=0; i < sizeof(ar)/sizeof(ar[0]); ++i)
        s.insert(ar[i]);        // �ι�° 1������ ����
    dump("����", s);

    set<int> s2;
    s2=s;
    dump("�纻",s2);

    const char *str="ASDFASDFGHJKL";
    set<char> sc(&str[0], &str[13]);
    dump("���ڼ�", sc);
    multiset<char> msc(&str[0], &str[13]);
    dump("���ڸ�Ƽ��", msc);
    
    sc.erase('A');
    dump("���ڼ� A����", sc);
    msc.erase('A');
    dump("���ڸ�Ƽ�� A����", msc);      // ��� 'A'����

    set<char>::iterator it;
    multiset<char>::iterator mit;

    it = sc.find('J');                  // it = find(sc.being(), sc.end(), 'J');
    if(it!=sc.end())
        cout << *it << endl;
    else
        cout << "ã�� Ű�� �����ϴ�" << endl;

    mit = msc.find('Z');
    if(mit!=msc.end())
        cout << *mit << endl;
    else
        cout << "ã�� Ű�� �����ϴ�" << endl;
}