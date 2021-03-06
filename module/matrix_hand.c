#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_hand.h"
#include "../regular_expression.h"
#include "../matrix.h"
#include "../utility.h"

char OrgBktYyc_MartixEE_Module_MatrixHand_RegexString_Swap[] = "(c|r)([0-9]+)~(c|r)([0-9]+)";
char OrgBktYyc_MartixEE_Module_MatrixHand_RegexString_Operation[] = "(c|r)([0-9]+)(\\*|/)((\\+|-){0,1}([0-9]*))";
char OrgBktYyc_MartixEE_Module_MatrixHand_RegexString_AddInto[] = "(c|r)([0-9]+)((\\+|-){1}([0-9]*))(c|r)([0-9]+)";

void OrgBktYyc_MartixEE_Module_MatrixHand_Main()
{
    //init matrix
    OrgBktYyc_MartixEE_Matrix_classMatrix *mt = OrgBktYyc_MartixEE_Module_MatrixHand_InitMatrix();
    if (mt == NULL)
        return;

    //declare the value which will be used
    char command[COMMAND_BUFFER_SIZE];

    while (true)
    {
        printf("matrix_ee - matrix_hand> ");
        OrgBktYyc_MartixEE_Utility_ReadLine(command);

        if (!strcmp(command, "help"))
            OrgBktYyc_MartixEE_Module_MatrixHand_Help();
        else if (!strcmp(command, "exit"))
            break;
        else if (!strcmp(command, "upgrade"))
            OrgBktYyc_MartixEE_Matrix_classMatrix_Upgrade(mt);
        else if (!strcmp(command, "show"))
            OrgBktYyc_MartixEE_Matrix_classMatrix_Print(mt);
        else if (OrgBktYyc_MartixEE_RegularExpression_IsMatch(command, OrgBktYyc_MartixEE_Module_MatrixHand_RegexString_Swap))
            OrgBktYyc_MartixEE_Module_MatrixHand_MatrixOperSwap(mt, command);
        else if (OrgBktYyc_MartixEE_RegularExpression_IsMatch(command, OrgBktYyc_MartixEE_Module_MatrixHand_RegexString_Operation))
            OrgBktYyc_MartixEE_Module_MatrixHand_MatrixOperMultiply(mt, command);
        else if (OrgBktYyc_MartixEE_RegularExpression_IsMatch(command, OrgBktYyc_MartixEE_Module_MatrixHand_RegexString_AddInto))
            OrgBktYyc_MartixEE_Module_MatrixHand_MatrixOperAddInto(mt, command);
        else
            printf("Unknow command!\n");
    }
    
    //release resources
    OrgBktYyc_MartixEE_Matrix_classMatrix_Dispose(mt);
}

void OrgBktYyc_MartixEE_Module_MatrixHand_Help()
{
    printf("Help\n");
    printf("\n");
    printf("Operation command: (In short words, you can input command just with normal math formation)\n");
    printf("\t[c|r][index]~[c|r][index] - swap 2 columns or rows\n");
    printf("\t[c|r][index][*|/][number] - do operation for specific rows or colums\n");
    printf("\t[c|r][target-index][multply-number(positive or negative)(default in 1 if you omit this)][c|r][origin-index] - add one columns or rows into another\n");
    printf("\n");
    printf("Example:\n");
    printf("\tc1~c2\n");
    printf("\tr3*2\n");
    printf("\tc3-5c2\n");
    printf("\n");
    printf("Global command:\n");
    printf("\tshow - display current matrix's status\n");
    printf("\tupgrade - upgrade matrix (from int to double)\n");
    printf("\thelp - print this message\n");
    printf("\texit - exit matrix_ee-matrix_hand\n");
}

//===================================================================================================================================

