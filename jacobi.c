double jacobi(int para, int N, double **array_in, double **array_out, int max_iter, double threshold, double **fmatrix) {

/* array_in and array_out are (N+2)*(N+2) */

    double	threshold2 = threshold * threshold;
    double 	d = threshold2 +1;
    int 	i, j, k=0;
    double 	**tmp;


//// SEQUENTIAL
    if(para==0){
    while (d > threshold2 && k < max_iter) {
	d = 0.0;
    	for(i = 1; i <= N; i++){ 
	    for(j = 1; j <= N; j++){
	    	array_out[i][j] = 0.25*(array_in[i-1][j]+array_in[i+1][j]+array_in[i] 			[j-1]+array_in[i][j+1]+fmatrix[i][j]);
		d += (array_in[i][j] - array_out[i][j])*(array_in[i][j] - array_out[i] 			[j]);
		}
	   }
	tmp=array_in;
	array_in = array_out;
	array_out = tmp;
	k++;

    }
}


//// PARALLEL REGION INSIDE WHILE LOOPS
    if(para==2){
    while (d > threshold2 &&  k < max_iter) {
	d = 0.0;
	#pragma omp parallel for default(none) private(i,j) shared(k,array_out,array_in,threshold2,max_iter,N,fmatrix,tmp) reduction(+:d)
    	for(i = 1; i <= N; i++){ 
	    for(j = 1; j <= N; j++){
	    	array_out[i][j] = 0.25*(array_in[i-1][j]+array_in[i+1][j]+array_in[i] 			[j-1]+array_in[i][j+1]+fmatrix[i][j]);
		d += (array_in[i][j] - array_out[i][j])*(array_in[i][j] - array_out[i] 			[j]);
		}
	   }
	tmp=array_in;
	array_in = array_out;
	array_out = tmp;
	k++;

    }
}



//// PARALLEL REGION OUTSIDE WHILE LOOPS
    else if(para==3){
    //Begin parallel region
    #pragma omp parallel default(none) private(i,j) shared(d,k,array_out,array_in,threshold2,max_iter,N,fmatrix,tmp)
    {
    while (d > threshold2 &&  k < max_iter) {
	#pragma omp barrier
        #pragma omp single
	d = 0.0;
	//Parallel for
	#pragma omp for reduction(+:d) 
    	for(i = 1; i <= N; i++){
	    for(j = 1; j <= N; j++){
	    	array_out[i][j] = 0.25*(array_in[i-1][j]+array_in[i+1][j]+array_in[i] 			[j-1]+array_in[i][j+1]+fmatrix[i][j]);
		d += (array_in[i][j] - array_out[i][j])*(array_in[i][j] - array_out[i][j]);
		}
	   }
	#pragma omp single
	{
	tmp=array_in;
	array_in = array_out;
	array_out = tmp;
	k++;
	}
    }
  }
}

    return k;
}
