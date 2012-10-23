/*++
    2012.10.20

    40.시퀀스컨테이너, 사용자정의요소(747p)

    클래스 내부에서 동작할당하는 객체의 벡터
    - 동적할당하는 클래스는 기본적으로 생성자, 가상 파괴자, 복사생성자, 대입연산자를 적절히 정의

    동적할당하는 객체 Dynamic은 벡터템플릿의 요구 조건을 모두 만족해야 한다.
    vector<Dynamic> vd;
    Dynamic a("dog");
    Dynamic b("cog");

    vd.push_back(a);                    // 벡터 끝에 추가할때 복사가 발생 => 복사 생성자 필요
    Dynamic c;
    c=vd[1];                            // 대입 연산자 필요
    Dynamic d("cat");
    find(vd.begin(), vd.end(), d);      // ==연산자 필요
    sort(vd.begin(), vd.end());         // < 연산자 필요
--*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Dynamic
{
private:
    char *ptr;
public:
    Dynamic()
    {
        ptr = new char[1];
        ptr[0] = 0;
    }

    Dynamic(const char* str)
    {
        ptr = new char[strlen(str)+1];
        strcpy(ptr, str);
    }

    // 복사생성자
    Dynamic(const Dynamic& d)
    {
        ptr = new char[strlen(d.ptr)+1];
        strcpy(ptr, d.ptr);
    }

    // 대입연산자
    Dynamic &operator=(const Dynamic& d)
    {
        if(this != &d)
        {
            delete [] ptr;
            ptr = new char[strlen(d.ptr)+1];
            strcpy(ptr, d.ptr);
        }
        return *this;
    }

    // 상등연산자(find)
    bool operator==(const Dynamic& d) const
    {
        return (strcmp(ptr, d.ptr) == 0 ? true : false);
    }

    // 대소연산자(sort)
    bool operator<(const Dynamic& d) const
    {
        return strcmp(ptr, d.ptr) < 0;
    }

    // 가상파괴자
    virtual ~Dynamic()
    {
        delete [] ptr;
    }

    virtual void OutDynamic()
    {
        cout << ptr << ' ';
    }
}; 

template<typename C> 
void dump(const char *desc, C c) 
{ 
    cout.width(12);cout << left << desc << "==> ";
    for (unsigned i=0;i<c.size();i++) { c[i].OutDynamic(); }
    cout << endl; 
}


void main()
{
    vector<Dynamic> vd;
    Dynamic a("dog");
    Dynamic b("cow");
    vd.push_back(a);
    vd.push_back(b);
    dump("요소 2개",vd);

    Dynamic c;
    c=vd[1];

    vector<Dynamic>::iterator it;
    Dynamic d("cat");
    it = find(vd.begin(), vd.end(), d);
    if(it==vd.end()) cout << "cat이 없다" << endl;

    sort(vd.begin(), vd.end());
    dump("정렬 후",vd);
}
