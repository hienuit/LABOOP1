#include <iostream>
using namespace std;
void FailureTable(int a[], int m, int failure[]) {
    failure[0] = 0;  // Giá trị đầu tiên luôn là 0
    int j = 0;       // Số lượng ký tự khớp
    for (int i = 1; i < m; i++) {
        while (j > 0 && a[i] != a[j]) {
            j = failure[j - 1];  // Nhảy về vị trí trước đó trong bảng thất bại
        }
        if (a[i] == a[j]) {
            j++;
        }
        failure[i] = j;  // Lưu số ký tự khớp dài nhất tại vị trí i
    }
}

//Thuật toán KMP dùng để so khớp mảng con A với B
int KMP(int a[], int b[], int m, int n, int positions[]) {
    int failure[m];
    FailureTable(a, m, failure);  // Tạo bảng thất bại cho A

    int j = 0;  // Biến đếm số ký tự đã khớp
    int count = 0;
    for (int i = 0; i < n; i++) {
        // Nếu không khớp, quay lại vị trí trong bảng thất bại
        while (j > 0 && b[i] != a[j]) {
            j = failure[j - 1];
        }
        if (b[i] == a[j]) {
            j++;  // Khớp thêm 1 ký tự
        }
        
        if (j == m) {
            //khớp toàn bộ
            positions[count++] = i - m + 1;  // Lưu vị trí xuất hiện của A
            j = failure[j - 1];  // Tiếp tục tìm kiếm
        }
    }
    return count;
}

int main() {
    int m,n;
    cout << "Nhập số phần tử của mảng A và B: ";
    cin >> m >> n;

    int a[m], b[n];
    
    cout << "Nhập các phần tử của mảng A: ";
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }

    cout << "Nhập các phần tử của mảng B: ";
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    int positions[n];

    int occurrences = KMP(a, b, m, n, positions);

    cout << "Số lần mảng A xuất hiện trong mảng B: " << occurrences << endl;
    if (occurrences > 0) {
        cout << "Các vị trí bắt đầu: ";
        for (int i = 0; i < occurrences; i++) {
            cout << positions[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
