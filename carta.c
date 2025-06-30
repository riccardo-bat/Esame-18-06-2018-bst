#include "carta.h"

int compare(tipo_inf a, tipo_inf b){
    //verifico in base al nome e cognome
    int result = strcmp(a.nomeCognome, b.nomeCognome);
    if(result < 0) return -1;
    if(result > 0) return 1; 

    //se hanno lo stesso nome e cognome, verifico i punti 
    if(a.totPunti < b.totPunti) return -1;
    if(a.totPunti > b.totPunti) return 1; 

    //se sia nome e cognome che il totale dei punti sono uguali, allora restituisco 0 
    return 0;
}

void copy(tipo_inf *dest, tipo_inf src){
    *dest = src;
}

void print_tipo_inf(tipo_inf v){
    printf("il cliente %s ha accumulato %li punti", v.nomeCognome, v.totPunti);
}