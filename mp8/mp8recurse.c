#include <stdlib.h>
#include <string.h>

#include "mp8.h"


/*
 * basicRecurse -- flood fill recursively from a point until reaching
 *                 white or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         x -- current x position of the flood
 *         y -- current y position of the flood
 *         marking -- array used to mark seen positions (indexed
 *                    in the same way as the RGB input arrays)
 * OUTPUTS: marking -- marked with flooded pixels
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void 
basicRecurse (int32_t width, int32_t height,
	      const uint8_t* inRed, const uint8_t* inGreen, 
	      const uint8_t* inBlue, 
	      int32_t x, int32_t y, 
	      uint8_t* marking)
{	//first check if in the bound
	if(x >= 0 && x < width && y >= 0 && y < height){
		int32_t z = x + y*width;
		//then check if it is marked and if it is white
		if(marking[z] != 1 && (inRed[z] != 255 || inGreen[z] != 255 || inBlue[z] != 255)){
			marking[z] = 1;//mark it
			//recursive check
			basicRecurse(width, height, inRed, inGreen, inBlue, x, y - 1, marking);
			basicRecurse(width, height, inRed, inGreen, inBlue, x + 1, y, marking);
			basicRecurse(width, height, inRed, inGreen, inBlue, x, y + 1, marking);
			basicRecurse(width, height, inRed, inGreen, inBlue, x - 1, y, marking);
		}	
	}
}


/*
 * greyRecurse -- flood fill recursively from a point until reaching
 *                near-white pixels or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         x -- current x position of the flood
 *         y -- current y position of the flood
 *         distSq -- maximum distance squared between white and boundary
 *                   pixel color
 *         marking -- array used to mark seen positions (indexed
 *                    in the same way as the RGB input arrays)
 * OUTPUTS: marking -- marked with flooded pixels
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void 
greyRecurse (int32_t width, int32_t height,
	     const uint8_t* inRed, const uint8_t* inGreen, 
	     const uint8_t* inBlue, 
	     int32_t x, int32_t y, uint32_t distSq, 
	     uint8_t* marking)
{	//first check if in the bound
	if(x >= 0 && x < width && y >= 0 && y < height){
		int32_t z = x + y*width;
		//then check if marked and if not within
		if(marking[z] != 1 && colorsWithinDistSq(inRed[z],inGreen[z],inBlue[z],255,255,255,distSq) == 0){
			marking[z] = 1;
			//recursion
			greyRecurse(width, height, inRed, inGreen, inBlue, x, y - 1, distSq, marking);
			greyRecurse(width, height, inRed, inGreen, inBlue, x + 1, y, distSq, marking);
			greyRecurse(width, height, inRed, inGreen, inBlue, x, y + 1, distSq, marking);
			greyRecurse(width, height, inRed, inGreen, inBlue, x - 1, y, distSq, marking);
		}	
	}
}


/*
 * limitedRecurse -- flood fill recursively from a point until reaching
 *                   pixels too different (in RGB color) from the color at
 *                   the flood start point, too far away (> 35 pixels), or
 *                   beyond the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         origX -- starting x position of the flood
 *         origY -- starting y position of the flood
 *         x -- current x position of the flood
 *         y -- current y position of the flood
 *         distSq -- maximum distance squared between pixel at origin 
 *                   and boundary pixel color
 *         marking -- array used to mark seen positions (indexed
 *                    in the same way as the RGB input arrays)
 * OUTPUTS: marking -- marked with flooded pixels
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
void 
limitedRecurse (int32_t width, int32_t height,
	        const uint8_t* inRed, const uint8_t* inGreen, 
	        const uint8_t* inBlue, 
	        int32_t origX, int32_t origY, int32_t x, int32_t y, 
		uint32_t distSq, uint8_t* marking)
{
	if(x >= 0 && x < width && y >= 0 && y < height){
		int32_t z = x + y*width;
		int32_t zs = origX + origY*width;
		int32_t m = (x - origX)*(x - origX) + (y - origY)*(y - origY);
		//check if out of the distance
		if(m <= 35*35){
			if(marking[z] != 1 && colorsWithinDistSq(inRed[z],inGreen[z],inBlue[z],inRed[zs],inGreen[zs],inBlue[zs],distSq) == 1){
				marking[z] = 1;
				limitedRecurse(width, height, inRed, inGreen, inBlue, origX, origY, x, y - 1, distSq, marking);
				limitedRecurse(width, height, inRed, inGreen, inBlue, origX, origY, x + 1, y, distSq, marking);
				limitedRecurse(width, height, inRed, inGreen, inBlue, origX, origY, x, y + 1, distSq, marking);
				limitedRecurse(width, height, inRed, inGreen, inBlue, origX, origY, x - 1, y, distSq, marking);
			}
		}	
	}
}

