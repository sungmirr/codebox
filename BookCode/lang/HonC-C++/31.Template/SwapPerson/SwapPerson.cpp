/*++
    2012.10.06

    31.1 SwapPerson(362p)
        class�� template �Լ��� �����
        template �Լ����� ���Ǵ� �����ڸ� �����ε�������Ѵ�
        cf) default�� ������, �Ҹ���, ��������� ����
 --*/

#include "Turboc.h"

template <typename T>
void Swap(T &a, T &b)
{
    // Swap�� ����ϴ� ��ü�� ���Կ����� �ʿ�
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

    // ���Կ�����
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
        printf("�̸�:%s, ����:%d\n", name, age);
    }
};


void main()
{
    Person A("�̽¸�", 10);
    Person B("������", 20);

    A.OutPerson();
    B.OutPerson();

    Swap(A, B);

    A.OutPerson();
    B.OutPerson();
}