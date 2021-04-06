/*									tab:8
 *
 * main.c - skeleton source file for ECE220 picture drawing program
 *
 * "Copyright (c) 2018 by Charles H. Zega, and Saransh Sinha."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Charles Zega, Saransh Sinha
 * Version:	    1
 * Creation Date:   12 February 2018
 * Filename:	    mp5.h
 * History:
 *	CZ	1	12 February 2018
 *		First written.
 */
#include "mp5.h"

/*
	You must write all your code only in this file, for all the functions!
*/

/*
	define func sgn
*/
int32_t sgn(int32_t x){
	if(x > 0){
		return 1;
	}
	if(x == 0){
		return 0;
	}else{
		return -1;
	}

}

/* 
 *  near_horizontal
 *	 
 *	 
 *	
 *	
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
near_horizontal(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int x1=x_start;
	int x2=x_end;,,zk
	int y1=y_start;
	int y2=y_end;
	int xmax=(((x1-x2) >= 0) ? x1:x2);	//find the larger x as xmax
	int ymax=(((x1-x2) >= 0) ? y1:y2);	//find the larger y as ymax
	int xmin=x1+x2-xmax;				//the smaller x as xmin
	int ymin=y1+y2-ymax;
	int r=1;							//initial return value as 1
	int x,y;
	for(x=xmin;(xmin<=x) && (x<=xmax);x++){
		y=(2*(y2-y1)*(x-x1)+(x2-x1)*sgn(y2-y1))/2/(x2-x1)+y1;//calculate y
		int z=draw_dot(x,y);//draw point
		r=r&&z;//AND return valus
	}	
	return r;
}


/* 
 *  near_vertical
 *	 
 *	 
 *	
 *	
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
near_vertical(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int x1=x_start;
	int x2=x_end;
	int y1=y_start;
	int y2=y_end;
	int ymax=((y1-y2) >= 0 ? y1:y2);//find larger y as ymax
	int ymin=y1+y2-ymax;//find smaller y as ymin
	int xmax=((y1-y2) >= 0 ? x1:x2);//find conresbonding x as xmax
	int xmin=x1+x2-xmax;//other one as xmin
	int r=1;//initial return value as 1
	int x,y;
	//if the same point, draw a single point
	if((x1==x2)&&(y1==y2)){
		int z=draw_dot(x1,y1);
		return z;
	//otherwise draw line
	}else{
		for(y=ymin;(ymin<=y) && (y<=ymax);y++){
			x=(2*(x2-x1)*(y-y1)+(y2-y1)*sgn(x2-x1))/2/(y2-y1)+x1;
			int z=draw_dot(x,y);
			r=r&&z;
		}	
	return r;
	}
}

/* 
 *  draw_line
 *	 
 *	 
 *	
 *	
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_line(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int x1=x_start;
	int x2=x_end;
	int y1=y_start;
	int y2=y_end;
	int z;
	//if denumerator is 0
	if(x1==x2){
		z=near_vertical(x1,y1,x2,y2);
		return z;
	}
	//the denumerator is not 0
	int k=((y2-y1)/(x2-x1));//calculate scope
	if(-1<=k && k<=1){
		z=near_horizontal(x1,y1,x2,y2);
	}else{
		z=near_vertical(x1,y1,x2,y2);
	}
	return z;
}


/* 
 *  draw_rect
 *	 
 *	 
 *	
 *	
 * INPUTS: x,y -- the coordinates of the of the top-left pixel of the rectangle
 *         w,h -- the width and height, respectively, of the rectangle
 * OUTPUTS: draws a pixel to every point of the edges of the rectangle
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_rect(int32_t x, int32_t y, int32_t w, int32_t h){
	/* Your code goes here! */
	int z1,z2,z3,z4;
	if(w<=0||h<0){
		return 0;
	}
	z1=draw_line(x,y,x+w,y);
	z2=draw_line(x,y+h,x+w,y+h);
	z3=draw_line(x,y,x,y+h);
	z4=draw_line(x+w,y,x+w,y+h);
	return z1&&z2&&z3&&z4;
}


