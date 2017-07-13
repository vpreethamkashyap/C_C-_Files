#include <stdio.h>
#include <malloc.h>

int main()
{
    int n = 10;
    int* dest = (int*)malloc(n*n);
    int a = 0, b= 0, i, j;
    
    do{
        dest[b++] = a;
        a++;
    }while(a <= n);
    
    //dest[b++] = '\n';
    a--;
    
    while(a >= 0)
    {
        dest[b++] = a;
        a--;
    }
    
    //dest[b++] = 'n';
    
    for(i = 0; i< (b/2); i++)
    {
        printf("%d ", dest[i]);
    }
    printf("\n");
    for(j = (b/2); j < b; j++)
    {
        printf("%d ", dest[j]);
    }

    free(dest);
}
