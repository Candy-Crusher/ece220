#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "lab7.h"

void 
edgeDetect (int32_t width, int32_t height, 
	    const int32_t* sobelX, const int32_t* sobelY,
	    const uint8_t* inRed, const uint8_t* inGreen, 
	    const uint8_t* inBlue, uint8_t* outMono, uint8_t* temp)
{
	int w,h,a,b,red,green,blue;
	for(h=0;h<height;h++){
		for(w=0;w<width;w++){
			int Gx=0;
			int Gy=0;
			for(a=0;a<3;a++){
				for(b=0;b<3;b++){
					
					if(0>h+a-1||height<=h+a-1||0>w+b-1||width<=w+b-1){
						continue;
					}
					
					red=inRed[(h+a-1)*width+w+b-1];
					green=inGreen[(h+a-1)*width+w+b-1];
					blue=inBlue[(h+a-1)*width+w+b-1];
					int m=red*0.2125+green*0.7154+blue*0.0721;
					Gx+=sobelX[a*3+b]*m;
					Gy+=sobelY[a*3+b]*m;
				}
			}
			outMono[h*width+w]=sqrt(Gx*Gx+Gy*Gy);
			
		}
	}
}

