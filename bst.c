#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/* Helper: aggiorna il puntatore del padre di p su q */
static void update_father(bnode *p, bnode *q) {
    bnode *par = p->parent;
    if (!par) return;
    if (par->left == p) par->left  = q;
    else                par->right = q;
    if (q) q->parent = par;
}

int compare_key(tipo_key a, tipo_key b){
    if(a < b) return -1;
    else if(a > b) return 1;
    else return 0; 
}

bnode *bst_newNode(tipo_key k, tipo_inf i) {
    bnode *n = malloc(sizeof *n);
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
    n->key    = k;
    copy(&n->inf, i);
    n->left   = n->right = n->parent = NULL;
    return n;
}

void bst_insert(bst *b, bnode *n) {
    bnode *y = NULL, *x = *b;
    while (x) {
        y = x;
        if (compare_key(n->key, x->key) < 0)
            x = x->left;
        else
            x = x->right;
    }
    n->parent = y;
    if (!y) {
        *b = n;  // era vuoto
    }
    else if (compare_key(n->key, y->key) < 0) {
        y->left = n;
    } else {
        y->right = n;
    }
}

bnode *bst_search(bst b, tipo_key k) {
    while (b) {
        int cmp = compare_key(k, b->key);
        if (cmp == 0)      return b;
        else if (cmp < 0)  b = b->left;
        else               b = b->right;
    }
    return NULL;
}

void bst_delete(bst *b, bnode *n) {
    bnode *child = NULL;

    /* 1) Caso: uno o zero figli */
    if (!n->left) {
        child = n->right;
    } else if (!n->right) {
        child = n->left;
    } else {
        /* 2) Due figli: trova predecessore (max nel sottoalbero sinistro) */
        bnode *pred = n->left;
        while (pred->right)
            pred = pred->right;
        /* Sposta il suo contenuto in n */
        n->key = pred->key;
        copy(&n->inf, pred->inf);
        /* Adesso eliminiamo pred al suo posto */
        n = pred;
        if (!n->left)
            child = n->right;
        else
            child = n->left;
    }

    /* 3) Ricollega child al padre di n */
    if (child)
        child->parent = n->parent;

    if (!n->parent) {
        *b = child;  // n era la radice
    } else {
        update_father(n, child);
    }

    free(n);
}

void bst_print(bnode *n) {
    if (!n) return;
    printf("Key: ");
    /* supponiamo di voler usare printf per tipo_key */
    printf("%d", n->key);
    printf("  Valore: /* qui stampa tipo_inf come preferisci */\n");
    bst_print(n->left);
    bst_print(n->right);
}

void stampa_bst_inorder(bst t){
    //visita in order
    if(t != NULL){
        stampa_bst_inorder(t->left);
        printf("\n\tcarta numero %d associata a %s Totale punti: %li", 
            t->key, t->inf.nomeCognome, t->inf.totPunti);
        stampa_bst_inorder(t->right);
    }
}
