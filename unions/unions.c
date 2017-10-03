#include <stdio.h>

typedef union{
    
    int a;
    int b;
    int c;
    int d;
    int e;

}g_u_obj;

typedef struct{
    
    int a;
    int b;
    
}g_s_obj;

main()
{
    g_u_obj l_u_obj;
    g_s_obj l_s_obj;
    
    l_u_obj.a = 999999999;
    l_u_obj.b = 888888888;
    
    printf("%d\n", (l_u_obj.a));
    //printf("%d\n", &(l_u_obj.b));
    
    printf("%d\n", &(l_s_obj.a));
    printf("%d\n", &(l_s_obj.b));
    
    printf("%d\n", sizeof(l_u_obj));
    printf("%d\n", sizeof(l_s_obj));
}

