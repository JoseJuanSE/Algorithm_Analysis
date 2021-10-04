#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <pthread.h>
#include <string.h>

int esta;

//------------------ARBOL-------------------------------------
//Implementacion de nuestro arbol binario de busqueda

//Esta es nuestra estructura de un nodo de un arbol
//para mas comodida redefinidmo struct Nodo* como ABB
typedef struct Nodo {
    int numero;
    struct Nodo* izq, * der;
}*ABB;

ABB arboles[4];

//Aqui creamos un nuevo nodo cuando es necesario
//asignamos el espacio de memoria, el numero y sus hijos nulos
//se recibe un el numero a insertar
ABB nuevoNodo(int elem) {
    ABB nuevo = (ABB)malloc(sizeof(struct Nodo));
    nuevo->numero = elem;
    nuevo->der = nuevo->izq = NULL;
    return nuevo;
}

//regresamos si el nodo es nulo
int esVacio(ABB a) {
    return a == NULL;
}

//regresamos el valor numerico de la raiz
int raiz(ABB a) {
    return a->numero;
}

//Insertamos en elemento a un arbol binario en la posicion que debe ir
//Observamos que para iniciar el arbol binario es necesario
//ABB nuevo = insertar(numero, NULL);
//Posteriormente para insertar cualquier valor solo es necesario
//insertar(numero, nuevo);

ABB busquedaAux(int elem, ABB a) {
    ABB aux = a;
    while (aux != NULL) {
        if (elem > raiz(aux)) {
            if (esVacio(aux->der)) {
                break;
            } else {
                aux = aux->der;
            }
        } else if (raiz(aux) > elem) {
            if (esVacio(aux->izq)) {
                break;
            } else {
                aux = aux->izq;
            }
        } else {
            return aux;
        }
    }
    return aux;
}

ABB insertar(int elem, ABB a) {
    ABB aux = busquedaAux(elem, a);
    if (esVacio(aux)) {
        return nuevoNodo(elem);
    } else if (raiz(aux) > elem){
        aux->izq = nuevoNodo(elem);
    } else if (raiz(aux) < elem) {
        aux->der = nuevoNodo(elem);
    } 
    return a;
}

void* busca(void* es) {
    if (!esta) {
        int* aux = (int*)es;
        esta = esta || aux[1] == busquedaAux(aux[1], arboles[aux[0]])->numero;
    }
    pthread_exit(NULL);
}

void inorder(ABB a) {
    if (!esVacio(a)) {
        inorder(a->izq);
        printf("%d  ", a->numero);
        inorder(a->der);
    }
}

// Fin de la implementacion
//------------------ARBOL-------------------------------------

void leerArreglo(int n, int* arreglo) {
    for (int i = 0;i < n; i++) {
        scanf("%d", &arreglo[i]);
    }
}


int main(int argc, char* argv[]) {
    int numeroDeNumeros, * arreglo;

    numeroDeNumeros = atoi(argv[1]);

    arreglo = (int*)malloc(sizeof(int) * numeroDeNumeros);

    leerArreglo(numeroDeNumeros, arreglo);

    int numeros[] = {322486, 14700764, 3128036, 6337399, 61396,
10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503,
5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666 , 2147470852, 0};

    // partimos el arreglo en 4 ya que la mayoria de procesadores actuales
    //tiene 4 hilos, sin embargo esto incluso lo podemos generalizar para n hilos, y podriamos
    //pasar n como parametro de forma muy sencilla
    pthread_t hilo[4];
    int estado[4][2] = {{0, numeroDeNumeros/4-1},
                        {numeroDeNumeros/4 , numeroDeNumeros/2-1},
                        {numeroDeNumeros/2, 3*numeroDeNumeros/4-1},
                        {3*numeroDeNumeros/4, numeroDeNumeros-1}};

    //guardamos los segmentos de arreglo deseados en rango
    for(int i=0; i<4; i++) {
        arboles[i] = NULL;
        for(int j=estado[i][0]; j<=estado[i][1]; j++) {
            arboles[i] = insertar(arreglo[j], arboles[i]);
        }
    }
    //empezamos a tomar tiempo
    for(int i=0;i<20;i++) {
        esta = 0;
        int numeroABuscar = numeros[i];
        int a[4][2] = {{0, numeroABuscar}
                ,{1, numeroABuscar}
                ,{2, numeroABuscar}
                ,{3, numeroABuscar}};
        //creamos cada hilo y le asignamos su rango determinado
        for(int j=0; j<4; j++) {
            if (pthread_create(&hilo[j], NULL, busca, (void *)a[j])) {
                perror("Error creando hilo");
                exit(1);
            }
        }

        //llamamos cadahilo a hacer su trabajo
        for(int j = 0; j<4; j++) {
            pthread_join(hilo[j], NULL);
        }

        printf("el numero: %d con %d numeros -> %d\n", numeroABuscar, numeroDeNumeros , esta);
    }
    //obtenemos el tiempo/20 y ese es el promedio para numeroDeNumeros

    return 0;
}