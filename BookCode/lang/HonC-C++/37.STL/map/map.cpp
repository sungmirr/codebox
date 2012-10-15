/*++
    2012.10.15

    37.STL개요(634p)

    map
     - 두개씩 짝을 이루는 데이터를 저장하는 컨테이너
     - 연관컨테이너의 일종으로 정렬된 위치에 삽입
     - 검색이 빠르다, 대량의 데이터를 신속하게 검색해야 할때 사용

     - 자료입력 : []연산자
     - 검색 : find()
     - size()
     - 자료접근 : it->first, it->second
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
    {"맛동산", 500},
    {"박카스",400},
    {"네스카페",250},
    {"신라면",450},
    {"88라이트",1900},
    {"불티나",300},
    {"스타킹",700},
    {"김치",2000},
    {"신문",500},
    {"비타500",500},
    {"비타1000",1000},
    {"왕꿈툴이",900},
    {"뽀빠이",200},
    {"위스퍼",900},
    {"콘태600",600},
    {"페리오치약",2200},
    {"모나미볼펜",90},
    {"까페라떼",990},
    {"배터리",1000},
    {"초코파이",250}
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

    // map 원소입력
    for(i=0; i<sizeof(arPro)/sizeof(arPro[0]); ++i)
        mPro[arPro[i].name] = arPro[i].price;

    while(1)
    {
        cout << "상품명을 입력하시오(끝낼때는 '끝'입력): ";
        cin >> name;
        if(name=="끝")
            break;
        // map검색
        it = mPro.find(name);
        if(it==mPro.end())
            cout << "그런 제품은 없습니다." << endl;
        else
            cout << name << "의 가격은" << it->second << "입니다." << endl;
    }

    // map의 size()는 원소개수
    cout << "size : " << mPro.size() << endl;

    // 정렬상태 확인
    for(it=mPro.begin(); it!=mPro.end(); ++it)
        cout << it->first << " : " << it->second << endl;

    cout << "---------------------------------\n";
    map<int,string> mFuncInfo;
    map<int,string>::iterator mIt;

    for(i=0; i<sizeof(FuncInfo)/sizeof(FuncInfo[0]); ++i)
        mFuncInfo[FuncInfo[i].addr] = FuncInfo[i].fname;

    // mFuncInfo는 첫번째 원소로 오름차순 정렬
    for(mIt=mFuncInfo.begin(); mIt!=mFuncInfo.end(); ++mIt)
        cout << mIt->first << " : " << mIt->second << endl;

}