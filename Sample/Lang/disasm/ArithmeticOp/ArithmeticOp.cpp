/*++
    2012. 8. 18

   Arithmetic Operation
    - 산술연산자

    - 프로젝트 셋팅 
       C/C++ - Optimaizations : 디폴트로 Maximize Speed(/O2)
       Disabled(/Od)로 변경
--*/

#include <stdio.h>

int main(void)
{
    int a = 0;
    int b = 1;

    a = a+11;
    a = a-b;
    a--;
    b++;
    b = a%3;

    return 0;
}