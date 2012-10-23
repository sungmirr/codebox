/*++
    2012.10.24

    40. ���������̳�, ����Ȱ��(805p)

--*/

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

struct 
{
    const char * first;
    unsigned second;
}sites[]=
{
    {"www.winapi.co.kr",0x10203040},
    {"www.lpacampus.com",0x20304050},
    {"www.microsoft.com",0x99999999},
    {"www.borland.com",0xbbbbbbbb},
    {"kangcom.com",0xccaabbdd},
    {"www.maxplusone.com",0x12345678},
};

void main()
{
    map<string,unsigned> m;
    map<string,unsigned>::iterator it;

    for(int i=0; i<sizeof(sites)/sizeof(sites[0]); ++i)
    {
        //m.insert(pair<string,unsigned>(sites[i].first, sites[i].second));
        m[sites[i].first] = sites[i].second;
    }

    it=m.find("www.winapi.co.kr");
    if(it==m.end())
        cout << "��ϵ��� ���� ����Ʈ�Դϴ�." << endl;
    else
        cout << it->first << "�� �ּҴ� " << showbase << hex << it->second << "�Դϴ�." << endl;
}