OrgBktYyc_MartixEE_Matrix_classMatrix *OrgBktYyc_MartixEE_Module_MatrixHand_InitMatrix()
{
    int rows, columns;
    printf("Input your matrix's rows and columns' count. Such as: 4 3 will construct a matrix with 4 rows and 3 columns.\n");
    scanf("%d%d", &rows, &columns);
    if (rows <= 0 || columns <= 0)
    {
        printf("Illegal parameter!\n");
        return NULL;
    }

    OrgBktYyc_MartixEE_Matrix_enumMatrixType type;
    int i, j;
    printf("Input your matrix type. 0 for Integer. 1 for Double.\n");
    scanf("%d", &i);
    switch (i)
    {
    case 0:
        type = OrgBktYyc_MartixEE_Matrix_enumMatrixType_INTEGER;
        break;
    case 1:
        type = OrgBktYyc_MartixEE_Matrix_enumMatrixType_DOUBLE;
        break;
    default:
        printf("Illegal parameter!\n");
        return NULL;
    }

    OrgBktYyc_MartixEE_Matrix_classMatrix *res = OrgBktYyc_MartixEE_Matrix_classMatrix_Init(rows, columns, type);

    //int i, j;
    printf("Now, please input data one by one for each rows.\n");
    switch (res->type)
    {
    case OrgBktYyc_MartixEE_Matrix_enumMatrixType_DOUBLE:;
        double cacheDouble;
        for (i = 0; i < res->rows; i++)
        {
            for (j = 0; j < res->columns; j++)
            {
                scanf("%lf", &cacheDouble);
                OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(res, i, j)->itemDOUBLE = cacheDouble;
            }
        }
        break;

    case OrgBktYyc_MartixEE_Matrix_enumMatrixType_INTEGER:;
        int cacheInt;
        for (i = 0; i < res->rows; i++)
        {
            for (j = 0; j < res->columns; j++)
            {
                scanf("%d", &cacheInt);
                OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(res, i, j)->itemINTEGER = cacheInt;
            }
        }
        break;
    }

    return res;
}

