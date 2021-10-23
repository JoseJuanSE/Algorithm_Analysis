#include<bits/stdc++.h>
#include<stdlib.h>
#include "Arbol.hpp"

using namespace std;

int main() {

    int numElems = 0;

    ifstream frecFile;
    frecFile.open("frecuencias.txt");
    unsigned int elements[256][2], elementsSize;
    memset(elements, 0, 256 * 2 * sizeof(int));
    frecFile >> elementsSize;
    for (int i = 0; i < elementsSize; i++) {
        int a, b;
        frecFile >> a >> b;
        elements[i][0] = a;
        elements[i][1] = b;
        numElems += b;
    }
    cout<<numElems<<endl;
    string extencion;
    frecFile >> extencion;
    frecFile.close();
    BT tree = createTree(elements, elementsSize);

    ifstream encoded;
    encoded.open("codificacion.dat");
    BT curr = tree;

    ofstream descom;
    descom.open("descompresed" + extencion);
    bool flag = false;
    while (!encoded.eof()) {
        unsigned char byte;
        encoded >> byte;
        for (int i = 0;i < 8;i++) {

            if (curr->key != NO_ITEM) {
                numElems--;
                if (numElems < 0) {
                    flag = true;
                    break;
                }
                descom << (char)curr->key;
                curr = tree;
            }

            if (curr->key == NO_ITEM) {
                if (byte & (1 << (8 - i -1))) {
                    curr = curr -> right;
                } else {
                    curr = curr -> izq;
                }
            }
            
            if (curr->key != NO_ITEM) {
                numElems--;
                if (numElems < 0) {
                    flag = true;
                    break;
                }
                descom << (char)curr->key;
                curr = tree;
            }
        }
        if (flag)break;
    }

    descom.close();
    encoded.close();
    return 0;
}