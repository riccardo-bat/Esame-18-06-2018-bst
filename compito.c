#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipo_inf.h"
#include "carta.h"
#include "bst.h"

//prototipi
long int int_input(char* msg, int minimum_value);
void string_input(char* msg, char* dest);
void richiediCarta(bst* bst_carte);

int main(){
    long int num_carte = int_input("\nNumero delle carte da inserire: ", 1);
    bst bst_carte = NULL;

    for(int i=0; i<num_carte; i++){
        printf("\nCARTA [%d]\n", i+1);
        richiediCarta(&bst_carte);
    }



    return 0;
}

long int int_input(char* msg, int minimum_value){
    char buffer[100];
    printf("%s", msg);

    while(fgets(buffer, 100, stdin) == NULL){
        printf("\nInput non valido\n");
    }

    //ora effettuo dei controlli per controllare di aver acquisito dei dati validi
    char* endptr = NULL;
    int base = 10; 
    long int n = strtol(buffer, &endptr, base);

    //se endptr = buffer vuol dire che non è stato convertito alcun carattere in intero
    if(endptr == buffer){
        printf("\t- Errore nell'acquisizione dell'input\n");
        return int_input(msg, minimum_value);
    }

    //ora che n è stato convertito correttamente, controllo che i suoi valori siano nei range
    if(n < minimum_value){
        printf("\t- Errore nell'acquisizione dell'input\n");
        return int_input(msg, minimum_value);
    }

    return n;
}

void string_input(char* msg, char* dest){
    char buffer[MAX_LENGTH_NAMESURNAME];
    printf("%s", msg);

    while(fgets(buffer, MAX_LENGTH_NAMESURNAME-1, stdin) == NULL){
        printf("\nInput non valido");
        printf("%s", msg);
    }

    //elimino il carattere \n
    buffer[strcspn(buffer, "\n")]= '\0'; 
    //printf("\n\nBUFFER: %s", buffer);

    strcpy(dest, dest);
}

/**
 * @brief richiesta dei dati di una singola carta 
 * 
 * @param bst_carte 
 */

void richiediCarta(bst* bst_carte){
    tipo_inf node_to_insert;
    char name[MAX_LENGTH_NAMESURNAME];
    char surname[MAX_LENGTH_NAMESURNAME];

    //acquisisco la chiave della carta fedeltà (chiave del bst)
    tipo_key key = int_input("\t- Chiave carta fedelta': ", 1000);

    //acquisisco nome e cognome
    string_input("\t- Nome del cliente: ", name);
    string_input("\t- Cognome del cliente: ", surname);

    //printf("Name inserito = %s, cognome = %s", name, surname);
    while((strlen(name) + 1 + strlen(surname)) > 40 ){ //+1 per considerare lo spazio
        printf("\n\t- Errore: nome e cognome troppo lunghi");
        string_input("\t- Nome del cliente: ", name);
        string_input("\t- Cognome del cliente: ", surname);
    }

    strcpy(node_to_insert.nomeCognome, strcat(name, " "));
    strcpy(node_to_insert.nomeCognome, strcat(node_to_insert.nomeCognome, surname)); 

    //acquisisco il totale dei punti
    node_to_insert.totPunti = int_input("\n\t- Totale dei punti della carta: ", 0); 

    bst_insert(bst_carte, bst_newNode(key, node_to_insert));
}
