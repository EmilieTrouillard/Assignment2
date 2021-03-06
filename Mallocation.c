
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

double **malloc_matrix(int m, int n){
    int i;

    if (m <= 0 || n <= 0)
	return NULL;

    double **A = malloc(m * sizeof(double *));
    if (A == NULL)
	return NULL;

    A[0] = malloc(m*n*sizeof(double));
    if (A[0] == NULL) {
	free(A);
	return NULL;
    }
    for (i = 1; i < m; i++)
	A[i] = A[0] + i * n;

    return A;
}

void 
init_data (int m, int n, double **A) {

   int i, j;

   for( i = 0; i < m; i++)
       for( j = 0; j < n; j++) {
	    A[i][j] = 0.0;	    
       }

}

void init_f (int N, double **A){
    int 	i, j;
    double 	i_inf=0.5*(N+1), i_sup=2*(N+1)/3, j_inf=(N+1)/6, j_sup=(N+1)/3;
    double 	delta = 2.0/(N+1);
    double 	fdelta2 = 200*delta*delta;
    for(i = 1; i <= N; i++){
	for(j = 1; j <= N; j++){ 
	     if(i>=i_inf && i <= i_sup && j>=j_inf && j<=j_sup){
	    	A[i][j] = fdelta2;
		     }
		else{
		A[i][j] = 0.0;
		     }
	}
    }
}
