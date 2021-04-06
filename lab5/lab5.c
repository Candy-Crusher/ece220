#include <stdint.h>
#include <stdio.h>

#include "lab5.h"

/*
 * The fit_pieces function determines whether the "pieces" (bit patterns,
 * with some number of leading 0s) can "fit together" (line up with exactly
 * one 1 in any bit position, filling all 32 bits with 1s) when shifted
 * left by appropriate amounts (without overflow / loss of any 1 bits).
 *
 * If such shifts can be found, the function prints the left shift amounts
 * for each of the three pieces in order--p1, p2, and p3--then returns 1.
 * If no such shifts exist, the function returns 0.
 */
int32_t
fit_pieces (uint32_t p1, uint32_t p2, uint32_t p3)
{
    // write your code here
	int i = 0, j = 0, k = 0;
	int p1Upper = 0, p2Upper = 0, p3Upper = 0;
	for(i = 0;32 > i;i++) {
		int a = p1 << i;
		if(a < 0) {
			p1Upper = i;
			break;
		}
	}
	for(i = 0;32 > i;i++) {
		int a = p2 << i;
		if(a < 0) {
			p2Upper = i;
			break;
		}
	}
	for(i = 0; 32 > i; i++) {
		int a = p3 << i;
		if(a < 0) {
			p3Upper = i;
			break;
		}
	}
	printf("upper: %d %d %d\n", p1Upper, p2Upper, p3Upper);
	for(i = 0; p1Upper >= i; i++){
		for(j = 0; p2Upper >= j; j++){
			for(k = 0; p3Upper >= k; k++){
				int a = p1 << i,b = p2 << j,c = p3 << k;
				int x = a & b & c;
				printf("%x\n", x);
				if ( x != 0 ){
					continue;
				}
				int y = a | b | c;
				int ans = -1;

				if ( y == ans ){
					if ( i >= 1 && i <= 26 ){
						printf( "%c", i + 'A' -1);
					} else {
						printf(" "); 
					}
					if ( j >= 1 && j <= 26 ){
						printf( "%c", j + 'A' -1);
					} else {
						printf(" "); 
					}
					if ( k >= 1 && k <= 26 ){
						printf( "%c", k + 'A' -1);
					} else {
						printf(" "); 
					}
				return 1;
				} 
			}
		}
	}
				
    // not possible
    return 0;
}

