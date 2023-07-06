#include <bits/stdc++.h>

using namespace std;

template<class T>
struct Node {
    int key;
    Node *pLeft;
    Node *pRight;
    Node *pParent;
};

Node<class T> *createNode(int x) {
    Node<T> *p = new Node<T>;
    p->key = x;
    p->pLeft = p->pRight = p->pParent = NULL;
    return p;
}

void insertNode(Node<T> *&root, int k) {
    insert(root, k, root);
}

void insert(Node<T> *&root, int value, Node<T> *parent) {
    Node<T> *p = createNode(value);
    if (root == NULL) {
        p->pParent = parent;
        root = p;
    }
    if (root->key == value) {
        return;
    }
    else if (root->key > value) {
        insert(root->pLeft, value, root);
    }
    else {
        insert(root->pRight, value, root);
    }
}

Node<T> *convertArrayToTree(int a[], int n) {
    Node<T> *root = NULL;
    for (int i = 0; i < n; ++i) {
        insertNode(root, a[i]);
    }
    return root;
}

Node<T> *searchTree(Node<T> *root, int k) {
    if (root == NULL || root->key == k) {
        return root;
    }
    else if (root->key > k) {
        return searchTree(root->pLeft, k);
    }
    else {
        return searchTree(root->pRight, k);
    }
}

Node<T> *searchTree(Node<T> *root, int k) {
    Node<T> *p = root;
    while (p != NULL && p->key != k) {
        if (p->key > k) {
            p = p->pLeft;
        }
        else {
            p = p->pRight;
        }
    }
    return p;
}

int removeNode(Node<T> *&root, int k) {
    Node<T> *tmp = searchTree(root, k);
    if (tmp == NULL) {
        return 0;
    }
    return remove(root, k);
}

int remove(Node<T> *&root, int x) {
    if (root->key > x) {
        return removeNode(root->pLeft, x);
    }
    else if (root->key < x) {
        return removeNode(root->pRight, x);
    }
    else {
        if (root->pLeft == NULL || root->pRight == NULL) {
            Node<T> *tmp = root->pLeft ? root->pLeft : root->pRight;
            if (tmp != NULL) {
                tmp->pParent = root->pParent;
            }
            delete root;
            root = tmp;
        }
        else {
            Node<T> *successor = findSuccessor(root);
            root->key = successor->key;
            return removeNode(root->pRight, successor->key);
        }
    }
    return 1;
}

Node<T> *findSuccessor(Node<T> *tmp) {
    tmp = tmp->pRight;
    while (tmp->pLeft != NULL) {
        tmp = tmp->pLeft;
    }
    return tmp;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
