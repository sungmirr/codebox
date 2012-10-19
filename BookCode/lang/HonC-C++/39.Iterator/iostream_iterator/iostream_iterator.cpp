/*++
    2012.10.19

    39.반복자 (691p)
    =========================================================================================
    반복자구간
    - STL,프로그래밍언어,운영체제등 0부터 시작하는 zero base이기 때문에
      끝을 제외해야 제외된 끝과 개수가 일치
    - STL에서는 범위의 끝을 제외
    - [first, last)
    - 반복자는 대소 비교가 불가능하며 항상 부등 비교
      for(;first!=last;++first)

    반복자의 종류
    - *,++,--,임의위치 이동, 비교,대입연산자 제공
    - 입력반복자(InIt)      : 오로지 입력만 가능하며 쓸수없다
    - 출력반복자(OutIt)     : 출력만 가능하며 읽지는 못한다
    - 순방향반복자(FwdIt)   : 입출력 모두 가능, 전진만 가능(++)
    - 양방향반복자(BiIt)    : FwdIt기능 + 앞뒤로이동가능, 감소연산자(--) 정의
    - 임의접근반복자(RanIt) : 임의의 요소를 참조, []연산자 정의

    - 알고리즘의 적용 조건을 제한하기 위해
    - 알고리즘원형(템플릿)에는 반복자에 대한 최소한의 요구사항 명시
      InIt find(InIt first, InIt last, const T& val);
      void sort(RanIt first, RanIt last);
    =========================================================================================
    
    입력반복자, Input Iterator(697p)
    - a=*it  // 가능
      *it=a; // 가능
    - 전위형,후위형 ++연산자
    - 같은 타입의 반복자와 상등비교 ==, !=연산자
    - ex)find

    출력반복자, Output Iterator
    - *로 쓰기기능
    - ++연산자
    - ex) OutIt copy(InIt first, InIt last, OutIt result)
          {
            while(first!=last) { *result++ = *first++; }
            return result;
          }  

    입출력반복자는 입출력 스트림에만 적용
    STL 컨테이너들은 모두 읽기, 쓰기가 동시에 가능하므로 입출력반복자 보다 더 높은 레벨의 반복자 지원

    cin의 반복자  : istream_iterator 클래스로 정의, 표준입력(키보드)로 입력받은 내용을 순회하여 읽어낼수 있다
    cout의 반복자 : ostream_iterator 클래스로 정의, 표준출력(모니터)로 문자를 출력할수 있다
--*/

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

template <typename C>
void dump(const char *desc, C &c)
{
    cout.width(12);
    cout << left << desc << "==>";
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout," "));  // typename C::value_type
    cout << endl;
}

void main()
{
    int ari[]={1,2,3,4,5};
    list<int> li(&ari[0], &ari[5]);

    // oit반복자는 콘솔 출력을 위해 정의
    // int타입, 출력스트림객체, 구분자로"."
    // oit를 통해 화면에 출력(복사)
    //ostream_iterator<int> oit(cout, ".");
    //copy(li.begin(), li.end(), oit);
    copy(li.begin(), li.end(), ostream_iterator<int>(cout,"."));
    cout << endl;

    vector<int> vi(16);
    istream_iterator<int> iit(cin);         // int타입, 생성자로 입력스트림지정
    
    copy(iit, istream_iterator<int>(), vi.begin());     // istream_iterator의 디폴드 생성자는 스트림 끝을 나타내는 반복자를 생성
    dump("입력 완료 후", vi);                           // 스트림의 끝 "Ctrl+Z"
}