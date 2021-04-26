#include <stdio.h>
#include <stdlib.h>

#include "mp4.h"

/*
*The logic problem forms a small part of solving a type of puzzle often called a Nonogram, 
*in which a player tries to fill in a pixelated, black-and-white image based on lists 
*of the lengths of the contiguous black regions in each row and column.
*/

int32_t 
print_row (int32_t width, int32_t r1, int32_t r2, int32_t r3, int32_t r4, int32_t r5)
{
    /*first check if the specified regions can fit into the given width*/
    /*if cannot fit,return 0 */
    if(width < r1 + r2 + r3 + r4 + r5 +4)
    {
        return 0;
    }
    /*declaration*/
    int i;
    int a = width-r1-r2-r3-r4-r5-4;
    int b;
    
    //for the first region, print "_" for min(a,r1) and print "*" for r1-a when r1>=a
    if(a<r1){
        b = a;
    }else{
        b = r1;
    }
    for(i=0;b>i;i++){
        printf("_");
    }
    for(i=0;r1-a>i;i++){
        printf("*");
    }
    //then print "_" to seperate regions
    printf("_");
    
    //for the second region, print "_" for min(a,r2) and print "*" for r2-a when r2>=a

    if(a<r2){
        b = a;
    }else{
        b = r2;
    }
    for(i=0;b>i;i++){
        printf("_");
    }
    for(i=0;r2-a>i;i++){
        printf("*");
    }
    printf("_");

    //for the third region, print "_" for min(a,r3) and print "*" for r3-a when r3>=a
    if(a<r3){
        b = a;
    }else{
        b = r3;
    }
    for(i=0;b>i;i++){
        printf("_");
    }
    for(i=0;r3-a>i;i++){
        printf("*");
    }
    printf("_");
 
    //for the forth region, print "_" for min(a,r4) and print "*" for r4-a when r4>=a
    if(a<r4){
        b = a;
    }else{
        b = r4;
    }
    for(i=0;b>i;i++){
        printf("_");
    }
    for(i=0;r4-a>i;i++){
        printf("*");
    }
    printf("_");
    
    //for the fifth region, print "_" for min(a,r5) and print "*" for r5-a when r5>=a
    if(a<r5){
        b = a;
    }else{
        b = r5;
    }
    for(i=0;b>i;i++){
        printf("_");
    }
    for(i=0;r5-a>i;i++){
        printf("*");
    }

    //finally,print "_" for a times
    for(i=0;a>i;i++){
        printf("_");
    }
    //print a new line
    printf("\n");
    return 1;
}