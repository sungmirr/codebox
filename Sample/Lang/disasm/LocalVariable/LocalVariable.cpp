/*++
    2012. 8. 18

    Local Variables
     - stack address 사용
     - ida에서 rename

     - pdb파일 제거하고 ida로 로드
     - 프로젝트 설정 Code generation -> Runtime Library를 
       static으로 하면 crt관련함수, 스트링정보들이 
       바이너리에 많이 포함되 있음을 확인할 수 있다
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