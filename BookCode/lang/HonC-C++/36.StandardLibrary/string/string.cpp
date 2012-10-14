/*++
    2012.10.14

    36.ǥ�ض��̺귯��, string(594p)

    <string>
    typedef basic_string<char> string;
    typedef basic_string<wchar_t> wstring;

    string:: 
    size,length,capacity,resize,reserve,clear,empty,data,c_str
--*/

#include "Turboc.h"
#include <iostream>
#include <string>
using namespace std;

void main()
{
    // string�� ������
    string s1("test");
    string s2(s1);
    string s3;
    s3=s1+"ing";
    string s4(32, 'S');
    string s5("very nicde day", 8);
    char *str ="abcdefghijklmnopqrstuvwxyz";
    string s6(str+5, str+10);       // str+5���� str+9���� ����, ������ ���Ծȵȴ�

    cout << "s1=" << s1 << endl;
    cout << "s2=" << s2 << endl;
    cout << "s3=" << s3 << endl;
    cout << "s4=" << s4 << endl;
    cout << "s5=" << s5 << endl;
    cout << "s6=" << s6 << endl;


    // string��ü�� ���� ������
    cout << "-----------------------------\n";
    string s("C++ string");

    cout << s << " ���ڿ��� ����=" << s.size() << endl;     // stl�� ȣȯ�� ���� size�Լ� ����
    cout << s << " ���ڿ��� ����=" << s.length() << endl;
    cout << s << " ���ڿ��� �Ҵ� ũ��=" << s.capacity() << endl;
    cout << s << " ���ڿ��� �ִ� ũ��" << s.max_size() << endl; // string::npos, (unsigned)-1�� ����
                                                                // �˻����и� ��Ÿ���� �÷��׷ε� ����

    s.resize(6);
    cout << s << " ����=" << s.size() << ", �Ҵ�ũ��" << s.capacity() << endl;
    s.resize(30,'*');
    cout << s << " ����=" << s.size() << ", �Ҵ�ũ��" << s.capacity() << endl;
    s.reserve(100);
    cout << s << " ����=" << s.size() << ", �Ҵ�ũ��" << s.capacity() << endl;


    // string��ü�� �ʱ�ȭ
    cout << "-----------------------------\n";
    s.clear();
    cout << "s.empty() is " << boolalpha << s.empty() << endl;


    // string ���ڿ� ���� ���
    cout << "-----------------------------\n";
    s="C++ Standard Library";
    cout << s.data() << endl;       // s��ü�� ���� �����͸� �״�� ����
    cout << s.c_str() << endl;      // ������ ���ڿ��� �ƴѰ�� �纻�� ������ �� �� ���� ���ڿ��� �ٲ㼭 ����

    char *p = new char[s.size()+1];
    strcpy(p, s.c_str());
    printf("p = %s\n", p);
    delete [] p;
}