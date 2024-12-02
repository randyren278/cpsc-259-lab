#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"

#define BUFSIZE 256 //capture matlab output 

int main(void) {
    /* Variables */
    Engine* ep = NULL; //pointer to matlatb engine 
    mxArray* matrixOneArray = NULL, * matrixTwoArray = NULL, * resultMatrix = NULL; //three pointers to hold data for matrix one and two as well as teh result 
    double matrixOne[3][3] = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };
    double matrixTwo[3][3] = { {9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0} };
    char buffer[BUFSIZE + 1]; //extra space for null charcater

    /* Start a MATLAB process */
    if (!(ep = engOpen(NULL))) {
        fprintf(stderr, "\nCan't start MATLAB engine\n");
        system("pause");
        return 1;
    }

    /* Create MATLAB variables for the data */
    matrixOneArray = mxCreateDoubleMatrix(3, 3, mxREAL);
    matrixTwoArray = mxCreateDoubleMatrix(3, 3, mxREAL);
    //memcpy((void*)mxGetPr(matrixOneArray), (void*)matrixOne, 9 * sizeof(double));
    //memcpy((void*)mxGetPr(matrixTwoArray), (void*)matrixTwo, 9 * sizeof(double));
    double* pr1 = mxGetPr(matrixOneArray); //mxGetPr is a poitner to the data of matrix in matlab 
    double* pr2 = mxGetPr(matrixTwoArray);
    for (int col = 0; col < 3; ++col) {
        for (int row = 0; row < 3; ++row) { //iterate over column then row 
            pr1[row + col * 3] = matrixOne[row][col];
            pr2[row + col * 3] = matrixTwo[row][col];
        }
    }
    // row+col*3 calculates the matlab index 
    // convertin from row major to column major 
    // memcpy doesnt work because it copies data as is so it doesnt account for how it is shifted 
    // transposed 

    //matrix one is 3x3 matrix 2 is 3x3 then copies from C code to matlab 

    /* Place the matrices into the MATLAB workspace */
    if (engPutVariable(ep, "matrixOne", matrixOneArray)) {
        fprintf(stderr, "\nCannot write matrixOne to MATLAB workspace\n");
        system("pause");
        exit(1); 
    }

    if (engPutVariable(ep, "matrixTwo", matrixTwoArray)) {
        fprintf(stderr, "\nCannot write matrixTwo to MATLAB workspace\n");
        system("pause");
        exit(1);
    }

    //places the arrays into matrixOne and Two

    /* Execute MATLAB command to calculate matrix product */
    if (engEvalString(ep, "resultMatrix = matrixOne * matrixTwo;")) {
        fprintf(stderr, "\nError calculating the product of matrices\n");
        system("pause");
        exit(1);
    }

    //multiplies matricies 

    /* Retrieve the product matrix from MATLAB workspace */
    if ((resultMatrix = engGetVariable(ep, "resultMatrix")) == NULL) {
        fprintf(stderr, "\nFailed to retrieve product matrix\n");
        system("pause");
        exit(1);
    }

    //stores the matrix in resultMatrix then retrieves this matrix from matlab 

    printf("This is matrixOne:\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%f ", matrixOne[i][j]);
        }
        printf("\n");
    }

    printf("\nThis is matrixTwo:\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%f ", matrixTwo[i][j]);
        }
        printf("\n");
    }

    //print matrix one and two before printing the result



    /* Print the product matrix */
    size_t rows = mxGetM(resultMatrix);
    size_t cols = mxGetN(resultMatrix);
    printf("The product of matrixOne and matrixTwo is:\n");
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            printf("%f ", *(mxGetPr(resultMatrix) + i + j * cols));
        }
        printf("\n");
    }

    //matlab  stores matricies columns fill first but c does row fill first we need to fix 
    // must write J+i so that it reads teh value sproperly 
    //print result matrix 

    /* Free allocated memory */
    mxDestroyArray(matrixOneArray);
    mxDestroyArray(matrixTwoArray);
    mxDestroyArray(resultMatrix);
    matrixOneArray = NULL;
    matrixTwoArray = NULL;
    resultMatrix = NULL;

    /* Close the MATLAB engine */
    if (engClose(ep)) {
        fprintf(stderr, "\nFailed to close MATLAB engine\n");
    }

    system("pause");
    return 0;
}
