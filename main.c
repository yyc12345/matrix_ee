#include <stdio.h>
#include <stdlib.h>

#include "utility.h"
#include "matrix.h"

#include "module/matrix_hand.h"
#include "module/matrix_auto.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void menu();

int main(int argc, char *argv[])
{
	int command;
	while (true)
	{
		menu();
		printf("matrix_ee> ");
		scanf("%d", &command);
		switch (command)
		{
		case 0:
			return 0;
		case 1:
			OrgBktYyc_MartixEE_Module_MatrixHand_Main();
			break;
		case 2:
			OrgBktYyc_MartixEE_Module_MatrixAuto_Main();
			break;
		default:
			printf("Error command!\n");
			break;
		}
	}
}

void menu()
{
	printf("Menu:\n");
	printf("\n");
	printf("1 - Matrix with hand calculation\n");
	printf("2 - Full automatically matrix calculation (experimental) (for ee calc)\n");
	printf("\n");
	printf("0 - exit\n");
	printf("Coming soon...\n");
}
