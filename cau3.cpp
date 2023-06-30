#include <bits/stdc++.h>
#include "cau1.cpp"
using namespace std;

// A
struct Node {
    PhanSo key;
    Node *left;
    Node *right;
};

// B
void insertNode(Node *&root, PhanSo k) {
    if (root == NULL) {
        root = createNode(k);
    }
    if (root->key.tu == k.tu && root->key.mau == k.mau) { // phân số bị trùng 
        return;
    }
    else if (compare(root->key, k) == 1) { // dùng lại hàm so sánh câu 2
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

// C
PhanSo findMaxSum(Node *root) {
    PhanSo res = { 0, 0 };
    traversal(root, res);
    return res;
}

void traversal(Node *root, PhanSo &res) {
    if (root == NULL) {
        return;
    }
    res = getMax(res, root->key);
    traversal(root->left, res);
    traversal(root->right, res);
}

PhanSo getMax(PhanSo a, PhanSo b) {
    return a.tu + a.mau > b.tu + b.mau ? a : b;
}

// D
// Để thực hiện được việc duyệt qua 1 cây nhị phân mà không dùng stack queue lẫn đệ quy
// ta sử dụng phương pháp Morris Traversal
// ý tưởng lớn của phương pháp này là 
/// tận dụng các con trỏ rỗng trong cây để lưu trữ thông tin về việc quay lại nút gốc sau khi duyệt nút trái.
void inorderTraversal(Node *root, PhanSo x) {
    Node* curr = root;
    while (curr != NULL) {
        if (curr->left == NULL) {
            if (curr->key.tu == x.tu) {
                cout << curr->key.mau << '/' << curr->key.mau << '\n';
            }
            curr = curr->right;
        }
        else {
            Node* pre = curr->left;
            while (pre->right != NULL && pre->right != curr) {
                pre = pre->right;
            }
            if (pre->right == NULL) {
                pre->right = curr;
                curr = curr->left;
            }
            else {
                pre->right = nullptr;
                if (curr->key.tu == x.tu) {
                    cout << curr->key.mau << '/' << curr->key.mau << '\n';
                }
                curr = curr->right;
            }
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}