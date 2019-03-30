#include <regex.h>

#include "utility.h"

#ifndef _H_ORGBKTYYC_MATRIXEE_REGULAREXPRESSION_
#define _H_ORGBKTYYC_MATRIXEE_REGULAREXPRESSION_

typedef struct
{
    bool is_success;
    size_t count;
    regmatch_t *result;
} OrgBktYyc_MartixEE_RegularExpression_Result;

bool OrgBktYyc_MartixEE_RegularExpression_IsMatch(
    char *origin,
    char *regularExpression);

OrgBktYyc_MartixEE_RegularExpression_Result *OrgBktYyc_MartixEE_RegularExpression_Matches(
    char *origin,
    char *regularExpression);

void OrgBktYyc_MartixEE_RegularExpression_Result_Free(
    OrgBktYyc_MartixEE_RegularExpression_Result *obj);

#endif