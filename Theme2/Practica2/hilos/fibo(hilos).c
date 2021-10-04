#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int esta, *arreglo;
int *rango[4];
int estado[4][2];

void leerArreglo(int n) {
    for (int i = 0;i < n;i++) {
        scanf("%d",&arreglo[i]);
    }
}

//Encuentra el menor número entre dos números dados
int min(int x,int y){//retorna un entrero y recibe como argumento dos enteros (X y Y)
	return (x<=y)?x:y;//Si x es menor o igual que y retorna x, sino retorna y
}

/*Recibe como argumaneto el numero de arreglo en el que 
  se buscará el elemento (rango[aux[0]]), el número a buscar 
  (aux[1]) y el tamaño del arreglo se obtiene de los estados junto con aux[0].*/
void fibMonaccianSearch(void * es){
    if(!esta) {
        int *aux = (int *)es;
        int *arr = rango[aux[0]];
        int x = aux[1];
        int n = estado[aux[0]][1]-estado[aux[0]][0]+1;

        int fibMMm2=0;//Representa a F_n-2 de la suceción de Fibonacci
        int fibMMm1=1;//Representa a F_n-1 de la suceción de Fibonacci
        int fibM=fibMMm2+fibMMm1;//Representa a F_n de la suceción de Fibonacci
        
        //Este while calcula el número más cercano o igual a n de la serie de Fibonacci
        while(fibM<n){
            fibMMm2=fibMMm1;
            fibMMm1=fibM;
            fibM=fibMMm2+fibMMm1;
        }
        
        //el offset se inicializa en -1, ya que nuestro arreglo comienza desde la posición 0
        int offset=-1;
        
        while (fibM>1) {
            /*i es la posición del arreglo con la que se comparará el número a buscar
            si la suma entre el offset y F_n-2 se pasa del tamaño total del arreglo
            se compara con el último elemento del arrelo, si no se compara con la
            posición i+F_n-2; de esta forma se descartan elementos del arreglo conforme
            la serie de Fibonacci.
            */
            int i=min(offset+fibMMm2,n-1);
            
            if (arr[i]<x) {/*Si el elemento de la posición i de arr es menor que x F_n,F_n-1 
                            y F_n-2 se recorren una posición de la serie de Fibonacci y offset
                            toma el valor de i, así se descartan F_n-1 elementos del arreglo.*/
                fibM=fibMMm1;
                fibMMm1=fibMMm2;
                fibMMm2=fibM-fibMMm1;
                offset=i;
            } else if(arr[i]>x) {/*Si el elemento de la posición i de arr es mayor que x F_n,F_n-1 
                                y F_n-2 se recorren una posición de la serie de Fibonacci, y el
                                offset mantiene su valor, de esta forma se compara por debajo de arr[i]*/
                    fibM=fibMMm2;
                    fibMMm1=fibMMm1-fibMMm2;
                    fibMMm2=fibM-fibMMm1;
                } else {
                    esta = 1;
                    pthread_exit(NULL);
                    return ;
                }   
        }
        esta = esta || fibMMm1&&arr[offset+1]==x;
    }
    pthread_exit(NULL);
}

int main(char argc, char* argv[]){
    int numeroDeNumeros;

    numeroDeNumeros = atoi(argv[1]);

    arreglo = (int*)malloc(sizeof(int) * numeroDeNumeros);

    leerArreglo(numeroDeNumeros);

    int numeros[] = {322486, 14700764, 3128036, 6337399, 61396,
10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503,
5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666 , 2147470852, 0};

    //partimos el arreglo en 4 ya que la mayoria de procesadores actuales
    //tiene 4 hilos, sin embargo esto incluso lo podemos generalizar para n hilos, y podriamos
    //pasar n como parametro de forma muy sencilla
    pthread_t hilo[4];
    int estadoAux[4][2] = {{0, numeroDeNumeros/4-1},
                        {numeroDeNumeros/4 , numeroDeNumeros/2-1},
                        {numeroDeNumeros/2, 3*numeroDeNumeros/4-1},
                        {3*numeroDeNumeros/4, numeroDeNumeros-1}};
    
    //copiamos la matriz anteriormente definida a la global
    memcpy(estado, estadoAux, sizeof (int) * 4 * 2);

    //guardamos los segmentos de arreglo deseados en rango
    for(int i=0;i<4;i++) {
        int size = estado[i][1]-estado[i][0]+1, k = 0;
        rango[i] = (int*)malloc(sizeof(int) * (size));
        for(int j=estado[i][0]; j<=estado[i][1]; j++) {
            rango[i][k] = arreglo[j];
            k++;
        }
    }
    //empezamos a tomar tiempo
    for(int i=0;i<20;i++) {
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
            if (pthread_create(&hilo[j], NULL, (void *) fibMonaccianSearch, (void *)a[j])) {
                perror("Error creando hilo");
                exit(1);
            }
        }
        //llamamos cada hilo a hacer su trabajo
        for(int j = 0; j<4;j++) {
            pthread_join(hilo[j], NULL);
        }
        printf("el numero: %d con %d numeros -> %d\n", numeroABuscar, numeroDeNumeros , esta);
    }
    //obtenemos el tiempo/20 y ese es el promedio para numeroDeNumeros
	
	return 0;
}