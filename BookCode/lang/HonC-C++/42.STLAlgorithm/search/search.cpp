/*++
    2012. 10. 24

    FwdIt1 search(FwdIt1 first1, FowdIt1 last1, FwdIt2 first2, FwdIt2 last2 [,BinPred F]);
    FwdIt1 find_end(FwdIt1 first1, FowdIt1 last1, FwdIt2 first2, FwdIt2 last2 [,BinPred F]);
    FwdIt1 search_n(FwdIt1 first1, FowdIt1 last1, Size count, const Type&val[,BinPred F]);

    first1~last1전체구간과 first2~last2구간과 일치하는 패턴을 찾아 그 반복자를 리턴
    search   - 앞쪽부터 검색
    find_end - 뒤쪽부터 검색
    search_n - 반복자 구간에서 val값이 count번 연속으로 나타나는 지점을 검색

 --*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main()
{
    int ar1[]={3,1,4,1,5,9,2,6,5,3,5,8,9,9,9,3,2,3,1,5,9,2,6,4,3};
    int ar2[]={1,5,9};

    int *p;
    p=search(&ar1[0],&ar1[25],&ar2[0],&ar2[3]);
    if (p!=&ar1[25]) 
        printf("%d번째에서 구간이 발견되었습니다.\n",p-ar1);
    
    p=find_end(&ar1[0],&ar1[25],&ar2[0],&ar2[3]);
    if (p!=&ar1[25]) 
        printf("%d번째에서 구간이 발견되었습니다.\n",p-ar1);
    
    p=search_n(&ar1[0],&ar1[25],3,9);
    if (p!=&ar1[25]) 
        printf("%d번째에서 3연속의 9를 발견했습니다.\n",p-ar1);
}