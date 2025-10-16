#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "Zeitmessung.h"
#include "SortEvaluation.h"



// prüft ob array sortiert ist (wenn Element größer als nächstes --> 0)
int checkIfSorted(t_sortdata arr[], long anzahl)
{
    int i;

    // Schleife bis zum vorletzten Element
    for (i = 0; i < anzahl - 1; i++)
    {
        // wenn aktuelles Element größer als das nächste => unsortiert
        if (arr[i] > arr[i + 1])
        {
            return 0;
        }
    }
    // wenn kein Element größer als das nächste => sortiert
    return 1;
}

// prüft alle identisch (wenn ein Wert anders als erster Wert --> 0)
int checkIdentical(t_sortdata arrayD[], long cnt)
{
    // Referenzwert: erstes Element
    t_sortdata v0 = arrayD[0];

    // Schleife: prüft jeden Wert gegen das erste Element
    for (long i = 1; i < cnt; i++)
    {
        if (arrayD[i] != v0)
        {
            return 0;
        }
    }
    // alle Werte gleich => identisch
    return 1;
}

// pivot = arithm. mittel (Durchschnitt aller Array Werte, zum Aufteilen des Arrays für Quicksort)
t_sortdata getPivot(t_sortdata data[], long count)
{
    // temporäre Variable zum Aufsummieren
    double summe = 0.0;

    // Werte zusammenzählen
    for (long i = 0; i < count; i++)
    {
        summe += data[i];
    }
    // Mittelwert zurückgeben
    return summe / count;
}

// Bubblesort
void Bubblesort(t_sortdata Data[], long DataCount)
{
    bool DataChanged;
    do
    {
        DataChanged=false;
        for(long i=0; i<DataCount-1; i++)
        {
            if (Data[i]>Data[i+1])
            {
                // austauschen
                swapdata(&Data[i], &Data[i+1]);
                DataChanged=true;
            }
        }
    }
    while (DataChanged);
}

// Shaker
void ShakerSort(t_sortdata Data[], long DataCount)
{
    // bool, das anzeigt, ob ein Tausch stattfand
    bool changed = true;

    // linke und rechte Grenze
    long start = 0;
    long end = DataCount - 1;

    // Schleife, solange getauscht wurde
    while (changed)
    {
        changed = false;

        // von links nach rechts:
        for (long i = start; i < end; i++)
        {
            if (Data[i] > Data[i + 1])
            {
                swapdata(&Data[i], &Data[i + 1]);
                changed = true;
            }
        }

        // wenn kein Tausch => Feld sortiert, Abbruch
        if (!changed)
        {
            break;
        }

        // letzte Position reduzieren
        end--;
        changed = false;

        // von rechts nach links:
        for (long j = end; j > start; j--)
        {
            if (Data[j - 1] > Data[j])
            {
                swapdata(&Data[j - 1], &Data[j]);
                changed = true;
            }
        }

        // erste Position erhöhen
        start++;
    }
}

// QuickSort
void QuickSort(t_sortdata Data[], long DataCount)
{
    // abbruch bei wenig Elementen
    if (DataCount < 2)
    {
        return;
    }

    // Spezialfall für genau zwei Elemente
    if (DataCount == 2)
    {
        if (Data[0] > Data[1])
        {
            swapdata(&Data[0], &Data[1]);
        }
        return;
    }

    // falls alle identisch, abbrechen:
    if (checkIdentical(Data, DataCount))
    {
        return;
    }

    // linkes und rechtes Ende
    long l = 0;
    long r = DataCount - 1;

    // pivot-Wert errechnen
    t_sortdata pivotWert = getPivot(Data, DataCount);

    // Elemente kleiner als pivot nach links, größere nach rechts schieben
    while (l <= r)
    {
        // linker Zeiger solange verschieben, bis Wert >= pivot
        while (Data[l] < pivotWert)
        {
            l++;
            if (l > r) break;
        }
        // rechter Zeiger solange verschieben, bis Wert < pivot
        while (Data[r] >= pivotWert)
        {
            r--;
            if (l > r) break;
        }

        // falls l<=r => tauschen
        if (l <= r)
        {
            swapdata(&Data[l], &Data[r]);
            l++;
            r--;
        }
    }

    // trenne = Startpunkt für rechten Teil
    long trenne = l;

    // linke Seite sortieren:
    QuickSort(Data, trenne);

    // rechte Seite sortieren:
    if (trenne < DataCount)
    {
        QuickSort(&Data[trenne], DataCount - trenne);
    }
}

