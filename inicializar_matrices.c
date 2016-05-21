#include<stdio.h>
#include<stdlib.h>


int Matriz[4][5] = {
  /*
  {-1,1,2,1,0},
  {-1,0,1,-1,9},
  {1,0,0,1,8},
  {-1,1,1,3,7}
  */
  
  {-1,1,2,1,2},
  {-1,0,1,-1,1},
  {1,0,0,1,-3},
  {-1,1,1,3,-4}
  
};

int main(){
  int filas, columnas;
  int i,j,z;
  long num_ren, num_col;
  
  num_ren = sizeof(Matriz)/sizeof(Matriz[0]); 
  num_col = sizeof(Matriz[0])/sizeof(Matriz[0][0]); 
  
  printf("Renglones: %lu\n ",num_ren);
  printf("Columnas: %lu\n ",num_col);
  
  printf("\n");
  printf("\n");
  
  printf("Imprimiendo Matriz Fuente \n");
  
  for (int i=0; i<num_ren; i++){
    
    for(int j=0; j<num_col; j++)
      printf("%d     ", Matriz[i][j]);
    printf("\n");
    
  }
  
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
  
  
  
}