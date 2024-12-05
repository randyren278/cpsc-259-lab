#define _CRT_SECURE_NO_WARNINGS // Suppress warnings about deprecated functions

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"

#define BUFSIZE 256


typedef struct {
    int node;
    double rank;
} Page;
// page structure for fiinal printing page thing 
int compare(const void* a, const void* b) {
    const Page* pageA = (const Page*)a;
    const Page* pageB = (const Page*)b;
    double diff = pageB->rank - pageA->rank;
    if (diff > 0) return 1;
    else if (diff < 0) return -1;
    else return 0;
}// for q sort comapres rank if return 1 B before A return -1 whne A come before B 0 if they equal 



int main(void) {
    Engine* ep = NULL;
    mxArray* connectivityArray = NULL, * pageRankArray = NULL;
    char buffer[BUFSIZE + 1];
    // instantiating matlab engine 

   //reading webtxt
    FILE* file = fopen("web.txt", "r");
    if (!file) {
        fprintf(stderr, "Error opening web.txt\n");
        return 1;
    }

    //determine size of matrix 
    size_t dimension = 0;
    char line[BUFSIZE];
    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) > 1) { // ignore empty lines 
            dimension++;
        }
    }
    rewind(file); // reset pointer to beginning 
    // reference this later ***** https://www.geeksforgeeks.org/g-fact-82/ 

    int** connectivityMatrix = (int**)malloc(dimension * sizeof(int*));
    for (size_t i = 0; i < dimension; i++) {
        connectivityMatrix[i] = (int*)malloc(dimension * sizeof(int));
    }

    //memmory allocatino for the connectivity amtrix 

    // connectivity matrix filled using web.txt
    size_t row = 0;
    while (fgets(line, sizeof(line), file) && row < dimension) {
        char* token = strtok(line, " \t\n");
        size_t col = 0;
        while (token != NULL && col < dimension) {
            connectivityMatrix[row][col] = atoi(token);
            token = strtok(NULL, " \t\n");
            col++;
        }
        row++;
    }
    fclose(file);
    //https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/ 
    // loops through tokienization and fills matrix 


    if (!(ep = engOpen(NULL))) {
        fprintf(stderr, "\nCan't start MATLAB engine\n");
        return 1;
    }

    connectivityArray = mxCreateDoubleMatrix((mwSize)dimension, (mwSize)dimension, mxREAL);
    double* pr = mxGetPr(connectivityArray);
    for (size_t col = 0; col < dimension; ++col) {
        for (size_t row = 0; row < dimension; ++row) {
            pr[row + col * dimension] = (double)connectivityMatrix[row][col];
        }
    }
    // prepare data for matlab fixing the column major order 

    //connectivity matrix to matlab
    if (engPutVariable(ep, "ConnectivityMatrix", connectivityArray)) {
        fprintf(stderr, "\nCannot write connectivity matrix to MATLAB workspace\n");
        return 1;
    }

    //run pagerank.m from last time 
    if (engEvalString(ep,
        "dimension = size(ConnectivityMatrix, 1);\n"
        "columnsums = sum(ConnectivityMatrix, 1);\n"
        "p = 0.85;\n"
        "zerocolumns = find(columnsums ~= 0);\n"
        "D = sparse(zerocolumns, zerocolumns, 1 ./ columnsums(zerocolumns), dimension, dimension);\n"
        "StochasticMatrix = ConnectivityMatrix * D;\n"
        "[row, column] = find(columnsums == 0);\n"
        "StochasticMatrix(:, column) = 1 / dimension;\n"
        "Q = ones(dimension, dimension);\n"
        "TransitionMatrix = p * StochasticMatrix + (1 - p) * (Q / dimension);\n"
        "PageRank = ones(dimension, 1);\n"
        "for i = 1:100\n"
        "    PageRank = TransitionMatrix * PageRank;\n"
        "end\n"
        "PageRank = PageRank / sum(PageRank);\n"
    )) {
        fprintf(stderr, "\nError calculating PageRank in MATLAB\n");
        return 1;
    }

    //get the pagerank values from matlatb back to vs 
    if ((pageRankArray = engGetVariable(ep, "PageRank")) == NULL) {
        fprintf(stderr, "\nFailed to retrieve PageRank vector\n");
        return 1;
    }

   // process results 
    double* pageRankValues = mxGetPr(pageRankArray);
    mwSize numPages = mxGetNumberOfElements(pageRankArray);

    // create the array for ranked list 
    Page* pages = (Page*)malloc(numPages * sizeof(Page));
    for (mwSize i = 0; i < numPages; i++) {
        pages[i].node = (int)(i + 1); // Node numbers start from 1
        pages[i].rank = pageRankValues[i];
    }

    //sorts pages descending order 
    qsort(pages, numPages, sizeof(Page), compare);
    
    // https://www.geeksforgeeks.org/comparator-function-of-qsort-in-c/ 

    //print matrix 
    printf("NODE  RANK\n");
    printf("---   ----\n");
    for (mwSize i = 0; i < numPages; i++) {
        printf("%d     %.4f\n", pages[i].node, pages[i].rank);
    }

   //free all variables
    for (size_t i = 0; i < dimension; i++) {
        free(connectivityMatrix[i]);
    }
    free(connectivityMatrix);
    free(pages);

    mxDestroyArray(connectivityArray);
    mxDestroyArray(pageRankArray);

    if (engClose(ep)) {
        fprintf(stderr, "\nFailed to close MATLAB engine\n");
    }

    printf("\nPress any key to continue . . .\n");
    getchar();

    return 0;
}
