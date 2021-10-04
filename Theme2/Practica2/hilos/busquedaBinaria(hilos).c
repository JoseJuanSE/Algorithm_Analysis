#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdbool.h>

/*
-------------- Binary search-------------
Descripcion: Este algoritmo requiere de un arreglo ordenado como entrada. Para encontrar el numero a buscar,
            usamos como punto central del arlgoritmo el hecho de que este esta ordenado, entonces es que vamos a la mitad de el y vemos que mitad se puede descartar pues sabiendo si es mayor o menor que el que esta en la mitad (el numero que buscamos), podemos descartar la mitad del arreglo, entonces se sigue haciendo esto tomando la mitad en la que sabemos que esta, de esta forma es facil ver, que se va partiendo en mitades, hasta que no puede ser partido mas. Ademas partimos el arreglo en varias partes y resolvermos cada una por 
            serparado haciendo uso de hilos, lo cual nos reduce la complejidad a nlog(n/4), a su vez de que esto se hace de forma casi simultanea, reduciendo el tiempo de busqueda.
Fecha: 27/09/2021
Versión: Final
Autor: Suarez Elizalde Jose Juan
*/

int *arreglo, numeroABuscar;
bool esta = 0;

//En esta funcion auxiliar, recibimos el tamaño y el arreglo que leeremos
void leerArreglo(int n) {
    for (int i = 0;i < n;i++) {
        scanf("%d",&arreglo[i]);
    }
}

//En esta funcion recibimos el numero a buscar, el tamaño del arreglo y el arreglo en el que se buscara el numero
//se lleva a cabo la busqueda binaria en la cual empezamos el rango de actuacion en ini y fin, el cual se va partiendo a 
//la mitad hacia donde se encuentraria el numero de interes, al final se regresa true si se encuentra y false si no
//dependiendo si esta o no en la posicion donde deberia
void *busquedaBinaria(void * estado) {
    if (!esta) {
        int *posiciones = (int *)estado;
        int ini = posiciones[0], fin = posiciones[1];
        while (ini<fin) {
            int mitad = (fin+ini) / 2 + 1;
            if (arreglo[mitad] <= numeroABuscar) {
                ini = mitad;
            } else {
                fin = mitad - 1;
            }
        }
        esta = esta || arreglo[ini] == numeroABuscar;
    }
    pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
    int numeroDeNumeros, i;

    numeroDeNumeros = atoi(argv[1]);

    arreglo = (int*)malloc(sizeof(int) * numeroDeNumeros);

    leerArreglo(numeroDeNumeros);

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

    //empezamos a tomar tiempo

    for(int i=0;i<20;i++) {
        esta = 0;  
        numeroABuscar = numeros[i];

        //creamos cada hilo y le asignamos su rango determinado
        for(int j=0;j<4;j++) {
            if (pthread_create(&hilo[j], NULL, busquedaBinaria, (void *)estado[j])) {
                perror("Error creando hilo");
                exit(1);
            }
        }

        //llamamos cadahilo a hacer su trabajo
        for(int j = 0; j<4;j++) {
            pthread_join(hilo[j], NULL);
        }

        printf("el numero: %d con %d numeros -> %d\n", numeroABuscar, numeroDeNumeros , esta);
    }
    //obtenemos el tiempo/20 y ese es el promedio para numeroDeNumeros
    
    return 0;
}