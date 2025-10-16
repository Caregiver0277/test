#include <stdio.h>
#include <stdlib.h>

struct z
{
    int Anzahl;
    double Rest;
};

struct x Rechner(double G,double SW)
    {
        struct x a;
        a.Anzahl = (G/SW);
        a.Rest = (G-(a.Anzahl*SW));
        return a;
    }


int main()
{

double A;
printf("Bitte geben sie die Gesamtsumme ein: ");
scanf("%lf",&A);
printf("Die Gesamtsumme kann aus:\n\n");
double Gesamtsumme = A;


double Stueckelungswert[15] = {500.00, 200.00, 100.00, 50.00, 20.00, 10.00, 5.00, 2.00, 1.00, 0.50, 0.20, 0.10, 0.05, 0.02, 0.01};
double Stueckelungsergebnis[15];




    for (int i=0; i<15; i++)
    {
        struct x Werte = Rechner(Gesamtsumme, Stueckelungswert[i]);

        Gesamtsumme=Werte.Rest;



        printf("Geldeinheit:%5.2lf  |  Anzahl:%5d\n----------------------------------\n", Stueckelungswert[i], Werte.Anzahl);

    }

printf("\n\nzusammengesetzt werden");

    return 0;
}

