#include <limits.h>
#define NO_ITEM 257
#define NO_COUNT 0

using namespace std;

typedef struct Node {
    int key, count;
    struct Node* izq, * right;
} *BT;

bool operator < (const pair<int, BT> &a, const pair<int, BT> &b) {
    return a.first < b.first;
}

BT createNode(int item, int cnt, BT lft, BT rght) {
    BT node = new Node; // en lugar de 
    //BT node = (BT)malloc(sizeof(struct Node));
    if (!node) {
        perror("Error: Node memory allocation failed");
        exit(1);
    }
    if (lft == NULL && rght == NULL)
        node->count = cnt;
    else
        node->count = lft->count + rght->count;
    node->key = item;
    node->izq = lft;
    node->right = rght;
    return node;
}

BT createTree(unsigned int arr[][2], int n) {
    multiset<pair<unsigned int, BT> > ms;
    ms.clear();
    for (int i = 0; i < n; i++){
        ms.insert({arr[i][1] ,createNode(arr[i][0], arr[i][1], NULL, NULL)});
    }
    while(ms.size()>1) {
        pair<unsigned int, BT> x = *ms.begin();
        ms.erase(x);
        pair<unsigned int, BT> y = *ms.begin();
        ms.erase(y);
        ms.insert({x.first + y.first, createNode(NO_ITEM, NO_COUNT, y.second, x.second)});
    }
    return (*ms.begin()).second;
}
