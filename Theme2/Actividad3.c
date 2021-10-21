#include<stdio.h>

int producto2mayores(int *A, int n) {
    int nOper = 0;

    int mayor1, mayor2;

    if (A[0] > A[1]) {
        mayor1 = A[0];
        mayor2 = A[1];
    } else {
        mayor1 = A[1];
        mayor2 = A[0];
    }

    int i = 2;

    while (i < n) {
        mOpera++;
        if (A[i] > mayor1) {
            mayor2 = mayor1;
            mayor1 = A[i];
            mOpera+=2;
        } else {
            mOpera++;
            if(A[i] > mayor2) {
                mayor2 = A[i];
                mOpera++;
            }
        }
        mOpera++;
        i++;
    }

    return mayor1 * mayor2;
}

int main(int argc, char* argv[]) {
    int nElementos = atoi(argv[1]);
    int *A = (int *)malloc(sizeof(int)*nElementos);

    for(int i=0; i<nElementos; i++) {
        scanf("%d", &A[i]);
    }

    int ans = producto2mayores(A, nElementos);

    return 0;
}