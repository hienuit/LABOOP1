#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

struct ChuyenBay {
    string ma_bay, ngay_bay, gio_bay, noi_di, noi_den;
};

// Kiểm tra xem chuỗi có chứa ký tự đặc biệt hoặc khoảng trắng không
bool KiemTraKyTuDacBiet(const string& s) {
    for (char c : s) {
        if (!isalnum(c)) // Kiểm tra nếu không phải là ký tự chữ hoặc số
            return false;
    }
    return true;
}

// Kiểm tra mã chuyến bay (không quá 5 ký tự, không có khoảng trắng, ký tự đặc biệt)
bool KiemTraMaChuyenBay(const string& ma) {
    return ma.length() <= 5 && KiemTraKyTuDacBiet(ma);
}

// Kiểm tra ngày hợp lệ theo định dạng YYYY-MM-DD
bool KiemTraNgayBay(const string& ngay) {
    if (ngay.length() != 10 || ngay[4] != '-' || ngay[7] != '-')
        return false;

    int year = stoi(ngay.substr(0, 4));
    int month = stoi(ngay.substr(5, 2));
    int day = stoi(ngay.substr(8, 2));

    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    // Kiểm tra số ngày trong từng tháng
    int daysInMonth[] = { 31, (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return day <= daysInMonth[month - 1];
}

// Kiểm tra giờ bay hợp lệ theo định dạng HH:MM
bool KiemTraGioBay(const string& gio) {
    if (gio.length() != 5 || gio[2] != ':')
        return false;

    int hour = stoi(gio.substr(0, 2));
    int minute = stoi(gio.substr(3, 2));

    return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
}

// Kiểm tra nơi đi/nơi đến (không quá 20 ký tự, không chứa số và ký tự đặc biệt)
bool KiemTraNoiDiDen(const string& noi) {
    if (noi.length() > 20)
        return false;

    for (char c : noi) {
        if (!isalpha(c) && c != ' ') // Chỉ cho phép chữ cái và khoảng trắng
            return false;
    }
    return true;
}

void Nhap(ChuyenBay& fl) {
    do {
        cout << "Thong tin ma chuyen bay la (khong qua 5 ky tu, khong co ky tu dac biet): ";
        cin >> fl.ma_bay;
    } while (!KiemTraMaChuyenBay(fl.ma_bay));

    do {
        cout << "Thong tin ngay bay (YYYY-MM-DD): ";
        cin >> fl.ngay_bay;
    } while (!KiemTraNgayBay(fl.ngay_bay));

    do {
        cout << "Thong tin gio bay (HH:MM): ";
        cin >> fl.gio_bay;
    } while (!KiemTraGioBay(fl.gio_bay));

    cin.ignore(); // Bỏ qua ký tự xuống dòng sau khi nhập

    do {
        cout << "Thong tin noi di (khong qua 20 ky tu, chi chu cai): ";
        getline(cin, fl.noi_di);
    } while (!KiemTraNoiDiDen(fl.noi_di));

    do {
        cout << "Thong tin noi den (khong qua 20 ky tu, chi chu cai): ";
        getline(cin, fl.noi_den);
    } while (!KiemTraNoiDiDen(fl.noi_den));
}

void NhapDS(ChuyenBay fl[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << "Thong tin cua chuyen bay thu " << i + 1 << " la: " << endl;
        Nhap(fl[i]);
    }
}

void TimKiemChuyenBay(ChuyenBay fl[], int n) {
    string key;
    cout << "Nhap ma chuyen bay, noi di hoac noi den de tim kiem: ";
    getline(cin, key); // Sử dụng getline để đọc cả chuỗi có khoảng trắng
    bool found = false;
    
    for (int i = 0; i < n; ++i) {
        if (fl[i].ma_bay == key || fl[i].noi_di == key || fl[i].noi_den == key) {
            cout << "Chuyen bay tim thay: " << fl[i].ma_bay << " " << fl[i].ngay_bay
                 << " " << fl[i].gio_bay << " " << fl[i].noi_di << " -> " << fl[i].noi_den << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Khong tim thay chuyen bay!" << endl;
    }
}

bool SoSanhThoiGian(ChuyenBay& a, ChuyenBay& b) {
    if (a.ngay_bay == b.ngay_bay)
        return a.gio_bay < b.gio_bay; // Sắp xếp theo giờ nếu ngày bằng nhau
    return a.ngay_bay < b.ngay_bay;  // Sắp xếp theo ngày
}

void SapXepChuyenBay(ChuyenBay fl[], int n) {
    sort(fl, fl + n, SoSanhThoiGian);
    cout << "Danh sach chuyen bay sau khi sap xep: \n";
    for (int i = 0; i < n; ++i) {
        cout << fl[i].ma_bay << " " << fl[i].ngay_bay << " " << fl[i].gio_bay
             << " " << fl[i].noi_di << " -> " << fl[i].noi_den << endl;
    }
}

void HienThiChuyenBayTheoNoi(ChuyenBay fl[], int n) {
    string noi, ngay;
    cout << "Nhap noi di: ";
    getline(cin, noi);
    cout << "Nhap ngay khoi hanh (YYYY-MM-DD): ";
    cin >> ngay;
    cin.ignore(); // Bỏ qua ký tự xuống dòng
    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (fl[i].noi_di == noi && fl[i].ngay_bay == ngay) {
            cout << "Chuyen bay: " << fl[i].ma_bay << " " << fl[i].ngay_bay << " "
                 << fl[i].gio_bay << " " << fl[i].noi_di << " -> " << fl[i].noi_den << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Khong tim thay chuyen bay!" << endl;
    }
}

void DemChuyenBay(ChuyenBay fl[], int n) {
    string noi_di, noi_den;
    int count = 0;
    cout << "Nhap noi di: ";
    getline(cin, noi_di);
    cout << "Nhap noi den: ";
    getline(cin, noi_den);
    for (int i = 0; i < n; ++i) {
        if (fl[i].noi_di == noi_di && fl[i].noi_den == noi_den) {
            count++;
        }
    }
    cout << "So luong chuyen bay tu " << noi_di << " den " << noi_den << ": " << count << endl;
}

void Menu(ChuyenBay fl[], int n) {
    int choice;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Tim kiem chuyen bay\n";
        cout << "2. Sap xep danh sach chuyen bay theo ngay gio khoi hanh\n";
        cout << "3. Hien thi chuyen bay theo noi di va ngay\n";
        cout << "4. Dem chuyen bay tu noi di den noi den\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore(); // Bỏ qua ký tự xuống dòng sau khi nhập

        switch (choice) {
        case 1:
            TimKiemChuyenBay(fl, n);
            break;
        case 2:
            SapXepChuyenBay(fl, n);
            break;
        case 3:
            HienThiChuyenBayTheoNoi(fl, n);
            break;
        case 4:
            DemChuyenBay(fl, n);
            break;
        case 0:
            cout << "Thoat chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

int main() {
    int n;
    cout << "Nhap so luong chuyen bay: ";
    cin >> n;
    cin.ignore(); // Bỏ qua ký tự xuống dòng sau khi nhập số lượng chuyến bay
    ChuyenBay ds[n];
    NhapDS(ds, n);
    
    Menu(ds, n); // Gọi hàm menu

    return 0;
}
