#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"

#define BUFSIZE 256


int main(void) {


	Engine* ep = NULL; //pointer to matlab 
	mxArray* testArray = NULL, * result = NULL; //fundamental matlab data type
	double time[3][3] = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} }; //test 3x3 matrix array 

	/* Start a MATLAB process */
	if (!(ep = engOpen(NULL))) {
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		system("pause");
		return 1;
	}// open matlab engine

	/* Create a MATLAB variable for the data */
	testArray = mxCreateDoubleMatrix(3, 3, mxREAL);
	memcpy((void*)mxGetPr(testArray), (void*)time, 9 * sizeof(double));

	/* Place the test array into the MATLAB workspace */
	if (engPutVariable(ep, "testArray", testArray)) {
		fprintf(stderr, "\nCannot write test array to MATLAB workspace\n");
		system("pause");
		exit(1);
	}

	/* Execute a MATLAB command to calculate eigenvalues */
	if (engEvalString(ep, "testArrayEigen = eig(testArray)")) {
		fprintf(stderr, "\nError calculating eigenvalues\n");
		system("pause");
		exit(1);
	}

	/* Retrieve the calculated eigenvalues from MATLAB workspace */
	printf("\nRetrieving eigenvalues\n");
	if ((result = engGetVariable(ep, "testArrayEigen")) == NULL) {
		fprintf(stderr, "\nFailed to retrieve eigenvalue vector\n");
		system("pause");
		exit(1);
	}

	size_t sizeOfResult = mxGetNumberOfElements(result);
	printf("The eigenvalues are:\n");
	for (size_t i = 0; i < sizeOfResult; ++i) {
		printf("%f\n", *(mxGetPr(result) + i));
	}

	char buffer[BUFSIZE + 1]; // Buffer to hold MATLAB output, +1 for the null terminator
	if (engOutputBuffer(ep, buffer, BUFSIZE)) {
		fprintf(stderr, "\nCan't create buffer for MATLAB output\n");
		system("pause");
		return 1;
	}
	buffer[BUFSIZE] = '\0'; // Null-terminate the buffer to avoid reading invalid characters

	engEvalString(ep, "whos"); // 'whos' is a MATLAB command that displays all current variables
	printf("%s\n", buffer); // Print the captured output


	/* Free allocated memory */
	mxDestroyArray(testArray);
	mxDestroyArray(result);
	testArray = NULL;  // Set pointers to NULL for safety
	result = NULL;

	/* Close the MATLAB engine */
	if (engClose(ep)) {
		fprintf(stderr, "\nFailed to close MATLAB engine\n");
	}
	system("pause"); // Keeps the terminal open for you to review the output
	return 0;        // Standard return for successful completion

}