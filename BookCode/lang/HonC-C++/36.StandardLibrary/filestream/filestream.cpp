/*++
    2012.10.7

    36.ǥ�ض��̺귯��, ���������(589p)

    <fstream>
    typedef basic_ifstream<char, char_traits<char> > ifstream;
    typedef basic_ofstream<char, char_traits<char> > ofstream;
    typedef basic_ifstream<wchar_t, char_traits<wchar_t> > wifstream;
    typedef basic_ofstream<wchar_t, char_traits<wchar_t> > wofstream;

    ofstream, ifstream�� 
    - open(), close()�� ��Ʈ������/���� 
    - ������尡 �ƴϹǷ� <<, >> �����ڷ� ����� ����
    - is_open
--*/

#include "Turboc.h"
#include <iostream>
#include <fstream>
using namespace std;

void main()
{
    //////////////////////// ���� ����
    ofstream f;

    // ����� ����, �̹� �����ϸ� �����
    // ofstream f("C:\\cpptest.txt");
    f.open("C:\\cpptest.txt");      
    f << "String " << 1234 << endl;
    f.close();


    //////////////////////  ���� �б�
    ifstream ifs;
    char str[128];
    int i;

    ifs.open("C:\\cpptest.txt");   

    if(ifs.is_open())
    {
        cout << "���� ���� ����" << endl;
    }
    else
    {
        cout << "���� ���� ����" << endl;
        return;
    }

    ifs >> str >> i;
    cout << str << " " << i << endl;
    ifs.close();
}