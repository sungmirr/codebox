/*++
    2012.10.15

    37.STL����(634p)

    map
     - �ΰ��� ¦�� �̷�� �����͸� �����ϴ� �����̳�
     - ���������̳��� �������� ���ĵ� ��ġ�� ����
     - �˻��� ������, �뷮�� �����͸� �ż��ϰ� �˻��ؾ� �Ҷ� ���

     - �ڷ��Է� : []������
     - �˻� : find()
     - size()
     - �ڷ����� : it->first, it->second
--*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

struct SProduct
{
    string name;
    int price;
}arPro[] = {
    {"������", 500},
    {"��ī��",400},
    {"�׽�ī��",250},
    {"�Ŷ��",450},
    {"88����Ʈ",1900},
    {"��Ƽ��",300},
    {"��Ÿŷ",700},
    {"��ġ",2000},
    {"�Ź�",500},
    {"��Ÿ500",500},
    {"��Ÿ1000",1000},
    {"�ղ�����",900},
    {"�Ǻ���",200},
    {"������",900},
    {"����600",600},
    {"�丮��ġ��",2200},
    {"�𳪹̺���",90},
    {"�����",990},
    {"���͸�",1000},
    {"��������",250}
};

struct _FuncInfo
{
    int addr;
    string fname;
}FuncInfo[] = {
    {3333,"GetModuleHandle"},
    {9999,"StrCpy"},
    {5555,"GetProcAddress"},
    {7777,"OpenFileMapping"},
    {1111,"CreateProcess"},
    {0000,"OpenFile"},
    {8888,"WaitForDebugEvent"},
    {2222,"CreateSemaphore"},
    {4444,"ContinueDebugEvent"},
    {6666,"printf"},
    {5555,"getchar"}
};


void main()
{
    map<string,int> mPro;
    map<string,int>::iterator it;
    int i;
    string name;

    // map �����Է�
    for(i=0; i<sizeof(arPro)/sizeof(arPro[0]); ++i)
        mPro[arPro[i].name] = arPro[i].price;

    while(1)
    {
        cout << "��ǰ���� �Է��Ͻÿ�(�������� '��'�Է�): ";
        cin >> name;
        if(name=="��")
            break;
        // map�˻�
        it = mPro.find(name);
        if(it==mPro.end())
            cout << "�׷� ��ǰ�� �����ϴ�." << endl;
        else
            cout << name << "�� ������" << it->second << "�Դϴ�." << endl;
    }

    // map�� size()�� ���Ұ���
    cout << "size : " << mPro.size() << endl;

    // ���Ļ��� Ȯ��
    for(it=mPro.begin(); it!=mPro.end(); ++it)
        cout << it->first << " : " << it->second << endl;

    cout << "---------------------------------\n";
    map<int,string> mFuncInfo;
    map<int,string>::iterator mIt;

    for(i=0; i<sizeof(FuncInfo)/sizeof(FuncInfo[0]); ++i)
        mFuncInfo[FuncInfo[i].addr] = FuncInfo[i].fname;

    // mFuncInfo�� ù��° ���ҷ� �������� ����
    for(mIt=mFuncInfo.begin(); mIt!=mFuncInfo.end(); ++mIt)
        cout << mIt->first << " : " << mIt->second << endl;

}