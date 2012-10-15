/*++
    2012.10.15

    37.STL개요(638p)

    반복자
     - 순회방법을 일반화하기 위해 사용하는 개념
     - 포인터 or [] or 객체(::iterator)
     
     - 컨테이너요소하나를 가리킴, *,++.--,대입,비교 연산자 정의
     - 포인터는 위 기능을 모두 가지므로 그 자체로 완변한 반복자로 모든 STL알고리즘에 사용가능
     - 모든 컨테이너는 시작점과 끝다음점을 조사하는 begin, end멤버 함수 제공
--*/
#include <iostream>
#include <vector>
#include <list>
using namespace std;

// 반복자를 일반화 하여 출력하는 Print 템플릿 함수
template <typename IT>
void Print(IT s, IT e)
{
    IT it;
    for(it=s; it!=e; ++it)
        printf("%d\n", *it);
}

void main()
{
    // 포인터를 반복자로 사용
    int ari[]={1,2,3,4,5};
    int *it;
    for(it=&ari[0]; it!=&ari[5]; ++it)
        printf("%d\n", *it);

    // 반복자사용
    cout << "-------------------------------\n";
    vector<int> vi(&ari[0], &ari[5]);
    vector<int>::iterator vIt;
    for(vIt=vi.begin(); vIt!=vi.end(); ++vIt)
        printf("%d\n", *vIt);


    // 반복자를 통해 얻게 되는 일반화
    cout << "-------------------------------\n";
    list<int> li(&ari[0], &ari[5]);

    Print(&ari[0], &ari[5]);
    Print(vi.begin(), vi.end());
    Print(li.begin(), li.end());
}

