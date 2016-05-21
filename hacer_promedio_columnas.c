#include<stdio.h>
#include<stdlib.h>


int Matriz[4][5] = {
  /*
  {-1,1,2,1,2},
  {-1,0,1,-1,1},
  {1,0,0,1,-3},
  {-1,1,1,3,-4}
  */
  
  {-1,1,2,1,0},
  {-1,0,1,-1,9},
  {1,0,0,1,8},
  {-1,1,1,3,7}
  
};

int main(){
  int filas, columnas;
  int i,j,z;
  long num_ren, num_col;
  
  num_ren = sizeof(Matriz)/sizeof(Matriz[0]); 
  num_col = sizeof(Matriz[0])/sizeof(Matriz[0][0]); 
  
  printf("Número de renglones: %lu\n", num_ren);
  printf("Número de columnas: %lu\n", num_col);
  
  printf("\n");
  printf("\n");
  
/*
    printf("Imprimiendo Matriz Fuente \n");
  
  for (int i=0; i<num_ren; i++){
    
    for(int j=0; j<num_col; j++)
      printf("%d     ", Matriz[i][j]);
    printf("\n");
    
  }
  
  printf("\n");
  printf("\n"); 
*/

  int vector_sumas[num_col];
  float promedios[num_col];
  
  for(j=0;j<num_col;j++){
    
    vector_sumas[j]=0;
    
    for(i=0;i<num_ren;i++){ 
      
      vector_sumas[j]+=Matriz[i][j];
      
    }
    
  }
  
/*
filas=4;
columnas=5;



int m;



printf("el primer valor de M es: %d\n",Matriz[0][0]);
*/





/*
for (int i=0; i<num_ren; i++){
  
  for(int j=0; j<num_col; j++)
    
    Matriz[i][j]=(i-j)+ 2*i-(j-3)+10;
  
}
*/

for(j=0;j<num_col;j++){
  
  promedios[j]=vector_sumas[j]/num_ren ;// Son las E[x];
  
}

float M_covarianzas[num_col][num_col];
float restasX[num_ren];
float restasY[num_ren];
float M_multiXY[num_col][num_col];

for(j=0;j<num_col;j++){
  
  //restasX[j]=0;
  
  
  for(z=0;z<num_col;z++){
  
    //restasY[z]=0;
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

for (int i=0; i<num_col; i++){
  
  for(int j=0; j<num_col; j++)
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

/*
printf("Número de renglones: %d\n", num_ren);
printf("Número de columnas: %d\n", num_col);

printf("filas: %d\n",filas);
printf("columnas: %d\n", columnas);
*/

}
