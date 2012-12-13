/*++
    2012.10.23

    40. 연관컨테이너, map(798p)

    map
    - template<class Key, class T, class BinPred = less<Key>, class A = allocator<T> >
      class map { ... }
    
    map의 내부자료형
    - set과 동일하지만 아래 두 요소만 다름
    - set: key_type과 value_type이 같음
      set: key_compare와 value_compare가 같은 함수 객체
      map: key_type과 value_type이 다르게 정의
      map: key_compare와 value_compare가 다른 함수 객체
    - value_type : 키와 값의 pair타입
      value_compare: 키 만으로 비교를 수행하는 함수

    생성자
    - explicit map(const BinPred& comp = BinPred());
      map(const map& x);
      map(InIt first, InIt last, const BinPred& comp = BinPred()); // 같은 타입의 맵끼리 구간 복사 가능
                                                                   // 타입이 key와 값을 쌍으로 가지는 pair이기 때문

    map의 반복자
    - 양방향 반복자

    삽입,삭제
    - value_type이 pair객체인점만 제외하면 set과 완전 동일
    - pair<iterator, bool> insert(const value_type& val);
    - iterator insert(iterator it, const value_type& val);
    - void insert((iterator first, iterator last);
      cf) 맵에 삽입되는 요소인 value_type은 키와 값을 쌍으로 가지는 pair객체야만 한다
          m.insert(pair<string,int>("문자열",1234);
    
    - iterator erase(iterator it);
    - iterator erase(iterator first, iterator last);
    - size_type erase(const Key& key);

     map에만 있는 삽입방법, multimap에는 사용불가
     - []연산자와 대입 연산자로 요소 삽입
     - T& operator[](const Key& k);
     - ex)[키]=값;   ex)m["문자열"] = 1234;

    검색
    - iterator find(const Key& val);
    - const_iterator find(const Key& val) const;
    - 멀티맵 : upper_bound, lower_bound... 셋,멀티셋과 같다
    - 맵검색에 전역 find알고리즘 사용할 수 없다
      it = find(m.begin(), m.end(), "부산");
      it = find(m.begin(), m.end(), pair<string,int>("부산",500)  
      // pair는 ==연산 지원안함
      // 지원해도 "부산",500데이터를 알고있어야 하는데 알고있는 데이터 검색 자체가 넌센스
    
    수정
    - []연산자는 키가 없으면 삽입, 존재할 경우 해당 요소의 값에 대한 리퍼런스 리턴
    - 키는 절대 변경안된다, 값은 변경가능하다

--*/ 
#include <iostream>
#include <string>
#include <map>
using namespace std;
/*
void main()
{
    // 키: string, 값: int
    map<string,int> m;
    map<string,int>::iterator it;

    // 삽입
    m.insert(pair<string,int>(string("서울"), 1000));
    m.insert(pair<string,int>("부산",500));
    m["대전"]=400;
    m["대구"]=300;
    m["광주"]=200;
    m["인천"]=100;
    m["독도"]=1;

    // 삭제
    m.erase(m.begin());
    m.erase("인천");

    // 순회, 키와 값 출력
    for(it=m.begin(); it!=m.end(); ++it)
        cout << it->first << " : " << it->second << endl;

    // 검색
    it=m.find("부산");
    if(it==m.end())
        cout << "맵에 없는 도시입니다." << endl;
    else
        cout << it->first << "의 인구는 " << it->second << "만 명이다." << endl;

    // 수정
    m["부산"]=5;   // 없으면 삽입 있으면 수정
    it=m.find("부산");
    cout << it->first << "의 인구는 " << it->second << "만 명이다." << endl;

    it->second=555;
    cout << it->first << "의 인구는 " << it->second << "만 명이다." << endl;
}
*/

class EST
{
    friend struct ESTComp;
private:
    int x;
    int y;
    int z;
public:
    EST(int ax, int by, int az) : x(ax), y(by), z(az) { }
    void PrintEST()
    {
        cout << x << " " << y << " " << z << endl;
    }

};


struct ESTComp
{
    bool operator<(const EST &a, EST &b) const
    {
        if(b.x > a.x)
        {
            return true;
        }
        else if(b.x == a.x)
        {
            if(b.y > a.y)
            {
                return true;
            }
            else if(b.y==a.y)
            {
                if(b.z > a.y)
                    return true;
            }
        }

        return false;
    }
};




void main()
{
    map<string,EST> m;

    m.insert(make_pair("AAA", EST(1,2,3)));
    m.insert(make_pair("BBB", EST(2,2,3)));
    m.insert(make_pair("CCC", EST(4,2,3)));
    m.insert(make_pair("DDD", EST(4,2,6)));
    m.insert(make_pair("EEE", EST(4,1,3)));

    map<string,EST>::iterator it;
    for(it=m.begin(); it!=m.end(); ++it)
    {
        cout << it->first << " : ";
        it->second.PrintEST();
    }

    it = find_if()

}