#include <bits/stdc++.h>
#include "nguyenham.cpp"
using namespace std;

// Thiết kế danh sách liên kết đơn các phân số để thêm vào cuối trong O(1) ta có các ràng buộc
// O(1) nghĩa là chương trình chỉ được thực hiên các công việc ở mức độ hằng số (các phép gán, cộng trừ, so sánh if else...)
// Vì vậy cần có cách chèn phần tử mới vào trong danh sách chỉ bằng cách gán (khả thi nhất và dễ nhất)
// cách giải quyết: sử dụng 2 con trỏ vào danh sách liên kết 1 con trỏ head và 1 con trỏ tail
// con trỏ head chỉ vào phần tử nằm đầu danh sách, tail chỉ phần từ nằm cuối danh sách
// dựa vào ý tưởng trên ta có 2 trường hợp khi thêm mới
// TH1: danh sách rỗng => cho con trỏ head và tail chỉ vào cùng 1 phần tử
// TH2: danh sách khác rỗng => chỉ cấp phát con trỏ tail bằng cách mở rộng vùng nhớ và đưa con trỏ tail vào đúng vị trí
// => các bước này chỉ tốn không quá 3 phép gán => O(1)

struct Node {
    PhanSo key;
    Node *next;
};

struct List {
    Node *head;
    Node *tail;
};

Node *createNode(PhanSo x) {
    Node *p = new Node;
    p->key = x;
    p->next = NULL;
    return p;
}

void insertLast(List *&ls, PhanSo k) {
    Node *p = createNode(k);
    if (ls->head == NULL && ls->tail == NULL) { // hàng chờ rỗng
        ls->head = ls->tail = p;
    }
    else { // hàng chờ khác rỗng
        ls->tail->next = p;
        ls->tail = p;
    }
}

// code bổ sung để minh họa 
List *init() {
    List *ls = new List;
    ls->head = ls->tail = NULL;
    return ls;
}

void output(List *ls) {
    while (ls->head != NULL) {
        auto [tu, mau] = ls->head->key;
        cout << tu << ' ' << mau << '\n';
        ls->head = ls->head->next;
    }
}

List *mockupData() {
    List *test = init();
    PhanSo a[] = { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 }, { 9, 10 } };
    int n = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < n; ++i) {
        insertLast(test, a[i]);
    }
    return test;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    List *ls = mockupData();
    output(ls);
}