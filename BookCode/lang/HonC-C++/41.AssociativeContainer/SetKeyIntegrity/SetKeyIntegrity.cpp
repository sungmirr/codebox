/*++
    2012.10.23

    40. 연관컨테이너, 키 변경 불가 원칙(793p)
    
    키는 셋이 요소의 순서를 정하기 위해 사용하는 중요한 값이므로
    셋에 이미 들어가 있는 키를 변경해서는 안된다.

    키를 강제로 바꾸면 셋은 무결성이 깨져 이후의 어떤 동작도 보장 못한다.

    cf)동등성비교(<연산자)에 사용되는 모든 멤버변수가 키이다
    cf)객체의 멤버변수 중 키로 사용되지 않는 값을 변경하는건 합법적이다
      => 맵은 키와 값이 분리되어 있기 때문에 이 문제에 대해 안전하다
        
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
    
    dump("최초",s);
    it=s.begin();it++;it++;it++;

    // key 변경... set의 무결성이 깨진다!!
    *it=99;
    dump("수정후",s);

    it=s.find(5);
    if (it!=s.end()) 
        cout << *it << endl;
    else 
        cout << "찾는 키가 없습니다." << endl;
}
