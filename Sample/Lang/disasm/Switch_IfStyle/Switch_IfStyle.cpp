/*++
    2012. 8. 18

    Switch statement - If Style
     - compare, conditional jump¿« ø¨º”...
       (cmp, jz)
     - /Od
--*/

#include <stdio.h>

int main(void)
{
    int i =3;

    switch(i)
    {
        case 1:
            printf("i = %d\n", i+1);
            break;
        case 2:
            printf("i = %d\n", i+2);
            break;
        case 3:
            printf("i = %d\n", i+3);
            break;
        default:
            break;
    }

    return 0;
}