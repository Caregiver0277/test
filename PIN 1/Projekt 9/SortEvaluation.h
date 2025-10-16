#ifndef SORTEVALUATION_H_INCLUDED
#define SORTEVALUATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/* Unser Datentyp */
typedef double t_sortdata;

/* Funktionspointer-Typ f�r Sortieralgorithmen */
typedef void (*SortAlgorithm)(t_sortdata Data[], long DataCount);

/* Swap-Hilfsfunktion inline */
static inline void swapdata(t_sortdata* A, t_sortdata* B)
{
    t_sortdata BufferTemp = *A;
    *A = *B;
    *B = BufferTemp;
}

/* Erzeugt ein Array zuf�lliger t_sortdata-Werte. */
t_sortdata* generateRandomData(long DataCount);

/* Gibt ein Array von t_sortdata-Werten aus (Debug). */
void printDataArray(t_sortdata Data[], long DataCount);

#endif // SORTEVALUATION_H_INCLUDED
