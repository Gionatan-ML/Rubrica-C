#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int n;

typedef struct rubrica{
    char* prefisso;
    char* nome;
    char* cognome;
    char* numero;
    struct rubrica* next;
} rubrica;

// Rinomina la variabile globale
rubrica** rubricaArray;
int compare(char* s1, char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        // Ignora spazi
        if (s1[i] == ' ' || s2[i] == ' ') {
            i++;
            continue;
        }

        // Confronta i caratteri in modo case-insensitive
        int a = toupper(s1[i]);
        int b = toupper(s2[i]);

        if (a > b) {
            return 1;
        } else if (a < b) {
            return -1;
        }

        i++;
    }

    // Se una delle stringhe è terminata
    if (s1[i] == '\0' && s2[i] == '\0') {
        return 0;  // Sono uguali
    } else if (s1[i] == '\0') {
        return -1;  // La prima stringa è più corta
    } else {
        return 1;   // La seconda stringa è più corta
    }
}


void insert(struct rubrica* node){
    bool find=false;
    if(rubricaArray[n]==NULL){
        rubricaArray[n]=node;
        rubricaArray[n]->next=NULL;
    }else{
        int i=1;
        bool find=false;
        struct rubrica* current=rubricaArray[n];
        struct rubrica* prev=NULL;
        while(current!=NULL){
            int cmp=compare(node->nome, current->nome);
            if(cmp<0){
                if(prev==NULL){
                    node->next=current;
                    rubricaArray[n]=node;
                    find=true;
                }else{
                    node->next=current;
                    prev->next=node;
                    find=true;
                }
                break;
            }
            prev=current;
            current=current->next;
        }
        if (find == false) {
            prev->next = node;
            node->next = NULL;
        }
        
    }
}

// Funzione per creare una nuova voce nella rubrica
void create(char* nome, char* cognome, char* numero, char* prefisso){
 
    n = (int)toupper(nome[0]) - 'A';
    
    struct rubrica *tmp = malloc(sizeof(rubrica));
    if(tmp == NULL){
        exit(1);
    }

    // Copia le stringhe in memoria (usa strdup per fare una copia delle stringhe)
    tmp->nome = strdup(nome);
    tmp->cognome = strdup(cognome);
    tmp->numero = strdup(numero);
    tmp->prefisso = strdup(prefisso);
    tmp->next = NULL;
    insert(tmp);


}

// Funzione per liberare la memoria allocata
void free_rubrica() {
    for(int i=0; i<26; i++){
        struct rubrica* tmp;
        tmp=rubricaArray[i];
        while(tmp!=NULL){
            struct rubrica* next=tmp->next;
            free(tmp->nome);
            free(tmp->cognome);
            free(tmp->prefisso);
            free(tmp);
            tmp=next;
        }
    }
    free(rubricaArray);

}

void showRubrica(int num1){
    for(struct rubrica* tmp=rubricaArray[num1]; tmp!=NULL; tmp=tmp->next ){
        printf("\nNome: %s, Cognome: %s, Numero: %s, Prefisso: %s ;", tmp->nome, tmp->cognome, tmp->numero, tmp->prefisso);
    }
}
void printAll(){
    for(int i=0; i<26; i++){
        for(struct rubrica* tmp=rubricaArray[i]; tmp!=NULL; tmp=tmp->next){
            printf("\nNome: %s, Cognome: %s, Numero: %s, Prefisso: %s ;", tmp->nome, tmp->cognome, tmp->numero, tmp->prefisso);
        }
    }
}
void printAllFile(char* string, char* method){
    FILE* stream=fopen(string,method);
    if (stream == NULL) {
        printf("Errore nell'apertura del file %s\n", string);
        exit(1);
    }
    for(int i=0; i<26; i++){
        for(struct rubrica* tmp=rubricaArray[i]; tmp!=NULL; tmp=tmp->next){
            fprintf(stream ,"\nNome: %s; Cognome: %s; Numero: %s; Prefisso: %s ;", tmp->nome, tmp->cognome, tmp->numero, tmp->prefisso);
        }
    }
    fclose(stream);
}

void init(){
    rubricaArray = malloc(sizeof(rubrica*) * 26);
    if(rubricaArray == NULL){
        exit(1);
    }

    // Inizializza tutti i puntatori della rubrica a NULL
    for(int i = 0; i < 26; i++){
        rubricaArray[i] = NULL;
    }
}