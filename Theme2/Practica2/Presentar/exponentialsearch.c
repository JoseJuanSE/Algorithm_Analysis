/*
----- Exponential Search o Búsqueda Exponencial -----
Descripción:El algoritmo de búsqueda exponencial realiza la busqueda de un elemento en un arreglo ordenado
			ascendentemente. El algoritmo lo que hace es buscar el posible rango donde se pueda encontrar
			el número de tal manera que va duplicando la posición incial; una vez que a encontrado el rango
			realiza una busqueda binaria en dicho rango.
Fecha: 27/09/21
Versión: 1.
Autor: Trinidad Toledo César Gonzalo
*/
//Librerias a utilizar
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
//Declaración de funciones
int exponentialSearch(int A[], int n, int x);
int binarySearch(int A[], int l, int r, int x);
//Función principal
int main(int argc, char* argv[]) {
	//Declaración de variables y arreglo
	int n, i, * A, x, resultado;
	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc != 3) {
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n", argv[0]);
		exit(1);
	}
	//Tomar el segundo argumento como tamaño del algoritmo
	else {
		n = atoi(argv[1]);
		x = atoi(argv[2]);
	}
	//Asignación dinámica de memoria
	A = (int*)malloc(sizeof(int) * n);
	//Se llena el arreglo
	for (i = 0;i < n;++i) {
		scanf("%d", &A[i]);
	}
	//Se manda a llamar a la función exponentialSearch
	resultado = exponentialSearch(A, n, x);
	//Imprime el resultado, si es un -1 significa que no se encuentra en el arreglo, sino, imprime la posición del número
	(resultado == -1) ? printf("Elemento no encontrado\n") : printf("Elemento en la posición %d\n", resultado);
}
//La función exponentialSearch es donde se lleva a cabo la exponenciación para encontrar el rango en el que posiblemente se encuentre el número
//Recibe el arreglo, el tamaño del mismo y el número a buscar y retorna la posición del numero a buscar
int exponentialSearch(int A[], int n, int x) {
	//Si el número se encuentra en la posición 0 se regresa el 0.
	if (A[0] == x)return 0;
	//Asignación de variables internas dentro de la función.
	int i = 1;
	//Busca el rango donde posiblemente se encuentre el numero que queremos buscar
	while (i < n && A[i] <= x)i = i * 2;
	//Retorna el numero obtenido por una busqueda binaria en el rango posible.
	int min;
	//Busca el menor posible entre i y n-1
	if (i < n - 1)min = i;
	else
		min = n - 1;
	return binarySearch(A, i / 2, min, x);
}
//La función binarySearch realiza una busqueda binaria sobre el rango posible
//Recibe el arreglo, la posición inicial y final del rango a buscar y el número por buscar
int binarySearch(int A[], int l, int r, int x) {
	//Función recursiva marcada como comentario
	/*if(r>=l){
		int mid=l+(r-l)/2;
		if(A[mid]==x)return mid;
		if(A[mid]>x)return binarySearch(A,l,mid<1,x);
		return binarySearch(A,mid+1,r,x);
	}
	return -1;*/
	//Asignación de variables internas dentro de la función.
	int izq = l;
	int der = r;
	int mid;
	//Ciclo iterativo de la busqueda binari
	while (izq <= der) {
		mid = (izq + der) / 2;
		if (A[mid] == x)return mid;
		if (x < A[mid])der = mid - 1;
		if (x > A[mid])izq = mid + 1;
	}
	//Retorna un -1 si no lo encuentra
	return -1;
}