/*++
    2012.10.7

    36.ǥ�ض��̺귯��, iostream

    // ostream�� char Ÿ���� ���ڿ��� ���, char_traits<char>��ü�� �� ���Ṯ�ڿ��� �����ϴ� ��ü
    typedef basic_ostream<char, char_traits<char> > ostream;
    typedef basic_ostream<wchar_t, char_traits<wchar_t> > wostream;

    <iostream>
    extern istream cin;
    extern ostream cout;
    extern ostream cerr;
    extern ostream clog;
    extern wistrem wcin;
    extern wostream wcout;

    ��� ��ü�� ���̳� ���е�, ���Ĺ��, ä����, ���� � ���� �ɼ���
    ����ϴ� �÷��׵��� ������ �����ڵ��� �� �÷��׸� �����ϴ� ��Ȱ ����
    ������ �ܿ� �÷��׸� ���� ���� : setf.unsetf����Լ� �̿�, ��¾�� �ϰ������� ����, ����
--*/


#include "Turboc.h"
#include <iostream>
using namespace std;


void main()
{
    int i=1234;
    int j=-567;

    hex(cout);
    cout << i << endl;
    dec(cout);
    cout << i << endl;

    cout << "-----------------------------\n";
    cout.width(10);                 // �ѹ� ����� �ڵ� ����
    cout << oct << i << endl;       // oct, hex, dex�ѹ� ������ ��� ��ȿ
    cout << hex << i << endl;
    cout << dec << i << endl;

    cout << "-----------------------------\n";
    cout.width(2);
    cout << oct << i << endl;
    cout << hex << i << endl;
    cout << dec << i << endl;

    cout << "-----------------------------\n";
    cout.width(10);
    cout.fill('_');                 // cout.fill �ѹ� ������ ��� ��ȿ
    cout << oct << i << endl;
    cout.width(10);
    cout << hex << i << endl;
    cout.fill(' ');                 // cout.fill ����
    cout.width(10);
    cout << dec << i << endl;

    cout << "-----------------------------\n";
    cout.width(10);
    cout << left << oct << i << endl;
    cout.width(10);
    cout << right << hex << i << endl;
    cout.width(10);
    cout << internal << dec << j << endl;       // internal ��ȣ(-, 0x)�� ����, ���� ������

    cout << "float-----------------------------\n";
    double d = 1.234;
    cout << d << endl;
    cout.precision(3); // �Ǽ��� ���е� ����
    cout << d << endl;
    cout.precision(10);
    cout << showpoint << d << endl;
    cout.precision(6);

    cout << fixed << d << endl; // �Ǽ� ��¹��( fixed, scientific�� �����ڷ� ����)
    cout << scientific << d << endl;

    cout << "----------------------------\n";
    bool b = true;
    cout << b << endl;
    cout << boolalpha << b << endl;
    cout << hex << i << endl;       // 4d2
    cout << showbase << i << endl;  // 0x4d2
    cout << uppercase << i << endl; // 0X4d2
    cout << dec << showpos << i << endl;

}