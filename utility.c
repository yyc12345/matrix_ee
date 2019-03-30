#include <stdio.h>

#include "utility.h"

void OrgBktYyc_MartixEE_Utility_ReadLine(char *str)
{
    char chr;
    int i = 0;
    while ((chr = getchar()) != '\n')
    {
        if (i < COMMAND_BUFFER_SIZE - 1)
            *(str + i) = chr;
        i++;
    }
    if (i < COMMAND_BUFFER_SIZE)
        *(str + i) = '\0';
    else
        *(str + COMMAND_BUFFER_SIZE - 1) = '\0';
}
