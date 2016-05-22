// MATRIX FROM A CSV FILE TO ARRAYS IN C

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAYSIZE(x)  (sizeof(x)/sizeof(*(x)))

int main(int argc, char *argv[])
{
    
    const char filename[] = "fuente.csv";
    const char filename2[] = "file2.csv";
    
    int array2[2][1];
    size_t i2, j2, k2;
    char buffer[BUFSIZ], *ptr;
    int p,q;
    
    FILE *file2 = fopen(filename2, "r");
    if ( file2 )
    {
        
        
        /*
         * Read each line from the file.
         */
        for ( i2 = 0; fgets(buffer, sizeof buffer, file2); ++i2 )
        {
            /*
             * Parse the comma-separated values from each line into 'array'.
             */
            for ( j2 = 0, ptr = buffer; j2 < ARRAYSIZE(*array2); ++j2, ++ptr )
            {
                array2[i2][j2] = (int)strtol(ptr, &ptr, 10);
            }
        }
        fclose(file2);
        /*
         * Print the data in 'array'.
         */
        for ( j2 = 0; j2 < i2; ++j2 )
        {
            //printf("array2[%lu]: ", j);
            for ( k2 = 0; k2 < ARRAYSIZE(*array2); ++k2 )
            {
                printf("%4d ", array2[j2][k2]);
            }
            putchar('\n');
        }
        //printf("suma de (0,0) y (1,0): %4d\n %4d\n", array2[0][0], array2[1][0]);
    }
    else /* fopen() returned NULL */
    {
        perror(filename2);
    }
    
//return 0;
//}

   
    /*
     * Open the file.
     */
    
    p=array2[0][0];
    q=array2[1][0];
   // printf("p: %d\n: ",p);
   // printf("q: %d\n: ",q);
    
    double array[p][q];

    FILE *file = fopen(filename, "r");
    if ( file )
    {
        
        //size_t i, j, k;
        //char buffer[BUFSIZ], *ptr;
        /*
         * Read each line from the file.
         */
       for ( i2 = 0; fgets(buffer, sizeof buffer, file); ++i2 )
        {
            /*
             * Parse the comma-separated values from each line into 'array'.
             */
           for ( j2 = 0, ptr = buffer; j2 < ARRAYSIZE(*array); ++j2, ++ptr )
            {
                array[i2][j2] = (double)strtol(ptr, &ptr, 10);
            }
        }
        fclose(file);
        /*
         * Print the data in 'array'.
         */
       for ( j2 = 0; j2 < i2; ++j2 )
        {
            printf("array[%lu]: ", j2);
            for ( k2 = 0; k2 < ARRAYSIZE(*array); ++k2 )
            {
                printf("%4f ", array[j2][k2]);
            }
            putchar('\n');
        }
        printf("suma de (0,0) y (1,1): %4f\n", array[0][0]+ array[1][1]);
    }
    else /* fopen() returned NULL */
   {
        perror(filename);
    }
    
    int	tid, nthreads, i, j, z, chunk;
    
    long num_ren, num_col;
    
    long thread_count;
    thread_count = strtol(argv[1],NULL,10);
    
    double	Matriz[p][q],
    M_multiXY[q][q],
    M_covarianzas[q][q];
    
     chunk = q/thread_count;

    
    
#pragma omp parallel shared(array,p,q,Matriz,M_multiXY,M_covarianzas,nthreads,chunk,num_ren,num_col) private(tid,i,j,z) num_threads(thread_count)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Starting matrix multiple example with %d threads\n",nthreads);
            printf("Initializing matrices...\n");
        }
        
