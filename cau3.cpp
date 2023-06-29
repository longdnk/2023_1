#include <bits/stdc++.h>
#include "cau1.cpp"
using namespace std;

struct Node {
    PhanSo key;
    Node *left;
    Node *right;
};
int compare(PhanSo a, PhanSo b);
Node *createNode(PhanSo x);

void insertNode(Node *&root, PhanSo k) {
    if (root == NULL) {
        root = createNode(k);
    }
    if (root->key.tu == k.tu && root->key.mau == k.mau) {
        return;
    }
    else if (compare(root->key, k) == 1) {
        insertNode(root->left, k);
    }
    else {
        insertNode(root->right, k);
    }
}

Node *createNode(PhanSo x) {
    Node *p = new Node;
    p->key = x;
    p->left = p->right = NULL;
    return p;
}

// Quy ước:
// 0 => 2 phân số bằng nhau
// -1 => phân số a lớn hơn b
// 1 => phân số a nhỏ hơn b
int compare(PhanSo a, PhanSo b) {
    int tmp = a.tu * b.mau;
    int nxt = b.tu * a.mau;
    if (tmp == nxt) {
        return 0;
    }
    else if (tmp > nxt) {
        return 1;
    }
    else {
        return -1;
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}