/*++
    2012. 8. 18

   For Loops
    - Initialization, comparison, execution, increment/decrement
    - 위로 향하는 화살표로 쉽게 알수 있다
    - /O2

    /Od로 컴파일 할경우와 /O2로 했을때 for문의 형태가 바뀐다
 
--*/

#include <stdio.h>

int main(void)
{
    int i;

    for(i=0; i<100; ++i)
    {
        printf("i equals %d\n", i);
    }

    return 0;
}