#pragma omp for schedule (static, chunk)
        for (i=0; i<p; i++){
            for (j=0; j<q; j++){
                Matriz[i][j]= array[i][j];
            }
        }
        
        num_ren = sizeof(Matriz)/sizeof(Matriz[0]);
        num_col = sizeof(Matriz[0])/sizeof(Matriz[0][0]);
        
        
        printf("******************************************************\n");
        
        printf("Número de renglones en Matriz Fuente: %lu\n", num_ren);
        printf("Número de columnas en Matriz Fuente: %lu\n", num_col);
        
        
        printf("******************************************************\n");
        
        printf("Imprimiendo Matriz array \n");
        
        for (i=0; i<num_ren; i++){
            
            for(j=0; j<num_col; j++)
                printf("%3.5f   ", array[i][j]);
            printf("\n");
            
        }
        
  
        double vector_sumas[num_col];
        double promedios[num_col];

        /*** Do matrix multiply sharing iterations on outer loop ***/
        /*** Display who does which iterations for demonstration purposes ***/
        printf("Thread %d empezando la suma por campo de la Matriz...\n",tid);
#pragma omp for schedule (static, chunk)
        for(j=0;j<num_col;j++){
            
            printf("Thread=%d hizo la columna=%d\n",tid,j);
            vector_sumas[j]=0;
            for(i=0;i<num_ren;i++){
                
                vector_sumas[j]+=Matriz[i][j];
                
            }
            
        }
        
        printf("Thread %d empezando los valores esperados por campo de la Matriz...\n",tid);
#pragma omp for schedule (static, chunk)
        for(j=0;j<num_col;j++){
            
            printf("Thread=%d hizo la columna=%d\n",tid,j);
            promedios[j]=vector_sumas[j]/num_ren ;// Son las E[x];
            
        }
        
        //float M_covarianzas[num_col][num_col];
        float restasX[num_ren];
        float restasY[num_ren];
        //float M_multiXY[num_col][num_col];
        
        
        printf("Thread %d empezando la matriz de los productos de desviaciones...\n",tid);
#pragma omp for schedule (static, chunk)
        //printf("Thread=%d hizo la columna (J) =%d\n",tid,j);
        for(j=0;j<num_col;j++){
            
            printf("Thread=%d hizo la columna (Z) =%d\n",tid,j);
            for(z=0;z<num_col;z++){
                
                
                M_multiXY[j][z]=0;
                
                for(i=0;i<num_ren;i++){
                    
                    restasX[i]=Matriz[i][j]-promedios[j];
                    restasY[i]=Matriz[i][z]-promedios[z];
                    M_multiXY[j][z]+=restasX[i]*restasY[i];
                    
                }
                
            }
            
        }
        
        
        printf("Thread %d empezando la matriz de las covarianzas...\n",tid);
#pragma omp for schedule (static, chunk)
        for(i=0;i<num_col;i++){
            printf("Thread=%d hizo la columna=%d\n",tid,i);
            for(j=0;j<num_col;j++){
                
                
                M_covarianzas[i][j]=M_multiXY[i][j]/num_ren;
                
            }
            
        }
        
        
    }   /*** End of parallel region ***/
    
    /*** Print results ***/


    
    
    printf("******************************************************\n");
    
    printf("Imprimiendo Matriz Fuente \n");
    
    for (i=0; i<num_ren; i++){
        
        for(j=0; j<num_col; j++)
            printf("%3.5f   ", Matriz[i][j]);
        printf("\n");
        
    }
    
    printf("******************************************************\n");
    
    printf("Imprimiendo Matriz Productos de desviaciones \n");
    
    for (i=0; i<num_col; i++){
        
        for(j=0; j<num_col; j++)
            printf("%3.5f   ", M_multiXY[i][j]);
        printf("\n");
        
    }

    
    printf("******************************************************\n");
    
    printf("Imprimiendo Matriz de Covarianzas \n");
    
    for (i=0; i<num_col; i++){
        
        for(j=0; j<num_col; j++)
            printf("%3.5f   ", M_covarianzas[i][j]);
        printf("\n");
        
    }
    
    printf("******************************************************\n");
    printf ("Done.\n");
    return 0;
    
}
