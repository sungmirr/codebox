#include <windows.h>
#include <stdio.h>
#include "Archive.h"
#include <strsafe.h>


int main(void)
{
    Archive ar;
    ar.SetProcessList();


	printf(">>> Ȯ���ϰ� ���� ���μ����� pid�� �Է�\n");
	printf(">>> ��� ���μ����� Ȯ���ϰ� ������ all�� �Է�\n");
	printf(">>> ���Ḧ ���ϸ� quit�̳� q�� �Է�\n\n");
	printf(">>> pid�� �Է��ϼ���(all or q) :");

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
				printf("pid�� ��ġ�ϴ� ���μ��� ������ �����ϴ�.\n");
		}

		printf("\n>>> pid�� �Է��ϼ���(all or q) :");
	}

    return 0;
}