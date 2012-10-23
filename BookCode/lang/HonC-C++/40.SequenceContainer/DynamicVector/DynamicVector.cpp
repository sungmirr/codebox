/*++
    2012.10.20

    40.�����������̳�, ��������ǿ��(747p)

    Ŭ���� ���ο��� �����Ҵ��ϴ� ��ü�� ����
    - �����Ҵ��ϴ� Ŭ������ �⺻������ ������, ���� �ı���, ���������, ���Կ����ڸ� ������ ����

    �����Ҵ��ϴ� ��ü Dynamic�� �������ø��� �䱸 ������ ��� �����ؾ� �Ѵ�.
    vector<Dynamic> vd;
    Dynamic a("dog");
    Dynamic b("cog");

    vd.push_back(a);                    // ���� ���� �߰��Ҷ� ���簡 �߻� => ���� ������ �ʿ�
    Dynamic c;
    c=vd[1];                            // ���� ������ �ʿ�
    Dynamic d("cat");
    find(vd.begin(), vd.end(), d);      // ==������ �ʿ�
    sort(vd.begin(), vd.end());         // < ������ �ʿ�
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
    dump("��� 2��",vd);

    Dynamic c;
    c=vd[1];

    vector<Dynamic>::iterator it;
    Dynamic d("cat");
    it = find(vd.begin(), vd.end(), d);
    if(it==vd.end()) cout << "cat�� ����" << endl;

    sort(vd.begin(), vd.end());
    dump("���� ��",vd);
}
