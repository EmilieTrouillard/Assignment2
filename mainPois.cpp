#include "jacobi.h"
#include "gauss_seidel.h"
#include "Mallocation.h"
#include "write_png.h"

int main(char method, int N, int max_iter, int threshold){

// Allocate the NxN matrix for the room with Dirichlet conditions
double ** matrixOut = malloc_matrix(N+2,N+2);
for(int i=0; i<N+2; ++i){
    matrixOut[i][N+2]=20;
    matrixOut[N+2][i]=20;
    matrixOut[0][i]=0;
}

// Either using Jacobi method
if(method=='j'){
        // Allocate the in-matrix
    double ** matrixIn = malloc_matrix(N+2,N+2);
    for(int i=0; i<N+2; ++i){
            matrixIn[i][N+2]=20;
            matrixIn[N+2][i]=20;
            matrixIn[0][i]=0;
    }
        // Run the jacobi method
    jacobi(N, matrixIn, matrixOut, max_iter, threshold);
}

// Or using Gauss-Seidel method
else if(method=='g'){
    gauss_seidel(N, matrixOut, max_iter, threshold);
}

// PNG output
write_png("poisPNG", matrixOut, N+2, N+2);


return 0;
}
