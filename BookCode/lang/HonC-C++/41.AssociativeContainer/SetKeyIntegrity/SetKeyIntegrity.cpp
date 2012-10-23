/*++
    2012.10.23

    40. ���������̳�, Ű ���� �Ұ� ��Ģ(793p)
    
    Ű�� ���� ����� ������ ���ϱ� ���� ����ϴ� �߿��� ���̹Ƿ�
    �¿� �̹� �� �ִ� Ű�� �����ؼ��� �ȵȴ�.

    Ű�� ������ �ٲٸ� ���� ���Ἲ�� ���� ������ � ���۵� ���� ���Ѵ�.

    cf)�����(<������)�� ���Ǵ� ��� ��������� Ű�̴�
    cf)��ü�� ������� �� Ű�� ������ �ʴ� ���� �����ϴ°� �չ����̴�
      => ���� Ű�� ���� �и��Ǿ� �ֱ� ������ �� ������ ���� �����ϴ�
        
--*/

#include <iostream>
#include <set>
using namespace std;

template<typename C> 
void dump(const char *desc, C c) 
{ 
    cout.width(12);
    cout << left << desc << "==> ";
    copy(c.begin(),c.end(),ostream_iterator<typename C::value_type>(cout," ")); 
    cout << endl; 
}

void main()
{
    int ar[]={1,3,2,6,4,5};
    int i;
    set<int> s;
    set<int>::iterator it;

    for (i=0;i<sizeof(ar)/sizeof(ar[0]);i++) 
        s.insert(ar[i]);
    
    dump("����",s);
    it=s.begin();it++;it++;it++;

    // key ����... set�� ���Ἲ�� ������!!
    *it=99;
    dump("������",s);

    it=s.find(5);
    if (it!=s.end()) 
        cout << *it << endl;
    else 
        cout << "ã�� Ű�� �����ϴ�." << endl;
}
