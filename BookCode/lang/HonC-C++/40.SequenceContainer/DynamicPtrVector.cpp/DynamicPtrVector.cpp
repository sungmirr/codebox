/*++
    2012.10.20

    40.�����������̳�, ��������ǿ��(747p)

    vector<Dynamic>�� vector<Dynamic *>�� ��ȯ
    => �˻�, ���Ľ� �����ͺ�...���ǹ�... �Լ���ü(sort,find_if)�� ���
    => �Ű��� �� �͵��� ���� �����ϱ� ������ ���Ϳ��� ��� ���� �����Ѵ�

--*/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


// DynamicVector�� Ŭ���� ������ find,sort�� ���� �Լ���ü�� ����
// �ش� �Լ���ü�� Ŭ������ ������� ����
// main������ find_if, sortȣ��� �Լ���ü ���
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

    // ���������
    Dynamic(const Dynamic& d)
    {
        ptr = new char[strlen(d.ptr)+1];
        strcpy(ptr, d.ptr);
    }

    // ���Կ�����
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

    // ������(find)
    bool operator==(const Dynamic& d) const
    {
        return (strcmp(ptr, d.ptr) == 0 ? true : false);
    }

    // ��ҿ�����(sort)
    bool operator<(const Dynamic& d) const
    {
        return strcmp(ptr, d.ptr) < 0;
    }

    // �����ı���
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
    dump("��� 2��",vd);

    /*
    Dynamic c;
    c=vd[1];
    */
    Dynamic d("cat");
    puts(find_if(vd.begin(),vd.end(),DynFind())==vd.end() ? "����":"�ִ�");
    sort(vd.begin(), vd.end(), DynCompare());
    //sort(vd.begin(), vd.end(), bind2nd(DynCompare(),"cat"));
    dump("���� ��",vd);

    vector<Dynamic *>::iterator it;
    for (it=vd.begin();it!=vd.end();it++) 
    {
        delete *it;
    }
}

#if 0
// ���� ��........ �����ͺ��� ������ ���� class�� ���ڰ��� �����ͷ� �ٲٸ� �ȵȴ�..
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

    // ���������
    Dynamic(const Dynamic* d)
    {
        ptr = new char[strlen(d->ptr)+1];
        strcpy(ptr, d->ptr);
    }

    // ���Կ�����
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

    // ������(find)
    bool operator==(const Dynamic* d) const
    {
        return (strcmp(ptr, d->ptr) == 0 ? true : false);
    }

    // ��ҿ�����(sort)
    bool operator<(const Dynamic* d) const
    {
        return strcmp(ptr, d->ptr) < 0;
    }

    // �����ı���
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