#include "utility.h"

#ifndef _H_ORGBKTYYC_MATRIXEE_FRACTION_
#define _H_ORGBKTYYC_MATRIXEE_FRACTION_

typedef struct
{
    ll numerator;
    ll denominator;
} OrgBktYyc_MartixEE_Fraction_classFraction;

typedef enum
{
    OrgBktYyc_MartixEE_Fraction_enumOperation_Add,
    OrgBktYyc_MartixEE_Fraction_enumOperation_Subtract,
    OrgBktYyc_MartixEE_Fraction_enumOperation_Multiply,
    OrgBktYyc_MartixEE_Fraction_enumOperation_Divide
} OrgBktYyc_MartixEE_Fraction_enumOperation;

void OrgBktYyc_MartixEE_Fraction_Operate(
    OrgBktYyc_MartixEE_Fraction_classFraction *target,
    OrgBktYyc_MartixEE_Fraction_classFraction *a,
    OrgBktYyc_MartixEE_Fraction_classFraction *b,
    OrgBktYyc_MartixEE_Fraction_enumOperation type);

void OrgBktYyc_MartixEE_Fraction_Scanf(OrgBktYyc_MartixEE_Fraction_classFraction *obj);
void OrgBktYyc_MartixEE_Fraction_Print(OrgBktYyc_MartixEE_Fraction_classFraction *obj);

ll OrgBktYyc_MartixEE_Fraction_gcd(ll a, ll b);
ll OrgBktYyc_MartixEE_Fraction_lcm(ll a, ll b);

#endif