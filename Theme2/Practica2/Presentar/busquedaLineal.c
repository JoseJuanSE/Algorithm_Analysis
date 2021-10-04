#include <stdio.h>
#include <stdlib.h>

int LinearSearch(int[], int, int);

int main(char argc, char** argv) {
	int n = atoi(argv[1]), i = 0, * arr, x;
	arr = malloc(n * sizeof(int));
	printf("n=%d\n", n);
	scanf("%d", &x);

	while (i < n) {
		scanf("%d", &arr[i++]);
	}
	i = 0;
	while (i < n) {
		printf("%d\n", arr[i++]);
	}
	int ind = LinearSearch(arr, x, n);

	if (ind >= 0)
		printf("El numero %d fue encontrado en el index %d", x, ind);
	else
		printf("El numero %d NO fue encontrado", x);

	return 0;
}

/*La búsqueda lineal o secuencial recorre todo el arreglo y va comparando elemento
  a elemento el número que se esta buscando.
  Recibe como argumantos el arreglo (arr), sutamaño (n) y el número a buscar (x)
  y retorna el indice donde se encuentra, en caso de estar.*/
int LinearSearch(int arr[], int x, int n) {
	int i;
	for (i = 0; i < n; i++)//Ciclo que recorre todo el arreglo
		if (arr[i] == x)//Comparación entre cada elemento de arreglo y el número que se busca
			return i;//Si el elemento esta retorna su posición
	return -1;//Si el elemento no esta retorna -1
}


