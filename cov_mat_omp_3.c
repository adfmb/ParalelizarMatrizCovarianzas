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


int main (int argc, char *argv[]){

    
    int m,p,q;
    p = 0;
    q=0;
    //int arreglo[2]=0;
    
    m = getchar();
    while( (m = getchar()) != EOF){
        if(m=='\n')
            p=p+1;
        
        
        if(m==',')
            q=q+1;
        
        
    }
    q=(q+p+1)/(p+1);
    p=p+1;
    printf("filas: %d\n",p);
    printf("columnas: %d\n",q);
    
    return 0;
           
}