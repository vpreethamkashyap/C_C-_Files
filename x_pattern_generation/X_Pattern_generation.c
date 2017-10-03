#include <stdio.h>
#include <malloc.h>


char* string_operations(unsigned int n){
    
    char* block = (char*)malloc(n*(n-1));
    
    int i,j,k=0;
    
    /*for(i=0; i<=(n-1); i++)*/
    for(i=(n-1); i>=0; i--){
        for(j=0; j<=i; j++){
            block[k++] = 'x';
        }
        block[k++] = ' '; /*use /n for next line appearance*/
    }
    return block;
}

int main()
{
    char* string = string_operations(5);
    puts(string);
    free(string);
}
