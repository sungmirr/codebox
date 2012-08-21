/*++
    2012. 8. 18

   If statement
      
    - 최적화 해제
       C/C++ - Optimaizations : 디폴트로 Maximize Speed(/O2)
       Disabled(/Od)로 변경
--*/

#include <stdio.h>

int main(void)
{
    int x=1;
    int y=2;

    if(x==y)
    {
        printf("x equals y.\n");
    }
    else
    {
        printf("x is not equal to y.\n");
    }

    return 0;
}