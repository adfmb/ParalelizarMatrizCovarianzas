#include<stdio.h>

//int arreglo1[10];
int filas, columnas;
int i,j;
int num_ren, num_col;

int main(){

filas=4;
columnas=5;

int Matriz[filas][columnas];
int m;
Matriz[0][0]=2;
Matriz[1][]=3;

printf("el primer valor de M es: %d\n",Matriz[0][0]);
printf("Valor de fila=1, columna=2: %d\n",Matriz[1][2]);

num_ren = sizeof(Matriz)/sizeof(Matriz[0]); 
num_col = sizeof(Matriz[0])/sizeof(Matriz[0][0]); 

printf("Número de renglones: %d\n", num_ren);
printf("Número de columnas: %d\n", num_col);

printf("filas: %d\n",filas);
printf("columnas: %d\n", columnas);

}
