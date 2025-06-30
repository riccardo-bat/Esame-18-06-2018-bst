#ifndef BST_H
#define BST_H

#include "tipo_inf.h"   /* per tipo_inf */
#include "carta.h"

/* Chiave numerica */
typedef int tipo_key;

/* Nodo dell’albero binario di ricerca */
typedef struct bnode {
    tipo_key      key;
    tipo_inf      inf;
    struct bnode *left;
    struct bnode *right;
    struct bnode *parent;
} bnode;

/* Radice dell’albero */
typedef bnode* bst;

/* --- Prototipi delle funzioni --- */

/**
 * Crea un nuovo nodo con chiave k e valore i.
 * parent/left/right saranno NULL.
 */
bnode*    bst_newNode(tipo_key k, tipo_inf i);

/** Restituisce la chiave del nodo n */
tipo_key  get_key(const bnode *n);

/** Restituisce il valore (tipo_inf) del nodo n */
tipo_inf  get_value(const bnode *n);

/** Restituisce il sottoalbero sinistro di t */
bst       get_left(bst t);

/** Restituisce il sottoalbero destro di t */
bst       get_right(bst t);

/** Restituisce il padre del nodo n */
bnode*    get_parent(const bnode *n);

/**
 * Inserisce il nodo n nell’albero *t.
 * Se la radice cambia, ne aggiorna il puntatore.
 */
void      bst_insert(bst *t, bnode *n);

/** Stampa la chiave k (adattala al tuo tipo_key) */
void      print_key(tipo_key k);

/**
 * Cerca nel BST t il nodo con chiave k.
 * Restituisce il puntatore al nodo o NULL se non trovato.
 */
bnode*    bst_search(bst t, tipo_key k);

/**
 * Elimina il nodo n dall’albero *t.
 * Se rimuove la radice, ne aggiorna il puntatore *t.
 */
void      bst_delete(bst *t, bnode *n);

/**
 * Comparazione di due chiavi (a, b)
 * se a < b return -1
 * se a > b return 1
 * se a = b return 0
 */
int compare_key(tipo_key a, tipo_key b);

/**
 * @brief stampa il bst in ordine crescente di chiavi. Per farlo, utiizzo una vista inorder dell'albero
 * 
 * @param t 
 */
void stampa_bst_inorder(bst t);

#endif /* BST_H */
