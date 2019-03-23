#include <stdio.h>
#include <stdlib.h>

#include "matrix_hand.h"
#include "../matrix.h"
#include "../utility.h"

void OrgBktYyc_MartixEE_Module_MatrixHand_Main()
{
    //output help
    OrgBktYyc_MartixEE_Module_MatrixHand_Help();
    //init matrix
    OrgBktYyc_MartixEE_Matrix_classMatrix *mt = OrgBktYyc_MartixEE_Module_MatrixHand_InitMatrix();
    if (mt == NULL)
        return;

    //declare the value which will be used
    char command;
    char swapAffect1, swapAffect2, operationAffect, operationOperator, addIntoAffect1, addIntoAffect2;
    int swapIndex1, swapIndex2, operationIndex, operationInt, addIntoIndex1, addIntoIndex2, addIntoMultiplyInt;
    double operationDouble, addIntoMultiplyDouble;
    OrgBktYyc_MartixEE_Matrix_unionMatrixItem *sharedNum = OrgBktYyc_MartixEE_Matrix_unionMatrixItem_Init();
    while (true)
    {
        printf("\nmatrix_ee - matrix_hand> ");
        if((command = getchar()) == '\n') continue;

        switch (command)
        {
        case 'u':
            OrgBktYyc_MartixEE_Matrix_classMatrix_Upgrade(mt);
            break;
        case 's':
            //read data
            scanf("%c%d-%c%d", &swapAffect1, &swapIndex1, &swapAffect2, &swapIndex2);
            //judge data
            if (OrgBktYyc_MartixEE_Module_MatrixHand_CheckSwapInput(swapAffect1, swapIndex1, swapAffect2, swapIndex2))
            {
                //calc type
                OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType swapType;
                switch (swapAffect1)
                {
                case 'c':
                    swapType = OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_COLUMNS;
                    break;
                case 'r':
                    swapType = OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_ROWS;
                    break;
                }

                //correct parameter
                swapIndex1--;
                swapIndex2--;

                OrgBktYyc_MartixEE_Matrix_classMatrix_Swap(mt, swapType, swapIndex1, swapIndex2);
            }
            else
                printf("Illegal parameter!\n");
            break;
        case 'o':
            //read data
            switch (mt->type)
            {
            case OrgBktYyc_MartixEE_Matrix_enumMatrixType_DOUBLE:
                scanf("%c%d%c%lf", &operationAffect, &operationIndex, &operationOperator, &operationDouble);
                sharedNum->itemDOUBLE = operationDouble;
                break;
            case OrgBktYyc_MartixEE_Matrix_enumMatrixType_INTEGER:
                scanf("%c%d%c%d", &operationAffect, &operationIndex, &operationOperator, &operationInt);
                sharedNum->itemINTEGER = operationInt;
                break;
            }
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

                OrgBktYyc_MartixEE_Matrix_classMatrix_Operation(mt, operationType, operatorType, operationIndex, sharedNum);
            }
            else
                printf("Illegal parameter!\n");
            break;
        case 'a':
            //read data
            switch (mt->type)
            {
            case OrgBktYyc_MartixEE_Matrix_enumMatrixType_DOUBLE:
                scanf("%c%d%lf%c%d", &addIntoAffect1, &addIntoIndex1, &addIntoMultiplyDouble, &addIntoAffect2, &addIntoIndex2);
                sharedNum->itemDOUBLE = addIntoMultiplyDouble;
                break;
            case OrgBktYyc_MartixEE_Matrix_enumMatrixType_INTEGER:
                scanf("%c%d%d%c%d", &addIntoAffect1, &addIntoIndex1, &addIntoMultiplyInt, &addIntoAffect2, &addIntoIndex2);
                sharedNum->itemINTEGER = addIntoMultiplyInt;
                break;
            }
            //judge data
            if (OrgBktYyc_MartixEE_Module_MatrixHand_CheckAddIntoInput(addIntoAffect1, addIntoIndex1, addIntoAffect2, addIntoIndex2))
            {
                //calc type
                OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType addIntoType;
                switch (swapAffect1)
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

                OrgBktYyc_MartixEE_Matrix_classMatrix_AddInto(mt, addIntoType, addIntoIndex2, addIntoIndex1, sharedNum);
            }
            else
                printf("Illegal parameter!\n");
            break;
        case 'e':
            goto endCalcFunction;
            break;
        default:
            printf("Unknow command!\n");
            break;
        }

        //display res
        OrgBktYyc_MartixEE_Matrix_classMatrix_Print(mt);
    }

endCalcFunction:
    //release resources
    OrgBktYyc_MartixEE_Matrix_unionMatrixItem_Dispose(sharedNum);
    OrgBktYyc_MartixEE_Matrix_classMatrix_Dispose(mt);
}

void OrgBktYyc_MartixEE_Module_MatrixHand_Help()
{
    printf("Help\n");
    printf("\n");
    printf("Format: [char tag][parameter]\n");
    printf("\tu - upgrade matrix (from int to double)\n");
    printf("\ts - swap 2 columns or rows\n");
    printf("\t\ts[c|r][index]-[c|r][index]\n");
    printf("\to - do operation for specific rows or colums\n");
    printf("\t\to[c|r][index][*|/][number]\n");
    printf("\ta - add one columns or rows into another\n");
    printf("\ta[c|r][target-index][multply-number(positive or negative)][c|r][origin-index]\n");
    printf("\n");
    printf("Example:\n");
    printf("\tu\n");
    printf("\tsc1-c2\n");
    printf("\tor3*4\n");
    printf("\tac3-5c2\n");
    printf("\n");
    printf("e - exit\n");
}

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
