/*++
    2012.10.7

    36.ǥ�ض��̺귯��, cout ����üũ(587p)

    cin��ü�� ���������� ���� �߻����θ� ǥ���ϴ� ������ �÷��� ����
    - failbit : �Է� ����, ������ �Է¹޴µ� ���ڰ� �Էµ� ���, fail()
    - eofbit : ���� ��, eof()
    - badbit : ��Ʈ���� ���������� �ջ�Ǿ� ���� �� ����, bad()
    - goodbit : ��� �������� �߻����� �ʾҴٴ� ��, good()

    cin�� �ϴ� ������ �߻��ϸ� ��� ���� ���� ����, ������ �������� ����
    rdstate, setstate, clear ���
--*/

#include "Turboc.h"
#include <iostream>
#include <string>
using namespace std;

void main()
{
    int i;
    string discard;

    if(cin >> i)
        cout << i << endl;
    else
        cout << "����" << endl;

    // ���ۺ���.. �߾ȵǳ�...
    //cin.ignore(100);
    //cin.ignore(cin.rdbuf()->in_avail());
    cin.clear();            // 
    cin >> discard;


    cin >> i;
    if(cin.good())
        cout << i << endl;
    else
        cout << "����" << endl;
}