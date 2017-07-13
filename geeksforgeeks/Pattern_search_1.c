/*Replace all occurrences of string AB with C without using extra space*/

#include <stdio.h>
#include <stdlib.h>

void patterntranslate(char* str)
{
	int i,j;

	if(str[0] == '\0')
		{return;}

	for(i=1; str[i] != '\0'; i++)
	{
		if(str[i-1] == 'A' && str[i] == 'B')
		{
			str[i-1] = 'C';

			for(j=i; str[j] != '\0'; j++)
			{
				str[j] = str[j+1];
			}
		}
	}
	return;
}

int main (void)
{

	char str[] = "helloABWorld";

	patterntranslate(str);

	printf("%s \n", str);

}