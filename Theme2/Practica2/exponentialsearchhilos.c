#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<pthread.h>
int pos,n,i,*A,resultado=-1,b,j;
pthread_t hilo[4];
void exponentialSearch();
void *binarySearch(void * estado);
int main(int argc, char* argv[]){
	int x[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503,
	5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666 , 2147470852, 0};
	if (argc!=2){
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	else{
		n=atoi(argv[1]);
	}
	A=(int *)malloc(sizeof(int)*n);
	for(i=0;i<n;++i){
		scanf("%d",&A[i]);
	}
	for(i=0;i<20;++i){
		b=x[i];
		resultado=-1;
		printf("Elemento a buscar= %d\n",b);
		exponentialSearch();
		(resultado==-1)?printf("Elemento no encontrado\n"):printf("Elemento en la posición %d\n",resultado);
	}
}
void exponentialSearch(){
	if(A[0]==b)resultado=0;
	int j=1,inicio,final;
	while(j<n&&A[j]<=b)j=j*2;
	inicio=j/2;
	//int final=fmin(j,n-1);
	if(j<n-1)final=j;
	else
		final=n-1;
	int estado[4][2]={{inicio,((final-inicio)/4)+inicio-1},
						{((final-inicio)/4)+inicio,((inicio+final)/2)-1},
						{(inicio+final)/2,final-((final-inicio)/4)-1},
						{final-((final-inicio)/4),final}};
	int k;
	for(k=0;k<4;++k){
		if(pthread_create(&hilo[k],NULL,binarySearch,(void *)estado[k])){
			perror("Error creando hilo");
			exit(1);
		}
	}
	for(k=0;k<4;++k){
		pthread_join(hilo[k],NULL);
	}
}
void *binarySearch(void * estado){
	int *posiciones=(int *)estado;
	int izq=posiciones[0];
	int der=posiciones[1];
	int mid;
	while(izq<=der){
		mid=(izq+der)/2;
		if(A[mid]==b){resultado= mid;break;}
		if(b<A[mid])der=mid-1;
		if(b>A[mid])izq=mid+1;
	}
	if(resultado==-1)resultado=-1;
	pthread_exit(NULL);
}