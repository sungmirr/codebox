/*++
    2012. 8. 18

   While Loops
    - Initialization, comparison, execution
    - For Loop와 비교했을 때 증가/감소 부분만 빠지고 나머지 같다
    - 위로 향하는 화살표로 쉽게 알수 있다
    - /Od

--*/

#include <stdio.h>

static int count = 10;

int CheckResult(void)
{
    count--;
    return count;
}

int main(void)
{
    int status = 1;

    while(status != 0)
    {
        status = CheckResult();
    }

    return 0;
}