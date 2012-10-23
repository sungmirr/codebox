/*++
    2012.10.23

    40.�����������̳�, ����Ʈ(765p)
    
    ����Ʈ�� ����
    - ����Ʈ�� ���� ���� �ݺ��ڸ� �������� �����Ƿ� ���� �ӵ��� ����� ������
    - sort�˰��� �Լ��� ������� ���ϴ� ���, sort����Լ��� ���
    - ����Ʈ�� ������ �ڷḦ �����ϴ°��� ���ʿ� ������ �߸���
      �� �ʿ��� ��츸 ���

    unique, �ι��̻� �ߺ��� �ߺ���� ����
    void unique();
    void unique(UniPred op);
    cf)�˰������� �����Ǵ� unique�� ������ ����Լ��� ��ũ������ Ȱ��

--*/ 

#include <Turboc.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

const unsigned NUM=1000000;

template<typename C> 
void dump(const char *desc, C c) 
{ 
    cout.width(12);cout << left << desc << "==> ";
    copy(c.begin(),c.end(),ostream_iterator<typename C::value_type>(cout," ")); 
    cout << endl; 
}

void main()
{
    const char str[]="stllistcontainer";
    list<char> li0(&str[0],&str[sizeof(str)-1]);

    dump("����",li0);
    li0.sort();
    dump("sort��",li0);
    li0.unique();
    dump("unique��",li0);


    randomize();
    vector<int> vi;
    list<int> li;
    int i;
    clock_t start;

    for (i=0;i<NUM;i++) {
        vi.push_back(random(100));
        li.push_back(random(100));
    }
    cout << "Ű�� ������ ���͸� �����մϴ�." << endl;
    getch();
    start=clock();
    sort(vi.begin(),vi.end());
    cout << "���� ���ĿϷ�. �ҿ�ð� = " << clock()-start << endl;

    cout << "Ű�� ������ ����Ʈ�� �����մϴ�." << endl;
    getch();
    start=clock();
    li.sort();
    cout << "����Ʈ ���ĿϷ�. �ҿ�ð� = " << clock()-start << endl;
}
