#ifndef CARTA_H
#define CARTA_H

#include "tipo_inf.h"  /* Assicurati che qui sia definito tipo_inf */
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Confronta due tipo_inf:
 *  - restituisce 0 se sono uguali
 *  - <0 se a < b
 *  - >0 se a > b
 */
int compare(tipo_inf a, tipo_inf b);

/**
 * Copia il contenuto di src in *dest.
 */
void copy(tipo_inf *dest, tipo_inf src);

/**
 * Stampa a video il contenuto di v (adatta il formato secondo i campi di tipo_inf).
 */
void print_tipo_inf(tipo_inf v);

#endif /* CARTA_H */
