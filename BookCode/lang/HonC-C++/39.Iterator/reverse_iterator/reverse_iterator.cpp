/*++
    2012.10.19

    39.반복자, 역방향반복자 (720p)
    
    역방향반복자
    - 양방향 반복자나 임의접근 반복자에 어댑터를 적용하여 구현
      ++,--연산이 반대로 정의
    - 각 컨테이너는 다음 두개의 역방향 반복자 타입 제공
      reverse_iterator
      const_reverse_iterator
    - 역방향 반복자는 rbegin, rend멤버 함수로 얻는다
          [0],  [1],  [2],  [3]
      rend                 rbegin  
          begin                  end    

    - 역방향 반복자의base()멤버함수 : 원래의 순방향 반복자 리턴
      삽입,삭제 함수들은 역방향 반복자를 받아들이지 않는다. 역방향 검색한 위치에 어떤 작업을 하고 싶을때 순방향으로 변환
      역방향 검색 후 순방향 검색하고 싶을때
--*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main()
{
    int ari[] = {1, 2, 3, 4, 5};
    vector<int> vi(&ari[0], &ari[5]);
    vector<int>::reverse_iterator rit;
    for(rit=vi.rbegin(); rit!=vi.rend(); ++rit)
        cout << *rit << endl;

    // find함수는 역방향 반복자를 받아들인다
    cout << "-------------------------------" << endl;
    int ari2[]={6,2,9,2,7};
    vector<int> vi2(&ari[0],&ari[5]);

    puts(find(vi.begin(), vi.end(), 2) == vi.end() ? "없다." : "있다.");
    puts(find(vi.rbegin(), vi.rend(), 2) == vi.rend() ? "없다." : "있다.");

    // 역방향반복자의 base멤버함수
    cout << "-------------------------------" << endl;
    const char *str="c++ standard template library";
    vector<char> vc(&str[0],&str[strlen(str)]);
    
    vector<char>::reverse_iterator rit3;
    vector<char>::iterator bit3, it3;
    rit3=find(vc.rbegin(), vc.rend(), 't');  // find에서 역방향반복자 사용지 리턴값도 역방향반복자
    bit3 = rit3.base();
    it3=find(bit3, vc.end(), 'a');
    if(it3!=vc.end())
        cout << "검색 결과=" << *it3 << endl;
}