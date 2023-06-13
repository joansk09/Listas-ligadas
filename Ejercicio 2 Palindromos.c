#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    char dato;
    struct nodo *ant;
    struct nodo *sig;
}*NODO;

NODO hallarFinal(NODO);
void insertarInicio(NODO *, char);
void insertarFinal(NODO *, char);
void insertarEnOrden(NODO *, char);
int eliminarInicio(NODO *);
int eliminarFinal(NODO *);
void verLista(NODO);
void verListaInverso(NODO);

int espalindromo(NODO *);

int main(){
    NODO lista = NULL;
    char *texto = calloc(32, sizeof(char));

    int i;
    printf("\nDigite una palabra: \n--> ");
    fgets(texto, 32, stdin);

    for(i=0; texto[i]!='\n'; i++)
        insertarFinal(&lista, texto[i]);

    if(espalindromo(&lista)){
        printf("\nLa palabra %s es palindroma", texto);
    }
    else{
        printf("\nLa palabra %s NO ES palindroma", texto);
    }


    verLista(lista);
    verListaInverso(lista);
    return 0;
}

NODO hallarFinal(NODO nodo){
    if(nodo->sig == NULL){
        return nodo;
    }
    return hallarFinal(nodo->sig);
}

void insertarInicio(NODO *l, char dato){
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
void insertarFinal(NODO *l, char dato){
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

void insertarEnOrden(NODO *l, char dato){
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
    char dato;
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
    char dato;
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
            printf("[Ant: %p | Dir: %p |Sig: %p | Dato: %d ] \n", aux->ant, aux, aux->sig, aux->dato);
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

int espalindromo(NODO *lista){
    NODO ini = *lista, fin = hallarFinal(*lista);
    while(ini!=NULL){
        if(ini->dato != fin->dato){
            return 0;
        }
        ini = ini->sig;
        fin = fin->ant;
        if(ini==fin)break;
    }
    return 1;
}
