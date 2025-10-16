#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "libminibmp.h"

#define HEADERSIZE 54
#define IMAGEGRANULARITY 2

#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))
#define SGN(x) ( (x)>0 ? 1 : (x)<0 ? -1 : 0 )
#define ABS(x) ( (x)>0 ? (x) : -(x) )

const pixelcolor COL_black = {0, 0, 0};
const pixelcolor COL_white = {255, 255, 255};
const pixelcolor COL_green = {0, 255, 0};
const pixelcolor COL_red = {0, 0, 255};
const pixelcolor COL_blue = {255, 0, 0};
const pixelcolor COL_yellow = {0, 255, 255};
const pixelcolor COL_cyan = {255, 255, 0};
const pixelcolor COL_purple = {100, 0, 150};
const pixelcolor COL_magenta = {255, 0, 255};

void BMPclear(bmp image, pixelcolor color)
{
    int i=0;
    for (i = 0; i < image.Width * image.Height; *(image.img + i++) = color);
}

bmp newBMP(long dx, long dy)
{
    bmp image;
    dx = (dx%IMAGEGRANULARITY)?((dx>>IMAGEGRANULARITY)+1)<<IMAGEGRANULARITY : dx;
    image.Type = 'M' << 8 | 'B';
    image.Size = HEADERSIZE + dx * dy * 3;
    image.Reserved = 0;
    image.Offset = HEADERSIZE;
    image.headerSize = 40;
    image.Width = dx;
    image.Height = dy;
    image.Planes = 1;
    image.BitsPerPixel = 24;
    image.Compression = 0;
    image.SizeImage = dx * dy * 3;
    image.XPixelsPerMeter = 0;
    image.YPixelsPerMeter = 0;
    image.ColorsUsed = 0;
    image.ColorsImportant = 0;
    image.img = (pixelcolor*) malloc(sizeof(pixelcolor) * dx * dy);
    BMPclear(image, COL_white);
    return image;
}

void save_BMP(char * name, bmp image)
{
    FILE* f = fopen(name, "w");
    fwrite(&image, HEADERSIZE, 1, f);
    fwrite(image.img, image.SizeImage, 1, f);
    fclose(f);
    return;
}

void setPixel(bmp image, int x, int y, pixelcolor color)
{
    int radr = y * image.Width + x;
    if (x>0 && x<image.Width && y>0 && y<image.Height)
        {
            *(image.img + radr) = color;
        }
}

void drawLine(bmp image, int x1, int y1, int x2, int y2, pixelcolor color)
{
    int xs,ys;
    int dx, dy;
    double steigung;
    xs = x1;
    ys = y1;
    dx = x2 - x1;
    dy = y2 - y1;
    /* Sonderfall senkrechte Linie*/
    if (dx == 0)
    {
        int i;
        for(i=MIN(y1, y2); i<=MAX(y1, y2); i++)
        {
            setPixel(image, x1, i, color);
        }
        return;
    }
    /* Sonst mit einfach mit Steigung arbeiten... */
    setPixel(image, xs, ys, color);
    steigung = (double)dy / (double)dx;
    while (xs != x2 || ys != y2)
    {
        if (ABS(dx)>=ABS(dy))
        {
            xs += SGN(dx);
            if (ys * SGN(dy) < (floor((xs-x1)*steigung + 0.5) + y1)*SGN(dy))
                ys += SGN(dy);
        }
        else
        {
            ys += SGN(dy);
            if (xs * SGN(dx) < (floor((ys-y1)/steigung + 0.5) + x1)*SGN(dx))
                xs += SGN(dx);
        }
        setPixel(image, xs, ys, color);
    }

}
