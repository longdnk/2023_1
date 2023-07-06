#include <bits/stdc++.h>
#include "cau1.cpp"
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

// A
struct Node {
    PhanSo key;
    Node *next;
};

struct List {
    Node *head;
    Node *tail;
};

// B vì đề không nói rõ độ phức tạp khi thêm vào là bao nhiêu nên có 2 cách
// cách 1 sử dụng con trỏ tail để cấp phát, ngắn gọn hơn và chi phí thêm là O(1)

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
// cách 2: duyệt hết danh sách để tìm vị trí cuối cùng và chèn vào vị trí này độ phức tạp O(n)
void addLast(List *&ls, PhanSo x) {
    Node *p = createNode(x);
    if (ls->head == NULL && ls->tail == NULL) {
        ls->head = ls->tail = p;
    }
    else {
        Node *last = ls->head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = p;
        ls->tail = p;
    }
}

Node *createNode(PhanSo x) {
    Node *p = new Node;
    p->key = x;
    p->next = NULL;
    return p;
}

// C
// Lưu ý: các phân số có giá trị bằng nhau có nghĩa là các phân số có sự giống nhau khi rút gọn ví dụ: 1/2, 2/4, 3/6
// ta có 2 cách để giải quyết vấn đề như sau
// cách 1: tạo 1 danh sách liên kết phụ và tiến hành duyệt qua danh sách đề cho, mỗi lần duyệt ta thực hiện việc thêm vào đầu
// khi đó danh sách được đưa ra đảm bảo có thự tự ngược lại, nhưng cách ngày sẽ phức tạp vì phải viết hàm thêm vào đầu
// cách 2: tạo 1 mảng phụ để chứa kết quả, mỗi khi duyệt qua danh sách đề cho ta đưa các phân số này vào mảng và khi in chỉ cần
// dùng for từ vị trí cuối về đầu là xong.

// Cách 1 câu C
void insertHead(Node *&head, PhanSo x) {
    Node *p = createNode(x);
    p->next = head;
    head = p;
}

void printRes(List *ls, PhanSo x) {
    Node *tmp = NULL;
    while (ls->head != NULL) {
        if (ls->head->key.tu * x.mau == ls->head->key.mau * x.tu) {
            insertHead(tmp, ls->head->key);
        }
        ls->head = ls->head->next;
    }
    while (tmp != NULL) {
        cout << tmp->key.tu << '/' << tmp->key.mau << ' ';
    }
}
// Cách 2 câu C
void printFrac(List *ls, PhanSo x) {
    PhanSo *a = new PhanSo[getListSize(ls) + 1]; // tạo mảng phụ
    int index = 0;
    while (ls->head != NULL) {
        if (ls->head->key.tu * x.mau == ls->head->key.mau * x.tu) {
            a[index] = ls->head->key;
            ++index;
        }
        ls->head = ls->head->next;
    }
    for (int i = index - 1; i >= 0; --index) {
        cout << a[i].tu << '/' << a[i].mau << ' ';
    }
}

int getListSize(List *ls) {
    int size = 0;
    while (ls->head != NULL) {
        ++size;
        ls->head = ls->head->next;
    }
    return size;
}

// Câu D
// vì đề không yêu cầu độ phức tạp nên ta sử dụng thuât toán Interchange sort cho danh sách liên kết để thực hiện
// Độ phức tạp O(N ^ 2)
// Dùng for
void sortList(List *ls) {
    for (Node *p = ls->head; p != NULL; p = p->next) {
        for (Node *q = p->next; q != NULL; q = q->next) {
            if (p->key.tu % 2 == 0 && q->key.tu % 2 == 0 && compare(p->key, q->key) == 1) {
                swap(p->key, q->key);
            }
            if (p->key.tu % 2 != 0 && q->key.tu % 2 != 0 && compare(p->key, q->key) == -1) {
                swap(p->key, q->key);
            }
        }
    }
}
// Dùng while
void sortList(List *ls) {
    Node *current = ls->head;
    Node *tmp = NULL;
    while (current != NULL) {
        tmp = current->next;
        while (tmp != NULL) {
            if (current->key.tu % 2 == 0 && tmp->key.tu % 2 == 0 && compare(current->key, tmp->key) == 1) {
                swap(current->key, tmp->key);
            }
            if (current->key.tu % 2 != 0 && tmp->key.tu % 2 != 0 && compare(current->key, tmp->key) == -1) {
                swap(current->key, tmp->key);
            }
            tmp = tmp->next;
        }
        current = current->next;
    }
}

void swap(PhanSo &a, PhanSo &b) {
    PhanSo tmp = a;
    a = b;
    b = tmp;
}

// cách giải khác có độ phúc tạp O(nlogn)
List *sort(List *&ls) {
    ls->head = mergeSort(ls->head);
    while (ls->tail->next != NULL) {
        ls->tail = ls->tail->next;
    }
    return ls;
}

Node *mergeSort(Node *head) {
    if (!head || !head->next)
        return head;
    Node *second = split(head);
    head = mergeSort(head);
    second = mergeSort(second);
    return merge(head, second);
}

Node *merge(Node *first, Node *second) {
    if (first == NULL)
        return second;

    if (second == NULL)
        return first;

    if (compare(first->key, second->key) == -1 && first->key.tu % 2 == 0 && second->key.tu % 2 == 0) {
        first->next = merge(first->next, second);
        return first;
    }
    
    else if (compare(first->key, second->key) == 1 && first->key.tu % 2 != 0 && second->key.tu % 2 != 0) {
        second->next = merge(first, second->next);
        return second;
    }
}

Node *split(Node *head) {
    Node *fast = head, *slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node *temp = slow->next;
    slow->next = NULL;
    return temp;
}

// Phần này là code bổ sung thêm kiến thức về việc sắp xếp danh sách liên kết 
// giả sử ta có danh sách liên kết các số nguyên
struct tmpList {
    int key;
    tmpList *next;
};

// O(N ^ 2), Interchange Sort
// Dùng for
void InterchangeSort(tmpList *&head) {
    for (tmpList *p = head; p != NULL; p = p->next) {
        for (tmpList *q = p->next; q != NULL; q = q->next) {
            if (p->key > q->key) {
                int tmp = p->key;
                p->key = q->key;
                q->key = tmp;
            }
        }
    }
}
// Dùng while
void InterchangeSort(tmpList *&head) {
    tmpList *currentNode = head;
    tmpList *nextNode = NULL;
    while (currentNode != NULL) {
        nextNode = currentNode->next;
        while (nextNode != NULL) {
            if (currentNode->key > nextNode->key) {
                int tmp = currentNode->key;
                currentNode->key = nextNode->key;
                nextNode->key = tmp;
            }
            nextNode = nextNode->next;
        }
        currentNode = currentNode->next;
    }
}
//  O(nlogn) Merge Sort
tmpList *mergeSort(tmpList *head) {
    if (!head || !head->next)
        return head;
    tmpList *second = split(head);
    head = mergeSort(head);
    second = mergeSort(second);
    return merge(head, second);
}

tmpList *merge(tmpList *first, tmpList *second) {
    if (first == NULL)
        return second;

    if (second == NULL)
        return first;

    if (first->key < second->key) {
        first->next = merge(first->next, second);
        return first;
    }
    else {
        second->next = merge(first, second->next);
        return second;
    }
}

tmpList *split(tmpList *head) {
    tmpList *fast = head, *slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    tmpList *temp = slow->next;
    slow->next = NULL;
    return temp;
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
        // addLast(test, a[i]);
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