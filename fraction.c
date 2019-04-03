#include <stdio.h>

#include "utility.h"
#include "fraction.h"

void OrgBktYyc_MartixEE_Fraction_Operate(
    OrgBktYyc_MartixEE_Fraction_classFraction *target,
    OrgBktYyc_MartixEE_Fraction_classFraction *a,
    OrgBktYyc_MartixEE_Fraction_classFraction *b,
    OrgBktYyc_MartixEE_Fraction_enumOperation type)
{
    ;//todo
}

void OrgBktYyc_MartixEE_Fraction_Scanf(OrgBktYyc_MartixEE_Fraction_classFraction *obj)
{
    ;//todo
}
void OrgBktYyc_MartixEE_Fraction_Print(OrgBktYyc_MartixEE_Fraction_classFraction *obj)
{
    ;//todo
}

ll OrgBktYyc_MartixEE_Fraction_gcd(ll a, ll b)
{
    ll t;
    while (b)
    {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}
ll OrgBktYyc_MartixEE_Fraction_lcm(ll a, ll b)
{
    return a / OrgBktYyc_MartixEE_Fraction_gcd(a, b) * b;
}