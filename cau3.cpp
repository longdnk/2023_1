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

// C duyệt theo thứ tự node left right => nếu tìm được phân só đạt yêu cầu thì cập nhật kết quả
// => khởi tạo phần tử là { 0, 0 } (phân số không xác định), tìm không được thì luôn trả về { 0, 0 } => báo lỗi hoặc cây rỗng
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

// Tổng quát duyệt node left right
void nodeLeftRight(Node *root) {
    if (root == NULL) {
        return;
    }
    cout << root->key << '\n';
    nodeLeftRight(root->left);
    nodeLeftRight(root->right);
}

// D
// Để thực hiện được việc duyệt qua 1 cây nhị phân mà không dùng stack queue lẫn đệ quy
// ta sử dụng phương pháp Morris Traversal
// ý tưởng lớn của phương pháp này là 
/// tận dụng các con trỏ rỗng trong cây để lưu trữ thông tin về việc quay lại nút gốc sau khi duyệt nút trái.
void inorderTraversal(Node *root, PhanSo x) {
    while (root) {
        if (root->left == NULL) {
            if (root->key.tu == x.tu) {
                cout << root->key.tu << '/' << root->key.mau << '\n';
            }
            root = root->right;
        }
        else {
            Node *current = root->left;
            while (current->right && current->right != root) {
                current = current->right;
            }
            if (current->right == root) {
                current->right = NULL;
                root = root->right;
            }
            else {
                if (root->key.tu == x.tu) {
                    cout << root->key.tu << '/' << root->key.mau << '\n';
                }
                current->right = root;
                root = root->left;
            }
        }
    }
}

// tổng quát Morris Traversal 
void morrisTraversal(Node *root) {
    while (root) {
        if (root->left == NULL) {
            cout << root->key << ' ';
            root = root->right;
        }
        else {
            Node *current = root->left;
            while (current->right && current->right != root) {
                current = current->right;
            }
            if (current->right == root) {
                current->right = NULL;
                root = root->right;
            }
            else {
                cout << root->key << ' ';
                current->right = root;
                root = root->left;
            }
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}