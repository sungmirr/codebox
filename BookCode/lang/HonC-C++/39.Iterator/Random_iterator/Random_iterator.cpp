/*++
    2012.10.19

    39.반복자, 임의접근반복자 (704p)
    
    Random Iterator
    - 최상위 레벨의 반복자
    - +n연산,-n연산,[]연산, +=연산, -=연산 지원
      임의의 원소에 상수시간내 이동가능
    - 배열처럼 인접한 위치에 배치되는 컨테이너에서 임의접근반복자 제공
      반복자끼리 대소비교 가능
    - ex) 벡터, 정적 배열의 위치를 가지는 포인터
          sort, binary_search 에서 임의 접근 반복자 사용


    cf) list는 임의접근이 불가능하므로 양방향반복자(BiIt) 제공
        - +연산 불가능, 대소비교 불가능
        - 반복자 끼리 뺄셈을 통해 구간의 요소 개수 구할 수 없다
        - 임의 접근이 가능하게 하려면 아래 두 함수 이용
          void advance(InIt &first, int off);
          int distance(InIt first, InIt last);

          // 오버헤드가 크다
          void advance(InIt &first, int off)
          {
          for(;off>0;--off) { ++first; }
          for(;off<0;++off) { --first; }
          }

    컨테이너는 자신이 제공하는 반복자의 종류 명시
    알고리즘은 요구하는 최소의 반복자 명시
--*/

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

void main()
{
    int ari[] = {1,2,3,4,5,6,7};
    list<int> li(&ari[0], &ari[7]);
    list<int>::iterator it;

    it=li.begin();
    printf("%d\n", *it);
    printf("%d\n", *(++it));
    //printf("%d\n", it[3]);    // 에러

    //it+=3;                    // 에러
    advance(it, 3);
    printf("%d\n", *it);
    //printf("거리=%d\n", li.end()-li.begin());   // 에러
    printf("거리=%d\n", distance(li.begin(), li.end()));  


    // 임의접근 반복자를 요구하는 sort알고리즘에 리스트의 양방향 반복자 적용
    //sort(li.begin(), li.end());    // 에러
}

