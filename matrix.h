#ifndef _H_ORGBKTYYC_MATRIXEE_MATRIX_
#define _H_ORGBKTYYC_MATRIXEE_MATRIX_

typedef enum {
	OrgBktYyc_MartixEE_Matrix_enumMatrixType_INTEGER,
	OrgBktYyc_MartixEE_Matrix_enumMatrixType_DOUBLE
}OrgBktYyc_MartixEE_Matrix_enumMatrixType;

typedef enum {
	OrgBktYyc_MartixEE_Matrix_enumMatrixSwapType_COLUMS,
	OrgBktYyc_MartixEE_Matrix_enumMatrixSwapType_ROWS
}OrgBktYyc_MartixEE_Matrix_enumMatrixSwapType;

typedef enum {
	OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType_ADD, 
	OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType_MULTIPLY
}OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType;

typedef struct {
	void *p;
	OrgBktYyc_MartixEE_Matrix_enumMatrixType type;
	int rows;
	int colums;
}OrgBktYyc_MartixEE_Matrix_classMatrix;

OrgBktYyc_MartixEE_Matrix_classMatrix *OrgBktYyc_MartixEE_Matrix_classMatrix_Init(
	int rows, 
	int colums, 
	OrgBktYyc_MartixEE_Matrix_enumMatrixType type
	);
	
void OrgBktYyc_MartixEE_Matrix_classMatrix_Dispose(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj);
	
void OrgBktYyc_MartixEE_Matrix_classMatrix_Swap(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj,
	OrgBktYyc_MartixEE_Matrix_enumMatrixSwapType mode,
	int originLine,
	int targetLine);
	
void OrgBktYyc_MartixEE_Matrix_classMatrix_Operation(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj,
	OrgBktYyc_MartixEE_Matrix_enumMatrixSwapType affectMode,
	OrgBktYyc_MartixEE_Matrix_enumMatrixOperationType operationMode,
	int targetIndex,
	void *num);
	
void OrgBktYyc_MartixEE_Matrix_classMatrix_AddInto(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj,
	OrgBktYyc_MartixEE_Matrix_enumMatrixSwapType mode,
	int originLine,
	int targetLine,
	void *num);

void OrgBktYyc_MartixEE_Matrix_classMatrix_Print(
	OrgBktYyc_MartixEE_Matrix_classMatrix *obj);

#endif
