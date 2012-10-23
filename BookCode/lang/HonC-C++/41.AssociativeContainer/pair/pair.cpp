/*++
    2012.10.23

    40. 연관컨테이너, pair(771p)

    ================================================================================================
    연관컨테이너(Associative Container)
    - 이진 트리에 데이터를 정렬하여 저장하고 검색할 때는 이진 트리 검색을 사용
    - 삽입 위치를 지정할 수 없다, 자동으로 삽입 위치 결정
    - 삽입속도는 시퀀스보다 느리지만 검색 속도는 월등하다
    cf) 균형잡힌이진트리 or 해쉬테이블(메모리낭비,데이터분포도에 따라 검색속도가 운에좌우) or 이진트리
      => 이진트리가 데이터 종류에 상관없이 일정한 성능 보장, 메모리낭비가 심하지 않다
      => STL표준에서는 이진트리방식의 연관컨테이너만 제공

    종류
    - 셋 : 중복불허, 키만 저장
    - 멀티셋 : 중복허용, 키만 저장
    - 맵 : 중복불허, 키+값
    - 멀티맵 : 중복허용, 키+값

    연관컨테이너의 반복자는 모두 양방향 반복자
    - 검색이 워낙 빨라 이분검색 할 필요없다
    - 순서대로 순회하면 정렬된 결과를 얻을 수 있다
    ================================================================================================

    pair
    - 키와 값의 쌍을 표현하는 템플릿 구조체
    - 두 개씩 짝을 이룬 데이터를 다루거나 한꺼번에 두개의 값을 리턴하고 싶을 때 사용
    - utility 헤더파일(다른stl파일에포함되있음)
    - make_pair(val1,val2) : 템플릿함수, pair를 생성해 리턴
    - template<class T1, class T2>
      struct pair
      {
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;
        pair() : first(T1()), second(T2()) {}
        pair(const T1& v1, const T2& v2) : first(v1), second(v2) {}
      };
--*/ 
#include <iostream>
#include <string>
//#include <utility>

using namespace std;

typedef pair<string,double> sdpair;

sdpair GetPair()
{
#if 0
    sdpair temp;
    temp.first = "문자열";
    temp.second = 1.234;
    return temp;
#else
    return make_pair("문자열", 1.234);
#endif
}

void main()
{
    sdpair SD;
    SD = GetPair();

    cout << SD.first << "," << SD.second << endl;
}