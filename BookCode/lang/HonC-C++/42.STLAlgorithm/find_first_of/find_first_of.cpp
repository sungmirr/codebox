/*++
    2012. 10. 24

    InIt find_if(InIt first, InIt last, UniPred F);
    - find�� ==������ �̿�, find_if�� �����Լ� ��ü F�� ��
 --*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main()
{
    int ar1[]={3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3};
    int ar2[]={2,4,6,8,0};

    int *p=find_first_of(&ar1[0],&ar1[25],&ar2[0],&ar2[4]);
    if (p!=&ar1[25]) 
        printf("������ ¦���� %d��°�� %d�Դϴ�.\n",p-ar1,*p);
}