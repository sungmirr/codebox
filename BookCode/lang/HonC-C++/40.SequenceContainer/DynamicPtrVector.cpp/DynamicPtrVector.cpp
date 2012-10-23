/*++
    2012.10.20

    40.시퀀스컨테이너, 사용자정의요소(747p)

    vector<Dynamic>을 vector<Dynamic *>로 변환
    => 검색, 정렬시 포인터비교...무의미... 함수객체(sort,find_if)를 사용
    => 신경써야 할 것들이 많고 불편하기 때문에 벡터에는 통상 값을 저장한다

--*/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


// DynamicVector의 클래스 원형에 find,sort를 위한 함수객체를 정의
// 해당 함수객체를 클래스의 프랜드로 선언
// main에서는 find_if, sort호출시 함수객체 사용
class Dynamic
{
    friend struct DynCompare;
    friend struct DynFind;
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

struct DynCompare
{
    bool operator()(Dynamic *a, Dynamic *b) const
    {
        return strcmp(a->ptr, b->ptr) < 0;
    }
};

#if 1
struct DynFind
{
    bool operator()(Dynamic *a) const
    {
        return (strcmp(a->ptr, "cat")==0? true:false);
    }
};
#endif

#if 0
struct DynFind : public binary_function<void *, char *, bool>
{
    bool operator()(Dynamic *a, const char *) const
    {
        return (strcmp(a->ptr, "cat")==0? true:false);
    }
};
#endif

template<typename C> 
void dump(const char *desc, const C& c) 
{ 
    cout.width(12);cout << left << desc << "==> ";
    for (unsigned i=0;i<c.size();i++) { c[i]->OutDynamic(); }
    cout << endl; 
}

void main()
{
    vector<Dynamic *> vd;
    vd.push_back(new Dynamic("dog"));
    vd.push_back(new Dynamic("cow"));
    dump("요소 2개",vd);

    /*
    Dynamic c;
    c=vd[1];
    */
    Dynamic d("cat");
    puts(find_if(vd.begin(),vd.end(),DynFind())==vd.end() ? "없다":"있다");
    sort(vd.begin(), vd.end(), DynCompare());
    //sort(vd.begin(), vd.end(), bind2nd(DynCompare(),"cat"));
    dump("정렬 후",vd);

    vector<Dynamic *>::iterator it;
    for (it=vd.begin();it!=vd.end();it++) 
    {
        delete *it;
    }
}

#if 0
// 나쁜 예........ 포인터벡터 지원을 위해 class의 인자값을 포인터로 바꾸면 안된다..
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
    Dynamic(const Dynamic* d)
    {
        ptr = new char[strlen(d->ptr)+1];
        strcpy(ptr, d->ptr);
    }

    // 대입연산자
    Dynamic *operator=(const Dynamic* d)
    {
        if(this != d)
        {
            delete [] ptr;
            ptr = new char[strlen(d->ptr)+1];
            strcpy(ptr, d->ptr);
        }
        return this;
    }

    // 상등연산자(find)
    bool operator==(const Dynamic* d) const
    {
        return (strcmp(ptr, d->ptr) == 0 ? true : false);
    }

    // 대소연산자(sort)
    bool operator<(const Dynamic* d) const
    {
        return strcmp(ptr, d->ptr) < 0;
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
#endif