/* 
 *  draw_triangle
 *	 
 *	 
 *	
 *	
 * INPUTS: x_A,y_A -- the coordinates of one of the vertices of the triangle
 *         x_B,y_B -- the coordinates of another of the vertices of the triangle
 *         x_C,y_C -- the coordinates of the final of the vertices of the triangle
 * OUTPUTS: draws a pixel to every point of the edges of the triangle
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_triangle(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	/* Your code goes here! */
	int z1,z2,z3;
	z1=draw_line(x_A,y_A,x_B,y_B);
	z2=draw_line(x_A,y_A,x_C,y_C);
	z3=draw_line(x_C,y_C,x_B,y_B);
	return z1&&z2&&z3;
}
/* 
 *  draw_parallelogram
 *	 
 *	 
 *	
 *	
 * INPUTS: x_A,y_A -- the coordinates of one of the vertices of the parallelogram
 *         x_B,y_B -- the coordinates of another of the vertices of the parallelogram
 *         x_C,y_C -- the coordinates of another of the vertices of the parallelogram
 * OUTPUTS: draws a pixel to every point of the edges of the parallelogram
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_parallelogram(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	/* Your code goes here! */
	int x_D=x_A+x_C-x_B;//calculate the forth point 
	int y_D=y_A+y_C-y_B;
	int z1,z2,z3,z4;
	z1=draw_line(x_A,y_A,x_B,y_B);
	z2=draw_line(x_C,y_C,x_B,y_B);
	z3=draw_line(x_A,y_A,x_D,y_D);
	z4=draw_line(x_C,y_C,x_D,y_D);
	return z1&&z2&&z3&&z4;
}


/* 
 *  draw_circle
 *	 
 *	 
 *	
 *	
 * INPUTS: x,y -- the center of the circle
 *         inner_r,outer_r -- the inner and outer radius of the circle
 * OUTPUTS: draws a pixel to every point whose distance from the center is
 * 	    greater than or equal to inner_r and less than or equal to outer_r
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_circle(int32_t x, int32_t y, int32_t inner_r, int32_t outer_r){
	/* Your code goes here!*/
	if(inner_r<0||(outer_r-inner_r)<0){
		return 0;
	}
	int r=1;
	int xi,yi,z;
	//only check the square determined by the outer_r
	for(xi=x-outer_r;(x-outer_r<=xi)&&(xi<=x+outer_r);xi++){
		for(yi=y-outer_r;(y-outer_r<=yi)&&(yi<=y+outer_r);yi++){
			int m=(xi-x)*(xi-x)+(yi-y)*(yi-y);//the square of distance
			if((inner_r*inner_r <= m)&&(m <= outer_r*outer_r)){
				z=draw_dot(xi,yi);//if in the scope,draw point
				r=r&&z;
			}
		}
	}
	return r;
}


/* 
 *  rect_gradient
 *	 
 *	 
 *	
 *	
 * INPUTS: x,y -- the coordinates of the of the top-left pixel of the rectangle
 *         w,h -- the width and height, respectively, of the rectangle
 *         start_color -- the color of the far left side of the rectangle
 *         end_color -- the color of the far right side of the rectangle
 * OUTPUTS: fills every pixel within the bounds of the rectangle with a color
 *	    based on its position within the rectangle and the difference in
 *          color between start_color and end_color
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
rect_gradient(int32_t x, int32_t y, int32_t w, int32_t h, int32_t start_color, int32_t end_color){
	/* Your code goes here! */
	if(h<0||w<1){
		return 0;
	}
	int32_t m=255;
	int32_t lb1=start_color&m;//copy last 8 bits and all others as 0
	int32_t lb2=end_color&m;
	int32_t lg1=(start_color>>8)&m;//copy 8-15 bits and all others as 0
	int32_t lg2=(end_color>>8)&m;
	int32_t lr1=(start_color>>16)&m;//copy 16-23 bits and all others as 0
	int32_t lr2=(end_color>>16)&m;	
	int32_t lb,lg,lr,color;
	int32_t x1=x;
	int32_t y1=y;
	int32_t x2=x+w;
	int32_t y2=y+h;
	int32_t r=1;
	int32_t xi,yi,z;
	for(xi=x1;(x1 <= xi) && (xi <= x2);xi++){
		//calculate each new level for each column
		lb=((2*(xi-x1)*(lb2-lb1)+(x2-x1)*sgn(lb2-lb1))/2/(x2-x1))+lb1;
		lg=((2*(xi-x1)*(lg2-lg1)+(x2-x1)*sgn(lg2-lg1))/2/(x2-x1))+lg1;
		lr=((2*(xi-x1)*(lr2-lr1)+(x2-x1)*sgn(lr2-lr1))/2/(x2-x1))+lr1;
		//add them together
		color=lb|(lg<<8)|(lr<<16);
		//change color for this column
		set_color(color);
		for(yi=y1;(y1<=yi)&&(yi<=y2);yi++){
			z=draw_dot(xi,yi);
			r=r&&z;
		}
	}
	return r;
}

