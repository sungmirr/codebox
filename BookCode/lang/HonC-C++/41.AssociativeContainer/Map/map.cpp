/*++
    2012.10.23

    40. ���������̳�, map(798p)

    map
    - template<class Key, class T, class BinPred = less<Key>, class A = allocator<T> >
      class map { ... }
    
    map�� �����ڷ���
    - set�� ���������� �Ʒ� �� ��Ҹ� �ٸ�
    - set: key_type�� value_type�� ����
      set: key_compare�� value_compare�� ���� �Լ� ��ü
      map: key_type�� value_type�� �ٸ��� ����
      map: key_compare�� value_compare�� �ٸ� �Լ� ��ü
    - value_type : Ű�� ���� pairŸ��
      value_compare: Ű ������ �񱳸� �����ϴ� �Լ�

    ������
    - explicit map(const BinPred& comp = BinPred());
      map(const map& x);
      map(InIt first, InIt last, const BinPred& comp = BinPred()); // ���� Ÿ���� �ʳ��� ���� ���� ����
                                                                   // Ÿ���� key�� ���� ������ ������ pair�̱� ����

    map�� �ݺ���
    - ����� �ݺ���

    ����,����
    - value_type�� pair��ü������ �����ϸ� set�� ���� ����
    - pair<iterator, bool> insert(const value_type& val);
    - iterator insert(iterator it, const value_type& val);
    - void insert((iterator first, iterator last);
      cf) �ʿ� ���ԵǴ� ����� value_type�� Ű�� ���� ������ ������ pair��ü�߸� �Ѵ�
          m.insert(pair<string,int>("���ڿ�",1234);
    
    - iterator erase(iterator it);
    - iterator erase(iterator first, iterator last);
    - size_type erase(const Key& key);

     map���� �ִ� ���Թ��, multimap���� ���Ұ�
     - []�����ڿ� ���� �����ڷ� ��� ����
     - T& operator[](const Key& k);
     - ex)[Ű]=��;   ex)m["���ڿ�"] = 1234;

    �˻�
    - iterator find(const Key& val);
    - const_iterator find(const Key& val) const;
    - ��Ƽ�� : upper_bound, lower_bound... ��,��Ƽ�°� ����
    - �ʰ˻��� ���� find�˰��� ����� �� ����
      it = find(m.begin(), m.end(), "�λ�");
      it = find(m.begin(), m.end(), pair<string,int>("�λ�",500)  
      // pair�� ==���� ��������
      // �����ص� "�λ�",500�����͸� �˰��־�� �ϴµ� �˰��ִ� ������ �˻� ��ü�� �ͼ���
    
    ����
    - []�����ڴ� Ű�� ������ ����, ������ ��� �ش� ����� ���� ���� ���۷��� ����
    - Ű�� ���� ����ȵȴ�, ���� ���氡���ϴ�

    ================================================================================
    pair
    - make_pair(val1,val2) : ���ø��Լ�, pair�� ������ ����
    - template<class T1, class T2>
      struct pair
      {
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;
        pair() : first(T1()), second(T2()) {}
        pair(const T1& v1, const T2& v2) : first(v1), second(v2) {}
      };
    ================================================================================

--*/ 
#include <iostream>
#include <string>
#include <map>
using namespace std;

void main()
{
    // Ű: string, ��: int
    map<string,int> m;
    map<string,int>::iterator it;

    // ����
    m.insert(pair<string,int>(string("����"), 1000));
    m.insert(pair<string,int>("�λ�",500));
    m["����"]=400;
    m["�뱸"]=300;
    m["����"]=200;
    m["��õ"]=100;
    m["����"]=1;

    // ����
    m.erase(m.begin());
    m.erase("��õ");

    // ��ȸ, Ű�� �� ���
    for(it=m.begin(); it!=m.end(); ++it)
        cout << it->first << " : " << it->second << endl;

    // �˻�
    it=m.find("�λ�");
    if(it==m.end())
        cout << "�ʿ� ���� �����Դϴ�." << endl;
    else
        cout << it->first << "�� �α��� " << it->second << "�� ���̴�." << endl;

    // ����
    m["�λ�"]=5;   // ������ ���� ������ ����
    it=m.find("�λ�");
    cout << it->first << "�� �α��� " << it->second << "�� ���̴�." << endl;

    it->second=555;
    cout << it->first << "�� �α��� " << it->second << "�� ���̴�." << endl;
}