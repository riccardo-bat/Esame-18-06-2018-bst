#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tipo_inf.h"
#include "carta.h"
#include "bst.h"

//prototipi
long int int_input(char* msg, int minimum_value);
void string_input(char* msg, char* dest);
void richiediCarta(bst* bst_carte);
long int totalePunti(bst t, int inf, int sup); 
void scambia(tipo_key *a, tipo_key *b);
void aggiorna(bst t, tipo_key numeroCarta, long int puntiAccumulati);
bool rec_aggiorna(bst t, tipo_key numeroCarta, long int puntiAccumulati);

int main(){
    //punto 1
    long int num_carte = int_input("\nNumero delle carte da inserire: ", 1);
    bst bst_carte = NULL;

    for(int i=0; i<num_carte; i++){
        printf("\nCARTA [%d]\n", i+1);
        richiediCarta(&bst_carte);
    }

    //punto 2
    //stampo tutte le carte fedeltà in ordine crescente delle chiavi 
    stampa_bst_inorder(bst_carte);


    //punto 3
    printf("\n------------------------------------------------");
    char buffer[MAX_LENGTH_NAMESURNAME]; 

    do{
        string_input("\nSi vogliono eseguire degli acquisti? (inserire Q/q per non aggiungere acquisti): ", buffer);
        
        if(buffer[0] != 'Q' && buffer[0] != 'q'){
            //inserisco un acquisto
            tipo_key chiave = int_input("\n\t-Chiave acquisto: ", 1000);
            long int puntiAccumulati = int_input("\t-Punti accumulati: ", 0);

            aggiorna(bst_carte, chiave, puntiAccumulati);
            printf("\n");
            stampa_bst_inorder(bst_carte);
            printf("\n");
        }

    } while(buffer[0] != 'Q' && buffer[0] != 'q');


    //punto 2.b
    printf("\n------------------------------------------------");
    tipo_key inf = int_input("\n\n\nEstremo inferiore: ", 1000);
    tipo_key sup = int_input("\nEstremo superiore: ", 1000);

    if(inf > sup){
        printf("\nValori dei due estremi scambiati\n");
        scambia(&inf, &sup);
    }

    printf("\nIl numero totale di punti delle carte comprese tra %d e %d = %li", inf, sup, totalePunti(bst_carte, inf, sup));



    return 0;
}

long int int_input(char* msg, int minimum_value){
    char buffer[100];
    printf("%s", msg);

    while(!fgets(buffer, 100, stdin)){
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

    while(!fgets(buffer, MAX_LENGTH_NAMESURNAME-1, stdin)){
        printf("\nInput non valido");
        printf("%s", msg);
    }

    //elimino il carattere \n
    buffer[strcspn(buffer, "\n")]= '\0'; 
    //printf("\n\nBUFFER: %s", buffer);

    strcpy(dest, buffer);
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
    
    //printf("Name inserito = %s, cognome = %s", name, surname);

    strcpy(node_to_insert.nomeCognome, strcat(name, " "));
    strcpy(node_to_insert.nomeCognome, strcat(node_to_insert.nomeCognome, surname)); 

    //acquisisco il totale dei punti
    node_to_insert.totPunti = int_input("\t- Totale dei punti della carta: ", 0); 

    //printf("\nNome e cognome: %s", node_to_insert.nomeCognome);

    bst_insert(bst_carte, bst_newNode(key, node_to_insert));
}

/**
 * @brief restituisce la somma dei punti delle carte | inf <= key-carta <= sup
 * 
 * @param t 
 * @param inf 
 * @param sup 
 * @return long int 
 */
long int totalePunti(bst t, int inf, int sup){
    //scorro tutto l'albero tramite una inorder, in modo da evitare di visulizzare parti di albero in cui so che non ci sono più carte comprese tra inf e sup
    //caso base --> albero vuoto
    if(t == NULL) return 0; 

    //caso ricorsivo
    if(inf <= t->key && t->key <= sup)
        return t->inf.totPunti + totalePunti(t->left, inf, sup) + totalePunti(t->right, inf, sup);
    return totalePunti(t->left, inf, sup) + totalePunti(t->right, inf, sup);
}

void scambia(tipo_key* a, tipo_key *b){
    tipo_key temp = *a; 
    *a = *b; 
    *b = temp;
}

void aggiorna(bst t, tipo_key numeroCarta, long int puntiAccumulati){
    bool esito = rec_aggiorna(t, numeroCarta, puntiAccumulati);
    //segnalo errore se la carta non esiste
    if(!esito){
        printf("\nErrore: la carta %d non esiste", numeroCarta);
    }
}

bool rec_aggiorna(bst t, tipo_key numeroCarta, long int puntiAccumulati){
    //scorro il bst 
    //caso base --> albero vuoto
    if(t == NULL) return false; 

    //se il nodo corrente corrisponde al numero della carta, effettuo gli aggiornamenti
    if(t->key == numeroCarta){
        t->inf.totPunti += puntiAccumulati; 
        return true; //ho effettuato l'aggiornamento
    }

    //in base al valore della chiave mi sposto a sx o a dx (E' UN BST)
    if(numeroCarta < t->key) //se sto cercando un numero < t->key, mi devo spostare alla sua sx
        return rec_aggiorna(t->left, numeroCarta, puntiAccumulati);
    else 
        return rec_aggiorna(t->right, numeroCarta, puntiAccumulati);

}