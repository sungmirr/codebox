/*++
    2012.10.7

    36.ǥ�ض��̺귯��, ���������(592p)

    ifstream, ofstream�� open�Լ�
    void open(const char *_Filename,ios_base::openmode _Mode = ios_base::in,int _Prot = (int)ios_base::_Openprot)
    void open(const char *_Filename, ios_base::open_mode _Mode)

    open�Ҷ� ���ϸ��� ios_base�� ���ǵ� ����� ����
    ios_base::out    ��¿����� ������ ����
    ios_base::in     �Է¿����� ������ ����
    ios_base::app    ���� ���� �����͸� �����δ�
    ios_base::ate    ���� ���ڸ��� ���� ������ fp�� ������, fp�� ���� ��ġ�� �ű� �� �ִ�
    ios_base::trunc  ������ ������ ��� ũ�⸦ 0���� �����
    ios_base::binary ���� ���� ����

    ios_base::binary ���� ��尡 ���� ����ϰ��, read, wirte�Լ� ���!!!
    _Myt& read(_Elem *_Str, streamsize _Count)
    _Myt&  write(const _Elem *_Str, streamsize _Count)

    ios_base::ate ��,��¿� ������ fp�̵�
    seekg
    seekp
    
--*/

#include "Turboc.h"
#include <iostream>
#include <fstream>
using namespace std;

void main()
{
    ifstream ifs("C:\\dummy.txt", ios_base::in | ios_base::binary);
    if(!ifs.is_open())
    {
        cout << "���� ������ �����ϴ�." << endl;
        return;
    }
    ofstream ofs("C:\\dummy2.txt", ios_base::out | ios_base::trunc | ios_base::binary);
    char buf[100000];
    int nread;

    while(1)
    {
        ifs.read(buf, sizeof(buf));
        nread = ifs.gcount();               // read �Լ��� ������ ���� ����Ʈ��
        if(nread==0) break;
        ofs.write(buf, nread);
    }

    ifs.close();
    ofs.close();
}
