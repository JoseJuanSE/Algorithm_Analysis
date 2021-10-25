#include<bits/stdc++.h>
#include<stdlib.h>
#include <locale.h>
#include "Arbol.hpp"

using namespace std;

int codes[256];
bool first;
string s;

void traverseInOrder(BT root, int str) {
    if (root != NULL) {
        traverseInOrder(root->izq, 2 * str);
        if (root->key != NO_ITEM) {
            codes[root->key] = str;
        }
        traverseInOrder(root->right, 2 * str + 1);
    }
}

void printTree(BT root) {
    if (root != NULL) {
        printTree(root->izq);
        cout<<root ->count<<" ";
        printTree(root->right);
    }
}

void escribeBytes(string a) {
    ofstream wf("codificacion.dat", ios::out | ios::binary);
    while (a.size() % 8 != 0)a += "0";
    for (int i = 0;i < a.size(); i += 8) {
        char b[1];
        b[0] = 0;
        for (int j = i; j < i + 8;j++) {
            b[0] *= 2;
            b[0] += (a[j] == '1');
        }
        wf.write((char*)b, sizeof(unsigned char));
    }
    wf.close();
}

string getExtention(string a) {
    string ans = "";
    bool flag = false;
    for (unsigned char i : a) {
        if (i == '.') {
            flag = true;
        }
        if (flag) {
            ans += i;
        }
    }
    return ans;
}


void printDecToBin(int dec) {
    if (dec == 0)
        return;
    printDecToBin(dec >> 1);
    if (!first)
        s += to_string(dec & 1);
    else first = false;
}

string printBin(int x) {
    first = true;
    s = "";
    printDecToBin(x);
    return s;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: correct usage: ./%s filePath", argv[0]);
        return 1;
    }
    //LLenamos tabla de frecuencias
    string str;
    vector<int> frequencies(256, 0);
    ifstream readChars;
    readChars.open(argv[1]);

    first = true;
    while (getline(readChars, str)) {
        if(!first){
            frequencies[10]++;
        }
        for(unsigned char buf:str) {
            frequencies[(int)buf]++;
        }
        first = false;
    }
    readChars.close();

    vector<pair<int,int>> elements;
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] != 0) {
            elements.push_back({i, frequencies[i]});
            cout<<(char) i << " "<<codes[i]<<endl;
        }
    }

    BT tree = createTree(elements);
    printTree(tree);
    //cout<<endl;
    traverseInOrder(tree, 1);

    ofstream external;
    external.open("frecuencias.txt");
    external<<elements.size()<<endl;
    for (int j = 0; j < elements.size(); j++) {
        /* char uc = elements[j][0];
        printf("%c\t%d\t%d\n", uc, elements[j][0], elements[j][1]);*/
        external<<elements[j].first<<" "<<elements[j].second<<endl; 
    }
    external<<getExtention(argv[1]);
    external.close();



    string fin = "";
    ifstream unencode;
    unencode.open(argv[1]);
    first = true;
    while (getline(unencode, str)) {
        if(!first)fin += printBin(codes[10]);
        for(unsigned char uc: str) {
            fin += printBin(codes[(int)uc]);
        }
        first = false;
    }
    unencode.close();

    escribeBytes(fin);
    return 0;
}
