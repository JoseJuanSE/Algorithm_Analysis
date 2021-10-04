#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

/*
------ Algoritmo de Búsqueda Lineal ------

Descripción: El algoritmo realizará una búsqueda de un número dado sobre un arreglo compuesto de números desordenados
             donde se comparará con cada elemento del arreglo hasta encontrarlo, o en caso de que no lo encuentre, solo
             recorrer el arreglo completo.
Fecha: 27/09/2021
Versión: Final
Autor: Serrano Cruz Gerardo
*/

int esta;
int *rango[4];
int estado[4][2];
/* Se recive aux[0] que seria el numero de rango en el cual haremos 
la busqueda, tambien hacemos uso de aux[1] que vendria siendo el numero a buscar
y para obtener el tamaño del rango usamos estado junto con aux[0] */
void busquedaLineal(void * es) {
    if (!esta) {
        int *aux = (int *)es;
        int *A = rango[aux[0]];
        int x = aux[1];
        int n = estado[aux[0]][1]-estado[aux[0]][0]+1;
        for (int i = 0; i < n; i++)
            if (A[i] == x){
                esta = 1;
                pthread_exit(NULL);
                return ;
            }
    }
    pthread_exit(NULL);
}

int main(char argc, char* argv[])
{
    int n = atoi(argv[1]), i = 0, *A;
    A = (int *)malloc(n * sizeof(int));

    //leer arreglo
    for(i;i<n;i++)    
        scanf("%d",&A[i]);


    int numeros[] = {322486, 14700764, 3128036, 6337399, 61396,
                    10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503,
                    5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666 ,2147470852, 0};
    //partimos el arreglo en 4 ya que la mayoria de procesadores actuales
    //tiene 4 hilos, sin embargo esto incluso lo podemos generalizar para n hilos, y podriamos
    //pasar n como parametro de forma muy sencilla
    pthread_t hilo[4];
    int estadoAux[4][2] = {{0, n/4-1},
                        {n/4 , n/2-1},
                        {n/2, 3*n/4-1},
                        {3*n/4, n-1}};                    
    //copiamos la matriz anteriormente definida a la global
    memcpy(estado, estadoAux, sizeof (int) * 4 * 2);

    //guardamos los segmentos de arreglo deseados en rango
    for(int i=0;i<4;i++) {
        int size = estado[i][1]-estado[i][0]+1, k = 0;
        rango[i] = (int*)malloc(sizeof(int) * (size));
        for(int j=estado[i][0]; j<=estado[i][1]; j++) {
            rango[i][k] = A[j];
            k++;
        }
    }
//empezamos a tomar tiempo
    for (i = 0; i < 20; i++) {
        esta = 0;
        int numeroABuscar = numeros[i];

        //creamos cada hilo y le asignamos su rango determinado
        //la matriz a continuacion sirve para pasar el numero de rango con el que se trabajara
        //en otras palabras el pedazo de arreglo que se partio asi como el numero a buscar
        int a[4][2] = {{0, numeroABuscar},
                       {1, numeroABuscar},
                       {2, numeroABuscar},
                       {3, numeroABuscar}};
        for(int j=0;j<4;j++) {
            if (pthread_create(&hilo[j], NULL, (void *) busquedaLineal, (void *)a[j])) {
                perror("Error creando hilo");
                exit(1);
            }
        }
        //llamamos cada hilo a hacer su trabajo
        for(int j = 0; j<4;j++) {
            pthread_join(hilo[j], NULL);
        }
        printf("el numero: %d con %d numeros -> %d\n", numeroABuscar, n , esta);
    }
    //obtenemos el tiempo/20 y ese es el promedio para numeroDeNumeros
    
    return 0;
}
