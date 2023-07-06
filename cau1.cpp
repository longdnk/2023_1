#include <bits/stdc++.h>
using namespace std;

// kiểu dữ liệu tự định nghĩa => phân số cấu tạo từ 2 phần tử và mẫu
// với kiểu dữ liệu này có thể lưu vào mảng như sau <ký số> <tên mảng> [] <=> PhanSo a[]
// không cần thiết phải lưu 3 mảng là mảng tử, mảng mẫu và 1 mảng dấu vì đề cho là tử và mẫu là số nguyên dương
// với kiểu là số nguyên dương thì C/C++ sẽ là unsigned int
struct PhanSo {
    unsigned int tu, mau;
};

// A
void input(PhanSo a[], int n) {
    if (n <= 0 || n > 1000) {
        cout << "fail" << '\n';
        return;
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i].tu >> a[i].mau;
    }
}

// B
// Lưu ý: 
// + Phân Số Lẻ => Tử hoặc Mẫu là số lẻ
// + Phân Số Chẵn = > Tử và Mẫu đều là số chẵn
PhanSo TinhTong(PhanSo a[], int n, int k, PhanSo x) {
    if (k < 0 || k > 1000) {
        return { 0, 0 };
    }
    PhanSo res = { 0, 0 };
    for (int i = 0; i < n; ++i) {
        if (a[i].tu * x.mau == a[i].mau * x.tu) {
            res = Cong(a[i], x);
        }
        if (i - k >= 0 && kiemTraLe(a[i - k])) { // case cho phân số lẻ
            res = Cong(res, a[i - k]);
        }
        if (i + k >= 0 && i + k <= 1000 && kiemTraLe(a[i + k])) {
            res = Cong(res, a[i + k]);
        }
    }
    return res;
}

PhanSo Cong(PhanSo a, PhanSo b) {
    PhanSo res = { 0, 0 };
    if (a.mau == b.mau) {
        res.tu += a.tu + b.tu;
        res.mau = b.mau;
    }
    else {
        res.tu = a.tu * b.mau + b.tu * a.mau;
        res.mau = a.mau * b.mau;
    }
    return res;
}

bool kiemTraLe(PhanSo a) {
    return a.tu % 2 != 0 || a.mau % 2 != 0;
}

bool kiemTraChan(PhanSo a) {
    return a.tu % 2 == 0 && a.mau % 2 == 0;
}

// C
// Ý tưởng: vì n <= 1000 (đề cho), ta có thể tạo 1 mảng phụ chứa kết quả và sau cùng sao chép từ mảng này vào lại mảng a
// + Phân Số Chẵn = > Tử và Mẫu đều là số chẵn
// + Phân Số Lẻ => Tử hoặc Mẫu là số lẻ
void change(PhanSo a[], int n) {
    PhanSo *b = new PhanSo[1001];
    int bIndex = 0;
    for (int i = 0; i < n; ++i) {
        if (kiemTraChan(a[i])) {
            b[bIndex] = a[i];
            ++bIndex;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (kiemTraLe(a[i])) {
            b[bIndex] = a[i];
            ++bIndex;
        }
    }
    for (int i = 0; i < bIndex; ++i) {
        a[i] = b[i];
    }
}

// D
// vì yêu cầu để không cho thêm mảng tạm nên ta thực hiện các công việc sau để đảm bảo yêu cầu:
// Sao chép và đè ngược lên mảng ban đầu => thao tác sao chép và xử lý thông qua 1 mảng duy nhất
// cách 1
void remove(PhanSo a[], int &n) {
    if (n == 0) {
        return;
    }
    int index = 1;

    for (int i = 1; i < n; i++) {
        bool isDuplicate = false;
        for (int j = 0; j < index; j++) {
            if (compare(a[i], a[j]) == 0) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            a[index] = a[i];
            ++index;
        }
    }
    n = index;
}

// cách 2
// dùng 2 for tìm các phân số bằng nhau về tính chât nếu thỏa tiến hành dời các phần tử về bên trái của mảng
// => sẽ có trường hợp sau khi mảng bị đè mà các phần tử liên tiếp nhau => lỗi logic do đang xét j + 1
// => để khắc phục thì khi tìm thấy dời j về 1 đơn vị, tiếp tục xét các phân số đồng dạng nhau
void removeDuplicate(PhanSo a[], int &n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (compare(a[i], a[j]) == 0) {
                deleteElement(a, n, a[j]);
                --j;
            }
        }
    }
}

void deleteElement(PhanSo a[], int &n, PhanSo x) {
    int flag = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i].tu == x.tu && a[i].mau == x.mau) {
            flag = i;
            break;
        }
    }
    if (flag != -1) {
        --n;
        for (int j = flag; j < n; ++j) {
            a[j] = a[j + 1];
        }
    }
}

// Quy ước
// 0 => phân số a = b
// 1 => a > b
// -1 => a < b
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
    PhanSo a[] = { { 1, 2 }, { 2, 4 }, { 3, 6 }, { 3, 4 }, { 5, 6 }, { 7, 8 }, { 9, 10 }, { 8, 10 } };
    int n = sizeof(a) / sizeof(a[0]);
    // remove(a, n);
    // display(a, n);
}