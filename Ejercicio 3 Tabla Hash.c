#include<stdio.h>
#include<stdlib.h>

#define MAX 10

typedef struct nodo{
    int dato;
    struct nodo *ant;
    struct nodo *sig;
}*NODO;

void insertar(NODO *, int);
void verTabla(NODO *);
int fHash(int);

int main(){
    NODO *lista = calloc(MAX, sizeof(NODO));
    int arr[] = {10, 15, 20, 13, 2,-1};

    int i;
    for(i=0; arr[i]!=-1; i++)
        insertar(lista, arr[i]);

    verTabla(lista);
    return 0;
}

int fHash(int key){
    return key % MAX;
}

void insertar(NODO *l, int dato){
    int pos = fHash(dato);
    NODO lista = l[pos];

    NODO nuevo = calloc(1, sizeof(struct nodo));
    nuevo->dato = dato;
    nuevo->sig = lista;
    nuevo->ant = NULL;
    if (lista != NULL) {
        lista->ant = nuevo;
    }
    l[pos] = nuevo;
}



void verTabla(NODO *t){
    int i;
    NODO *aux = t;
    NODO rec;
    printf("\n");
    for(i=0; i<MAX; i++){
        if(*aux != NULL){
            printf("\n");
            rec = *aux;
            while(rec != NULL){
                printf("%d ", rec->dato);
                rec = rec->sig;  // Agregar esta línea para avanzar al siguiente nodo
            }
        }
        else{
            printf("NULL\n");
        }
        aux++;
    }
}
