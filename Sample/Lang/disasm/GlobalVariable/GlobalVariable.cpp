/*++
    2012. 8. 18

    Global Variables
     - memory address ���
     - ida���� dword_40318, ����� rename
     - Runtime library�� DLL�� ���� : crt�Լ�, ��Ʈ������ ������ ������

--*/


#include <stdio.h>

int x = 1;
int y = 2;

int main(void)
{

    x = x+y;
    printf("Total = %d\n", x);

    return 0;
}