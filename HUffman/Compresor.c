#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Arbol.h"

int codes[256];
FILE *external;

void traverseInOrder(Node root, int str) {
    if (root != NULL) {
        int aux = 2 * str;
        traverseInOrder(root->izq, aux);
        if (root->key != NO_ITEM) {
            codes[root->key] = str;
        }
        traverseInOrder(root->right, aux + 1);
    }
}
int first;
void printDecToBin(int dec) {
    if (dec == 0)
        return ;
    printDecToBin(dec >> 1);
    if(!first)
        fprintf(external, "%d", dec&1);
    else first = 0;
}

void printBin(int x) {
    first = 1;
    printDecToBin(x);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: correct usage: ./%s filePath", argv[0]);
        return 1;
    }
    FILE* fp = fopen(argv[1], "rb"); //open file in binary read
    if (!fp) {
        fprintf(stderr, "Error: file open failed '%s'.\n", argv[1]);
        return 1;
    }
    unsigned char* buf = malloc(sizeof(unsigned char));
    if (!buf) {
        perror("Error: buf memory allocation failed");
        return 1;
    }
    size_t bytes = 0;                    //bytes read
    unsigned int frequencies[256]; //hash map
    memset(frequencies, 0, 256*sizeof(int));
    while ((bytes = fread(buf, sizeof(*buf), 1, fp)) == 1) {
        printf("%d\t", *buf);
        frequencies[*buf]++;
    }
    fclose(fp);
    //reduce hash map
    unsigned int elements[256][2], elementsSize;
    memset(elements, 0, 256*2*sizeof(int));
    int i, j;
    for (i = 0, j = 0; i < 256; i++) {
        if (frequencies[i] != 0) {
            elements[j][0] = i;
            elements[j][1] = frequencies[i];
            j++;
        }
    }
    printf("\n");
    elementsSize = j;

    for (j = 0; j < elementsSize; j++) {
        printf("%c\t%d\t%d\n", elements[j][0], elements[j][0], elements[j][1]);
    }
    Node tree = createTree(elements, elementsSize);
    memset(codes, -1, 256 * sizeof(int));
    traverseInOrder(tree, 1);

    external = fopen("frecuencias.txt","w");    
    for (j = 0; j < 256; j++) {
        if (codes[j] != -1) {
            printf("c:%c  %d: code: ",j , j);
            fprintf(external, "%d ",j);
            printBin(codes[j]);
            fprintf(external,"\n");
            printf("\n");
        }
    }
    fclose(external);

    fp = fopen(argv[1], "rb"); //open file in binary read
    if (!fp) {
        fprintf(stderr, "Error: file open failed '%s'.\n", argv[1]);
        return 1;
    }
    external = fopen("codificacion.dat", "w");    
    buf = malloc(sizeof(char));
    if (!buf) {
        perror("Error: buf memory allocation failed");
        return 1;
    }
    bytes = 0;                    //bytes read
    printf("\n");
    while ((bytes = fread(buf, sizeof(*buf), 1, fp)) == 1) {
        printBin(codes[*buf]);
    }
    fclose(external);
    fclose(fp);
    free(buf);
    return 0;
}
