#include <stdio.h>
#include <stdlib.h>

//  The benchmark function. IAXPY takes two integer arrays and a scalar as 
//  input. It adds the two arrays, element by element, storing the results in 
//  Result. The first term is multiplied by the scalar, called A. Hence, why 
//  it is called AXPY: scalar A times X plus Y. The I in the name indicates it 
//  is an integer.

void dgemm_scalar(int N, double *a, double *b, double *c) {
    for (int i=0;  i<N;  i++)
        for (int j=0;  j<N;  j++) {
            double cij = 0;
            for (int k=0;  k<N;  k++)
                //     a[i][k]  * b[k][j]
                cij += a[i+k*N] * b[k+j*N];
            // c[i][j]
            c[i+j*N] = cij;
        }
}


//  The benchmark
int main( void ) {
  const int N = 1024; // The benchmark runs on a fixed size of work
  printf( "Running DGEMM operation of size %d x 1\n", N );

  //  Create three N x 1 matrixes on the heap using malloc. There are 
  //  generally two reasons why we do not want to do this statically i.e. int 
  //  X[N]. One, with the benchmark program we're making we may exceed the 
  //  allowable size of a static array (yep, this is possible given we are 
  //  taxing the system). Two, if you wanted to, you could dynamically adjust 
  //  the workload via the command line (though this is not how it is currently
  //  set up).
  double *X = (double *) malloc( N*N * sizeof(double) );      // First vector
  double *Y = (double *) malloc( N*N * sizeof(double) );		
  double *Z = (double *) malloc( N*N * sizeof(double) );


   // Carry out the operation
   dgemm_scalar( N, X, Y, Z );

   // Free up the memory
   free( X );
   free( Y );
   free( Z );

   return 0;
}
