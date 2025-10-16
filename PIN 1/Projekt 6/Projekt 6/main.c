#include <stdio.h>
#include <string.h>

void decrypt(char valuetext, char valuekey, char* decrypted_char)
{
    if (valuetext < 32)
    {
        // Steuerzeichen unverändert lassen
        *decrypted_char = valuetext;
    }
    else
    {
        *decrypted_char = (valuetext & 0xF0) | ((valuetext & 0x0F) ^ (valuekey & 0x0F));
    }
}

void decrypt_file(const char* key)
{

    FILE* infile = fopen("geheim.txt", "r");
    FILE* outfile = fopen("entschluesselt.txt", "w");

    char line[100];
    int key_len = strlen(key);

    while (fgets(line, sizeof(line), infile))  // Liest die Eingabedatei zeilenweise
    {
        int line_len = strlen(line);
        char decrypted_line[100];


        // Zeile entschlüsseln
        for (int i = 0; i < line_len; i++)
        {
            decrypt(line[i], key[i % key_len], &decrypted_line[i]);
        }

        // Entschlüsselte Zeile in die Ausgabedatei schreiben
        fwrite(decrypted_line, 1, line_len, outfile);
    }

    fclose(infile); // Dateien schließen
    fclose(outfile);
}

int main()
{

    const char* key = "Erdbeermilch";

    decrypt_file(key);

    return 0;
}
