/*++
    2012.10.20

    40.시퀀스컨테이너, 반복자 무효화 현상(735p)

    반복자의 무효화 규칙은 컨테이너 마다 다르다
    리스트는 자신을 삭제하는 경우를 제외하고 무효화 현상이 없다
    
    STL프로그래밍에서 삽입,삭제시 반복자를 다시 조사하는 편이 좋다
--*/ 


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main()
{
    vector<int> vi;
    vector<int>::iterator it;
    for (int i=0;i<80;i++) 
        vi.push_back(i);


    it=find(vi.begin(),vi.end(),55);
    cout << *it << endl;

    vi.erase(it+1);
    cout << *it << endl;        // 앞요소 삭제로 무효화현상 없음

    vi.erase(it-1);             // 뒷요소 삭제로 무효화현상 발생
    cout << *it << endl;

    vi.insert(vi.begin(), 1234);    // 앞요소 추가, 무효화현상 발생
}
