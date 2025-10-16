#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "libminibmp.h"

#define WIDTH 1600
#define HEIGHT 900

struct Point
    {
    int x;
    int y;
    };

const struct Point polygon[] =
    {
    {1500, 40}, {1519, 51}, {1434, 118}, {1336, 55}, {1283, 115}, {1257, 75}, {1156, 237}, {1188, 238},
    {1169, 318}, {1118, 231}, {1113, 252}, {1023, 202}, {1055, 135}, {935, 42}, {888, 112}, {815, 73},
    {873, 235}, {929, 177}, {853, 134}, {965, 75}, {965, 191}, {1016, 190}, {999, 311}, {1141, 346},
    {1087, 498}, {991, 478}, {912, 578}, {1006, 602}, {965, 653}, {852, 618}, {782, 716}, {669, 640},
    {647, 667}, {671, 733}, {685, 714}, {746, 727}, {710, 789}, {821, 813}, {854, 727}, {888, 752},
    {934, 678}, {1083, 745}, {1095, 642}, {1194, 688}, {1127, 810}, {1025, 760}, {993, 866}, {893, 825},
    {826, 890}, {744, 822}, {742, 832}, {705, 835}, {770, 882}, {782, 862}, {814, 892}, {700, 891},
    {670, 786}, {603, 788}, {583, 723}, {467, 758}, {496, 675}, {407, 687}, {453, 784}, {327, 879},
    {292, 811}, {389, 773}, {344, 677}, {415, 644}, {371, 576}, {441, 562}, {399, 477}, {505, 436},
    {527, 588}, {589, 575}, {613, 494}, {743, 496}, {720, 610}, {802, 651}, {864, 581}, {833, 521},
    {938, 500}, {934, 465}, {870, 481}, {879, 376}, {766, 417}, {780, 464}, {834, 479}, {796, 511},
    {846, 588}, {767, 558}, {752, 615}, {796, 621}, {794, 626}, {801, 627}, {803, 590}, {837, 604},
    {803, 641}, {773, 622}, {768, 626}, {724, 601}, {752, 525}, {795, 556}, {795, 512}, {748, 512},
    {734, 419}, {754, 412}, {732, 374}, {787, 312}, {903, 329}, {881, 401}, {962, 430}, {939, 482},
    {1045, 473}, {1034, 402}, {937, 397}, {960, 256}, {836, 245}, {830, 173}, {719, 195}, {659, 60},
    {611, 90}, {651, 30}
    };
int polygonSize = sizeof(polygon)/sizeof(polygon[0]);

//  zum Zeichnen des Polygon
void drawPolygon(bmp image, const struct Point* poly, int points, pixelcolor col)
    {
    // Zeichne Linien
    for (int i = 0; i < points - 1; i++)
        {
        int x1 = poly[i].x;
        int y1 = poly[i].y;
        int x2 = poly[i + 1].x;
        int y2 = poly[i + 1].y;
        drawLine(image, x1, y1, x2, y2, col);
        }

    // Schließe Polygon
    int xLast = poly[points - 1].x;
    int yLast = poly[points - 1].y;
    int xFirst = poly[0].x;
    int yFirst = poly[0].y;
    drawLine(image, xLast, yLast, xFirst, yFirst, col);
    }

//  Berechnen des kleinsten umschließenden Rechtecks
void Rechteck(const struct Point* poly, int n, struct Point* rect)
    {
    int minx = poly[0].x;
    int miny = poly[0].y;
    int maxx = poly[0].x;
    int maxy = poly[0].y;
    for (int i=1; i<n; i++)
        {
        if (poly[i].x < minx) minx = poly[i].x;
        if (poly[i].y < miny) miny = poly[i].y;
        if (poly[i].x > maxx) maxx = poly[i].x;
        if (poly[i].y > maxy) maxy = poly[i].y;
        }
    rect[0].x = minx; rect[0].y = miny; // Untere linke Ecke
    rect[1].x = maxx; rect[1].y = miny; // Untere rechte Ecke
    rect[2].x = maxx; rect[2].y = maxy; // Obere rechte Ecke
    rect[3].x = minx; rect[3].y = maxy; // Obere linke Ecke
    }

