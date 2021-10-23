#include<bits/stdc++.h>
#include<stdlib.h>
#include "Arbol.hpp"

using namespace std;

int codes[256];

void traverseInOrder(BT root, int str) {
    if (root != NULL) {
        int aux = 2 * str;
        traverseInOrder(root->izq, aux);
        if (root->key != NO_ITEM) {
            codes[root->key] = str;
        }
        traverseInOrder(root->right, aux + 1);
    }
}

void escribeBytes(string a) {
    ofstream wf("codificacion.dat", ios::out | ios::binary);
    while (a.size() % 8 != 0)a += "0";
    for (int i = 0;i < a.size(); i += 8) {
        unsigned char b[1];
        b[0] = 0;
        for (int j = i; j < i + 8;j++) {
            b[0] *= 2;
            b[0] += (a[j] == '1');
            //printf("%d %d  ", (a[j] == '1'), b[0]);
        }

        //cout << endl;
        //printf("%d  ", b[0]);
        //cout << endl;
        wf.write((char*)b, sizeof(char));
    }
    wf.close();
}
string getExtention(string a) {
    string ans = "";
    bool flag = false;
    for (char i : a) {
        if (i == '.') {
            flag = true;
        }
        if (flag) {
            ans += i;
        }
    }
    return ans;
}

int first;
string s;
void printDecToBin(int dec) {
    if (dec == 0)
        return;
    printDecToBin(dec >> 1);
    if (!first)
        s += to_string(dec & 1);
    else first = 0;
}

string printBin(int x) {
    first = 1;
    s = "";
    printDecToBin(x);
    return s;
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
    unsigned char* buf = new unsigned char();
    if (!buf) {
        perror("Error: buf memory allocation failed");
        return 1;
    }
    size_t bytes = 0;
    unsigned int frequencies[256];
    memset(frequencies, 0, 256 * sizeof(int));
    while ((bytes = fread(buf, sizeof(*buf), 1, fp)) == 1) {
        //printf("%d\t", *buf);
        frequencies[*buf]++;
    }
    fclose(fp);
    //reduce hash map
    unsigned int elements[256][2], elementsSize;
    memset(elements, 0, 256 * 2 * sizeof(int));
    int i, j;
    for (i = 0, j = 0; i < 256; i++) {
        if (frequencies[i] != 0) {
            elements[j][0] = i;
            elements[j][1] = frequencies[i];
            j++;
        }
    }
    elementsSize = j;

    BT tree = createTree(elements, elementsSize);
    memset(codes, -1, 256 * sizeof(int));
    traverseInOrder(tree, 1);

    ofstream external;
    external.open("frecuencias.txt");
    external<<elementsSize<<endl;
    for (j = 0; j < elementsSize; j++) {
        //printf("%c\t%d\t%d\n", elements[j][0], elements[j][0], elements[j][1]);
        external<<elements[j][0]<<" "<<elements[j][1]<<endl;
    }
    external<<getExtention(argv[1]);
    external.close();
    fp = fopen(argv[1], "rb"); //open file in binary read
    if (!fp) {
        fprintf(stderr, "Error: file open failed '%s'.\n", argv[1]);
        return 1;
    }

    /* FILE *external;
    external = fopen("codificacion.dat", "wb");    */

    buf = new unsigned char();
    if (!buf) {
        perror("Error: buf memory allocation failed");
        return 1;
    }
    bytes = 0;                    //bytes read

    string fin = "";
    while ((bytes = fread(buf, sizeof(*buf), 1, fp)) == 1) {
        fin += printBin(codes[*buf]);
    }
    //fclose(external);
    cout << fin << endl;
    escribeBytes(fin);
    fclose(fp);
    free(buf);

    return 0;
}
