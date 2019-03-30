#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#include "regular_expression.h"
#include "utility.h"

bool OrgBktYyc_MartixEE_RegularExpression_IsMatch(
    char *origin,
    char *regularExpression)
{
    //build
    regex_t target;
    int result;
    result = regcomp(&target, regularExpression, REG_EXTENDED|REG_NOSUB);
    if (result != 0)
        return false;

    //match
    result = regexec(&target, origin, 0, NULL, 0);

    //free resources
    regfree(&target);
    return (result == 0 ? true : false);
}

OrgBktYyc_MartixEE_RegularExpression_Result *OrgBktYyc_MartixEE_RegularExpression_Matches(
    char *origin,
    char *regularExpression)
{
    //build
    regex_t target;
    int result;
    result = regcomp(&target, regularExpression, REG_EXTENDED);

    //generate data
    OrgBktYyc_MartixEE_RegularExpression_Result *res = malloc(sizeof(OrgBktYyc_MartixEE_RegularExpression_Result));

    if (result != 0)
    {
        res->is_success = false;
        res->count = 0;
        res->result = NULL;

        return res;
    }
    else
    {
        res->count = target.re_nsub + 1;
        res->result = malloc(sizeof(regmatch_t) * res->count);
    }

    //match
    result = regexec(&target, origin, res->count, res->result, 0);
    if (result != 0)
        res->is_success = false;
    else
        res->is_success = true;

    //free resources
    regfree(&target);
    return res;
}

void OrgBktYyc_MartixEE_RegularExpression_Result_Free(
    OrgBktYyc_MartixEE_RegularExpression_Result *obj)
{
    free(obj->result);
    free(obj);
}
