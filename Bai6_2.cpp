#include<iostream>
#include<vector>
#include<string>
#include<algorithm> 
using namespace std;

struct HocSinh{
    string ho_ten;
    float diemtoan, diemvan, diemnn;
};

bool KiemTraHoTen(string ho_ten) {
    // Kiểm tra xem họ tên có chứa ký tự đặc biệt không
    for (char c : ho_ten) {
        if (isdigit(c)) return false;
    }
    return true;
}

void Nhap(HocSinh &hs){
    do {
        cout << "Ho ten hoc sinh: ";
        getline(cin, hs.ho_ten);
    } while (!KiemTraHoTen(hs.ho_ten) || hs.ho_ten.empty());

    do {
        cout << "Nhap diem toan: ";
        cin >> hs.diemtoan;
    } while (hs.diemtoan > 10 || hs.diemtoan < 0);

    do {
        cout << "Nhap diem van: ";
        cin >> hs.diemvan;
    } while (hs.diemvan > 10 || hs.diemvan < 0);

    do {
        cout << "Nhap diem ngoai ngu: ";
        cin >> hs.diemnn;
    } while (hs.diemnn > 10 || hs.diemnn < 0);

    cin.ignore();
}

void NhapDS(HocSinh a[], int n){
    for(int i = 0; i < n; ++i){
        cout << "Thong tin hoc sinh thu " << i+1 << " la:" << endl;
        Nhap(a[i]);
    }
}

float DiemTB(HocSinh hs){
    return ((2 * hs.diemtoan) + hs.diemvan + hs.diemnn) / 4;
}

void Xuat(HocSinh hs){
    cout << "Ho ten hoc sinh: " << hs.ho_ten << endl;
    cout << "Diem toan: " << hs.diemtoan << endl;
    cout << "Diem van: " << hs.diemvan << endl;
    cout << "Diem ngoai ngu: " << hs.diemnn << endl;
    cout << "Diem trung binh: " << DiemTB(hs) << endl;
}

void XepLoai(HocSinh hs){
    float diem = DiemTB(hs);
    if (diem >= 9) cout << "Xuat sac" << endl;
    else if (diem >= 8) cout << "Gioi" << endl;
    else if (diem >= 6.5) cout << "Kha" << endl;
    else if (diem >= 5) cout << "Trung binh" << endl;
    else cout << "Yeu" << endl;
}

void XepLoaiHS(HocSinh hs[], int n){
    for (int i = 0; i < n; ++i){
        cout << "Xep loai cua hoc sinh thu " << i+1 << " la: ";
        XepLoai(hs[i]);
    }
}

float TBCaoNhat(HocSinh hs[], int n){
    float diemmax = DiemTB(hs[0]);
    for (int i = 1; i < n; ++i){
        if (DiemTB(hs[i]) > diemmax) diemmax = DiemTB(hs[i]);
    }
    return diemmax;
}

float WorstMathPoint(HocSinh hs[], int n){
    float diemmin = hs[0].diemtoan;
    for (int i = 1; i < n; ++i){
        if (hs[i].diemtoan < diemmin) diemmin = hs[i].diemtoan;
    }
    return diemmin;
}

// Ham tim kiem hoc sinh theo ten
void TimKiemHocSinh(HocSinh hs[], int n, string keyword){
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower); // Chuyển keyword thành chữ thường

    bool found = false;
    for (int i = 0; i < n; ++i){
        string name = hs[i].ho_ten;
        transform(name.begin(), name.end(), name.begin(), ::tolower); // Chuyển họ tên thành chữ thường

        if (name.find(keyword) != string::npos) {
            Xuat(hs[i]);
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay hoc sinh nao!" << endl;
}

int main(){
    HocSinh hs[100];
    int n;
    cout << "Nhap vao so hoc sinh: ";
    cin >> n;
    cin.ignore();  // Xử lý ký tự xuống dòng sau khi nhập số lượng

    NhapDS(hs, n);

    int select;
    do {
        cout << "Menu:\n1. Nhap danh sach hoc sinh\n2. Xep loai hoc sinh\n3. Tim hoc sinh co diem TB cao nhat\n4. Tim hoc sinh co diem toan thap nhat\n5. Tim kiem hoc sinh theo ten\n0. Thoat\nChon: ";
        cin >> select;
        cin.ignore();

        if(select == 1){
            NhapDS(hs, n);
        } else if (select == 2){
            XepLoaiHS(hs, n);
        } else if (select == 3){
            float diem_max = TBCaoNhat(hs, n);
            for(int i = 0; i < n; ++i){
                if(DiemTB(hs[i]) == diem_max) {
                    Xuat(hs[i]);
                }
            }
        } else if (select == 4){
            float min_toan = WorstMathPoint(hs, n);
            for (int i = 0; i < n; ++i){
                if (hs[i].diemtoan == min_toan) {
                    cout << "Thong tin cua hoc sinh co diem toan thap nhat la: ";
                    Xuat(hs[i]);
                }
            }
        } else if (select == 5){
            string keyword;
            cout << "Nhap tu khoa tim kiem ten: ";
            getline(cin, keyword);
            TimKiemHocSinh(hs, n, keyword);
        }
    } while(select != 0);

    return 0;
}
