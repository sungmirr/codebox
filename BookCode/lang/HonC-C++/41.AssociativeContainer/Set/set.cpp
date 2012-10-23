/*++
    2012.10.23

    40. 연관컨테이너, set(774p)
    
    셋
    - 저장하는 데이터 자체가 키로 사용하며 데이터는 저장않는다
    - 정렬된 위치에 삽입되며, 검색 속도가 빠르다
    - 중복 허용 않는다, multiset은 중복허용
    - 디폴트로 미만 비교로 정렬, 검색이 목적이면 정렬방식을 바꿀필요없다
    
    셋의 내부자료형
    value_type,iterator,const_iterator,refrence등..
    key_type        : 키의 타입, value_type과 동일하며 맵은 키와 값의 pair타입으로 정의
    key_compare     : 키를 비교하는 함수 객체 타입, 디폴트로 less
    value_compare   : 값을 비교하는 함수 객체 타입, 셋은 key_compare와 동일한 타입으로 정의,
                      맵에서는 pair를 비교

    생성자
    explicit set(const BinPred& cmp = BinPred());
    set(const set& x);
    set(InIt first, InIt last, const BinPred& comp=BinPred());
    cf)multiset도 동일

    삽입,삭제
    - set의 insert
      pair<iterator, bool> insert(const value_type& val);  // 삽입위치와 삽입 성공여부가 pair로 리턴 
                                                           // set은 중복허용하므로 val이존재할경우 실패
    - multiset의 insert
      iterator insert(const value_type& val);  // 중복허용하므로 삽입은 항상 성공, 반복자만 리턴
    - set,multiset insert(공통)
      iterator insert(iterator it, const value_type& val);  // it는 위치에대한 힌트일뿐 아무 위치나 지정해도 삽입은 정렬후 저장
                                                            // set..실패할경우 중복된 val의 위치가 리턴, 성공시 위치 리턴
      void insert(iterator first, iterator last);      
    - iterator erase(iterator it);
    - iterator erase(iterator first, iterator last);
    - size_type erase(const Key& key);

    검색(검색실패시 end()리턴)
    - iterator find(const Key& val);
    - const_iterator find(const Key& val) const;
    cf)알고리즘함수 find보다 멤버 find가 이진트리검색을 사용하므로 빠르다
       multiset의 경우 이진트리의 특성상 중복된 키중 어떤것이 검색될 지 알 수 없다
       알고리즘함수 find는 순차검색을 진행하므로 중복되는 값중 첫요소 검색

    multiset의 중복값 검색
    [ 1, 2, 3, 4, 5, 7, 7, 7, 7, 7, 10, 13, 13 ]    
    - iterator lower_bound(const Key& key);     // 중복되는 값중 첫요소
    - iterator upper_bound(const Key& key);     // 중복되는 값중 마지막요소의 다음
    - pair<iterator, iterator> equal_range(const Key& key);  // 처음과 끝의 반복자 쌍

--*/

#include <iostream>
#include <set>
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
    int ar[]={1,4,8,1,9,6,3};

    set<int> s;
    for(int i=0; i < sizeof(ar)/sizeof(ar[0]); ++i)
        s.insert(ar[i]);        // 두번째 1삽입은 실패
    dump("원본", s);

    set<int> s2;
    s2=s;
    dump("사본",s2);

    const char *str="ASDFASDFGHJKL";
    set<char> sc(&str[0], &str[13]);
    dump("문자셋", sc);
    multiset<char> msc(&str[0], &str[13]);
    dump("문자멀티셋", msc);
    
    sc.erase('A');
    dump("문자셋 A제거", sc);
    msc.erase('A');
    dump("문자멀티셋 A제거", msc);      // 모든 'A'제거

    set<char>::iterator it;
    multiset<char>::iterator mit;

    it = sc.find('J');                  // it = find(sc.being(), sc.end(), 'J');
    if(it!=sc.end())
        cout << *it << endl;
    else
        cout << "찾는 키가 없습니다" << endl;

    mit = msc.find('Z');
    if(mit!=msc.end())
        cout << *mit << endl;
    else
        cout << "찾는 키가 없습니다" << endl;
}