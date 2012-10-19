/*++
    2012.10.19

    39.반복자, 상수반복자 (718p)
    
    상수반복자
    - 상수레퍼런스를 리턴하므로 값을 변경할 수 없고, 읽을 수만 있다
    - 상수반복자가 가리키는 상수이지, 반복자 자체가 상수가 이니므로 전후로 이동 가능
    - 상수컨테이너를 인수로 받는 함수 내에서 컨테이너는 상수성을 가지며, 상수반복자만 사용가능
    ex) vector<int>::const_iterator cit = vi.begin();
--*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 상수 컨테이너를 인수로 받는 함수
int vectorsum(const vector<int> &cvt)
{
    vector<int>::const_iterator cit;
    int sum=0;

    for(cit=cvt.begin(); cit!=cvt.end(); ++cit)
        sum += *cit;

    //*cit = 1234;  //에러

    find(cvt.begin(), cvt.end(), 60);     // 사용가능
    //sort(cvt.begin(), cvt.end());       // 에러
    return sum;
}

void main()
{
    int ari[] = {80, 98, 75, 60, 100};
    vector<int> vi(&ari[0], &ari[5]);

    int sum;
    sum = vectorsum(vi);
    printf("총 합은 %d입니다\n", sum);
}