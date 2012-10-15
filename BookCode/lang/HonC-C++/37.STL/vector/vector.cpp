/*++
    2012.10.15

    ============================================================================
    STL의 구조
     - 컨테이너
     - 알고리즘
     - 반복자(iterator)
     - 함수 객체 
     - 어댑터
     - 할당기

     시퀀스컨테이너(Sequence Container)
      - 자료의 선형적인 집합
      - 임의 위체에 원하는 요소를 마음대로 삽입, 삭제
      - ex) vector, list, deque
     연관컨테이너(Associative Container)
      - 정렬, 해시등의 방법을 통해 삽입되는 자료를 일정한 기준에 맞는 위치에 저장
      - 검색 속도가 빠르다
      - ex) set, map
     어댑터 컨테이너(Adapter Container)
      - 시퀀스컨테이너를 변형하여 미리 정해진 일정한 방식에 따라 관리
      - 자료를 넣고 빼는 순서를 컨테이너의 규칙대로 조작
      - ex) stack, queue, priority_queue
     
     cf) 리스트는 검색은 느리지만 삽입, 삭제가 빨라 수시로 변하는 자료에 적합
         벡터는 삽입, 삭제가 느리지만 일기 속도가 빨라 대용량 참조용 자료에 적합

         함수객체는 알고리즘의 활용성을 높이는 역활
         어댑터는 다른 요소들을 약간만 수정하여 형태를 변형
         할당기는 컨테이너의 메모리를 관리하는 객체
     ============================================================================

     37.STL개요(631p)
      
     vector
      - 동적 배열
      - 단순한 첨자 연산만으로도 원하는 요소를 빠르게 읽고 쓸수 있다
        임의의 요소로 이동하는 동작도 상수 시간에 수행
        => 정렬, 이분 검색등의 알고리즘에 효율적
      - 중간에 삽입 삭제 속도는 느리다
      - 정적 배열의 크기는 반드시 상수로만 지정
        벡터는 실행 중에 생성되므로 변수로도 크기를 지정할 수 있다

      - []연산자, push_back(), size()
--*/

#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

void main()
{
    int num;
    int i;

    printf("배열 크기를 입력하시오:");
    scanf("%d", &num);
    vector<int> vi(num);

    for(i=0;i<num;++i)
        vi[i]=i*2;

    for(i=0;i<num;++i)
        printf("vi[%d]=%d\n",i,vi[i]);

    printf("벡터의 크기는 %d입니다\n", vi.size());

    printf("-------------------------\n");
    vector<int> vi2;

    for(i=0; i<10;++i)
        vi2.push_back(i*2);

    for(i=0;i<10;++i)
        printf("vi2[%d]=%d\n",i,vi2[i]);

    printf("벡터의 크기는 %d입니다\n", vi2.size());
}