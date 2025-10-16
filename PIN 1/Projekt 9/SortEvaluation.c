#include "SortEvaluation.h"

t_sortdata* generateRandomData(long DataCount)
{
    t_sortdata* ItemStorage;
    ItemStorage = (t_sortdata*)malloc(DataCount * sizeof(t_sortdata));
    for (long i=0; i<DataCount; i++)
    {
        ItemStorage[i]=((double)rand()/rand()+1);
    }
    return ItemStorage;
}

/* Zum Debuggen: Array ausgeben */
void printDataArray(t_sortdata Data[], long DataCount)
{
    printf("\n---------Anfang---------\n");
    for (long i = 0; i < DataCount; i++)
    {
        printf("%f ", Data[i]);
        if ( (i + 1) % 5 == 0 )
        {
            printf("\n");
        }
    }
    printf("\n----------Ende----------\n");
}
