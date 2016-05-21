#include<stdio.h>
#include<stdlib.h>
#include <omp.h>

#define NRA 200                 /* number of rows in matrix A */
#define NCA 200

/*

 int Matriz[4][5] = {

  
  {-1,1,2,1,0},
  {-1,0,1,-1,9},
  {1,0,0,1,8},
  {-1,1,1,3,7} }; */

int filas(void){

    int m,p,q;
    p = 0;
    q=0;
    //int arreglo[2]=0;
    
    m = getchar();
    while( (m = getchar()) != EOF){
        if(m=='\n')
            p=p+1;
        
    }
    q=(q+p+1)/(p+1);
    
    //printf("\n Se contaron %i lineas \n",p+1);
    //printf("\n Se contaron %d Columnas \n",q);
    //arreglo[0]=p;
    //arreglo[1]=q;
    
    return(p+1);
}

int col(void){
    
    int m,p,q;
    p = 0;
    q=0;
    //int arreglo[2]=0;
    
    m = getchar();
    while( (m = getchar()) != EOF){
        
        if(m==',')
            q=q+1;
        
    }
    q=(q+p+1)/(p+1);
    
    //printf("\n Se contaron %i lineas \n",p+1);
    //printf("\n Se contaron %d Columnas \n",q);
    //arreglo[0]=p;
    //arreglo[1]=q;
    
    return(q);
}


int main (int argc, char *argv[]){

    
  int	tid, nthreads, i, j, z, chunk;

  long num_ren, num_col;
  
  long thread_count;
  thread_count = strtol(argv[1],NULL,10);
  
  double	Matriz[NRA][NCA],
        M_multiXY[NCA][NCA],
        M_covarianzas[NCA][NCA];
  
  chunk = 5; 
  
  
  
  #pragma omp parallel shared(Matriz,M_multiXY,M_covarianzas,nthreads,chunk,num_ren,num_col) private(tid,i,j,z) num_threads(thread_count)
  {
    tid = omp_get_thread_num();
    if (tid == 0)
    {
      nthreads = omp_get_num_threads();
      printf("Starting matrix multiple example with %d threads\n",nthreads);
      printf("Initializing matrices...\n");
    }
    
  #pragma omp for schedule (static, chunk) 
    for (i=0; i<NRA; i++){
      for (j=0; j<NCA; j++){
        Matriz[i][j]= i*j+1-(j-i)*(j*j-i);
      }
    }
    
    num_ren = sizeof(Matriz)/sizeof(Matriz[0]); 
    num_col = sizeof(Matriz[0])/sizeof(Matriz[0][0]);
  
  
  
  int vector_sumas[num_col];
  float promedios[num_col];

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


/*
void Hello(){
  //int filas, columnas;
  int i,j,z;
  long num_ren, num_col;
  
  num_ren = sizeof(Matriz)/sizeof(Matriz[0]); 
  num_col = sizeof(Matriz[0])/sizeof(Matriz[0][0]); 
  
  printf("Número de renglones: %lu\n", num_ren);
  printf("Número de columnas: %lu\n", num_col);
  
  printf("\n");
  printf("\n");

  int vector_sumas[num_col];
  float promedios[num_col];
  
  for(j=0;j<num_col;j++){
    
    vector_sumas[j]=0;
    
    for(i=0;i<num_ren;i++){ 
      
      vector_sumas[j]+=Matriz[i][j];
      
    }
    
  }


for(j=0;j<num_col;j++){
  
  promedios[j]=vector_sumas[j]/num_ren ;// Son las E[x];
  
}

float M_covarianzas[num_col][num_col];
float restasX[num_ren];
float restasY[num_ren];
float M_multiXY[num_col][num_col];

for(j=0;j<num_col;j++){
  
  
  for(z=0;z<num_col;z++){
  

    M_multiXY[j][z]=0;
    
    for(i=0;i<num_ren;i++){
   
      restasX[i]=Matriz[i][j]-promedios[j];
      restasY[i]=Matriz[i][z]-promedios[z];  
      M_multiXY[j][z]+=restasX[i]*restasY[i];
      
    }
    
  }
  
}

for(i=0;i<num_col;i++){
  
  for(j=0;j<num_col;j++){
    
    M_covarianzas[i][j]=M_multiXY[i][j]/num_ren;
    
  }
  
}



printf("Imprimiendo Matriz Fuente \n");

for (i=0; i<num_ren; i++){
  
  for(j=0; j<num_col; j++)
    printf("%d     ", Matriz[i][j]);
  printf("\n");
  
}

printf("\n");
printf("\n");

printf("Imprimiendo Matriz de Suma de Resta de productos \n");

for (i=0; i<num_col; i++){
  
  for(j=0; j<num_col; j++)
    printf("%f     ", M_multiXY[i][j]);
  printf("\n");
  
}

printf("\n");
printf("\n");

printf("Imprimiendo Matriz de Covarianzas \n");

for (i=0; i<num_col; i++){
  
  for(j=0; j<num_col; j++)
    printf("%f     ", M_covarianzas[i][j]);
  printf("\n");

}

}
*/
