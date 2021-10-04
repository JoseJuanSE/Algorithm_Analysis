#include <stdio.h>
#include <stdlib.h>

int min(int, int);
int fibMonaccianSearch(int[], int, int);

int main(char argc, char** argv) {
	int n = atoi(argv[1]), i = 0, * arr, x;
	arr = malloc(n * sizeof(int));
	printf("n=%d\n", n);
	scanf("%d", &x);

	while (i < n)
		scanf("%d", &arr[i++]);


	int ind = fibMonaccianSearch(arr, x, n);
	if (ind >= 0)
		printf("El numero %d fue encontrado en el index %d", x, ind);
	else
		printf("El numero %d NO fue encontrado", x);

	return 0;
}

//Encuentra el menor n�mero entre dos n�meros dados
int min(int x, int y) {//retorna un entrero y recibe como argumento dos enteros (X y Y)
	return (x <= y) ? x : y;//Si x es menor o igual que y retorna x, sino retorna y
}



/*Recibe como argumaneto el arreglo en el que
  se buscar� el elemento (arr), el n�mero a buscar
  (x) y el tama�o del arreglo (n).*/
int fibMonaccianSearch(int arr[], int x, int n) {
	int fibMMm2 = 0;//Representa a F_n-2 de la suceci�n de Fibonacci
	int fibMMm1 = 1;//Representa a F_n-1 de la suceci�n de Fibonacci
	int fibM = fibMMm2 + fibMMm1;//Representa a F_n de la suceci�n de Fibonacci

	//Este while calcula el n�mero m�s cercano o igual a n de la serie de Fibonacci
	while (fibM < n) {
		fibMMm2 = fibMMm1;
		fibMMm1 = fibM;
		fibM = fibMMm2 + fibMMm1;
	}

	//el offset se inicializa en -1, ya que nuestro arreglo comienza desde la posici�n 0
	int offset = -1;

	while (fibM > 1) {
		/*i es la posici�n del arreglo con la que se comparar� el n�mero a buscar
		  si la suma entre el offset y F_n-2 se pasa del tama�o total del arreglo
		  se compara con el �ltimo elemento del arrelo, si no se compara con la
		  posici�n i+F_n-2; de esta forma se descartan elementos del arreglo conforme
		  la serie de Fibonacci.
		*/
		int i = min(offset + fibMMm2, n - 1);

		if (arr[i] < x) {/*Si el elemento de la posici�n i de arr es menor que x F_n,F_n-1
						y F_n-2 se recorren una posici�n de la serie de Fibonacci y offset
						toma el valor de i, as� se descartan F_n-1 elementos del arreglo.*/
			fibM = fibMMm1;
			fibMMm1 = fibMMm2;
			fibMMm2 = fibM - fibMMm1;
			offset = i;
		} else if (arr[i] > x) {/*Si el elemento de la posici�n i de arr es mayor que x F_n,F_n-1
							y F_n-2 se recorren una posici�n de la serie de Fibonacci, y el
							offset mantiene su valor, de esta forma se compara por debajo de arr[i]*/
			fibM = fibMMm2;
			fibMMm1 = fibMMm1 - fibMMm2;
			fibMMm2 = fibM - fibMMm1;
		} else/*Si el elemento no es mayor ni menor que arr[i] a arr[i] es el elemento que se esta
				buscando y se retorna la posici�n en donde esta.*/
			return i;
	}
	if (fibMMm1 && arr[offset + 1] == x)/*En caso de que arr[i]>x siempre se cumpla este if checar� si x esta
								   en la �ltima posici�n del arreglo*/
		return offset + 1;

	return -1;//Si el elemento no se encontro rwtnorna -1
}
