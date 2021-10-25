#include<bits/stdc++.h>
#include<stdlib.h>
#include "Arbol.hpp"

using namespace std;

int main() {

    int numElems = 0;
    vector<pair<int,int>> elements;
    int elementsSize;

    ifstream frecFile;
    frecFile.open("frecuencias.txt");
    frecFile >> elementsSize;
    for (int i = 0; i < elementsSize; i++) {
        int a, b;
        frecFile >> a >> b;
        elements.push_back({a, b});
        numElems += b;
    }
    
    string extencion;
    frecFile >> extencion;
    frecFile.close();
    
    BT tree = createTree(elements);

    ifstream encoded;
    encoded.open("codificacion.dat");
    string str;
    BT curr = tree;

    ofstream descom;
    descom.open("descompresed" + extencion);
    bool flag = false;
    while (getline(encoded, str)) {
        for(unsigned char byte: str){
            for (int i = 0;i < 8;i++) {
                //cout<<numElems<<endl;
                if (curr->key != NO_ITEM) {
                    numElems--;
                    if (numElems < 0) {
                        flag = true;
                        break;
                    }
                    descom << (unsigned char)curr->key;
                    curr = tree;
                }
                /* bool aaa = (byte & (1 << (8 - i -1)));
                cout<<aaa; */

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
                    descom << (unsigned char)curr->key;
                    curr = tree;
                }
                //cout<<numElems<<endl;

            }
            //cout<<endl;
            if (flag)break;
        }
    }

    descom.close();
    encoded.close();
    return 0;
}