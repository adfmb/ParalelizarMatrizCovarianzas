#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char buffer[1024] ;
    char *record,*line;
    int i=0,j=0;
    char *end;
    long mat1[5][4];
    
    FILE *fstream = fopen("matriz_1.txt","r");
    if(fstream == NULL)
    {
        printf("\n file opening failed ");
        return -1 ;
    }
    
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
    {
        record = strtok(line,",");
        while(record != NULL)
        {
            //printf("%s",record) ;    //here you can put the record into the array as per your requirement.
            mat1[i][j++] = strtoul(record,&end,10) ;
            record = strtok(NULL,",");
        }
        ++i ;
        
    }
    <
    return 0 ;
}