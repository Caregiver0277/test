#ifndef LIBMINIBMP_H
#define LIBMINIBMP_H

typedef struct {
                unsigned char b;
                unsigned char g;
                unsigned char r;
            } pixelcolor;

#pragma pack(1)
typedef struct {
            unsigned short Type; 	        // File type. Set to "BM".
            unsigned int Size; 	            // Size in BYTES of the file.
            unsigned int Reserved; 	        // Reserved. Set to zero.
            unsigned int  Offset; 	        // Offset to the data.
            unsigned int  headerSize; 	    // Size of rest of header. Set to 40.
            int  Width; 	        // Width of bitmap in pixels.
            int  Height; 	        // Height of bitmap in pixels.
            unsigned short Planes; 	        // Number of Planes. Set to 1.
            unsigned short BitsPerPixel; 	// Number of bits per pixel.
            unsigned int Compression; 	    // Compression. Usually set to 0.
            unsigned int SizeImage; 	    // Size in bytes of the bitmap.
            unsigned int XPixelsPerMeter; 	// Horizontal pixels per meter.
            unsigned int YPixelsPerMeter; 	// Vertical pixels per meter.
            unsigned int ColorsUsed; 	    // Number of colors used.
            unsigned int ColorsImportant; 	// Number of "important" colors.
            pixelcolor * img;
            }
#ifndef _MSC_VER
            __attribute__((packed))
#endif
                bmp ;


extern const pixelcolor COL_black;
extern const pixelcolor COL_white;
extern const pixelcolor COL_green;
extern const pixelcolor COL_red;
extern const pixelcolor COL_blue;
extern const pixelcolor COL_yellow;
extern const pixelcolor COL_purple;
extern const pixelcolor COL_magenta;

bmp newBMP(long dx, long dy);
void BMPclear(bmp image, pixelcolor color);
void save_BMP(char * name, bmp image);
void setPixel(bmp image, int x, int y, pixelcolor color);
void drawLine(bmp image, int x1, int y1, int x2, int y2, pixelcolor color);
#endif
