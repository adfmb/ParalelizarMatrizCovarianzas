#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int  i=0,totalNums,totalNum,j=0;
    size_t count;
    int numbers[100][100];
    char *line = malloc(100);
    
    FILE *file;  /* declare a FILE pointer  */
    file = fopen("g.txt", "r");  /* open a text file for reading */
    
    while(getline(&line, &count, file)!=-1) {
        for (; count > 0; count--, j++)
            sscanf(line, "%d", &numbers[i][j]);
        i++;
    }
    
    totalNums = i;
    totalNum = j;
    for (i=0 ; i<totalNums ; i++) {
        for (j=0 ; j<totalNum ; j++) {
            printf("\n%d",  numbers[i][j]);
        }
    }
    fclose(file);
    return 0;
}