// Zeichnen Rechteck
void drawRectangle(bmp image, const struct Point* rect, pixelcolor col)
    {
    drawPolygon(image, rect, 4, col);
    }

// horizontaler Strahl von P aus Schnitt mit Segment AB
// 1 ja, sonst 0.
int testSegment(struct Point P, struct Point A, struct Point B) {
    // Wenn A.y größer als B.y ist -> tauschen A und B,
    if (A.y > B.y)
        {
        struct Point temp = A;
        A = B;
        B = temp;
        }

    // Prüfen, ob P außerhalb des vertikalen Bereichs von A bis B liegt.
    if (P.y < A.y || P.y >= B.y)
    {
        return 0;
    }

    // Falls A und B auf gleicher Höhe liegen, ist das Segment horizontal.
    if (A.y == B.y)
        {
        return 0;
        }

    // Berechnen, wie weit oben P zwischen A.y und B.y liegt.
    double t = (double)(P.y - A.y) / (double)(B.y - A.y);

    // x Koordinate Schnittpunkt P und AB
    double intersectX = A.x + t * (B.x - A.x);

    // Wenn Schnittpunkt rechts von P liegt, Schnitt mit P
    if (intersectX > P.x) {
        return 1;
    } else {
        return 0;
    }
}

// Punkt-in-Polygon-Test (Jordan-Test)
int pointInPolygon(struct Point P, const struct Point* poly, int n) {
    int sum = 0;
    for (int i=0; i<n; i++) {
        struct Point A = poly[i];
        struct Point B = poly[(i+1)%n];
        sum += testSegment(P, A, B);
    }
    // Wenn Innen: sum ungerade
    return (sum % 2 != 0);
}

int main() {
    // Grafik erstellen
    bmp image = newBMP(WIDTH, HEIGHT);
    BMPclear(image, COL_white);

    // Polygon zeichnen
    drawPolygon(image, polygon, polygonSize, COL_blue);

    // Umschließendes Rechteck berechnen
    struct Point rect[4];
    Rechteck(polygon, polygonSize, rect);

    // Rechteck zeichnen
    drawRectangle(image, rect, COL_red);

    // Anzahl der Punkte:
    int numberOfPoints = 50000;

    // Zufall initialisieren
    srand((unsigned)time(NULL));

    int Zi = 0; // Treffer im Polygon
    int Za = 0; // Außerhalb

    // Rechteck Breite Höhe
    int widthRect = rect[1].x - rect[0].x;
    int heightRect = rect[3].y - rect[0].y;
    double areaRect = (double)widthRect * (double)heightRect;

    for (int i=0; i<numberOfPoints; i++) {
        // Zufällige Koordinaten im Rechteck
        int rx = rect[0].x + rand()%(widthRect+1);
        int ry = rect[0].y + rand()%(heightRect+1);

        struct Point testP = {rx, ry};
        int inside = pointInPolygon(testP, polygon, polygonSize);

        if (inside) {
            Zi++;
            setPixel(image, rx, ry, COL_green);
        } else {
            Za++;
            setPixel(image, rx, ry, COL_purple);
        }
    }

    double ratio = (double)Zi / (double)(Zi + Za);
    double areaPolygon = areaRect * ratio;

    printf("| Treffer im Polygon:  %d |\n", Zi);
    printf("| Treffer aussen:  %d |\n", Za);
    printf("| Verhaeltnis:  %.6f |\n", ratio);
    printf("| Rechteck: %.2f Quadratpixel |\n", areaRect);
    printf("| Polygon:  %.2f Quadratpixel |\n", areaPolygon);

    save_BMP("MonteCarloPolygon.bmp", image);

    return 0;
}
