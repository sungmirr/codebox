/*++
    2012. 8. 18

   For Loops
    - Initialization, comparison, execution, increment/decrement
    - ���� ���ϴ� ȭ��ǥ�� ���� �˼� �ִ�
    - /O2

    /Od�� ������ �Ұ��� /O2�� ������ for���� ���°� �ٲ��
 
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