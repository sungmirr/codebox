/*++
    2012.10.23

    40.시퀀스컨테이너, 리스트(756p)

    1.리스트
    - 이중연결리스트를 템플릿으로 추상화한 버전
    - 리스트가 제공하는 내부타입, 벡터와 동일
      value_type         : 컨테이너 요소의 타입
      (const_) pointer   : 요소를 가리키는 포인터 타입
      (const_) reference : 요소의 레퍼런스 타입
      (const_) iterator  : 우리는 iterator타입으로 변수를 선언해 사용
      (const_) reverse_iterator
      difference_type    : 두 반복자의 차를 표현하는 타입, 통산 int
      size_type          : 크기를 표현하는 타입, 통상 unsigned

    2. 리스트와 벡터의 차이점
    - 반복자레벨, 벡터 RanIt, 리스트 BiIt, 반드시 순회로 원하는 요소 접근(+n,[]연산불가능)
    - 상수시간에 임의의 위치에 삽입,삭제가능
      push_front, pop_front 제공
      capacity, reserve불필요
    - 벡터에 비해 링크요소때문에 메모리 사용량이 크고, 메모리 단편화가 심하다
    - 반복자 무효화의 경우.. 가리키는 요소가 삭제시만 발생
    => 벡터는 일기에 강하고 리스트는 쓰기에 강하다
       읽기가 빈번하면 벡터, 삽입,삭제가 빈번하면 리스트를 선택

    3. 리스트의 생성자(벡터와 동일)
    explicit list();
    explicit list(size_type n, const T& v = T());
    list(const vector& x);    //복사생성자
    list(const_iterator first, const_iterator last);

    4. 삽입,삭제(벡터와 동일)
    iterator insert(iterator it, const T& x=T());
    void insert(iterator it, size_type n, const T& x);
    void insert(iterator it, const_iterator first, const_iterator last);
    iterator erase(iterator it);
    iterator erase(iterator first, iterator last);

    5. 특정값을 가지는 모든 요소 삭제
    void remove(const Type& val);
    void remove_if(UniPred F);
    cf)전역 remove알고리즘함수.. 동작방식이 다르다

    6. 이외 멤버함수
    void swap(list& Right);
    void reverse();
    void merge(list& Right);
    cf)전역 알고리즘 제공, but 리스트의 멤버함수를 사용하면 리스트의 링크를 이용..빠르게동작

    7. splice
    void splice(iterator it, list& x);
    void splice(iterator it, list& x, iterator first);
    void splice(iterator it, list& x, iterator first, iterator last);

    8. unique, 두번이상 중복된 중복요소 제거 (ListSort프로젝트에 예제있음)
    void unique();
    void unique(UniPred op);

--*/ 

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

template <typename C>
void dump(const char *dest, C &c)
{
    cout.width(12);
    cout << left << dest << "==>";
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " "));
    cout << endl;
}

void main()
{
    // 보통 빈리스트로 생성 후, push(pop)_front(back)함수를 사용 요소 첨삭
    list<int> li;
    list<int>::iterator it;

    li.push_back(8);
    li.push_back(9);
    li.push_front(2);
    li.push_front(1);

    for(it=li.begin(); it!=li.end(); ++it)
        printf("%d\n", *it);

    cout << "--------------------------------------" << endl;
    const char *str = "abcdefghij";
    list<char> lc(&str[0], &str[10]);
    list<char>::iterator it2;

    dump("최초", lc);
    it2=lc.begin(); 
    //it2++;it2++;it2++;it2++;it2++;      // advance
    advance(it2,5);
    lc.insert(it2, 'Z');
    dump("Z삽입", lc);
    it2=lc.end();
    it2--;it2--;it2--;
    lc.erase(it2);
    dump("h삭제", lc);


    cout << "--------------------------------------" << endl;
    const char *str3="double linked list class";
    list<char> li3(&str3[0],&str3[strlen(str3)]);

    dump("최초", li3);
    li3.remove('l');
    dump("l삭제",li3);
}

