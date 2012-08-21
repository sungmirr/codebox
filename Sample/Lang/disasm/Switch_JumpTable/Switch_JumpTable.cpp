/*++
    2012. 8. 18

    Switch statement - JumpTable
     - large, contiunous switch statements
     - jmp     ds:off_401088[edx*4]
     - /Od
--*/

#include <stdio.h>

int main(void)
{
    int i =3;

    switch(i)
    {
        case 3:
            printf("i = %d\n", i+3);
            break;
        case 5:
            printf("i = %d\n", i+5);
            break;
        case 7:
            printf("i = %d\n", i+7);
            break;
        case 8:
            printf("i = %d\n", i+9);
        default:
            break;
    } 

    return 0;
}