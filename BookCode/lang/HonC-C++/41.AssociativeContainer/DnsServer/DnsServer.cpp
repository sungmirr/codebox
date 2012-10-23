/*++
    2012.10.24

    40. 연관컨테이너, 맵의활용(805p)

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
        cout << "등록되지 않은 사이트입니다." << endl;
    else
        cout << it->first << "의 주소는 " << showbase << hex << it->second << "입니다." << endl;
}