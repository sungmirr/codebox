/*++
    2012.10.15

    37.STL개요(634p)

    list
     - 삽입, 삭제가빠르다, 
     - 읽기속도는 느리다, 한 요소를 찾으려면 첫 노드부터 순서대로 링크를 따라 이동
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
        printf("%d번째=%d\n", i, *it);
}