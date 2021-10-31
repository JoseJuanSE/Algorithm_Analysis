#include<bits/stdc++.h>
#include "Arbol.hpp"

using namespace std;

string getExtention(string a) {
    return a.substr(a.find_last_of("."));
}   

int main(int argc, char* argv[]) {
    //validamos los parametros
    if (argc != 3 || getExtention(argv[1]) != ".txt" || getExtention(argv[2]) != ".dat") {
        if (argc != 3) {
            cout << "Error: Cantidad de argumentos invalida" << endl;
        } else if(getExtention(argv[1]) != ".txt") {
            cout << "Error: El archivo de texto debe ser .txt" << endl;
        } else if(getExtention(argv[2]) != ".dat") {
            cout << "Error: El archivo de datos debe ser .dat" << endl;
        }
        cout << "Pasa de forma correcta los parametros";
        return 1;
    }

    int numElems = 0;
    //Leemos el archivo con las frecuencias
    vector<int> frecuencias(256, 0);

    ifstream frecFile;
    frecFile.open(argv[1]);
    for (int i = 0; i < 256; i++) {
        int b;
        frecFile >> b;
        frecuencias[i] = b;
        numElems += b;
    }
    //Leemos la extension del archivo a decodificar
    string extencion;
    frecFile >> extencion;
    frecFile.close();

    //Se abre el archivo comprimido
    FILE *archivoAComprimir = fopen(argv[2], "rb");
    if (archivoAComprimir == NULL) {
        cout << "No se pudo abrir el archivo";
        return 1;
    }

    //Se lee el archivo comprimido y se pasa al Buf
    fseek(archivoAComprimir, 0, SEEK_END);
    unsigned int size = ftell(archivoAComprimir);
    vector<unsigned char> Buf(size);
    rewind(archivoAComprimir);
    fread(&Buf[0], size, sizeof(unsigned char), archivoAComprimir);
    fclose(archivoAComprimir);

    //Se crea el arbol
    BT tree = createTree(frecuencias);
    BT curr = tree;

    //Se decodifica el archivo y se guarda en ans
    vector<unsigned char> ans;
    for(unsigned char byte : Buf) {
        for (int i = 7; i >= 0; i--) {
            if (curr->left == NULL && curr->right == NULL) {
                ans.push_back(curr->character);
                curr = tree;
                numElems--;
                if (numElems == 0) {
                    break;
                }
            }
            if (byte & (1 << i)) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
    }
    if (curr->left == NULL && curr->right == NULL) {
        ans.push_back(curr->character);
    }
    //Se escribe el archivo decodificado
    string fileName = "Descompresed" + extencion;
    FILE* descom = fopen(fileName.c_str(), "wb");
    fwrite(&ans[0], sizeof ans[0], ans.size(), descom);
    fclose(descom);
    return 0;
}