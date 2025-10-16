#include <stdio.h>
#include <stdlib.h>


int Kantenlaenge = 5;



void printzeile (int links,int mitte)
{

    for (int i=links; i>0; i--)
    {
        printf(" ");
    }
    printf("*");



    for (int j=mitte; j>0; j--)
    {
        printf(" ");
    }
    printf("*");
    printf("\n");
}



void Raute (Kl)
{
int linksx = Kl-1;
int mittex = 0;

int linksz = 0;
int mittez = (Kl*2)-2;


    for (int y=0; y<Kl; y++)
      {
        printzeile(linksx, mittex);
        linksx = linksx-1;
        mittex = mittex+2;
      }


    for (int z=Kl; z>0; z--)
    {
        printzeile(linksz, mittez);
        linksz = linksz+1;
        mittez = mittez-2;
    }

}

int main()
{
 for (Kantenlaenge = 2; Kantenlaenge <= 11; Kantenlaenge++) {
        Raute(Kantenlaenge);
        printf("\n");
    }
return 0;
}
