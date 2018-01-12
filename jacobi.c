int jacobi(int N, double **array_in, double **array_out, int max_iter, double threshold, double **fmatrix) {
/* array_in and array_out are (N+2)*(N+2) */

    double	threshold2 = threshold * threshold;
    double 	d = threshold2 +1;
    int 	i, j, k=0;
    double 	**tmp;
    //double matSum;

    while (d > threshold2 &&  k < max_iter) {
	d = 0.0;
	//Orphaned parallel, is only entered if specified at runtime
	#pragma omp for collapse(2) private(i, j) //reduction(+:matSum)
    	for(i = 1; i <= N; i++){ 
	    for(j = 1; j <= N; j++){
	    	array_out[i][j] = 0.25*(array_in[i-1][j]+array_in[i+1][j]+array_in[i] 			[j-1]+array_in[i][j+1]+fmatrix[i][j]);
		d += (array_in[i][j] - array_out[i][j])*(array_in[i][j] - array_out[i] 			[j]);
		
		//matSum += array_out[i][j];
		}
	   }
	tmp=array_in;
	array_in = array_out;
	array_out = tmp;
	k++;

    }
    return k;
}
