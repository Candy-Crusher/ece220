#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "mp5.h"


static void
build_tree (int32_t level, int32_t x, int32_t y, double angle, double width)
{
    if(level == 5){
        printf("set_color(0x00E040);");
        printf("draw_circle(%d,%d,0,5);",x,y);
        return ;
        }
    double length = 60*(drand48 () + 1)*pow(0.666666,level);
    double xend = x + length*cos(angle);
    double yend = y - length*sin(angle);
    double width_end = width*((drand48()+2)/3);
    printf("set_color(0x795B35);");
    double x1=x-width*sin(angle);
    double y1=y-width*cos(angle);
    double x2=xend-width_end*sin(angle);
    double y2=yend-width_end*cos(angle);
    double x3=x+width*sin(angle);
    double y3=y+width*cos(angle);
    double x4=xend+width_end*sin(angle);
    double y4=yend+width_end*cos(angle);


    printf("draw_line(%f,%f,%f,%f);",x1,y1,x2,y2);
    printf("draw_line(%f,%f,%f,%f);",x3,y3,x4,y4);
    int32_t numchildren = 2 + 4*drand48();
    double anglespan = M_PI_2*(1 + drand48());
    for(double a = angle + anglespan/2; a >= angle - anglespan/2; a = a - anglespan/numchildren){
        build_tree(level+1,xend,yend,a,width_end/2);
    }

        // you need to write this code
    // don't forget to set the color before drawing anything!
}

int
main ()
{
    // this random seed produces the tree in the lab specification
    srand48 (0x5BDE78CB);

    // for random trees, uncomment the line below
    // srand48 (time (NULL));

    printf ("#include <stdint.h>\n\n#include \"mp5.h\"\n\nvoid\n");
    printf ("draw_tree (void) {\n");
    build_tree (0, WIDTH / 2, HEIGHT - 1, M_PI_2, 20);
    printf ("}\n");
    
    return 0;
}

