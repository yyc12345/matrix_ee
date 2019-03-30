#include <stdio.h>
#include <stdlib.h>

#include "utility.h"

void OrgBktYyc_MartixEE_Utility_ReadLine(char *str)
{
    char chr;
    int i = 0;
    while (true)
    {
        chr = getchar();
        if(chr=='\n' && i==0) continue;
        if(chr=='\n') break;

        if (i < COMMAND_BUFFER_SIZE - 1)
            *(str + i) = chr;
        i++;
    }
    if (i < COMMAND_BUFFER_SIZE)
        *(str + i) = '\0';
    else
        *(str + COMMAND_BUFFER_SIZE - 1) = '\0';
}

int OrgBktYyc_MartixEE_Utility_IntParse(char *str, int start)
{
    return atoi(str + start);
}
ll OrgBktYyc_MartixEE_Utility_LongLongParse(char *str, int start)
{
    return atoll(str + start);
}
double OrgBktYyc_MartixEE_Utility_DoubleParse(char *str, int start)
{
    return atof(str + start);
}