void OrgBktYyc_MartixEE_Module_MatrixHand_MatrixOperSwap(
    OrgBktYyc_MartixEE_Matrix_classMatrix *mt,
    char *command)
{
    //get data
    OrgBktYyc_MartixEE_RegularExpression_Result *sp =
        OrgBktYyc_MartixEE_RegularExpression_Matches(command, OrgBktYyc_MartixEE_Module_MatrixHand_RegexString_Swap);

    char affect1 = *(command + ((sp->result + 1)->rm_so)),
         affect2 = *(command + ((sp->result + 3)->rm_so));
    int index1 = OrgBktYyc_MartixEE_Utility_IntParse(command, (sp->result + 2)->rm_so),
        index2 = OrgBktYyc_MartixEE_Utility_IntParse(command, (sp->result + 4)->rm_so);
    //free resources
    OrgBktYyc_MartixEE_RegularExpression_Result_Free(sp);

    //judge data
    if (OrgBktYyc_MartixEE_Module_MatrixHand_CheckSwapInput(affect1, index1, affect2, index2))
    {
        //calc type
        OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType swapType;
        switch (affect1)
        {
        case 'c':
            swapType = OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_COLUMNS;
            break;
        case 'r':
            swapType = OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_ROWS;
            break;
        }

        //correct parameter
        index1--;
        index2--;

        OrgBktYyc_MartixEE_Matrix_classMatrix_Swap(mt, swapType, index1, index2);
    }
    else
        printf("Illegal parameter!\n");
}
void OrgBktYyc_MartixEE_Module_MatrixHand_MatrixOperMultiply(
    OrgBktYyc_MartixEE_Matrix_classMatrix *mt,
    char *command)
{
    //get data
    OrgBktYyc_MartixEE_RegularExpression_Result *sp =
        OrgBktYyc_MartixEE_RegularExpression_Matches(command, OrgBktYyc_MartixEE_Module_MatrixHand_RegexString_Operation);

    char operationAffect = *(command + ((sp->result + 1)->rm_so)),
         operationOperator = *(command + ((sp->result + 3)->rm_so));
    int operationIndex = OrgBktYyc_MartixEE_Utility_IntParse(command, (sp->result + 2)->rm_so);

    OrgBktYyc_MartixEE_Matrix_unionMatrixItem sharedNum;
    if (mt->type == OrgBktYyc_MartixEE_Matrix_enumMatrixType_DOUBLE)
        sharedNum.itemDOUBLE = OrgBktYyc_MartixEE_Utility_DoubleParse(command, (sp->result + 4)->rm_so);
    else
        sharedNum.itemINTEGER = OrgBktYyc_MartixEE_Utility_IntParse(command, (sp->result + 4)->rm_so);

    //free resources
    OrgBktYyc_MartixEE_RegularExpression_Result_Free(sp);

    //judge data
    if (OrgBktYyc_MartixEE_Module_MatrixHand_CheckOperationInput(operationAffect, operationIndex, operationOperator))
    {
        //calc type
        OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType operationType;
        switch (operationAffect)
        {
        case 'c':
            operationType = OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_COLUMNS;
            break;
        case 'r':
            operationType = OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_ROWS;
            break;
        }
        OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType operatorType;
        switch (operationOperator)
        {
        case '*':
            operatorType = OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType_MULTIPLY;
            break;
        case '/':
            operatorType = OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType_DIVISION;
            break;
        }

        //correct parameter
        operationIndex--;

        OrgBktYyc_MartixEE_Matrix_classMatrix_Operation(mt, operationType, operatorType, operationIndex, &sharedNum);
    }
    else
        printf("Illegal parameter!\n");
}
void OrgBktYyc_MartixEE_Module_MatrixHand_MatrixOperAddInto(
    OrgBktYyc_MartixEE_Matrix_classMatrix *mt,
    char *command)
{
    //get data
    OrgBktYyc_MartixEE_RegularExpression_Result *sp =
        OrgBktYyc_MartixEE_RegularExpression_Matches(command, OrgBktYyc_MartixEE_Module_MatrixHand_RegexString_AddInto);

    char addIntoAffect1 = *(command + ((sp->result + 1)->rm_so)),
         addIntoAffect2 = *(command + ((sp->result + 6)->rm_so));
    int addIntoIndex1 = OrgBktYyc_MartixEE_Utility_IntParse(command, (sp->result + 2)->rm_so),
        addIntoIndex2 = OrgBktYyc_MartixEE_Utility_IntParse(command, (sp->result + 7)->rm_so);

    OrgBktYyc_MartixEE_Matrix_unionMatrixItem sharedNum;
    //judge whether have number and judge data type
    if (mt->type == OrgBktYyc_MartixEE_Matrix_enumMatrixType_DOUBLE)
    {
        if ((sp->result + 5)->rm_so == (sp->result + 5)->rm_eo)
            sharedNum.itemDOUBLE = (*(command + ((sp->result + 4)->rm_so)) == '+' ? 1 : -1);
        else
            sharedNum.itemDOUBLE = OrgBktYyc_MartixEE_Utility_DoubleParse(command, (sp->result + 3)->rm_so);
    }
    else
    {
        if ((sp->result + 5)->rm_so == (sp->result + 5)->rm_eo)
            sharedNum.itemINTEGER = (*(command + ((sp->result + 4)->rm_so)) == '+' ? 1 : -1);
        else
            sharedNum.itemINTEGER = OrgBktYyc_MartixEE_Utility_IntParse(command, (sp->result + 3)->rm_so);
    }

    //free resources
    OrgBktYyc_MartixEE_RegularExpression_Result_Free(sp);

    //judge data
    if (OrgBktYyc_MartixEE_Module_MatrixHand_CheckAddIntoInput(addIntoAffect1, addIntoIndex1, addIntoAffect2, addIntoIndex2))
    {
        //calc type
        OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType addIntoType;
        switch (addIntoAffect1)
        {
        case 'c':
            addIntoType = OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_COLUMNS;
            break;
        case 'r':
            addIntoType = OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_ROWS;
            break;
        }

        //correct parameter
        addIntoIndex1--;
        addIntoIndex2--;

        OrgBktYyc_MartixEE_Matrix_classMatrix_AddInto(mt, addIntoType, addIntoIndex2, addIntoIndex1, &sharedNum);
    }
    else
        printf("Illegal parameter!\n");
}

//=================================================================================================================================

bool OrgBktYyc_MartixEE_Module_MatrixHand_CheckSwapInput(
    char a1, int i1, char a2, int i2)
{
    if (i1 <= 0 || i2 <= 0)
        return false;
    if (a1 != a2)
        return false;
    if (a1 != 'c' && a1 != 'r')
        return false;

    return true;
}

bool OrgBktYyc_MartixEE_Module_MatrixHand_CheckOperationInput(
    char a, int i, char optr)
{
    if (i <= 0)
        return false;
    if (a != 'c' && a != 'r')
        return false;
    if (optr != '*' && optr != '/')
        return false;

    return true;
}

bool OrgBktYyc_MartixEE_Module_MatrixHand_CheckAddIntoInput(
    char a1, int i1, char a2, int i2)
{
    return OrgBktYyc_MartixEE_Module_MatrixHand_CheckSwapInput(a1, i1, a2, i2);
}
