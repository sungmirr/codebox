/*++
    2012.10.14

    36.ǥ�ض��̺귯��, string(612p)

    find - �߰ߵ��� ���� ��� string::npos(string�ǳ�) ����    
        size_type __CLR_OR_THIS_CALL find(const _Elem *_Ptr,
            size_type _Off, size_type _Count) const
            {	// look for [_Ptr, _Ptr + _Count) beginnng at or after _Off  
    rfind - ������ �˻�
    find_first_of
    find_last_of
    find_first_not_of
    find_last_not_of
--*/
#include <iostream>
#include <string>
using namespace std;

void main()
{
    string s1("string class find function");
    string s2("func");

    cout << s1 << endl;
    cout << "i:" << s1.find('i') << "��°" << endl;
    cout << "i:" << s1.find('i',10) << "��°" << endl;
    cout << "ass:" << s1.find("ass") << "��°" << endl;
    cout << "finding�� ��4:" << s1.find("finding",0,4) << "��°" << endl;  //
    cout << "kiss:" << s1.find("kiss") << "��°" << endl;
    unsigned ret = s1.find("kiss");
    if(ret != string::npos)
        cout << "kiss:" << ret << "��°" << endl;
    else
        cout << "kiss:" << "�߰ߵ�������" << endl;
    

    cout << "----------------------------" << endl;
    string s3("starcraft");
    string s4("123abc456");
    string moum("aeiou");
    string num("0123456789");
    
    cout << s3 << endl;
    cout << "������ t:" << s3.find('t') << "��°" << endl;
    cout << "������ t:" << s3.rfind('t') << "��°" << endl;
    cout << "������ cra:" << s3.rfind("cra") << "��°" << endl;
    cout << "������ ����" << s3.find_first_of(moum) << "����" << endl;
    cout << "������ ����" << s3.find_last_of(moum) << "����" << endl;

    cout << s4 << endl;
    cout << "������ �����" << s4.find_first_not_of(num) << "��°" << endl;
    cout << "������ �����" << s4.find_last_not_of(num) << "��°" << endl;
}