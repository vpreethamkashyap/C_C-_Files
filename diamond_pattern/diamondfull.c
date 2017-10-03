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
		for(j=1; j<((n+1)-i); j++)
		{
			location[k++] = '*';
		}
		for(j=1; j<(n-i); j++)
		{
			location[k++] = '*';
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
		for(j=1; j<((n+1)-i); j++)
		{
			location[k++] = '*';
		}
		for(j=1; j<(n-i); j++)
		{
			location[k++] = '*';
		}
	    for(l=0; l<=(i); l++)
		{
			location[k++] = ' ';
		}
		location[k++] = '\n';
	}
	//location[k++] = '\n';
	return location;

}

int main(void)
{
	int i;

	char* display = string_output(20);

    for(i = 0; i < (10000); i++)
    {
    	printf("%c", display[i]);
    }
}