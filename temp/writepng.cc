#include <stdio.h>
#include <float.h>
#include <math.h>

#include "pngwriter.h"
#include "writepng.h"

double maxcolours = 65535;

double
maxval(double **array, int x, int y) {

    int i, j;
    double max = FLT_MIN;

    for(i = 0; i < x; i++)
	for(j=0; j < y; j++)
		max = array[i][j] > max ? array[i][j] : max;

    return(max);
}

void
writepng(char *filename, double **array, int x, int y) {
    
    int i, j;
    double scale = 1.0 / maxval(array, x, y);
    double c;
	printf("%d %d", x, y);

    // create the PNGwriter object
    pngwriter png1(x ,y , (int)maxcolours, filename);

    for(i = 0; i < x; i++) {
	for(j = 0; j < y; j++) {
	    c = (maxcolours * sqrt((float)array[i][j] * scale));
	    // plot expects pixel numbers from 1..xmax, 1..ymax!
	    png1.plot(i+1, j+1, (int) (3*c/5), (int) (3*c/5), (int) c);
	}
    }

    //  Remember to close this object - saves it to disk!!
    png1.close(); 
}
