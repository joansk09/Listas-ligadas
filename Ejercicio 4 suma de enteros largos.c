#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct nodo{
    int dato;
    struct nodo *ant;
    struct nodo *sig;
}*NODO;

NODO hallarFinal(NODO);
void insertarInicio(NODO *, int);
void insertarFinal(NODO *, int);
void insertarEnOrden(NODO *, int);
int eliminarInicio(NODO *);
int eliminarFinal(NODO *);
void verLista(NODO);
void verListaInverso(NODO);

int main(){
    NODO lista1 = NULL;
    NODO lista2 = NULL;
    NODO r = NULL;
    char *cad1 = (char *) calloc(32, sizeof(char));
    char *cad2 = (char *) calloc(32, sizeof(char));
    int i, acarreo = 0;

    printf("\nDigite el primer numero: \n--> ");
    gets(cad1);
    fflush(stdin);
    printf("\nDigite el segundo numero: \n--> ");
    gets(cad2);

    for(i=0; cad1[i]!='\0'; i++) insertarFinal(&lista1, cad1[i]-'0');
    for(i=0; cad2[i]!='\0'; i++) insertarFinal(&lista2, cad2[i]-'0');

    NODO n1 = hallarFinal(lista1);
    NODO n2 = hallarFinal(lista2);
    NODO aux;
    if(strlen(cad2) > strlen(cad1)){
        aux = n1;
        n1 = n2;
        n2 = aux;
    }

    while(n2 != NULL){
        if(n2->dato + n1->dato + acarreo >= 10){
            insertarInicio(&r, n1->dato + n2->dato + acarreo - 10);
            acarreo = 1;
        }
        else{
            insertarInicio(&r, n1->dato + n2->dato + acarreo);
            acarreo = 0;
        }
        n2 = n2->ant;
        n1 = n1->ant;
    }
    while(n1 != NULL){
        if(acarreo + n1->dato >= 10){
            insertarInicio(&r, n1->dato + acarreo - 10);
            acarreo = 1;
        }
        else{
            insertarInicio(&r, n1->dato + acarreo);
            acarreo = 0;
        }
        n1 = n1->ant;
    }
    if(acarreo > 0){
        insertarInicio(&r, acarreo);
    }
    printf("Numero 1: \n");
    verLista(lista1);
    printf("\nNumero 2: \n");
    verLista(lista2);

    printf("\nEl resultado es: ");
    verLista(r);
    verListaInverso(r);

    free(cad1);
    free(cad2);

    return 0;
}

NODO hallarFinal(NODO nodo){
    NODO aux = nodo;
    while(aux->sig != NULL){
        aux = aux->sig;
    }
    return aux;
}

void insertarInicio(NODO *l, int dato){
    NODO nuevo = calloc(1, sizeof(struct nodo));
    nuevo->dato = dato;
    if(*l == NULL){
        *l = nuevo;
    }
    else{
        nuevo->sig = *l;
        (*l)->ant = nuevo;
        *l = nuevo;
    }
}
void insertarFinal(NODO *l, int dato){
    NODO nuevo = calloc(1, sizeof(struct nodo));
    nuevo->dato = dato;

    if(*l == NULL){
        *l = nuevo;
    }
    else{
        NODO ultimo = hallarFinal(*l);
        ultimo->sig = nuevo;
        nuevo->ant = ultimo;
    }
}

void insertarEnOrden(NODO *l, int dato){
    NODO nuevo = calloc(1, sizeof(struct nodo));
    nuevo->dato = dato;
    NODO aux = *l;
    NODO anterior = NULL;
    NODO siguiente;
    printf("Direccion de nodo %d : %p\n", nuevo->dato, nuevo);
    if(*l == NULL){
        *l = nuevo;
    }
    else{
        while(aux != NULL && dato < aux->dato){
            anterior = aux;
            aux = aux->sig;
            if(aux==NULL)break;
        }
        if(aux == *l){ //Va en el primer nodo
            nuevo->sig = *l;
            (*l)->ant = nuevo;
            *l = nuevo;
        }
        else if(aux == NULL){ //Va al ultimo
            nuevo->ant = anterior;
            anterior->sig = nuevo;
        }
        else{
            nuevo->sig = aux;
            nuevo->ant = anterior;
            anterior->sig = nuevo;
            aux->ant = nuevo;
        }
    }
}

int eliminarInicio(NODO *l){
    NODO aux = *l;
    int dato;
    if(aux != NULL){
        dato = aux->dato;
        *l = (*l)->sig;
        if(*l == NULL){ //Es el unico nodo ahora
            free(aux);
            return dato;
        }
        (*l)->ant = NULL;
        free(aux);
        return dato;
    }
    else{
        printf("\nLista vacia\n");
        return -1;
    }
}

int eliminarFinal(NODO *l){
    NODO fin = *l;
    NODO penultimo;
    int dato;
    if(*l != NULL){
        dato = fin->dato;
        fin = hallarFinal(*l);
        if(fin->ant == NULL){ //Es el primero
            free(fin);
            *l = NULL;
            return dato;
        }
        penultimo = fin->ant;
        penultimo->sig = NULL;
        free(fin);
        return dato;
    }
    else{
        printf("\nLista vacia");
        return -1;
    }
}

void verLista(NODO l){
    NODO aux = l;
    if(l!=NULL){
        printf("\nRecorrido: ");
        while(aux != NULL){
            printf("%d", aux->dato);
            aux = aux->sig;
        }
        printf("\n");
    }
}

void verListaInverso(NODO l){
    NODO ult;
    if(l != NULL){
        ult = hallarFinal(l);
        printf("\nRecorrido Inverso: ");
        while(ult != NULL){
            printf("%d ", ult->dato);
            ult = ult->ant;
        }
        printf("\n");
    }
    else{
        printf("\nLista vacia");
        return;
    }
}
