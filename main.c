#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// structures

typedef struct
{
    char patente[6];
    int valor;
    char marca[10];
} automovil;

typedef struct nodoAuto
{
    automovil dato;
    struct nodoAuto* sig;
} nodoAuto;

/// funciones

automovil cargarAuto ()
{
    automovil aux;
    printf("\nINGRESE PATENTE: ");
    fflush(stdin);
    scanf("%s", aux.patente);
    printf("\nINGRESE VALOR: ");
    scanf("%i", &aux.valor);
    printf("\nINGRESE MARCA: ");
    fflush(stdin);
    scanf("%s", aux.marca);
    return aux;
}

void mostrarAuto (automovil aux)
{
    printf("\nMARCA: %s", aux.marca);
    printf("\nVALOR: %i", aux.valor);
    printf("\nPATENTE: %s", aux.patente);
}

void mostrarArreglo (automovil arr[], int dim)
{
    for (int i = 0; i < dim; i++)
        mostrarAuto(arr[i]);
}

void inicLista (nodoAuto** lista)
{
    *lista = NULL;
}

nodoAuto* crearNodo (automovil dato)
{
    nodoAuto* aux = (nodoAuto*)malloc(sizeof(nodoAuto));
    aux->dato = dato;
    aux->sig = NULL;
    return aux;
}

void agregarAlFinal (nodoAuto** lista, nodoAuto* nuevo)
{
    if (*lista)
    {
        nodoAuto* aux = *lista;

        while (aux->sig)
            aux = aux->sig;

        aux->sig = nuevo;
    }
    else
        *lista = nuevo;
}

void agregarMuchos (nodoAuto** lista)
{
    char seguir = 's';

    while (seguir == 's')
    {
        agregarAlFinal(lista, crearNodo(cargarAuto()));
        printf("\nDesea seguir ? s/n\n");
        fflush(stdin);
        scanf("%c", &seguir);
    }
}

void mostrarArregloRecursivo (automovil arr[], int i, int dim)
{
    if (i < dim)
    {
        mostrarAuto(arr[i]);
        mostrarArregloRecursivo(arr, ++i, dim);
    }
}

int retValorPatsPares (nodoAuto* lista)
{
    if (lista)
    {
        if (strtol(&lista->dato.patente[5], NULL, 10) % 2 == 0)
        {
            return lista->dato.valor + retValorPatsPares(lista->sig);
        }
        else
            return retValorPatsPares(lista->sig);
    }
    else
        return 0;
}

int insertarAutoEnOrden (automovil arr[], int dim, automovil nuevo, int validos)
{
    int ultPos = dim-1;

    while (ultPos >= 0 && arr[ultPos].valor > nuevo.valor)
    {
        arr[ultPos+1] = arr[ultPos];
        ultPos--;
    }

    arr[ultPos+1] = nuevo;

    return validos+1;
}

void pasar (nodoAuto* lista, automovil arr[], int* dim)
{
    while (lista)
    {
        *dim = insertarAutoEnOrden(arr, *dim, lista->dato, *dim);
        lista = lista->sig;
    }
}

/// main

int main()
{
    //automovil arregloAutos[10];
    //int dim = 0;

    nodoAuto* lista;
    inicLista(&lista);

    agregarMuchos(&lista);

    //pasar(lista, arregloAutos, &dim);

    //mostrarArregloRecursivo(arregloAutos, 0, dim);

    printf("\n\nSUMA: %i", retValorPatsPares(lista));

    return 0;
}
