#ifndef MALLOCATION_H_INCLUDED
#define MALLOCATION_H_INCLUDED

double **malloc_matrix(int m, int n){
    double **A = new double *[m];

    A[0] = new double[n*m];

    int i;

    for(int i=0; i<m; ++i){
        A[i] = A[0] + i * n;
    }

    return A;
}

#endif // MALLOCATION_H_INCLUDED
