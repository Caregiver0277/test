#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "libminibmp.h"

#define XSIZE 800
#define YSIZE 600


#define PI 3.141593

int main()
{
    bmp mybmp1;
    int i;

    mybmp1 = newBMP(600, 600);

    BMPclear(mybmp1, COL_white);
    drawLine(mybmp1, 0,0,100,100, COL_red);
    drawLine(mybmp1, 100,0,100,100, COL_red);
    drawLine(mybmp1, 0,100,100,100, COL_red);

    drawLine(mybmp1, 500,500,400,400, COL_red);
    drawLine(mybmp1, 400,500,400,400, COL_red);
    drawLine(mybmp1, 500,400,400,400, COL_red);

    for (i = 0; i < 60; i++)
    {
        drawLine(mybmp1, 300, 300,
                            300 + 100 * cos(2*PI*i/60),
                            300 + 100 * sin(2*PI*i/60), COL_purple);
    }
    save_BMP("MyImage.bmp", mybmp1);
    return 0;
}
