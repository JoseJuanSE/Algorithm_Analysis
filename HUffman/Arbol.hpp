#define EMPTY_ITEM 255
#define EMPTY_COUNT 0
using namespace std;

typedef struct Node {
    unsigned char character;
    int count;
    Node* left, * right;
}*BT;

class Compare {
public:
    bool operator()(BT a, BT b) {
        return a->count < b->count;
    }
};

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