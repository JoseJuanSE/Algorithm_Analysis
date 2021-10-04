#include <stdio.h>
#include <stdlib.h>

/*
------ Algoritmo de Búsqueda Lineal ------

Descripción: El algoritmo realizará una búsqueda de un número dado sobre un arreglo compuesto de números desordenados
             donde se comparará con cada elemento del arreglo hasta encontrarlo, o en caso de que no lo encuentre, solo
             recorrer el arreglo completo.
Fecha: 27/09/2021
Versión: Final
Autor: Serrano Cruz Gerardo
*/
int busquedaLineal(int A[], int n, int x)
{
    int i;
    for (i = 0; i < n; i++)
        if (A[i] == x)
            return i;
    return -1;
}

int main(char argc, char* argv[])
{
    int n = atoi(argv[1]), i = 0, *A;
    A = malloc(n * sizeof(int));

    //leer arreglo
    for(i=0;i<n;i++)    
        scanf("%d",&A[i]);


    int x[] = { 322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003,
    450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354,
    2109248666 , 2147470852, 0 };
    // Function call

    for (i = 0; i < 20; i++) {
        int resultado = busquedaLineal(A, n, x[i]);
        if (resultado == -1) {
            printf("El elemento no pertenece al arreglo.\n");
        } else {
            printf("El elemeneto se encuentra en el indice %d\n", resultado);
        }
    }

    
    return 0;
}



/*


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


*/