#include<bits/stdc++.h>
#include "Arbol.hpp"

using namespace std;

string codes[256];

void traverseTree(BT root, string str) {
    if (root) {
        traverseTree(root->left, str + "0");
        if (root->right == NULL && root->left == NULL) {
            codes[(int)root->character] = str;
        }
        traverseTree(root->right, str + "1");
    }
}

void writeBytes(string str) {
    //Transformamos los 0 y 1 de string a bits reales
    //los cuales se escriben en el archivo .dat
    FILE* wf = fopen("codificacion.dat", "wb");
    while (str.size() % 8 != 0)str += "0";
    vector<unsigned char> buffer;
    for (int i = 0; i < str.size(); i += 8) {
        unsigned char b = 0;
        for (int j = i; j < i + 8;j++) {
            b *= 2;
            b += (str[j] == '1');
        }
        buffer.push_back(b);
    }
    fwrite(&buffer[0], sizeof(unsigned char), buffer.size(), wf);
    fclose(wf);
}

string getExtention(string a) {
    return a.substr(a.find_last_of("."));
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Pasa de forma correcta los parametros, solo el archivo a comprimir";
        return 1;
    }
    FILE* archivoAComprimir = fopen(argv[1], "rb");
    if (archivoAComprimir == NULL) {
        cout << "No se pudo abrir el archivo";
        return 1;
    }
    //Se lee el archivo a comprimir
    fseek(archivoAComprimir, 0, SEEK_END);
    unsigned int size = ftell(archivoAComprimir);
    vector<unsigned char> Buf(size);
    rewind(archivoAComprimir);
    fread(&Buf[0], size, sizeof(unsigned char), archivoAComprimir);
    fclose(archivoAComprimir);

    //Se crea la tabla de frecuencias
    vector<int> frecuencias(256, 0);

    for (unsigned char i : Buf) {
        frecuencias[(int)i]++;
    }
    //Se crea el archivo de frecuencias
    ofstream external;
    external.open("frecuencias.txt");
    for (int  i = 0; i < 256; i++) {
        external<<frecuencias[i]<<endl; 
    }
    //Se le agrega la extension del archivo original
    external<<getExtention(argv[1]);
    external.close();

    //Se crea el arbol
    BT tree = createTree(frecuencias);
    //Se obtienen las codificaciones
    traverseTree(tree, "");

    //Se codifica el archivo
    string finalFile = "";
    for (unsigned char i : Buf) {
        finalFile += codes[(int)i];
    }
    //Se escribe el archivo codificado
    writeBytes(finalFile);
    return 0;
}