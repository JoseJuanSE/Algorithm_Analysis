#include<stdio.h>
#include<stdlib.h>

int arreglo[10000003];

//Explicacion
// Se intercambian los valores de A[i] y A[j]
// usando una variable temporal
//--------
//Se recibe i y j enteros que representan los indices de A 
void intercambiar(int i, int j) {
    int temp = arreglo[i];
    arreglo[i] = arreglo[j];
    arreglo[j] = temp;
}

//Explicacion
//Aqui se toma el primer elemento del rango como
//pivote posteriomente se recorre una variable que empieza 
//apuntado al inicio+1 y otra al final del rango
//la de inicio va hacia el fin y la del fin va 
//hacia el inicio hasta que el inicio encuentre una
//variable mayor o igual al pivote y la del fin una menor o igual
//una vez que esto pasa se intercambian las variables.
//en cuanto esto pasa y el inicio esta despues del fin
//entonces se intercambian pero se regresa el fin para
//ser tomado como pivote. El proceso se repite hasta que esto 
//ultimo pase
//--------
//Se recibe p y r enteros que son el rango de accion del quickSort
//regresa un entero 
int pivote(int p, int r) {
    int piv = arreglo[p], i = p + 1, j = r;
    while (1) {
        while (i < r && arreglo[i] < piv) {
            i++;
        }
        while (arreglo[j] > piv) {
            j--;
        }
        if (i < j) {
            intercambiar(i, j);
        } else {
            intercambiar(p, j);
            return j;
        }
    }
}

//Explicacion
//Se obtiene el pivote mientras el rango
//y se manda a buscar el pivote de ambos lados 
//del pivote, hasta que el tamaño del rango sea 1
//--------
//Se recibe p y r enteros que son el rango donde se aplicara el divide y venceras
void QuickSort(int p, int r) {
    if (p < r) {
        int j = pivote(p, r);
        QuickSort(p, j - 1);
        QuickSort(j + 1, r);
    }
}
//imprime el arreglo si lo necesitamos
//se recibe n que es la cantidad de numeros
void imprimirArreglo(int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arreglo[i]);
    }
    printf("\n");
}
//Imprime que no esta funcionando si el arreglo queda mal ordendo
//se recibe n que es la cantidad de numeros
void checaOrdenamiento(int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (arreglo[i] > arreglo[i + 1]) {
            printf("Not working..\n");
            return;
        }
    }
}

//leemos el arreglo a ordenar
//se recibe n que es la cantidad de numeros
void leerArreglo(int n) {
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &arreglo[i]);
    }
}

int main(int argc, char* argv[]) {
    int numeroDeNumeros, i;

    numeroDeNumeros = atoi(argv[1]);

    leerArreglo(numeroDeNumeros);

    QuickSort(0, numeroDeNumeros - 1);

    checaOrdenamiento(numeroDeNumeros);

    return 0;
}