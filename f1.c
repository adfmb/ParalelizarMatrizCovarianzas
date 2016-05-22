#include<stdio.h>
int main (void){

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
    q=(q+p+1)/(p+1)+1;
    p=p+1-1;
    printf("%d\n %d\n",p, q);
    
return 0;
    
}
