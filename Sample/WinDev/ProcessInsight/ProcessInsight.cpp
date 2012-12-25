#include <windows.h>
#include <stdio.h>
#include "Archive.h"
#include <strsafe.h>


int main(void)
{
    Archive ar;
    ar.SetProcessList();


	printf(">>> 확인하고 싶은 프로세스의 pid를 입력\n");
	printf(">>> 모든 프로세스를 확인하고 싶으면 all을 입력\n");
	printf(">>> 종료를 원하면 quit이나 q를 입력\n\n");
	printf(">>> pid를 입력하세요(all or q) :");

	char input[1024];
	int pid;

	while(gets(input))
	{
		if(!strcmp(input, "quit"))
			break;
		else if(!strcmp(input, "q"))
			break;
		else if(!strcmp(input, "all"))
			ar.PrintProcessList();
		else
		{
			pid = atoi(input);
			if(!ar.PrintProcessInfoByPid(pid))
				printf("pid와 일치하는 프로세스 정보가 없습니다.\n");
		}

		printf("\n>>> pid를 입력하세요(all or q) :");
	}

    return 0;
}