/*++
    2012.10.23

    40. 연관컨테이너, 동등성 조건(789p)

    set의 멤버함수 find는 동등성조건(<연산자)으로 검색할 키를 찾는다
    find알고리즘 함수는 동일성(==연산자)으로 검색할 키를 찾는다

    동일성(equality) 
    - ==연산자사용
    - 두 값이 완전히 같은지 검사,객체의 경우 모든 멤버가 일치하는지 검사할때 사용

    동등성(equivalent)
    - <연산자의 조합
    - !(a<b) && !(b<a)
    - !Comp(a,b) && !Comp(b,a)  // Comp는 사용자정의객체
    - 두 값이 같은 값으로 인정되는지 검사

    cf)int, double같은 타입은 객체 전체가 키이므로 동등성이 동일성과 같으며 이 둘을 같이 사용해도 상관없다
       객체의 특정 멤버중 하나를 키로 사용할 경우 동일성과 동등성이 다르다

    cf)동등성비교(<연산자)에 사용되는 모든 멤버변수가 키이다

--*/

#include <iostream>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

class President
{
public:
    int Id;
    string Name;
    string Addr;

    President(int aId,char *aName, char *aAddr) 
        : Id(aId), Name(aName), Addr(aAddr) { }

    void OutPresident() 
    {
        printf("Id:%d, 이름:%s, 주소:%s\n",Id,Name.c_str(),Addr.c_str());
    }

    // 동등성, find멤버함수에서 사용
    // Id순으로 정렬, Id가 키
    bool operator<(const President &Other) const 
    {
        return Id < Other.Id;
    }

    // 동일성, find알고리즘함수에서 사용
    bool operator==(const President &Other) 
    {
        return (Id==Other.Id && Name==Other.Name && Addr==Other.Addr);
    }
};

void main()
{
    set<President> King;
    set<President>::iterator it;
    King.insert(President(516,"박정희","동작동"));
    King.insert(President(1212,"전두환","연희동"));
    King.insert(President(629,"노태우","강북"));
    King.insert(President(3030,"김영삼","상도동"));
    King.insert(President(1234,"김대중","강남"));

    for(it=King.begin(); it!=King.end(); ++it)
        (*it).OutPresident();


    President ZeroThree(3030,"아무개","아무데나");
    // 멤버find
    it = King.find(ZeroThree);
    if(it!=King.end())
    {
        cout << "검색되었음" << endl;
        (*it).OutPresident(); 
    }

    // 전역find
    it = find(King.begin(), King.end(), ZeroThree);
    if(it!=King.end())
    {
        cout << "검색되었음" << endl;
        it->OutPresident();//(*it).OutPresident(); 
    }
}