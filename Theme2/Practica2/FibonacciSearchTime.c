//*****************************************************************
//M. EN C. EDGARDO ADRI脕N FRANCO MART脥NEZ 
//Curso: An谩lisis de algoritmos
//(C) Enero 2013
//ESCOM-IPN
//Ejemplo de medici贸n de tiempo en C y recepci贸n de parametros en C bajo UNIX
//Compilaci贸n: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementaci贸n de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecuci贸n: "./main n" (Linux y MAC OS)
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
//*****************************************************************
//DEFINICION DE CONSTANTES DEL PROGRAMA
//*****************************************************************

//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************

//*****************************************************************
//DECLARACI脫N DE FUNCIONES
//*****************************************************************
int min(int,int);
int fibMonaccianSearch(int[],int,int);
//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************
int *A,j,aux;
//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char* argv[])
{	
	//******************************************************************	
	//Variables del main
	//******************************************************************	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medici贸n de tiempos
	int n; 	//n determina el tama帽o del algorito dado por argumento al ejecutar
	int i; //Variables para loops
	int x; //N鷐ero a buscar

	//******************************************************************	
	//Recepci贸n y decodificaci贸n de argumentos
	//******************************************************************	

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecuci贸n y cadena=n)
	if (argc!=2) 
	{
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tama帽o del algoritmo
	else
	{
		n=atoi(argv[1]);
	}
	//Se asigna la memoria de manera din谩mica.
	arr = (int *) malloc(sizeof(int) *n); 
	//Se lee el n鷐ero a buscar
	scanf("%d",&x);
	//Se leen los datos del arreglo.
	for(i=0;i<n;++i){
        scanf("%d",&arr[i]);
    }
	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
		if(ind>=0)
			printf("El numero %d fue encontrado en el index %d",x,ind);
		else
			printf("El numero %d NO fue encontrado",x);
	//******************************************************************

	//******************************************************************	
	//Evaluar los tiempos de ejecuci贸n 
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);
	
	//C谩lculo del tiempo de ejecuci贸n del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acci贸nes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acci贸nes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	//******************************************************************

	//Terminar programa normalmente	
	exit (0);	
}

//************************************************************************
//DEFINICI脫N DE FUNCIONES 
//************************************************************************
//B鷖queda de Fibonacci
int fibMonaccianSearch(int arr[],int x,int n){
	int fibMMm2=0;
	int fibMMm1=1;
	int fibM=fibMMm2+fibMMm1;
	
	while(fibM<n){
		fibMMm2=fibMMm1;
		fibMMm1=fibM;
		fibM=fibMMm2+fibMMm1;
	}
	
	int offset=-1;
	
	while(fibM>1){
		int i=min(offset+fibMMm2,n-1);
		
		if(arr[i]<x){
			fibM=fibMMm1;
			fibMMm1=fibMMm2;
			fibMMm2=fibM-fibMMm1;
			offset=i;
		}else if(arr[i]>x){
				fibM=fibMMm2;
				fibMMm1=fibMMm1-fibMMm2;
				fibMMm2=fibM-fibMMm1;
			}else
				return i;			
	}
	if(fibMMm1&&arr[offset+1]==x)
		return offset+1;
		
	return -1;
}
