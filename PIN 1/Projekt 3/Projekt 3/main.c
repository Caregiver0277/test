#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Include math.h for pow function

float berechnespannungsteiler(float U, float R_1, float R_E) {
    float U_2 = (U * R_E) / (R_1 + R_E);
    return U_2;
}


float berechneersatzwiderstand(float R_2, float R_L) {
    float R_E = pow(((1 / R_2) + (1 / R_L)), -1);
    return R_E;
}


int main() {
    float U = 5.01;
    float R_1 = 100.00;
    float R_2 = 150.00;
    float R_L;
    float R_E;
    float U_2;

    printf("R_L , U_2\n");

    for (R_L = 5; R_L <= 2000; R_L += 5)
{
        R_E = berechneersatzwiderstand(R_2, R_L);
        U_2 = berechnespannungsteiler(U, R_1, R_E);
        printf("%.2f, %.2f\n", R_L, U_2);
}

    return 0;
}
