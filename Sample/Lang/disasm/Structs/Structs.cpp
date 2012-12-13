/*++
    2012. 8. 18

   Structs
    - mob eax, [ebp+arg0]
      mov byte ptr [eax+14h], 61h   // 멤버변수 : char

    - mov ecx, [ebp+arg0]
      fld ds:dbl_40c280
      fstrp qword ptr [ecx+18g]     // 멤버변수 : double

    - mov ecx, [ebp+arg0]
      mov [ecx+eax*4], edx          // 멤버변수.. 배열 : ecx 베이스, eax 인덱스, 4:size
      
    - /Od

    memory에 위치 순서
    (-) x[5]
        y
    (+) z

--*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _MY_STRUCTS
{
    int x[5];
    char y;
    double z;
}MY_STRUCTS, *PMY_STRUCTS;


PMY_STRUCTS gms;

void test(PMY_STRUCTS p)
{
    int i;
    p->y = 'a';
    p->z = 15.6;
    for(i=0; i<5; ++i)
        p->x[i]=i;
}


int main(void)
{
    gms = (PMY_STRUCTS)malloc(sizeof(MY_STRUCTS));
    test(gms);

    return 0;
}