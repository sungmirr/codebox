/*++
    2012. 8. 18

   While Loops
    - Initialization, comparison, execution
    - For Loop�� ������ �� ����/���� �κи� ������ ������ ����
    - ���� ���ϴ� ȭ��ǥ�� ���� �˼� �ִ�
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