// Selectionsort (sucht das kleinste Element ab i und setzt es an i)
void SelectionSort(t_sortdata Data[], long DataCount)
{
    // geht über alle Elemente
    for (long i = 0; i < DataCount - 1; i++)
    {
        // Position mit kleinstem Element (initial: i)
        long minpos = i;

        // ab i+1: kleinstes Element suchen
        for (long j = i + 1; j < DataCount; j++)
        {
            if (Data[j] < Data[minpos])
            {
                minpos = j;
            }
        }

        // falls eine kleinere Position gefunden wurde => tauschen
        if (minpos != i)
        {
            swapdata(&Data[i], &Data[minpos]);
        }
    }
}

// Algomessung
void MeasureAlgorithm(SortAlgorithm TheAlgorithm, long DataAmount, t_timevalue* SortDuration, t_timevalue* SortDurationPresorted)
{
    // 1) Zufallsdaten erzeugen
    t_sortdata* dataTest = generateRandomData(DataAmount);
    if (!dataTest) return;



    // 2) Stoppuhr
    t_stopwatch watch;

    // 3) Messen (unsortiert)
    startStopwatch(&watch);
    TheAlgorithm(dataTest, DataAmount);
    *SortDuration = stopStopwatch(&watch);

    // sortiertes Array ausgeben (100)
    if (DataAmount == 100)
    {
        printf("Sorted array:\n");
        printDataArray(dataTest, DataAmount);
    }

    // 4) Ein Element tauschen => fast sortiert
        swapdata(&dataTest[0], &dataTest[DataAmount - 1]);


    // 5) Erneut messen
    startStopwatch(&watch);
    TheAlgorithm(dataTest, DataAmount);
    *SortDurationPresorted = stopStopwatch(&watch);

    // Speicher freigeben
    free(dataTest);
}

int main()
{
    // Zufallsgenerator
    srand((unsigned)time(NULL));

    long experimentgroessen[] = {
        100, 200, 500, 1000, 2000, 5000, 7000, 10000,
        20000, 30000, 40000, 50000, 60000, 70000
    };

    // Anzahl dieser Datenmengen
    int anzahlVersuche = sizeof(experimentgroessen) / sizeof(long);

    // algos: Liste mit Sortierfunktionen
    SortAlgorithm algoList[] = { Bubblesort, ShakerSort, QuickSort, SelectionSort };


    char algonamen[][20] = { "Bubblesort", "Shakersort", "Quicksort", "Selectionsort" };

    // Anzahl der Algorithmen in der Liste
    int anzahlAlgos = 4;

    // 1. Algorithmus 2. Index der Datenmenge
    static t_timevalue Messung[100][100];
    static t_timevalue Messungfastsortiert[100][100];

    // (äußere Schleife: Datenmengen (100, 200) Innere Schleife: läuft über alle Algorithmen)
    for (int e = 0; e < anzahlVersuche; e++)
    {
        long currSize = experimentgroessen[e];
        printf("Test: %d: Sortiere %ld Elemente...\n", e, currSize);

        for (int a = 0; a < anzahlAlgos; a++)
        {
            printf("   -> %s\n", algonamen[a]);
            MeasureAlgorithm(algoList[a], currSize, &Messung[a][e], &Messungfastsortiert[a][e]);
        }
        printf("\n");
    }

    // Ergebnisdateien erstellen
    FILE* f1 = fopen("Ergebnis_unsortiert.txt", "w");
    FILE* f2 = fopen("Ergebnis_fastsortiert.txt", "w");

    // Überschriften schreiben
    fprintf(f1, "   Samples ");
    fprintf(f2, "   Samples ");
    for (int a = 0; a < anzahlAlgos; a++)
    {

    fprintf(f1, "%13s ", algonamen[a]);
    fprintf(f2, "%13s ", algonamen[a]);
    }
    fprintf(f1, "\n");
    fprintf(f2, "\n");


    // Messdaten in Dateien ausgeben
    for (int e = 0; e < anzahlVersuche; e++)
    {
        long cs = experimentgroessen[e];
    fprintf(f1, "%10ld ", cs);
    fprintf(f2, "%10ld ", cs);

    for (int a = 0; a < anzahlAlgos; a++)
{

    fprintf(f1, "%13I64u ", Messung[a][e]);
    fprintf(f2, "%13I64u ", Messungfastsortiert[a][e]);
}
    fprintf(f1, "\n");
    fprintf(f2, "\n");

    }

    // Dateien schließen
    fclose(f1);
    fclose(f2);

    printf("\nFertig. Output in 'Ergebnis_unsortiert.txt' und 'Ergebnis_vorsortiert.txt'\n");
    return 0;
}
