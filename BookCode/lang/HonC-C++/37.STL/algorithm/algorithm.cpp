/*++
    2012.10.15

    37.STL����(644p)

    �˰���
    
    find
     _InIt find(_InIt _First, _InIt _Last, const _Ty& _Val)
    sort
     - <�����ڷ� ����� ������ �Ǵ��Ͽ� ����
       ���Ĵ���� <�����ڸ� �ݵ�� ����
     - ����Ʈ�˰��� ���
    reverse
    random_shuffle
--*/

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <time.h>
using namespace std;

void main()
{
    int ari[]={1,2,3,4,5};
    vector<int> vi(&ari[0], &ari[5]);
    list<int> li(&ari[0], &ari[5]);
    vector<int>::iterator it;

    // find
    puts(find(&ari[0],&ari[5],3)==&ari[5] ? "����" : "�ִ�");       // 
    puts(find(vi.begin(),vi.end(),4)==vi.end() ? "����" : "�ִ�");
    puts(find(li.begin(),li.end(),8)==li.end() ? "����" : "�ִ�");

    // random_shuffle
    cout << "----------------------------\n";
    srand(time(NULL));
    random_shuffle(vi.begin(),vi.end());
    for(it=vi.begin(); it!=vi.end(); ++it)
        cout << *it;
    cout << endl;

    // sort
    cout << "----------------------------\n";
    sort(vi.begin(), vi.end());
    for(it=vi.begin(); it!=vi.end(); ++it)
        cout << *it;
    cout << endl;

    // reverse
    cout << "----------------------------\n";
    reverse(&ari[1],&ari[4]);           // reverse ������ [1,4)
    for(int i=0; i<sizeof(ari)/sizeof(ari[0]); ++i)
        cout << ari[i];
    cout << endl;
}