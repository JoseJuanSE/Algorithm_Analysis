#include<bits/stdc++.h>
#include "Arbol.hpp"

using namespace std;

string codes[256];

//Recorrido en inorden para obtener el codigo de cada caracter, de tal forma que despues cuando se quiera obtener el camino en el arbol a un caracter, no se recorra el arbol, solo se consulte el arreglo.
//Se recibe el arbol a recorrer y el string en el cual se va llevando el camino.
//Complejidad O(n)
void traverseTree(BT root, string str) {
    if (root) {
        traverseTree(root->left, str + "0");
        if (root->right == NULL && root->left == NULL) {
            codes[(int)root->character] = str;
        }
        traverseTree(root->right, str + "1");
    }
}
//En esta funcion se pasa el nombre de un archivo y regresa la extension
string getExtention(string a) {
    return a.substr(a.find_last_of("."));
}

//Escribimos el archivo de salida (codificado)
//Se recibe un vector de bytes que seria el archivo original a codificar.
//Complejidad O(n)
void writeBytes(vector<unsigned char> &Buf) {
    //Creamos el archivo condificacion.dat
    FILE* wf = fopen("codificacion.dat", "wb");
    //Creamos el buffer que sera el archivo final a escribir
    vector<unsigned char> buffer;
    int k = 0;
    //Esta string llamada minibuffer lo que hace es convertir un byte del Buf a su camino en el arbol, es decir codifica byte a byte.
    //Esto lo hacemos hasta que tengamos al menos un bloque de 8 ceros y/o unos. Una vez que tenemos un bloque de al menos este tamaño.
    //Esos caracteres se convierten a un byte real en unsigned char b, el cual se agrega al buffer que es lo que se escribira al final.
    //Esto es una optimizacion en ram, pues si codificamos todo el archivo de una sola vez en una string que despues convertiremos a bytes reales, esta string pesara 8 veces mas
    //que el archivo final, puesto que cada uno de sus bits, se tendrian aqui como un caracter, por lo que un bit ocuparia un byte de memoria. Por lo que si codificamos un archivo de 5GB que nos e pudo comprimir nada, entonces para escribir el .dat, necesitariamos 40GB de ram para escribir el archivo.
    //De la forma en que se hace aqui, agarrar bloques mayores a 8, estamos haciendo la memoria de este miniBuf, constante, por lo que si escribiremos 4GB, solo necesitaremos 4GB de memoria.
    //Esto es O(n) con respecto al archivo
    string miniBuf = "";
    while (k < Buf.size()) {
        while (miniBuf.size() < 8) {
            miniBuf += codes[Buf[k++]];
            if (k == Buf.size()) {
                while (miniBuf.size() % 8 != 0) {
                    miniBuf += '0';
                }
                break;
            }
        }
        unsigned char b = 0;
        for (int j = 0; j < 8;j++) {
            b *= 2;
            b += (miniBuf[j] == '1');
        }
        buffer.push_back(b);
        //Puesto que vamos a agarrar 8 bits, y en el miniBuf podriamos tener mas de 8 bits que tenemos que conservar, por eso le borramos los 8 primeros usados y continuamos de forma persistente con el resto.
        miniBuf = miniBuf.substr(8);
    }
    //Se escribe el buffer en el archivo
    fwrite(&buffer[0], sizeof(unsigned char), buffer.size(), wf);
    fclose(wf); 
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Pasa de forma correcta los parametros, solo el archivo a comprimir";
        return 1;
    }
    //Se abre el archivo a comprimir
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
    for (int i = 0; i < 256; i++) {
        external << frecuencias[i] << endl;
    }

    //Se le agrega la extension del archivo original
    external << getExtention(argv[1]);
    external.close();

    //Se crea el arbol
    BT tree = createTree(frecuencias);

    //Se obtienen las codificaciones de los caracteres y se guarda en el arreglo codes, para no calcularlo cada vez que se necesiten.
    traverseTree(tree, "");

    //Se escribe el archivo codificado
    writeBytes(Buf);
    return 0;
}