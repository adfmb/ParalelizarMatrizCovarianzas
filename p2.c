// MATRIX FROM A CSV FILE TO ARRAYS IN C

#include <stdio.h>
#include <stdlib.h>

#define ARRAYSIZE(x)  (sizeof(x)/sizeof(*(x)))

int main(void)
{
    const char filename[] = "file.csv";
    /*
     * Open the file.
     */
    FILE *file = fopen(filename, "r");
    if ( file )
    {
        int array[10][10];
        size_t i, j, k;
        char buffer[BUFSIZ], *ptr;
        /*
         * Read each line from the file.
         */
        for ( i = 0; fgets(buffer, sizeof buffer, file); ++i )
        {
            /*
             * Parse the comma-separated values from each line into 'array'.
             */
            for ( j = 0, ptr = buffer; j < ARRAYSIZE(*array); ++j, ++ptr )
            {
                array[i][j] = (int)strtol(ptr, &ptr, 10);
            }
        }
        fclose(file);
        /*
         * Print the data in 'array'.
         */
        for ( j = 0; j < i; ++j )
        {
            printf("array[%lu]: ", j);
            for ( k = 0; k < ARRAYSIZE(*array); ++k )
            {
                printf("%4d ", array[j][k]);
            }
            putchar('\n');
        }
        printf("suma de (0,0) y (1,1): %4d\n", array[0][0]+ array[1][1]);
    }
    else /* fopen() returned NULL */
    {
        perror(filename);
    }
    return 0;
}


/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
         tok && *tok;
         tok = strtok(NULL, ",\n"))
    {
        if (!--num)
        return tok;
    }
    return NULL;
}

int main()
{
    FILE* stream = fopen("file.csv", "r");
    
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        printf("Column would be %s\n", getfield(tmp, 12));
        // NOTE strtok clobbers tmp
        free(tmp);
    }
}*/

