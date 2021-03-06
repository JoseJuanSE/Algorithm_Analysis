#include<stdio.h>
#include<stdlib.h>

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
ABB insertar(int elem, ABB a) {
    if (esVacio(a)) {
        return nuevoNodo(elem);
    }
    ABB aux = a;
    while (1) {
        if (raiz(aux) > elem) {
            if (esVacio(aux->izq)) {
                aux->izq = nuevoNodo(elem);
                break;
            } else {
                aux = aux->izq;
            }
        } else {
            if (esVacio(aux->der)) {
                aux->der = nuevoNodo(elem);
                break;
            } else {
                aux = aux->der;
            }
        }
    }
    return a;
}

// Fin de la implementacion
//------------------ARBOL-------------------------------------

//----------------PILA----------------------------
typedef struct Node {
    ABB val;
    struct Node* next;
} *Stack;
Stack Empty() { return NULL; }
int IsEmpty(Stack a) { return a == NULL; }
ABB Top(Stack a) { return a->val; }
Stack Pop(Stack l) { return l->next; }
Stack Push(ABB x, Stack res) {
    Stack nuevo = (Stack)malloc(sizeof(struct Nodo));
    nuevo->val = x;
    nuevo->next = res;
    return nuevo;
}
//----------------PILA----------------------------


int* arreglo;

//Se va lo mas a la izquierda posible (al mas peque??o posible)
//se agrega el numero al arreglo y despues con el backtracking recursivo
//vamos regresado a las posiciones mayores y visitando a la derecha recorriendo el 
//arbol en orden por lo que terminamos con el arreglo ordenado
int cPos;
//Iterativa implementando pila
void inOrder(ABB a) {
    Stack s = Empty();

    ABB actual = a;

    while (!esVacio(actual) || !IsEmpty(s)) {
        while (!esVacio(actual)) {
            s = Push(actual, s);
            actual = actual->izq;
        }
        actual = Top(s);
        s = Pop(s);
        arreglo[cPos++] = actual->numero;
        actual = actual->der;
    }
}

//Obtenemos el arreglo ordenado
//a traves del recorrido inorder implementado anteriomente
void obtenerArreglo(ABB a) {
    cPos = 0;
    inOrder(a);
}

//imprimimos el arreglo de ser necesario
void imprimirArreglo(int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d\n", arreglo[i]);
    }
}

//Insertamos un arreglo completo a un arbol
ABB insertarArregloEnArbol(int n) {
    ABB arbol = insertar(arreglo[0], NULL);
    for (int i = 1; i < n; i++) {
        insertar(arreglo[i], arbol);
    }
    return arbol;
}

//Imprime que no esta funcionando si el arreglo queda mal ordendo
void checaOrdenamiento(int size) {
    int i;
    for (i = 0;i < size - 1;i++) {
        if (arreglo[i] > arreglo[i + 1]) {
            printf("Not working..\n");
            return;
        }
    }
}

//leemos el arreglo a ordenar
void leerArreglo(int n) {
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &arreglo[i]);
    }
}

int main(int argc, char* argv[]) {
    int numeroDeNumeros, i;

    numeroDeNumeros = atoi(argv[1]);
    arreglo = (int*)malloc(sizeof(int) * numeroDeNumeros);

    leerArreglo(numeroDeNumeros);

    ABB arbol = insertarArregloEnArbol(numeroDeNumeros);

    obtenerArreglo(arbol);

    imprimirArreglo(numeroDeNumeros);

    checaOrdenamiento(numeroDeNumeros);

    return 0;
}
