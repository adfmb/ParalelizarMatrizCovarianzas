#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
//#include <support.h>

#define NRA 1000                   /* number of rows in matrix A */
#define NCA 1000                  /* number of columns in matrix A */
#define NCB 100                     /* number of columns in matrix B */

int main (int argc, char *argv[]) 
{
int	tid, nthreads, i, j, k, chunk;
double	a[NRA][NCA],                /* matrix A to be multiplied */
        b[NCA][NCB],                /* matrix B to be multiplied */
        c[NRA][NCB];                /* result matrix C */

chunk = 100;                         /* set loop iteration chunk size */
if (argc > 1)
omp_set_num_threads(atoi(argv[1]));

/*** Spawn a parallel region explicitly scoping all variables ***/
#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Starting matrix multiple example with %d threads\n",nthreads);
    printf("Initializing matrices...\n");
    }
  /*** Initialize matrices ***/
  #pragma omp for schedule (static, chunk) 
  for (i=0; i<NRA; i++){
   #ifdef DEBUG
   printf("Thread=%d did A[] row=%d\n",tid,i);
   #endif
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;
      }
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NCA; i++){
   #ifdef DEBUG
   printf("Thread=%d did B[] coloumn=%d\n",tid,i);
   #endif
    for (j=0; j<NCB; j++)
      b[i][j]= i*j;
      }
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)
     for (j=0; j<NCB; j++)
      c[i][j]= 0;
}/*** End of parallel region that does the initialyzation***/ 
startTime();
#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
  {
  /*** Do matrix multiply sharing iterations on outer loop ***/
  /*** Display who does which iterations for demonstration purposes ***/
#ifdef DEBUG_MM
  tid = omp_get_thread_num();
  printf("Thread %d starting matrix multiply...\n",tid);
#endif
  
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)    
    {
	#ifdef DEBUG_MM
    printf("Thread=%d did row=%d\n",tid,i);
	#endif
    for(j=0; j<NCB; j++)       
      for (k=0; k<NCA; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
  }   /*** End of parallel region that does the multiplication ***/
stopTime();
elapsedTime();  
#ifdef DEBUG
printf("******************************************************\n");
printf("Result Matrix:\n");
for (i=0; i<NRA; i++)
  {
  for (j=0; j<NCB; j++) 
    printf("%6.2f   ", c[i][j]);
  printf("\n"); 
  }
printf("******************************************************\n");
#endif
printf ("Done.\n");
return 0;
}
