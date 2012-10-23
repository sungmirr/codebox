/*++
    2012.10.23

    40. ���������̳�, ����Ȱ��(780p)

    set�� insert,erase,findȰ��

    set�� ��� ��� ��ȸ
    => begin���� end���� ��ȸ�ϸ� �ݺ�
       for_each���
--*/ 

#include <iostream>
#include <set>
#include <string>
using namespace std;

void main()
{
    set<string> s;
    set<string>::iterator it;
    string name;
    char ch;

    for(;;) 
    {
        cout << "1:����, 2:����, 3:����, 4:�˻�, 5:���� => ";
        cin >> ch;
        switch (ch) 
        {
        case '1':
            cout << "�� �̸��� �Է� �Ͻÿ� : ";
            cin >> name;
            s.insert(name);
            break;
        case '2':
            cout << "������ �̸��� �Է� �Ͻÿ� : ";
            cin >> name;
            s.erase(name);
            break;
        case '3':
            for(it=s.begin(); it!=s.end(); ++it)
                cout << *it << endl;
            break;
        case '4':
            cout << "�˻��� �̸��� �Է� �Ͻÿ� : ";
            cin >> name;
            cout << name << "��(��) " << (s.find(name) != s.end() ? "��":"��")
                     << "���ϴ�." << endl;
            break;
        case '5':
            return;
        }
    }
}