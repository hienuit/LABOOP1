#include<iostream>
#include<string>
#include<math.h>
using namespace std;

// Khai báo hai thành phần của phân số
struct PhanSo {
    int tu, mau;
};

// Hàm nhập tử và mẫu của phân số và kiểm tra mẫu số nếu bằng 0 thì nhập lại
void Nhap(PhanSo& x, PhanSo& y) {
    do {
        cout << "Nhap phan so thu nhat:" << endl;
        cout << "Nhap tu: "; cin >> x.tu;
        cout << "Nhap mau: "; cin >> x.mau;
    } while (x.mau == 0);

    do {
        cout << "Nhap phan so thu hai: " << endl;
        cout << "Nhap tu: "; cin >> y.tu;
        cout << "Nhap mau: "; cin >> y.mau;
    } while (y.mau == 0);
}

// Hàm tính ước chung lớn nhất của hai số
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
//hàm in ra số nguyên nếu tử số chia hết cho mấu số, nếu không thì để dưới dạng phân số
void InKetQua(int tu, int mau) {
    if (tu % mau == 0) {
        // Nếu tử chia hết cho mẫu, in ra kết quả là số nguyên
        cout << tu / mau << endl;
    }
    else {
        // Ngược lại, in dưới dạng phân số
        cout << tu << "/" << mau << endl;
    }
}
//hàm tính tổng
void TongPhanSo(PhanSo x, PhanSo y) {
    int tong_tu = x.tu * y.mau + x.mau * y.tu;
    int mau_chung = x.mau * y.mau;

    int _gcd = abs(gcd(tong_tu, mau_chung));
    tong_tu = tong_tu / _gcd;
    mau_chung = mau_chung / _gcd;

    if (mau_chung < 0) {
        mau_chung = -mau_chung;
        tong_tu = -tong_tu;
    }

    cout << "Tong hai phan so la: ";
    InKetQua(tong_tu, mau_chung);
}
//hàm tính hiệu
void HieuPhanSo(PhanSo x, PhanSo y) {
    int hieu_tu = x.tu * y.mau - x.mau * y.tu;
    int mau_chung = x.mau * y.mau;

    int _gcd = abs(gcd(hieu_tu, mau_chung));
    hieu_tu = hieu_tu / _gcd;
    mau_chung = mau_chung / _gcd;

    if (mau_chung < 0) {
        mau_chung = -mau_chung;
        hieu_tu = -hieu_tu;
    }

    cout << "Hieu hai phan so la: ";
    InKetQua(hieu_tu, mau_chung);
}
//hàm tính tích
void Tich(PhanSo x, PhanSo y) {
    int tich_tu = x.tu * y.tu;
    int tich_mau = x.mau * y.mau;

    int _gcd = abs(gcd(tich_tu, tich_mau));
    tich_tu = tich_tu / _gcd;
    tich_mau = tich_mau / _gcd;

    if (tich_mau < 0) {
        tich_mau = -tich_mau;
        tich_tu = -tich_tu;
    }

    cout << "Tich cua hai phan so la: ";
    InKetQua(tich_tu, tich_mau);
}

//hàm tính thương
void Thuong(PhanSo x, PhanSo y) {
    if (y.tu == 0) {     // nếu tử =0 thì phân số =0 => không chia được
        cout << "Khong ton tai thuong cua hai phan so" << endl;
    }
    else {
        int thuong_tu = x.tu * y.mau;
        int thuong_mau = x.mau * y.tu;

        int _gcd = abs(gcd(thuong_tu, thuong_mau));
        thuong_tu = thuong_tu / _gcd;
        thuong_mau = thuong_mau / _gcd;

        if (thuong_mau < 0) {
            thuong_mau = -thuong_mau;
            thuong_tu = -thuong_tu;
        }

        cout << "Thuong cua hai phan so la: ";
        InKetQua(thuong_tu, thuong_mau);
    }
}

int main() {
    PhanSo x, y;
    Nhap(x, y);
    TongPhanSo(x, y);
    HieuPhanSo(x, y);
    Tich(x, y);
    Thuong(x, y);
}
