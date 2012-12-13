/*++
    2012.10.19

    39.반복자, 삽입반복자 (713p)
    
    1-1 삽입반복자 타입 생성(클래스템플릿)
    insert_iterator<Container> 
     - insert멤버함수를 사용하여 중간에 삽입
     - 모든 컨테이너에서 사용 가능
     - 생성자 인수로 컨테이너와 삽입 위치를 지정하는 반복자 전달
    front_insert_iterator<Container> 
     - push_front멤버함수를 사용해 선두에 삽입
     - 리스트, 데크에서 사용, 벡터는 사용불가
    back_insert_iterator<Container>
     - push_back멤버함수를 사용해 끝에 추가
     - 모든 컨테이너에서 사용가능



    1-2 삽입반복자를 생성하여 리턴하는 템플릿함수
    insert_iterator<Container> inserter(Container& Cont, Iterator it);      // 인자1: 컨테이너, 인자2: 삽입위치
    front_insert_iterator<Container> front_inserter(Container& Cont);
    back_insert_iterator<Container> back_inserter(Container& Cont);

    ex) insert_iterator<Container> insit = inserter(vi, vi.begin()+2);
--*/

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

template<typename C>
void dump(const char *name, C &c)
{
    cout.width(12);
    cout << left << name << "==>";
    copy(c.begin(), c.end(), ostream_iterator<typename C::value_type>(cout, " "));
    cout << endl;
}

void main()
{
    int ari[] = {1,2,3,4,5};
    int ari2[] = {6,7,8,9,10,11,12,13,14,15};

    vector<int> vi(&ari[0], &ari[5]);
    vector<int>::iterator it;
    it = find(vi.begin(), vi.end(), 4);
    // 복사할때 vi 컨테이너의 용량을 넘어서서 에러 발생
    //copy(&ari2[0], &ari2[10], it);   //에러
    // dump("복사후", vi);          
    

    // Insert Iterator를 사용해 삽입
    //insert_iterator<vector<int> > iit(vi, it);
    insert_iterator<vector<int> > iit(vi, find(vi.begin(), vi.end(), 4));
    copy(&ari2[0], &ari2[10], iit);     
    //*iit = 99;
    //*iit = 100;
    dump("삽입후", vi);
 

    // inserter
    cout << "----------------------------------------\n";
    copy(&ari2[0], &ari2[10], inserter(vi, find(vi.begin(), vi.end(), 4)));
    dump("삽입후", vi);

    // revcopy
    cout << "----------------------------------------\n";
    list<int> li;
    copy(&ari[0], &ari[5], front_inserter(li));
    copy(li.begin(), li.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // 입력값의 개수가 정해지지 않을 경우 insert활용
    cout << "----------------------------------------\n";
    cout << "input int(ctrl+z) : ";
    vector<int> vi2;
    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(vi2));
    copy(vi2.begin(), vi2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

}