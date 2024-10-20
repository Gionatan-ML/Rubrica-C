#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>  // Aggiungi per usare strcmp
#include "copyFile.c"  // Assicurati che il file header sia corretto

int main(void) {
    init();  // Inizializza la rubrica
    bool finish = false, equal = false;
    FILE* stream;
    char* valori[4];  // Per nome, cognome, numero, prefisso
    char choose;
    char s[40];  // Stringa per il nome del file
    char s1[40];  // Stringa per il file su cui lavorare

    // Allocazione memoria per i campi
    for (int i = 0; i < 4; i++) {
        valori[i] = malloc(50 * sizeof(char));  // Allocazione di 50 caratteri per ogni campo
        if (valori[i] == NULL) {
            printf("Errore di allocazione memoria.\n");
            exit(1);
        }
    }

    // Lettura del file database
    printf("\nInserisci il file da aprire come database: ");
    scanf("%39s", s);  // Limita la lettura a 39 caratteri per evitare buffer overflow
    printf("\nIn che file vuoi lavorare?: ");
    scanf("%39s", s1);

    // Confronto dei nomi di file
    if (strcmp(s1, s) == 0) {
        equal = true;
        copyFromFile(s);  // Copia i dati dal file di database
    } else {
        copyFromFile(s);  // Copia i dati dal file di database
    }

    // Ciclo per l'inserimento di nuove persone
    do {
        printf("\nVuoi aggiungere una persona in rubrica? [y,n]: ");
        scanf(" %c", &choose);  // Aggiungi uno spazio prima di %c per ignorare caratteri di spazio

        if (choose == 'y') {
            finish = false;
            printf("\nScrivi il nome: ");
            scanf("%49s", valori[0]);  // Limita la lunghezza delle stringhe per evitare buffer overflow
            printf("\nScrivi il cognome: ");
            scanf("%49s", valori[1]);
            printf("\nScrivi il numero: ");
            scanf("%49s", valori[2]);
            printf("\nScrivi il prefisso: ");
            scanf("%49s", valori[3]);
            create(valori[0], valori[1], valori[2], valori[3]);  // Inserisce la nuova voce
            printf("\nContatto creato correttamente!");
            printAll();
        } else {
            finish = true;
        }
    } while (finish == false);
    char chr;
    // Scrittura dei dati sul file scelto
    if (equal == true) {
        printAllFile(s,"w");  // Scrive i dati sullo stesso file
    } else {
        printAllFile(s1,"w");
        printf("\nVuoi aggiornare il Database? [y,n]: ");
        scanf(" %c", &chr);

        // Se l'utente vuole aggiornare il database
        if(chr == 'y'){
            printAllFile(s,"w");
            printAll();
        }
    }
    printf("\nVuoi vedere la rubrica completa? [y,n]: ");
    scanf(" %c", &chr);

    // Mostra la rubrica se l'utente sceglie 'y'
    if(chr == 'y'){
        
        printAll();
    }

    free_rubrica();  // Libera la rubrica alla fine

    return 0;
}
