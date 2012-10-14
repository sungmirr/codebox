/*++
    2012.10.14

    36.ǥ�ض��̺귯��, string(602p)

    string�� �Է�, ���
     - ignore : �����ִ� ����(ex..�����ڵ�)�� ����\
    string�� ���� ����
     - [] or at()

--*/
#include <iostream>
#include <string>
using namespace std;

void main()
{
    string name, addr;
    cout << "�̸��� �Է��Ͻÿ�: ";
    cin >> name;
    cout << "�Է��� �̸��� " << name << "�Դϴ�." << endl;
    cin.ignore();       // �����ִ� �����ڵ�(���͹���)�� ����.. 

    cout << "�ּҸ� �Է��Ͻÿ�: ";
    getline(cin, addr);
    cout << "�Է��� �ּҴ� " << addr << "�Դϴ�." << endl;

    cout << "----------------------------\n";
    string s("korea");
    size_t len, i;

    len = s.size();
    for(i=0; i<len; ++i)
        cout << s[i];       // ������������ʴ´�, ��� ������, size�� �����ȳ����Ƿ� ��õ
    cout << endl;
    s[0] = 'c';

    for(i=0; i<len; ++i)
        cout << s.at(i);    // ��������Ѵ�.
    cout << endl;
}