/*++
    2012.10.14

    36.ǥ�ض��̺귯��, string(612p)

    compare
    int __CLR_OR_THIS_CALL compare(const _Myt& _Right) const
    int __CLR_OR_THIS_CALL compare(size_type _Off, size_type _N0,const _Myt& _Right) const
    int __CLR_OR_THIS_CALL compare(size_type _Off,
                size_type _N0, const _Myt& _Right,
                size_type _Roff, size_type _Count) const
--*/

#include <iostream>
#include <string>
using namespace std;

void main()
{
    string s1("aaa");
    string s2("bbb");
    cout << (s1==s1 ? "����" : "�ٸ���") << endl;
    cout << (s1==s2 ? "����" : "�ٸ���") << endl;
    cout << (s1>s2 ? "ũ��" : "��ũ��") << endl;

    string s3("1234567");
    string s4("1234999");
    cout << (s3.compare(s4)==0 ? "����":"�ٸ���") << endl;
    cout << (s3.compare(0,4,s4,0,4)==0 ? "����":"�ٸ���") << endl;

    string s5("hongkildong");
    cout << (s5=="hongkildong"?"����":"�ٸ���") << endl;
    // ==�����ڴ� ���� ������ �Լ��� ���ǵ��ִ�
    // cout << ("hongkildong"==s5?"����":"�ٸ���") << endl;
}