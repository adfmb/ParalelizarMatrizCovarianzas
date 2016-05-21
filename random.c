#include <time.h>
#include <stdlib.h>
#include<stdio.h>

int main(){
srand(time(NULL));
int r = rand() % 1000; 
printf("%d\n",r/1000);

return 0;
}
