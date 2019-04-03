#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

/*==================================================================================================*/

void OrgBktYyc_MartixEE_Matrix_unionMatrixItem_Upgrade(
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *obj)
{
	(obj->itemDOUBLE) = (double)(obj->itemINTEGER);
}

void OrgBktYyc_MartixEE_Matrix_unionMatrixItem_Swap(
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *origin,
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *target,
	OrgBktYyc_MartixEE_Matrix_enumMatrixType swapMode)
{
	switch (swapMode)
	{
	case OrgBktYyc_MartixEE_Matrix_enumMatrixType_INTEGER:;
		int intCache = origin->itemINTEGER;
		origin->itemINTEGER = target->itemINTEGER;
		target->itemINTEGER = intCache;
		break;
	case OrgBktYyc_MartixEE_Matrix_enumMatrixType_DOUBLE:;
		double doubleCache = origin->itemDOUBLE;
		origin->itemDOUBLE = target->itemDOUBLE;
		target->itemDOUBLE = doubleCache;
		break;
	}
}

/*==================================================================================================*/

OrgBktYyc_MartixEE_Matrix_classMatrix *OrgBktYyc_MartixEE_Matrix_classMatrix_Init(
	int rows,
	int columns,
	OrgBktYyc_MartixEE_Matrix_enumMatrixType type)
{
	OrgBktYyc_MartixEE_Matrix_classMatrix *res =
		(OrgBktYyc_MartixEE_Matrix_classMatrix *)malloc(sizeof(OrgBktYyc_MartixEE_Matrix_classMatrix));
	res->columns = columns;
	res->rows = rows;
	res->type = type;
	res->p = (OrgBktYyc_MartixEE_Matrix_unionMatrixItem *)malloc(sizeof(OrgBktYyc_MartixEE_Matrix_unionMatrixItem) * rows * columns);
	return res;
}

void OrgBktYyc_MartixEE_Matrix_classMatrix_Dispose(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj)
{
	free(obj->p);
	free(obj);
}

void OrgBktYyc_MartixEE_Matrix_classMatrix_Upgrade(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj)
{
	int i, j;
	for (i = 0; i < obj->rows; i++)
	{
		for (j = 0; j < obj->columns; j++)
		{
			OrgBktYyc_MartixEE_Matrix_unionMatrixItem_Upgrade(obj->p + i * obj->columns + j);
		}
	}
}

void OrgBktYyc_MartixEE_Matrix_classMatrix_Swap(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj,
	OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType mode,
	int originIndex,
	int targetIndex)
{
	int i;
	switch (mode)
	{
	case OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_ROWS:
		for (i = 0; i < obj->columns; i++)
			OrgBktYyc_MartixEE_Matrix_unionMatrixItem_Swap(
				OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, originIndex, i),
				OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, targetIndex, i),
				obj->type);
		break;
	case OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_COLUMNS:
		for (i = 0; i < obj->rows; i++)
			OrgBktYyc_MartixEE_Matrix_unionMatrixItem_Swap(
				OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, i, originIndex),
				OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, i, targetIndex),
				obj->type);
		break;
	}
}

void OrgBktYyc_MartixEE_Matrix_classMatrix_Operation(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj,
	OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType affectMode,
	OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType operationMode,
	int targetIndex,
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *num)
{
	int rowMin, rowMax, colMin, colMax;
	switch (affectMode)
	{
	case OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_COLUMNS:
		rowMin = 0;
		rowMax = obj->rows - 1;
		colMin = colMax = targetIndex;
		break;
	case OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_ROWS:
		colMin = 0;
		colMax = obj->columns - 1;
		rowMin = rowMax = targetIndex;
		break;
	}
	int i, j;
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *cache = NULL;
	for (i = rowMin; i <= rowMax; i++)
	{
		for (j = colMin; j <= colMax; j++)
		{
			cache = OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, i, j);
			switch (obj->type)
			{
			case OrgBktYyc_MartixEE_Matrix_enumMatrixType_DOUBLE:
				switch (operationMode)
				{
				case OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType_DIVISION:
					cache->itemDOUBLE /= num->itemDOUBLE;
					break;
				case OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType_MULTIPLY:
					cache->itemDOUBLE *= num->itemDOUBLE;
					break;
				}
				break;
			case OrgBktYyc_MartixEE_Matrix_enumMatrixType_INTEGER:
				switch (operationMode)
				{
				case OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType_DIVISION:
					cache->itemINTEGER /= num->itemINTEGER;
					break;
				case OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType_MULTIPLY:
					cache->itemINTEGER *= num->itemINTEGER;
					break;
				}
				break;
			}
		}
	}
}

void OrgBktYyc_MartixEE_Matrix_classMatrix_AddInto(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj,
	OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType mode,
	int originIndex,
	int targetIndex,
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *num)
{
	int i;
	switch (obj->type)
	{
	case OrgBktYyc_MartixEE_Matrix_enumMatrixType_DOUBLE:;
		switch (mode)
		{
		case OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_ROWS:
			for (i = 0; i < obj->columns; i++)
				OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, targetIndex, i)->itemDOUBLE +=
					num->itemDOUBLE * OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, originIndex, i)->itemDOUBLE;
			break;
		case OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_COLUMNS:
			for (i = 0; i < obj->rows; i++)
				OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, i, targetIndex)->itemDOUBLE +=
					num->itemDOUBLE * OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, i, originIndex)->itemDOUBLE;
			break;
		}
		break;
	case OrgBktYyc_MartixEE_Matrix_enumMatrixType_INTEGER:
		switch (mode)
		{
		case OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_ROWS:
			for (i = 0; i < obj->columns; i++)
				OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, targetIndex, i)->itemINTEGER +=
					num->itemINTEGER * OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, originIndex, i)->itemINTEGER;
			break;
		case OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_COLUMNS:
			for (i = 0; i < obj->rows; i++)
				OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, i, targetIndex)->itemINTEGER +=
					num->itemINTEGER * OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, i, originIndex)->itemINTEGER;
			break;
		}
		break;
	}
}

OrgBktYyc_MartixEE_Matrix_unionMatrixItem *OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj,
	int rowIndex,
	int columnsIndex)
{
	return obj->p + rowIndex * obj->columns + columnsIndex;
}

void OrgBktYyc_MartixEE_Matrix_classMatrix_Print(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj)
{
	int i, j;
	for (i = 0; i < obj->rows; i++)
	{
		for (j = 0; j < obj->columns; j++)
		{
			switch (obj->type)
			{
			case OrgBktYyc_MartixEE_Matrix_enumMatrixType_INTEGER:
				printf("%d", OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, i, j)->itemINTEGER);
				break;
			case OrgBktYyc_MartixEE_Matrix_enumMatrixType_DOUBLE:
				printf("%lf", OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(obj, i, j)->itemDOUBLE);
				break;
			}
			printf("\t");
		}
		printf("\n");
	}
}
