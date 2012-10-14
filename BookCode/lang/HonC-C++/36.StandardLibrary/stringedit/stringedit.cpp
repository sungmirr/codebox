/*++
    2012.10.14

    36.ǥ�ض��̺귯��, string(605p)

    string�� 
    operator= , operator+=, operator+ ������
    assign, append
        _Myt& __CLR_OR_THIS_CALL assign(const _Myt& _Right,size_type _Roff, size_type _Count)
        _Myt& __CLR_OR_THIS_CALL append(const _Myt& _Right,size_type _Roff, size_type _Count)
    copy, swap
        size_type __CLR_OR_THIS_CALL copy(_Elem *_Dest,size_type _Count, size_type _Off = 0) const
    insert, erase
        string�� ������ ��ġ�� ���ڿ�, string�� �����Ѵ�. cf)append�� ù��° �μ��� size()�� insert�Լ�
        _Myt& __CLR_OR_THIS_CALL erase(size_type _Off = 0, size_type _Count = npos)
    replace
        _Myt& __CLR_OR_THIS_CALL replace(size_type _Off, size_type _N0, const _Elem *_Ptr)
    substr
        _Myt __CLR_OR_THIS_CALL substr(size_type _Off = 0, size_type _Count = npos) const  
--*/

#include "Turboc.h"
#include <iostream>
#include <string>
using namespace std;

void main()
{
    string s1("��ȣ �ų���.");
    string s2;

    // operator=������
    s2="������ ���ڿ�";
    cout << s2 << endl;
    s2=s1;
    cout << s2 << endl;
    s2='A';
    cout << s2 << endl;

    // operator+=
    cout << "-------------------------\n";
    s1+="���ڿ� ����.";
    cout << s1 << endl;
    s1+=s2;
    cout << s1 << endl;
    s1+='!';
    cout << s1 << endl;

    // operator+
    cout << "-------------------------\n";
    string s3;
    s3 = "s1:"+s1+"s2:"+s2+".";
    cout << s3 << endl;

    // assign, append
    cout << "-------------------------\n";
    string st1("1234567890");
    string st2("abcdefghijklmnopqrstuvwxyz");
    string st3;
    st3.assign(st1,3,4);
    cout << st3 << endl;
    st3.append(st2,10,7);
    cout << st3 << endl;

    // copy, swap
    cout << "-------------------------\n";
    string ss("1234567890");
    char str[128]="abcdefghijklmnopqrstuvwxyz";
    ss.copy(str, 5, 3);     // ù��° ���ڰ��� ���ڿ��������� ���ڿ��� ����ȴ� ex) ss.copy(str+5,5,3)
    cout << str << endl;
    cout << "st1:" << st1 << " st2:" << st2 << endl;
    st1.swap(st2);             // st2.swap(st1);
    cout << "st1:" << st1 << " st2:" << st2 << endl;

    // insert, erase
    cout << "-------------------------\n";
    string a("1234567890");
    string b("^_^");
    cout << a << endl;
    a.insert(5,"XXX");
    cout << a << endl;
    a.insert(5, b);
    cout << a << endl;
    a.erase(5,6);
    cout << a << endl;

    // replace
    cout << "-------------------------\n";
    string c="������ �Ϻ���";
    cout << c << endl;
    c.replace(7,4,"���ѹα�");
    cout << c << endl;

    // substr
    string d("1234567890");
    string e=d.substr(3,4);
    cout << e << endl;
}