#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"
#include "matrix.h"

#include "module/matrix_hand.h"
#include "module/matrix_auto.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void help();

int main(int argc, char *argv[])
{
	printf("Welcome to use matrix_ee~\n");
	char command[COMMAND_BUFFER_SIZE];
	while (true)
	{
		printf("matrix_ee> ");
		OrgBktYyc_MartixEE_Utility_ReadLine(command);

		if (!strcmp(command, "help"))
			help();
		else if (!strcmp(command, "exit"))
			break;
		else if (!strcmp(command, "matrix-hand"))
			OrgBktYyc_MartixEE_Module_MatrixHand_Main();
		else if (!strcmp(command, "matrix-auto"))
			OrgBktYyc_MartixEE_Module_MatrixAuto_Main();
		else
			printf("Error command!\n");
	}
}

void help()
{
	printf("Help\n");
	printf("\n");
	printf("\tmatrix-hand - Matrix with hand calculation\n");
	printf("\tmatrix-auto - Full automatically matrix calculation (experimental) (for ee calc)\n");
	printf("\tComing soon...\n");
	printf("\n");
	printf("\texit - exit matrix_ee\n");
	printf("\thelp - print this message\n");
}
