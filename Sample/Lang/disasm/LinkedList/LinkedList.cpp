/*++
    2012. 8. 18

   LinkedList
    - you must recognize that some object contains a pointer that points to
      another object of the same type

    - /Od

    push 8
    call _malloc        // 구조체의 사이즈가 8임을 알수있다
    add  esp, 4
    mov [ebp+ptr],eax

    mov ecx, [ebp+ptr]
    mov edx, [ebp+idx]
    mov [ecx], edx      // 구조체 첫번째 멤버에 index를 저장

    mov eax, [ebp+ptr]
    mov ecx, [ebp+var_C]
    mov [eax+4], ecx    // 구조체 두번째 멤버에 Var_C를 저장

    mov edx, [ebp+ptr]
    mov [ebp+var_C], edx  // var_C에 ptr을 저장 하고 있다 그래서 ebp+var_C는
                          // 같은 구조체를 가리키는 포인터변수임을 알수있다
                          // 또 구조체 두번째 멤버변수도 구조체를 가리키는 포인터변수임
                          // 알수있다
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
        cur->next = head;    // 구조체 변수에 포인터를 저장한다
        head = cur;          // 외부변수에 해당 구조체 포인터를 저장한다
    }
    cur = head;

    while(cur)
    {
        printf("%d\n", cur->x);
        cur = cur->next;
    }

    return 0;
}