/* 
 *  triangle_gradient
 *	 
 *	 
 *	
 *	
 * INPUTS: x1,y1,x2,y2,x3,y3 -- the coordinates of the of the vertex pixel of the tritangle
 *         start_color -- the color of the far left side of the rectangle
 *         end_color -- the color of the far right side of the rectangle
 * OUTPUTS: fills every pixel within the bounds of the rectangle with a color
 *	    based on its position within the rectangle and the difference in
 *          color between start_color and end_color
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
triangle_gradient(int32_t xl, int32_t xr, int32_t yb,int32_t xt, int32_t yt, int32_t start_color, int32_t end_color){
	/* Your code goes here! */
	int32_t m=255;
	int32_t lb1=start_color&m;
	int32_t lb2=end_color&m;
	int32_t lg1=(start_color>>8)&m;
	int32_t lg2=(end_color>>8)&m;
	int32_t lr1=(start_color>>16)&m;
	int32_t lr2=(end_color>>16)&m;	
	int32_t lb,lg,lr,color;
	int32_t r=1;
	int32_t xi,yi,z;
	if((xl<=xt)&&(xt<=xr)){
		for(xi=xl;(xl <= xi) && (xi <= xt);xi++){
			lb=((2*(xi-xl)*(lb2-lb1)+(xr-xl)*sgn(lb2-lb1))/2/(xr-xl))+lb1;
			lg=((2*(xi-xl)*(lg2-lg1)+(xr-xl)*sgn(lg2-lg1))/2/(xr-xl))+lg1;
			lr=((2*(xi-xl)*(lr2-lr1)+(xr-xl)*sgn(lr2-lr1))/2/(xr-xl))+lr1;
			color=lb|(lg<<8)|(lr<<16);
			set_color(color);
			for(yi=yt;(yt<=yi)&&(yi<=yb);yi++){
				int ya=(2*(yt-yb)*(xi-xl)+(xt-xl)*sgn(yt-yb))/2/(xt-xl)+yb;
				if(ya<=yi){
					z=draw_dot(xi,yi);
					r=r&&z;
				}
			
			}
		}
		for(xi=xt;(xt <= xi) && (xi <= xr);xi++){
			lb=((2*(xi-xl)*(lb2-lb1)+(xr-xl)*sgn(lb2-lb1))/2/(xr-xl))+lb1;
			lg=((2*(xi-xl)*(lg2-lg1)+(xr-xl)*sgn(lg2-lg1))/2/(xr-xl))+lg1;
			lr=((2*(xi-xl)*(lr2-lr1)+(xr-xl)*sgn(lr2-lr1))/2/(xr-xl))+lr1;
			color=lb|(lg<<8)|(lr<<16);
			set_color(color);
			for(yi=yt;(yt<=yi)&&(yi<=yb);yi++){
				int yc=(2*(yt-yb)*(xi-xr)+(xt-xr)*sgn(yt-yb))/2/(xt-xr)+yb;
				if(yc<=yi){
					z=draw_dot(xi,yi);
					r=r&&z;
				}
			
			}
		}
	}else{
		for(xi=xl;(xl <= xi) && (xi <= xt);xi++){
			lb=((2*(xi-xl)*(lb2-lb1)+(xr-xl)*sgn(lb2-lb1))/2/(xr-xl))+lb1;
			lg=((2*(xi-xl)*(lg2-lg1)+(xr-xl)*sgn(lg2-lg1))/2/(xr-xl))+lg1;
			lr=((2*(xi-xl)*(lr2-lr1)+(xr-xl)*sgn(lr2-lr1))/2/(xr-xl))+lr1;
			color=lb|(lg<<8)|(lr<<16);
			set_color(color);
			for(yi=yt;(yt<=yi)&&(yi<=yb);yi++){
				int ya=(2*(yt-yb)*(xi-xl)+(xt-xl)*sgn(yt-yb))/2/(xt-xl)+yb;
				int yc=(2*(yt-yb)*(xi-xr)+(xt-xr)*sgn(yt-yb))/2/(xt-xr)+yb;
				int ymax=(ya>yc?ya:yc);
				int ymin=(ya>yc?yc:ya);
				if((ymin<=yi)&&(yi<=ymax)){
					z=draw_dot(xi,yi);
					r=r&&z;
				}
			
			}
		}
	}
	return r;
}

