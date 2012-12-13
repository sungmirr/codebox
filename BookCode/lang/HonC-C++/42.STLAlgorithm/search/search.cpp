/*++
    2012. 10. 24

    FwdIt1 search(FwdIt1 first1, FowdIt1 last1, FwdIt2 first2, FwdIt2 last2 [,BinPred F]);
    FwdIt1 find_end(FwdIt1 first1, FowdIt1 last1, FwdIt2 first2, FwdIt2 last2 [,BinPred F]);
    FwdIt1 search_n(FwdIt1 first1, FowdIt1 last1, Size count, const Type&val[,BinPred F]);

    first1~last1��ü������ first2~last2������ ��ġ�ϴ� ������ ã�� �� �ݺ��ڸ� ����
    search   - ���ʺ��� �˻�
    find_end - ���ʺ��� �˻�
    search_n - �ݺ��� �������� val���� count�� �������� ��Ÿ���� ������ �˻�

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
        printf("%d��°���� ������ �߰ߵǾ����ϴ�.\n",p-ar1);
    
    p=find_end(&ar1[0],&ar1[25],&ar2[0],&ar2[3]);
    if (p!=&ar1[25]) 
        printf("%d��°���� ������ �߰ߵǾ����ϴ�.\n",p-ar1);
    
    p=search_n(&ar1[0],&ar1[25],3,9);
    if (p!=&ar1[25]) 
        printf("%d��°���� 3������ 9�� �߰��߽��ϴ�.\n",p-ar1);
}