#include <stdio.h>
#include <stdlib.h>

//ex 3x4 * 4x3 matrix

/*
  {
   {1,2,3,4},       [1,2,3]
   {5,6,7,8},       [4,5,6]
   {9,10,11,12}     [7,8,9]
  }					[10,11,12]


 */

int main(void){

	int n,m,j,k,value,i,p, *arr;

	printf("Enter the dimension's for a_matrix \n");
	printf("Enter the value of n: ");
	scanf("%d", &n);
	printf("Enter the value of m: ");
	scanf("%d", &m);

	printf("Enter values for a_matrix ");
	for(i=0; i<(n*m); i++)
	{
		scanf("%d", &value);
		*(arr+i) = value;
	}
	
	int *t_arr = NULL;

	t_arr = arr;

	printf("The matrix entered is\n");
    for(i=n; i>0; --i){
     for(p=0; p<m; ++p){
         printf("%d ", *(arr)++);
     }
     printf("\n");
    }
    
    printf("Enter the dimension's for b_matrix \n");
	printf("Enter the value of j: ");
	scanf("%d", &j);
	printf("Enter the value of k: ");
	scanf("%d", &k);
	
	//int* foo = (int*)malloc(sizeof(j*k));
	
	int foo[20];

	printf("Enter values for b_matrix ");
	for(i=0; i<(j*k); i++)
	{
		scanf("%d", &value);
		*(foo+i) = value;
	}

	printf("The matrix entered is\n");
	int t = 0;
    for(i=j; i>0; --i){
     for(p=0; p<k; ++p){
         printf("%d ", *(foo + t));
         t++;
     }
     printf("\n");
    }

    printf("The matrix entered is\n");
    for(i=n; i>0; --i){
     for(p=0; p<m; ++p){
         printf("%d ", *(t_arr)++);
     }
     printf("\n");
    }
    
    printf("%d\n", *(arr));
    printf("%d\n", *(arr+1));
    printf("%d\n", *(arr+1) + 1);
    
    /*int baa[20];
    int r = 0;
    for(i=0; i<n; i++){
        for(p=0; p<k; p++){
            
            baa[r++] = ((*(arr + i) + p) * () 
            
        }
    }*/
    
}