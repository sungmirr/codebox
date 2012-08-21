/*++
    2012. 8. 18

   Nested if statement
      
    - 최적화 해제
       C/C++ - Optimaizations : 디폴트로 Maximize Speed(/O2)
       Disabled(/Od)로 변경
--*/

#include <stdio.h>

int main(void)
{
    int x=0;
    int y=0;
    int z=2;

    if(x==y)
    {
        if(z==0)
            printf("z is zero and x=y\n");
        else
            printf("z is non-zero and x=y\n");
    }
    else
    {
        if(z==0)
            printf("z is zero and x!=y\n");
        else
            printf("z is non-zero and x!=y\n");
    }

    return 0;
}