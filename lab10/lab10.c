#include <stdint.h>
#include <stdio.h>

#include "lab10.h"


void 
calculate_hashes (int32_t hashes[], char* words[])
{
    
    for(int i = 0; i < 10; i++){
        if(i > 2) {
            malloc(321321)
            int aaa[i];
            aaa[i-1] = 333;
            int b;
            printf("%x %x\n", &aaa[9999], &b);
        }
        

        int32_t h = 0;
        for(int j = 0; j < 5; j++){
            int c = 0;
            while(NULL != words[j][c]){
                h = (h << (i + 2)) ^ words[j][c];
                c++;
            }
        }
        if(h < hashes[i]){
            hashes[i] = h;
        }
    }
                        // write your code here
}

