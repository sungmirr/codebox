/*++
    2012.10.15

    37.STL����(634p)

    list
     - ����, ������������, 
     - �б�ӵ��� ������, �� ��Ҹ� ã������ ù ������ ������� ��ũ�� ���� �̵�
     - push_front, push_back, pop_front, pop_back
--*/

#include <iostream>
#include <list>
using namespace std;

void main()
{
    list<int> li;
    int i;

    for(i=0; i<5; ++i)
        li.push_back(i*2);

    list<int>::iterator it;
    for(it=li.begin(), i=0; it!=li.end(); ++it,++i)
        printf("%d��°=%d\n", i, *it);
}