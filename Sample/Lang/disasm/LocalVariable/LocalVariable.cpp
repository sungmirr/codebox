/*++
    2012. 8. 18

    Local Variables
     - stack address ���
     - ida���� rename

     - pdb���� �����ϰ� ida�� �ε�
     - ������Ʈ ���� Code generation -> Runtime Library�� 
       static���� �ϸ� crt�����Լ�, ��Ʈ���������� 
       ���̳ʸ��� ���� ���Ե� ������ Ȯ���� �� �ִ�
--*/


#include <stdio.h>

int main(void)
{
    int x = 1;
    int y = 2;

    x = x+y;
    printf("Total = %d\n", x);

    return 0;
}