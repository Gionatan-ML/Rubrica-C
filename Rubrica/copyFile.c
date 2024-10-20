#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "rubrica.c"



void put(int state, rubrica* tmp, char* valore){
    switch(state){
        case 0:
            tmp->nome = malloc(strlen(valore) + 1);  // Allocare memoria per la stringa
            strcpy(tmp->nome, valore);  // Copiare il valore
            break;
        case 1:
            tmp->cognome = malloc(strlen(valore) + 1);
            strcpy(tmp->cognome, valore);
            break;
        case 2:
            tmp->numero = malloc(strlen(valore) + 1);
            strcpy(tmp->numero, valore);
            break;
        case 3:
            tmp->prefisso = malloc(strlen(valore) + 1);
            strcpy(tmp->prefisso, valore);
            break;
    }
}

int firstCharacter(char* string){
    for(int i=0; i<strlen(string); i++){
        if(!isspace(string[i])){
            int num1=(int)(toupper(string[i])) - 65;
            return num1;
        }
    }
}

void copyFromFile(char* string){
    bool find=false;
    FILE* stream=fopen(string, "r");
    char chr;
    int i=0;
    bool isTrue=false;
    int state=0;
    struct rubrica* tmp=malloc(sizeof(rubrica));
    if(tmp==NULL){
        free(rubricaArray);
        fclose(stream);
        exit(0);
    }
    char* controll=malloc(sizeof(char)*50);
    while((chr=fgetc(stream))!=EOF){
        if(isspace(chr)&&isTrue==true){
            continue;
        }
        if(chr==':'){
            find=true;
            continue;
        }
        isTrue=false;
        if((chr==';')){
            if(i==0){
                controll[0]=' ';
                controll[i+1]='\0';
            }else{
                controll[i]='\0';
            }
            char* valore=calloc((i+1), sizeof(char));
            memcpy(valore,controll, (i+1) * sizeof(char));
            put(state, tmp, valore);
            state++;
            find=false;

            if(state==4){
                state=0;
                n=firstCharacter(tmp->nome);
                insert(tmp);
                tmp=malloc(sizeof(rubrica));
                isTrue=true;

            }

            free(valore); // Libera memoria di "nome"
            i=0;
        }else{
            if(chr!=';' && find==true){
                controll[i]=chr;
                i++;
            }

        }
    }
    free(controll);
    fclose(stream);

}