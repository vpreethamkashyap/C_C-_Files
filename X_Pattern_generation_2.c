#include <stdio.h>
#include <malloc.h>


char* string_operations(unsigned int n){
    
    char* block = (char*)malloc(n*n);
    
    int i,j,k,l=0;
    
    /*for(i=1; i<=n; i++)*/
    for(i=n; i>=0; i--){
        
        for(j=i;j<n;j++){
            block[k++] = ' ';
        }
        for(l=1;l<(i*2);l++){
        block[k++] = '*';
        }
        block[k++] = '\n';
    }
    return block;
}

int main()
{
    char* string = string_operations(5);
    puts(string);
    //free(string);
}

char* string_operations_2(unsigned int n){
    
    char* block = (char*)malloc(n*n);
    
    int i,j,k,l=0;
    
   for(i=1;i<=5;i++)
    {
        for(j=1;j<=6-i;j++)
        {
            block[k++] = '*';
        }
        for(l=1;l<i;l++)
        {
            block[k++] = ' ';
        }
        for(j=1;j<=6-i;j++)
        {
            block[k++]= '*';
        }
        block[k++] = '\n';
    }
    for(i=2;i<=5;i++)
    {
        for(j=1;j<=i;j++)
        {
             block[k++] = '*';
        }
        for(l=1;l<=5-i;l++)
        {
             block[k++] = ' ';
        }
        for(j=1;j<=i;j++)
        {
            block[k++]= '*';
        }
        block[k++] = '\n';
    }
    return block;
}