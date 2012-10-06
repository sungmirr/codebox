/*++
    2012.10.06

    31.1 SwapPerson(362p)
        class를 template 함수에 적용시
        template 함수에서 사용되는 연산자를 오버로딩해줘야한다
        cf) default로 생성자, 소멸자, 복사생성자 정의
 --*/

#include "Turboc.h"

template <typename T>
void Swap(T &a, T &b)
{
    // Swap을 사용하는 객체는 대입연산자 필요
    T t;
    t=a; a=b; b=t;
}

class Person
{
private:
    char *name;
    int age;

public:
    Person()
    {
        name = new char[1];
        name[0] = NULL;
        age=0;
    }
    Person(const char *name_, int age_)
    {
        int len = strlen(name);
        name = new char[len+1];
        strcpy(name, name_);
        age = age_;
    }
    Person(const Person &p)
    {
        int len = strlen(p.name);
        name = new char[len+1];
        strcpy(name, p.name);
        age = p.age;
    }
    virtual ~Person()
    {
        delete [] name;
    }

    // 대입연산자
    Person &operator=(const Person &p)
    {
        if(this != &p)
        {
            delete [] name;
            int len = strlen(p.name);
            name = new char[len+1];
            strcpy(name, p.name);
            age = p.age;
        }
   
        return *this;
    }
    void OutPerson()
    {
        printf("이름:%s, 나이:%d\n", name, age);
    }
};


void main()
{
    Person A("이승만", 10);
    Person B("박정희", 20);

    A.OutPerson();
    B.OutPerson();

    Swap(A, B);

    A.OutPerson();
    B.OutPerson();
}