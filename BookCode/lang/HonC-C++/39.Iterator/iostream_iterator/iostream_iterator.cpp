/*++
    2012.10.19

    39.�ݺ��� (691p)
    =========================================================================================
    �ݺ��ڱ���
    - STL,���α׷��־��,�ü���� 0���� �����ϴ� zero base�̱� ������
      ���� �����ؾ� ���ܵ� ���� ������ ��ġ
    - STL������ ������ ���� ����
    - [first, last)
    - �ݺ��ڴ� ��� �񱳰� �Ұ����ϸ� �׻� �ε� ��
      for(;first!=last;++first)

    �ݺ����� ����
    - *,++,--,������ġ �̵�, ��,���Կ����� ����
    - �Է¹ݺ���(InIt)      : ������ �Է¸� �����ϸ� ��������
    - ��¹ݺ���(OutIt)     : ��¸� �����ϸ� ������ ���Ѵ�
    - ������ݺ���(FwdIt)   : ����� ��� ����, ������ ����(++)
    - �����ݺ���(BiIt)    : FwdIt��� + �յڷ��̵�����, ���ҿ�����(--) ����
    - �������ٹݺ���(RanIt) : ������ ��Ҹ� ����, []������ ����

    - �˰����� ���� ������ �����ϱ� ����
    - �˰������(���ø�)���� �ݺ��ڿ� ���� �ּ����� �䱸���� ���
      InIt find(InIt first, InIt last, const T& val);
      void sort(RanIt first, RanIt last);
    =========================================================================================
    
    �Է¹ݺ���, Input Iterator(697p)
    - a=*it  // ����
      *it=a; // ����
    - ������,������ ++������
    - ���� Ÿ���� �ݺ��ڿ� ���� ==, !=������
    - ex)find

    ��¹ݺ���, Output Iterator
    - *�� ������
    - ++������
    - ex) OutIt copy(InIt first, InIt last, OutIt result)
          {
            while(first!=last) { *result++ = *first++; }
            return result;
          }  

    ����¹ݺ��ڴ� ����� ��Ʈ������ ����
    STL �����̳ʵ��� ��� �б�, ���Ⱑ ���ÿ� �����ϹǷ� ����¹ݺ��� ���� �� ���� ������ �ݺ��� ����

    cin�� �ݺ���  : istream_iterator Ŭ������ ����, ǥ���Է�(Ű����)�� �Է¹��� ������ ��ȸ�Ͽ� �о�� �ִ�
    cout�� �ݺ��� : ostream_iterator Ŭ������ ����, ǥ�����(�����)�� ���ڸ� ����Ҽ� �ִ�
--*/

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

template <typename C>
void dump(const char *desc, C &c)
{
    cout.width(12);
    cout << left << desc << "==>";
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout," "));  // typename C::value_type
    cout << endl;
}

void main()
{
    int ari[]={1,2,3,4,5};
    list<int> li(&ari[0], &ari[5]);

    // oit�ݺ��ڴ� �ܼ� ����� ���� ����
    // intŸ��, ��½�Ʈ����ü, �����ڷ�"."
    // oit�� ���� ȭ�鿡 ���(����)
    //ostream_iterator<int> oit(cout, ".");
    //copy(li.begin(), li.end(), oit);
    copy(li.begin(), li.end(), ostream_iterator<int>(cout,"."));
    cout << endl;

    vector<int> vi(16);
    istream_iterator<int> iit(cin);         // intŸ��, �����ڷ� �Է½�Ʈ������
    
    copy(iit, istream_iterator<int>(), vi.begin());     // istream_iterator�� ������ �����ڴ� ��Ʈ�� ���� ��Ÿ���� �ݺ��ڸ� ����
    dump("�Է� �Ϸ� ��", vi);                           // ��Ʈ���� �� "Ctrl+Z"
}