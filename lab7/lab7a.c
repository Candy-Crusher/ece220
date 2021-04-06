#include <stdint.h>
#include <stdio.h>


static void
show_mapping (int32_t A[3][5][7], int32_t* B)
{
    int a,b,c;
    for(c=0;c<105;c++){
        B[c]=c;
    }
    for(a=0;a<3;a++){
        for(b=0;b<5;b++){
            for(c=0;c<7;c++){
                printf("%3d\n",A[a][b][c]);
            }
        }
    }
    printf ("A = %p, B = %p\n\n", A, B);
}


int
main ()
{
    int32_t array[3][5][7];

    show_mapping (array, (int32_t*)array);
    
    return 0;
}


