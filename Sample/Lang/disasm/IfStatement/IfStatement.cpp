/*++
    2012. 8. 18

   If statement
      
    - ����ȭ ����
       C/C++ - Optimaizations : ����Ʈ�� Maximize Speed(/O2)
       Disabled(/Od)�� ����
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