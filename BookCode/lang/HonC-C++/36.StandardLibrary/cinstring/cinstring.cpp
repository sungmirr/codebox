/*++
    2012.10.7

    36.ǥ�ض��̺귯��, �Է½�Ʈ��(585p)

    cin, >>�������� ����(�����̽�,��,���๮��) �Է¸��޴� Ư¡�� �����ϱ� ����
    basic_istream& get(char& c);
    basic_istream& getline(char *s, streamsize, n, char delim='\n');
--*/

#include "Turboc.h"
#include <iostream>
using namespace std;

void main()
{
    char ch;
    char str[128];

    cin.get(ch);
    cout << showbase << hex <<  (int)ch << endl;
    cin.get(ch);

    cin.getline(str, sizeof(str));
    cout << str << endl;
}