/*++
    2012. 8. 18

    Global Variables
     - memory address 사용
     - ida에서 dword_40318, 요넘을 rename
     - Runtime library를 DLL로 설정 : crt함수, 스트링관련 정보가 빠진다

--*/


#include <stdio.h>

int x = 1;
int y = 2;

int main(void)
{

    x = x+y;
    printf("Total = %d\n", x);

    return 0;
}