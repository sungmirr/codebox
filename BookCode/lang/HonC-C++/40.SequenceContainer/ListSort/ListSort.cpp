/*++
    2012.10.23

    40.시퀀스컨테이너, 리스트(765p)
    
    리스트의 정렬
    - 리스트는 임의 접근 반복자를 제공하지 않으므로 정렬 속도가 대단히 느리다
    - sort알고리즘 함수를 사용하지 못하는 대신, sort멤버함수를 사용
    - 리스트에 정렬할 자료를 저장하는것은 애초에 선택이 잘못됨
      꼭 필요한 경우만 사용

    unique, 두번이상 중복된 중복요소 제거
    void unique();
    void unique(UniPred op);
    cf)알고리즘으로 제공되는 unique도 있지만 멤버함수는 링크구조를 활용

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

    dump("원본",li0);
    li0.sort();
    dump("sort후",li0);
    li0.unique();
    dump("unique후",li0);


    randomize();
    vector<int> vi;
    list<int> li;
    int i;
    clock_t start;

    for (i=0;i<NUM;i++) {
        vi.push_back(random(100));
        li.push_back(random(100));
    }
    cout << "키를 누르면 벡터를 정렬합니다." << endl;
    getch();
    start=clock();
    sort(vi.begin(),vi.end());
    cout << "벡터 정렬완료. 소요시간 = " << clock()-start << endl;

    cout << "키를 누르면 리스트를 정렬합니다." << endl;
    getch();
    start=clock();
    li.sort();
    cout << "리스트 정렬완료. 소요시간 = " << clock()-start << endl;
}
