/*++
    2012. 8. 18

   Arithmetic Operation
    - ���������

    - ������Ʈ ���� 
       C/C++ - Optimaizations : ����Ʈ�� Maximize Speed(/O2)
       Disabled(/Od)�� ����
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