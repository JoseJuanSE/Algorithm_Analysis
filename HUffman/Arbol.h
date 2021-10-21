#include <limits.h>
#define NO_ITEM 257
#define NO_COUNT 0

typedef struct Node {
    int key, count;
    struct Node *izq, *right;
} *Node;

Node createNode(int item, int cnt, Node lft, Node rght) {
    Node node = (Node)malloc(sizeof(struct Node));
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

Node createTree(unsigned int arr[][2], int n) {
    Node nodeArr[2 * n];
    int i;
    for (i = 0; i < n; i++) {
        nodeArr[i] = createNode(arr[i][0], arr[i][1], NULL, NULL);
    }
    int end = n, lowest1, lowest2, index1, index2;
    int j;
    for (j = 0; j < n - 1; j++) {
        lowest1 = lowest2 = index1 = index2 = INT_MAX;
        for (i = 0; i < end; i++) {
            if (nodeArr[i]->count < lowest1) {
                lowest2 = lowest1;
                index2 = index1;
                lowest1 = nodeArr[i]->count;
                index1 = i;
            } else if (nodeArr[i]->count < lowest2) {
                lowest2 = nodeArr[i]->count;
                index2 = i;
            }
        }
        nodeArr[end] = createNode(NO_ITEM, NO_COUNT, nodeArr[index1], nodeArr[index2]);
        end++;
        nodeArr[index1]->count = nodeArr[index2]->count = INT_MAX;
    }
    return nodeArr[end - 1];
}
