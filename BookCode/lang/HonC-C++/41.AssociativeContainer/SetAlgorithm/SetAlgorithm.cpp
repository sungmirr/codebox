/*++
    2012.10.23

    40. 연관컨테이너, 집합연산(795p)

    집합연산알고리즘
    - 합집합,교집합,차집합,대칭차집합,포함 여부 등의 집합 관련 연산 기능 제공
    - 전역 알고리즘 함수라 임의의 컨테이너와 함께 사용 가능
    - 해당 컨테이너는 효율적인 합집합 연산을 위해 반드시 정렬된 상태로 사용
    


    // [first1~last1)와 [first2~last2)사이의 집합관련 연산을 수행해 result에 기록
    // 입력반복구간은 꼭 셋일 필요 없고 정렬괸 벡터나 리스트 구간도 사용가능
    // result에는 임의의 컨테이너에 결과저장가능, 충분한 공간이 있거나 back_inserter를 사용
    OutIt set_union(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt result);
    OutIt set_intersection(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt result);     
    OutIt set_difference(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt result);
    OutIt set_sysmmetric_difference(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt result);
    bool include(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2);         // 두반복자 구간이 포함관계에 있는지 조사
--*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
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
    int i;
    int ar1[]={7,0,0,6,2,9,1,9,1,4,9,2,0};
    int ar2[]={9,1,7,6,0,0,4,0,5,1,8};
    set<int> s1;
    for (i=0;i<sizeof(ar1)/sizeof(ar1[0]);i++) {
        s1.insert(ar1[i]);
    }
    set<int> s2;
    for (i=0;i<sizeof(ar2)/sizeof(ar2[0]);i++) {
        s2.insert(ar2[i]);
    }


    vector<int> v;
    set_union(s1.begin(),s1.end(),s2.begin(),s2.end(),back_inserter(v));
    dump("합집합", v);

    v.clear();
    set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(),back_inserter(v));
    dump("교집합", v);

    v.clear();
    set_difference(s1.begin(),s1.end(),s2.begin(),s2.end(),back_inserter(v));
    dump("차집합", v);

    v.clear();
    set_symmetric_difference(s1.begin(),s1.end(),s2.begin(),s2.end(),back_inserter(v));
    dump("대칭차", v);
}