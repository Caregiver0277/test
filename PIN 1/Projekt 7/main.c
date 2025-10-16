#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Zeitmessung.h"

// Struktur zur Speicherung von Namen und deren H�ufigkeit
struct Namecounter
{
    char* name; // Zeiger auf den Namen
    int frequency; // H�ufigkeit des Namens
};

// Lesen der Namen aus Datei
int readnameDB(FILE* inputfile, struct Namecounter freqnames[], int Max_names)
{
    char buffer[1500]; // Puffer zum Speichern jeder Zeile
    int count = 0; // Z�hler f�r Anzahl der einzigartigen Namen

    // Lesen der Datei Zeile f�r Zeile
    while (fgets(buffer, sizeof(buffer), inputfile))
    {
        int namelen = strlen(buffer); // L�nge des gelesenen Namens
        int existance = 0; // �berpr�fung, ob Name existiert

        // Entfernen Zeilenumbruch am Ende der Zeile
        if (buffer[namelen-1] == '\n')
        {
            buffer[namelen-1] = '\0';
        }

        // �berpr�fung, ob Name bereits in freqnames vorhanden ist
        for (int i = 0; i < count; i++)
        {
            if (strcmp(freqnames[i].name, buffer) == 0)
            {
                freqnames[i].frequency++; // H�ufigkeit erh�hen
                existance = 1; // Name existiert deklarieren
                break;
            }
        }

        // Wenn Name noch nicht existiert, hinzuf�gen
        if (existance == 0)
        {
            freqnames[count].name = malloc((namelen + 1) * sizeof(char)); // Speicher f�r Namen reservieren
            strcpy(freqnames[count].name, buffer); // Namen kopieren
            freqnames[count].frequency = 1; // H�ufigkeit auf 1
            count++; // NamensZ�hler erh�hen
        }
    }
    return count; // R�ckgabe Gesamtanzahl einzigartiger Namen
}

// Funktion zum Sortieren der Namen nach H�ufigkeit
void sortNameDB(struct Namecounter freqnames[], int count)
{
    int F = 1; // Flag f�r das Sortierverfahren

    // Sortier Algorithmus
    while (F == 1)
    {
        F = 0; // Flag zur�cksetzen
        for (int i = 0; i < count - 1; i++)
        {
            // wenn +1 h�her, dann tauschen
            if (freqnames[i].frequency < freqnames[i + 1].frequency)
            {
                // Tauschen der Elemente
                struct Namecounter temp = freqnames[i];
                freqnames[i] = freqnames[i + 1];
                freqnames[i + 1] = temp;
                F = 1; // weiterer Durchlauf
            }
        }
    }
}

// Funktion zum Finden eines Namens in  sortierter Datenbank
int find_Name(char* vorname, struct Namecounter freqnames[], int count)
{
    for (int i = 0; i < count; i++)
    {
        // Vergleich des gesuchten Namens mit vorhandenen Namen
        if (strcmp(freqnames[i].name, vorname) == 0)
        {
            return i; // R�ckgabe Index, wenn der Name gefunden wurde
        }
    }
    return -1; // R�ckgabe -1, wenn der Name nicht gefunden wurde
}

// Hauptfunktion des Programms
int main()
{
    const int Max_names = 500; // Maximale Anzahl Namen
    struct Namecounter freqnames[Max_names]; // Array zur Speicherung der Namen und H�ufigkeiten
    FILE* inputfile = fopen("vornamen.txt", "r");

    int count = 0; // Z�hler f�r die Anzahl der Namen
    if (inputfile != NULL)
    {
        count = readnameDB(inputfile, freqnames, Max_names); // Lesen der Namensdatenbank
        fclose(inputfile); // Schlie�en der Datei
    }

    t_stopwatch sw; // Variable f�r die Stoppuhr
    startStopwatch(&sw); // Starten der Zeitmessung
    sortNameDB(freqnames, count); // Sortieren der Namen
    t_timevalue elapsed = stopStopwatch(&sw); // Beenden der Zeitmessung und Erfassen der verstrichenen Zeit

    // Ausgabe der Sortierzeit in Nanosekunden
    printf("Sortierzeit in Nanosekunden: %I64d\n", (long long unsigned)elapsed);

    char vorname[1500] = {0}; // Puffer f�r die Benutzereingabe des Namens
    printf("Bitte geben Sie Ihren Namen ein: ");
    scanf("%1499s", vorname); // Einlesen des Namens vom Benutzer

    int locindex = find_Name(vorname, freqnames, count); // Suchen des Namens in der Datenbank

    if (locindex >= 0)
    {
        // Ausgabe der Position und H�ufigkeit des gefundenen Namens
        printf("\n%s steht an Stelle %d und ist %d mal vorhanden.\n", vorname, locindex, freqnames[locindex].frequency);
    }
    else
    {
        // Ausgabe, wenn der Name nicht gefunden wurde
        printf("\n%s konnte nicht gefunden werden.\n", vorname);
    }

    return 0; // Programmende
}
