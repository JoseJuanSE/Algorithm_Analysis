#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/*
-------------- Binary search-------------
Descripcion: Este algoritmo requiere de un arreglo ordenado como entrada. Para encontrar el numero a buscar,
            usamos como punto central del arlgoritmo el hecho de que este esta ordenado, entonces es que vamos a la mitad de el y vemos que mitad se puede descartar pues sabiendo si es mayor o menor que el que esta en la mitad (el numero que buscamos), podemos descartar la mitad del arreglo, entonces se sigue haciendo esto tomando la mitad en la que sabemos que esta, de esta forma es facil ver, que se va partiendo en mitades, hasta que no puede ser partido mas.
Fecha: 27/09/2021
Versión: Final
Autor: Suarez Elizalde Jose Juan
*/

//En esta funcion auxiliar, recibimos el tamaño y el arreglo que leeremos
void leerArreglo(int n, int *arreglo) {
    for (int i = 0;i < n;i++) {
        scanf("%d",&arreglo[i]);
    }
}

//En esta funcion recibimos el numero a buscar, el tamaño del arreglo y el arreglo en el que se buscara el numero
//se lleva a cabo la busqueda binaria en la cual empezamos el rango de actuacion en 0 y n-1, el cual se va partiendo a 
//la mitad hacia donde se encuentraria el numero de interes, al final se regresa true si se encuentra y false si no
//dependiendo si esta o no en la posicion donde deberia
bool busquedaBinaria(int x, int n, int *arreglo) {
    int ini = 0, fin = n-1, i =0;
    while (ini<fin) {
        i++;
        int mitad = (fin+ini) / 2 + 1;
        if (arreglo[mitad] <= x) {
            ini = mitad;
        } else {
            fin = mitad - 1;
        }
    }
    return arreglo[ini] == x;
}


int main(int argc, char* argv[]) {
    int numeroDeNumeros, i;
    numeroDeNumeros = atoi(argv[1]);
    
    int numeroABuscar[] = {322486, 14700764, 3128036, 6337399, 61396,
10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503,
5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666 , 2147470852, 0};

    int *arreglo = (int*)malloc(sizeof(int) * numeroDeNumeros);

    leerArreglo(numeroDeNumeros, arreglo);

    //empezar medicion

    for(int i=0;i<20;i++) {
        bool esta = busquedaBinaria(numeroABuscar[i], numeroDeNumeros, arreglo);
        printf("el numero: %d con %d numeros -> %d\n", numeroABuscar[i], numeroDeNumeros , esta);
    }
    //terminar medicion
    //tiempo/20 -> promedio, se imprime

    return 0;
}