#define EMPTY_ITEM 255
#define EMPTY_COUNT 0
using namespace std;

typedef struct Node {
    unsigned char character;
    int count;
    Node* left, * right;
}*BT;

//Este comparador lo usamos para que el multiset sepa como ordenar arboles binarios
class Compare {
public:
    bool operator()(BT a, BT b) {
        return a->count < b->count;
    }
};

//creamos un nodo, si nos pasan arboles, el count lo llevamos con base a estos, si no, con base al count que nos pasen. De esta forma podemos crear un solo arbol, o combinarlos en una sola funcion.
//Complejidad O(1)
BT newNode(unsigned char character, int count, BT left, BT right) {
    BT n = new Node;
    if (left && right)
        n->count = left->count + right->count;
    else
        n->count = count;
    n->character = character;
    n->left = left;
    n->right = right;
    return n;
}

//Recibimos nuestros el arreglo de frecuencias (256 de tamaño), creamos un arbol por cada posicion que tenga al menos una aparicion, y lo combinamos en un solo arbol.
//Recorrer la tabla de frecuencias para crear los arboles binarios. Nos cuesta n recorrer y 1 crealos. Insertar al multiset los arboles, cuesta amortizado, 1. Por lo que toda la primer parte del algoritmo es O(n)
//Posteriormente lo que se hace es tomar los dos mas chicos del multiset (cuesta O(1) amortizado) y los combinamos en un solo arbol. Que volvemos a insertar en el multiset, que es O(1). Por lo que la complejidad total es O(n)
//Complejidad Final O(n)
BT createTree(vector<int> Frec) {
    multiset<BT, Compare> ms;
    for (int i = 0; i < Frec.size(); i++) {
        if (Frec[i] != 0) {
            ms.insert(newNode((unsigned char)i, Frec[i], NULL, NULL));
        }
    }
    while (ms.size() > 1) {
        BT a = *(ms.begin());
        ms.erase(ms.begin());
        BT b = *(ms.begin());
        ms.erase(ms.begin());
        ms.insert(newNode(EMPTY_ITEM, EMPTY_COUNT, a, b));
    }
    return *(ms.begin());
}