/* 
 *  circle_gradient
 *	 
 *	 
 *	
 *	
 * INPUTS: x,y -- the coordinates of the of the center pixel of the circle
 *         inner_r,outer_r -- the radius, respectively, of the inner and outer circle
 *         start_color -- the color of the far left side of the rectangle
 *         end_color -- the color of the far right side of the rectangle
 * OUTPUTS: fills every pixel within the bounds of the ring with a color
 *	    based on its position within the rectangle and the difference in
 *          color between start_color and end_color
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */
int32_t
circle_gradient(int32_t x, int32_t y, int32_t inner_r, int32_t outer_r, int32_t start_color, int32_t end_color){
	/* Your code goes here! */
	if(inner_r<0||(outer_r-inner_r)<0){
		return 0;
	}
	int32_t m=255;
	int32_t lb1=start_color&m;
	int32_t lb2=end_color&m;
	int32_t lg1=(start_color>>8)&m;
	int32_t lg2=(end_color>>8)&m;
	int32_t lr1=(start_color>>16)&m;
	int32_t lr2=(end_color>>16)&m;	
	int32_t lb,lg,lr,color;
	int32_t x1=x-outer_r;
	int32_t y1=y-outer_r;
	int32_t x2=x+outer_r;
	int32_t y2=y+outer_r;
	int32_t r=1;
	int32_t xi,yi,z;
	for(xi=x1;(x1 <= xi) && (xi <= x2);xi++){
		lb=((2*(xi-x1)*(lb2-lb1)+(x2-x1)*sgn(lb2-lb1))/2/(x2-x1))+lb1;
		lg=((2*(xi-x1)*(lg2-lg1)+(x2-x1)*sgn(lg2-lg1))/2/(x2-x1))+lg1;
		lr=((2*(xi-x1)*(lr2-lr1)+(x2-x1)*sgn(lr2-lr1))/2/(x2-x1))+lr1;
		color=lb|(lg<<8)|(lr<<16);
		set_color(color);
		for(yi=y1;(y1<=yi)&&(yi<=y2);yi++){
			int m=(xi-x)*(xi-x)+(yi-y)*(yi-y);
			if((inner_r*inner_r <= m)&&(m <= outer_r*outer_r)){
				z=draw_dot(xi,yi);
				r=r&&z;
			}
		}
	}
	return r;
}


/* 
 *  draw_picture
 *	 
 *	 
 *	
 *	
 * INPUTS: none
 * OUTPUTS: alters the image by calling any of the other functions in the file
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */


int32_t
draw_picture(){
	/* Your code goes here! */
	set_color(2699064);//back ground color
	int z=rect_gradient(0,0,624,320,2699064,2699064);
	//a circle
	z &= circle_gradient(365,105,0,35,9322238,15875725);
	//a ring
	z &= circle_gradient(365,105,39,41,9322238,15875725);
	//another ring
	z &= circle_gradient(365,105,45,47,9322238,15875725);
	//a triangle
	z &= triangle_gradient(75,135,300,105,250,9322238,15875725);
	//a triangle
	z &= triangle_gradient(150,235,300,275,150,9322238,9322238);
	//a triangle
	z &= triangle_gradient(235,385,300,275,150,9322238,15875725);
	set_color(11634687);
	//a line
	z &= draw_line(276,149,150,300);
	//a line
	z &= draw_line(276,149,235,300);
	//a triangle
	z &= triangle_gradient(355,385,302,405,230,11634687,11634687);
	//a triangle
	z &= triangle_gradient(385,475,302,405,230,9322238,15875725);
	//a triangle
	z &= triangle_gradient(435,475,304,495,200,11634687,11634687);
	//a triangle
	z &= triangle_gradient(475,575,304,495,200,9322238,15875725);
	return z;
}
