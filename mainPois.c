#include "jacobi.h"
#include "gauss_seidel.h"
#include "Mallocation.h"
#include "writepng.h"
#include <stdlib.h>

int main(int argc, char *argv[]){


///// PRELOAD AND INITIALIZATION /////
    int method = atoi(argv[1]);
    int N = atoi(argv[2]);
    int max_iter = atoi(argv[3]);
    double threshold = atof(argv[4]);
    double num_iter;

    // Allocate and initialize the NxN matrix for the room with Dirichlet conditions
    double ** matrixOut = malloc_matrix(N+2,N+2);
    init_data(N+2, N+2, matrixOut);
    for(int i=0; i<N+2; ++i){
    	matrixOut[i][N+1]=20.0;
    	matrixOut[N+1][i]=20.0;
    	matrixOut[0][i]=20.0;
	matrixOut[i][0]=0.0;
    }

    // Create the matrix for values of the function
    double ** fmatrix = malloc_matrix(N+2,N+2);
    init_f(N, fmatrix);


///// JACOBI AND GAUSS METHODS /////


    // If using Jacobi method not parallel
    if(method==0){
        // Allocate and initialize the in-matrix
    	double ** matrixIn = malloc_matrix(N+2,N+2);
    	init_data(N+2, N+2, matrixIn);
    	for(int i=0; i<N+2; ++i){
            matrixIn[i][N+1]=20.0;
            matrixIn[N+1][i]=20.0;
            matrixIn[0][i]=20.0;
	    matrixIn[i][0]=0.0;
    	}
        // Run the jacobi method
    	num_iter = jacobi(N, matrixIn, matrixOut, max_iter, threshold, fmatrix);
    }



    // If using Gauss-Seidel method not parallel
    else if(method==1){
    	num_iter = gauss_seidel(N, matrixOut, max_iter, threshold, fmatrix);
    }



    // If using Jacobi method in parallel
    else if(method==2){
        // Allocate and initialize the in-matrix
    	double ** matrixIn = malloc_matrix(N+2,N+2);
    	init_data(N+2, N+2, matrixIn);
    	for(int i=0; i<N+2; ++i){
            matrixIn[i][N+1]=20.0;
            matrixIn[N+1][i]=20.0;
            matrixIn[0][i]=20.0;
	    matrixIn[i][0]=0.0;
    	}
        // Run the jacobi method in parallel
	#pragma omp parallel
    	num_iter = jacobi(N, matrixIn, matrixOut, max_iter, threshold, fmatrix);
    }




/*
// PNG output
writepng("poisPNG", matrixOut, N+2, N+2);

//writing in text file
for(int i=0; i<N+2; i++){
    for(int j=0; j<N+2; j++){
	printf("%f \t", matrixOut[i][j]);}
    printf("\n");}
*/

printf("%d\t %f\n", N, num_iter);
return 0;
}
