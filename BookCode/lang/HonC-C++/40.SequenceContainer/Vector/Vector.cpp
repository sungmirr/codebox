/*++
    2012.10.20

    40.시퀀스컨테이너, 벡터(725p)

    1. 벡터 클래스 템플릿에 정의된 타입(typedef)
    - 모든 컨테이너는 자신이 정의하는 타입을 약속된 이름으로 제공해야 
      반복자나 알고리즘에서 컨테이너를 조작하기 위해 미리 정의된 타입을 사용  

    - value_type         : 컨테이너 요소의 타입
      (const_) pointer   : 요소를 가리키는 포인터 타입
      (const_) reference : 요소의 레퍼런스 타입
      (const_) iterator  : 우리는 iterator타입으로 변수를 선언해 사용
      (const_) reverse_iterator
      difference_type    : 두 반복자의 차를 표현하는 타입, 통산 int
      size_type          : 크기를 표현하는 타입, 통상 unsigned


    2. 벡터의 생성자
    explicit vector();
    explicit vector(size_type n, const T& v = T());
    vector(const vector& x);    //복사생성자
    vector(const_iterator first, const_iterator last);

    3. 벡터의 메모리 관련 멤버함수
    size        : 요소 개수
    max_size    : 벡터가 관리 할 수 있는 최대 요수 개수
    capacity    : 할당된 요소개수(메모리의 크기)
    resize(n)   : 크기를 변경, 새크기가 더 클경우 새로할당된 요소는 디폴트값으로 초기화
    reserve(n)  : 최소한의 크기를 지정하며, 메모리를 미리 할당
    clear       : 모든 요소를 삭제
    empty       : 비어 있는지 조사
    
    cf) empty와 size()==0
        요소가 많은 경우 size()는 일일이 세어본다.. 오버헤드가 크다
        empty는 0인지 아닌지만 체크

    4. 벡터의 삽입삭제 멤버 함수
    void push_back(const T& x); 
    void pop_back();            //제거
    iterator insert(iterator it, const T& x=T());
    void insert(iterator it, size_type n, const T& x);
    void insert(iterator it, const_iterator first, const_iterator last);
    iterator erase(iterator it);
    iterator erase(iterator first, iterator last);

    cf) 컨테이너 구조가 상이하기 때문에 삽입, 삭제 방식도 컨테이너별로 다르다
        삽입,삭제 함수는 일반 알고리즘으로 제공되기 보다 컨테이너의 멤버 함수로 제공
        insert, erase는 요소를 관리하는 기본 동작이므로 대부분의 컨테이너에서 동일한 이름과 형식으로 존재 

    5. 벡터의 연산자
    대입 : =(전체), assign(일부구구만 복사)
    교환 : swap
    비교 : ==,!=, <,>,<=,>=
    요소참조 : [], at
--*/ 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<typename C>
void dump(const char *desc, const C &c)
{
    cout.width(12);
    cout << left << desc << "==>";
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " "));
    cout << endl;
}

void main()
{
    vector<string> v1;
    dump("v1", v1);

    vector<double> v2(10);
    dump("v2", v2);

    vector<int> v3(10,7);
    dump("v3", v3);

    vector<int> v4(v3);
    dump("v4", v4);

    v4.clear();
    dump("v4 clear", v4);

    if(v4.empty())
        cout << "v4는 요소가 없다"  << endl;

    int ar[]={1,2,3,4,5,6,7,8};
    vector<int> v5(&ar[2], &ar[5]);
    dump("v5", v5);

    
}