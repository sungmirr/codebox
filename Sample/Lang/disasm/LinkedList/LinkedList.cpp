/*++
    2012. 8. 18

   LinkedList
    - you must recognize that some object contains a pointer that points to
      another object of the same type

    - /Od

    push 8
    call _malloc        // ����ü�� ����� 8���� �˼��ִ�
    add  esp, 4
    mov [ebp+ptr],eax

    mov ecx, [ebp+ptr]
    mov edx, [ebp+idx]
    mov [ecx], edx      // ����ü ù��° ����� index�� ����

    mov eax, [ebp+ptr]
    mov ecx, [ebp+var_C]
    mov [eax+4], ecx    // ����ü �ι�° ����� Var_C�� ����

    mov edx, [ebp+ptr]
    mov [ebp+var_C], edx  // var_C�� ptr�� ���� �ϰ� �ִ� �׷��� ebp+var_C��
                          // ���� ����ü�� ����Ű�� �����ͺ������� �˼��ִ�
                          // �� ����ü �ι�° ��������� ����ü�� ����Ű�� �����ͺ�����
                          // �˼��ִ�
--*/
#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE
{
    int x;
    struct _NODE *next;    //****** 
}NODE, *PNODE;


int main(void)
{
    PNODE cur, head;
    int i;

    head = NULL;

    for(i=0; i <10; ++i)
    {
        cur = (PNODE)malloc(sizeof(NODE));
        cur->x = i;
        cur->next = head;    // ����ü ������ �����͸� �����Ѵ�
        head = cur;          // �ܺκ����� �ش� ����ü �����͸� �����Ѵ�
    }
    cur = head;

    while(cur)
    {
        printf("%d\n", cur->x);
        cur = cur->next;
    }

    return 0;
}