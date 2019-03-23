#ifndef _H_ORGBKTYYC_MATRIXEE_MATRIX_
#define _H_ORGBKTYYC_MATRIXEE_MATRIX_

//declare some type

typedef enum
{
	OrgBktYyc_MartixEE_Matrix_enumMatrixType_INTEGER,
	OrgBktYyc_MartixEE_Matrix_enumMatrixType_DOUBLE
} OrgBktYyc_MartixEE_Matrix_enumMatrixType;

typedef enum
{
	OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_COLUMNS,
	OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType_ROWS
} OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType;

typedef enum
{
	OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType_DIVISION,
	OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType_MULTIPLY
} OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType;

//declare matrix basic unit

typedef union {
	int itemINTEGER;
	double itemDOUBLE;
} OrgBktYyc_MartixEE_Matrix_unionMatrixItem;

OrgBktYyc_MartixEE_Matrix_unionMatrixItem *OrgBktYyc_MartixEE_Matrix_unionMatrixItem_Init();

void OrgBktYyc_MartixEE_Matrix_unionMatrixItem_Dispose(
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *obj);

void OrgBktYyc_MartixEE_Matrix_unionMatrixItem_Upgrade(
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *obj);

void OrgBktYyc_MartixEE_Matrix_unionMatrixItem_Swap(
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *origin,
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *target,
	OrgBktYyc_MartixEE_Matrix_enumMatrixType swapMode);

//declre matrix struct

typedef struct
{
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *p;
	OrgBktYyc_MartixEE_Matrix_enumMatrixType type;
	int rows;
	int columns;
} OrgBktYyc_MartixEE_Matrix_classMatrix;

//init matrix
OrgBktYyc_MartixEE_Matrix_classMatrix *OrgBktYyc_MartixEE_Matrix_classMatrix_Init(
	int rows,
	int columns,
	OrgBktYyc_MartixEE_Matrix_enumMatrixType type);

//free matrix
void OrgBktYyc_MartixEE_Matrix_classMatrix_Dispose(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj);

//upgrade matrix. from int to double
void OrgBktYyc_MartixEE_Matrix_classMatrix_Upgrade(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj);

//swap 2 columns or rows
void OrgBktYyc_MartixEE_Matrix_classMatrix_Swap(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj,
	OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType mode,
	int originIndex,
	int targetIndex);

//do some calculation for specific row or columns
void OrgBktYyc_MartixEE_Matrix_classMatrix_Operation(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj,
	OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType affectMode,
	OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType operationMode,
	int targetIndex,
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *num);

//basic matrix fransform
void OrgBktYyc_MartixEE_Matrix_classMatrix_AddInto(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj,
	OrgBktYyc_MartixEE_Matrix_enumMatrixAffectionType mode,
	int originIndex,
	int targetIndex,
	OrgBktYyc_MartixEE_Matrix_unionMatrixItem *num);

OrgBktYyc_MartixEE_Matrix_unionMatrixItem *OrgBktYyc_MartixEE_Matrix_classMatrix_GetItem(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj,
	int rowIndex,
	int columnsIndex);

void OrgBktYyc_MartixEE_Matrix_classMatrix_Print(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj);

#endif
