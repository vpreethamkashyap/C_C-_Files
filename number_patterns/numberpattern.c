#include <stdio.h>
#include <stdlib.h>

char* string_output(unsigned int n)
{
	char* location = (char*)malloc(10000);
	int i,j,k = 0,l;

	for(i=(n-1); i>=0; i--)
	{
		for(j=0; j<=(i); j++)
		{
			location[k++] = ' ';
		}
		for(j=1; j<= 1; j++)
		{
			location[k++] = '1';
		}
		for(j=1; j<(n-i); j++)
		{
			location[k++] = '3';
		}
		for(j=1; j<(n-i); j++)
		{
			location[k++] = '5';
		}
		for(j=1; j<= 1; j++)
		{
			location[k++] = '1';
		}
	    for(l=0; l<=i; l++)
		{
			location[k++] = ' ';
		}
		location[k++] = '\n';
	}

	for(i = 1; i<=(n-1); i++)
	{
		for(j=0; j<=(i); j++)
		{
			location[k++] = ' ';
		}
		for(j=1; j<= 1; j++)
		{
			location[k++] = '1';
		}
		for(j=1; j<(n-i); j++)
		{
			location[k++] = '3';
		}
		for(j=1; j<(n-i); j++)
		{
			location[k++] = '5';
		}
		for(j=1; j<= 1; j++)
		{
			location[k++] = '1';
		}
	    for(l=0; l<=i; l++)
		{
			location[k++] = ' ';
		}
		location[k++] = '\n';
	}
	return location;

}

int main(void)
{
	int i,j,k,l;

	int *ptr = (int*)malloc(sizeof(int) * 4 * 4);

	ptr[0] = 45;
	ptr[1] = 46;
	ptr[2] = 47;
	ptr[3] = 48;
	ptr[4] = 49;
	ptr[5] = 50;
	ptr[24] = 51;

	char* display = string_output(20);

    for(i = 0; i < (10000); i++)
    {
    	printf("%c", display[i]);
    }

    printf("\n");

    for(i = 0; i<= 17; i++)
    {
    	printf("%d ", ptr[i]);
    }
        printf("\n");    

    for(i = 0; i<= 17; i++)
    {
    	printf("%d ", (ptr + i));
    }

    printf("\n");

    for(i = 0; i<= 17; i++)
    {
    	printf("%d ", &ptr[i]);
    }

    printf("\n");

}