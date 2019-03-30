#include "../matrix.h"
#include "../utility.h"

#ifndef _H_ORGBKTYYC_MATRIXEE_MODULE_MATRIXHAND_
#define _H_ORGBKTYYC_MATRIXEE_MODULE_MATRIXHAND_

void OrgBktYyc_MartixEE_Module_MatrixHand_Main();
void OrgBktYyc_MartixEE_Module_MatrixHand_Help();

OrgBktYyc_MartixEE_Matrix_classMatrix *OrgBktYyc_MartixEE_Module_MatrixHand_InitMatrix();

void OrgBktYyc_MartixEE_Module_MatrixHand_MatrixOperSwap(
    OrgBktYyc_MartixEE_Matrix_classMatrix *mt,
    char *command);
void OrgBktYyc_MartixEE_Module_MatrixHand_MatrixOperMultiply(
    OrgBktYyc_MartixEE_Matrix_classMatrix *mt,
    char *command);
void OrgBktYyc_MartixEE_Module_MatrixHand_MatrixOperAddInto(
    OrgBktYyc_MartixEE_Matrix_classMatrix *mt,
    char *command);

bool OrgBktYyc_MartixEE_Module_MatrixHand_CheckSwapInput(
    char a1, int i1, char a2, int i2);
bool OrgBktYyc_MartixEE_Module_MatrixHand_CheckOperationInput(
    char a, int i, char optr);
bool OrgBktYyc_MartixEE_Module_MatrixHand_CheckAddIntoInput(
    char a1, int i1, char a2, int i2);

#endif