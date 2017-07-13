#include <stdio.h>

int main()
{
    int a[3][3][1] = {
                       {
                           {23},
                           {22},
                           {234}
                       },
                      {
                          {26},
                          {2234},
                          {3434}
                      },
                      {
                          {45},
                          {7899},
                          {790}
                      }
                    };
                   
    //int 
                   
    int *p_a = (int*)a[0];
    
   // printf("%x \n", p_a);
   // printf("%d \n", *p_a);
    //printf("%x \n", p_a);
   // printf("%d \n", *p_a++);
    //printf("%x \n", p_a);
    //printf("%d \n", *++p_a);
    
    int result = *(p_a + 8); //+ a[1][0] + a[2][0];
    
    printf("%d \n" ,result);
    
    int b = 340;
    
    int *p_b = &b;
    printf("%x\n", p_b);
    
    int **pp_b = &p_b;
    printf("%x\n", pp_b);
    printf("%d\n", **pp_b);
    
    int *trunk_p = (int*)pp_b;
    int ***p = &trunk_p;
    printf("%x\n", (*trunk_p));
    printf("%d\n", ***p);
    
    int **p_2 = (int**)p;
    
}