#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/*
--------------Tree search-------------
Descripcion:Para esta busqueda usamos las propiedades de un arbol binario de busqueda
            estructura que ya vimos en la practica pasada, simplemente lo que hacemos es checar si el elemento de 
            la raiz es mas grande o mas chico, y con base en esto decidimos hacia donde irnos. Pues sabemos que con
            base a esto esta construida esta estructura.
Fecha: 27/09/2021
Versión: Final
Autor: Suarez Elizalde Jose Juan
*/



//------------------ARBOL-------------------------------------
//Implementacion de nuestro arbol binario de busqueda

//Esta es nuestra estructura de un nodo de un arbol
//para mas comodida redefinidmo struct Nodo* como ABB
typedef struct Nodo {
    int numero;
    struct Nodo* izq, * der;
}*ABB;

//Aqui creamos un nuevo nodo cuando es necesario
//asignamos el espacio de memoria, el numero y sus hijos nulos
//se recibe un el numero a insertar
ABB nuevoNodo(int elem) {
    ABB nuevo = (ABB)malloc(sizeof(struct Nodo));
    nuevo->numero = elem;
    nuevo->der = nuevo->izq = NULL;
    return nuevo;
}

//Recibimos un ABB, regresamos si el nodo es nulo
int esVacio(ABB a) {
    return a == NULL;
}

//Recibimos un ABB, regresamos el valor numerico de la raiz
int raiz(ABB a) {
    return a->numero;
}

//En esta busqueda auxiliar, lo que hacemos es recibir el elemento a buscar y el ABB
//encontrarmos la posicion en la que esta, o el padre de donde deberia estar este numero
// regresamos ese nodo y esto nos sirve tanto para insertar un nodo como para buscar, de esta forma
//reutilizamos codigo.
ABB busquedaAux(int elem, ABB a) {
    if (esVacio(a)) {
        return NULL;
    }
    ABB aux = a;
    while (1) {
        if(raiz(aux) == elem){
            return aux;
        } else if (raiz(aux) > elem) {
            if (esVacio(aux->izq)) {
                break;
            } else {
                aux = aux->izq;
            }
        } else {
            if (esVacio(aux->der)) {
                break;
            } else {
                aux = aux->der;
            }
        }
    }
    return aux;
}

bool busca(int n, ABB tree) {
    return n == busquedaAux(n, tree)->numero;
}

//Recibimos el nodo que nos da la busquedaAuxiliar, 
ABB insertar(int elem, ABB a) {
    ABB aux = busquedaAux(elem, a);
    if (esVacio(aux)) {
        return nuevoNodo(elem);
    } else if (aux->numero == elem) {
        return a;
    } else if (aux->numero < elem) {
        aux->der = nuevoNodo(elem);
    } else {
        aux->izq = nuevoNodo(elem);
    }
    return a;
}

// Fin de la implementacion
//------------------ARBOL-------------------------------------

int* arreglo;

//Insertamos un arreglo completo a un arbol, recibimos su tamaño
ABB insertarArregloEnArbol(int n) {
    ABB arbol = insertar(arreglo[0], NULL);
    for (int i = 1; i < n; i++) {
        insertar(arreglo[i], arbol);
    }
    return arbol;
}
//recibimos el tamaño del arreglo y leemos esa cantidad de datos que guardamos en el arreglo
void leerArreglo(int n) {
    for (int i = 0;i < n;i++) {
        scanf("%d",&arreglo[i]);
    }
}


int main(int argc, char* argv[]) {
    int numeroDeNumeros, i, numeroABuscar;

    numeroDeNumeros = atoi(argv[1]);
    numeroABuscar = atoi(argv[2]);

    arreglo = (int*)malloc(sizeof(int) * numeroDeNumeros);

    leerArreglo(numeroDeNumeros);

    ABB arbol = insertarArregloEnArbol(numeroDeNumeros);

    bool esta = busca(numeroABuscar, arbol);

    printf("%d\n", esta);

    return 0;
}
