/*++
    2012. 8. 18

   Arrays
    - Local Array
      mov [ebp+ecx*4+var_14]  : var_14 = -20, ecx = index, 4 : element size

    - Gloval Array
      mov dword_40AC40[eax*4] : eax = index, 4 : element size

    - /Od

--*/

#include <stdio.h>

int b[5] = {123, 87, 487, 978};

int main(void)
{
    int i;
    int a[5];

    for(i =0; i<5; ++i)
    {
        a[i] = i;
        b[i] = i;
    }

    return 0;
}