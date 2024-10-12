#include <iostream>
#include <iomanip> 
using namespace std;

//Kiểm tra năm nhuận
bool KTNamNhuan(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Hàm tính số ngày của mỗi tháng trong năm
int DaysInMonth(int month, int year) {
    int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && KTNamNhuan(year)) {
        return 29;
    }
    return daysPerMonth[month - 1];
}

// Hàm kiểm tra xem ngày nhập vào có hợp lệ không
bool ValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > DaysInMonth(month, year)) {
        return false;
    }
    return true;
}

// Hàm tính xem ngày hôm sau là ngày mấy
void NgayTiepTheo(int& day, int& month, int& year) {
    if (day < DaysInMonth(month, year)) {
        day++;
    }
    else {
        day = 1;
        if (month < 12) {
            month++;
        }
        else {
            month = 1;
            year++;
        }
    }
}

// Hàm tính xem ngày hôm trước là ngày mấy
void NgayTruoc(int& day, int& month, int& year) {
    if (day > 1) {
        day--;
    }
    else {
        if (month > 1) {
            month--;
            day = DaysInMonth(month, year);
        }
        else {
            month = 12;
            day = 31;
            year--;
        }
    }
}

// Hàm tính xem ngày đó là ngày thứ mấy trong năm
int NgayThuN(int day, int month, int year) {
    int dayCount = 0;
    for (int i = 1; i < month; i++) {
        dayCount += DaysInMonth(i, year);
    }
    dayCount += day;
    return dayCount;
}

// Hàm check xem input nhập vào có đúng định dạng DD/MM/YYYY không
bool ValidFormat(const string& date) {
    return date.size() == 10 && date[2] == '/' && date[5] == '/';
}

int main() {
    string input;
    int day, month, year;

    // Nhập lại nếu sai định dạng
    while (true) {
        cout << "Nhap vao ngay thang nam (DD/MM/YYYY): ";
        cin >> input;

        if (!ValidFormat(input)) {
            cout << "Loi: Dinh dang ngay thang nam khong dung!" << endl;
            continue;  
        }

        day = stoi(input.substr(0, 2));
        month = stoi(input.substr(3, 2));
        year = stoi(input.substr(6, 4));

       
        if (!ValidDate(day, month, year)) {
            cout << "Loi: Ngay thang nam khong hop le!" << endl;
            continue;  
        }

        break;
    }

    int next_day = day, next_month = month, next_year = year;
    NgayTiepTheo(next_day, next_month, next_year);
    cout << "Ngay tiep theo la: "
        << setw(2) << setfill('0') << next_day << "/"
        << setw(2) << setfill('0') << next_month << "/"
        << next_year << endl;

    int prev_day = day, prev_month = month, prev_year = year;
    NgayTruoc(prev_day, prev_month, prev_year);
    cout << "Ngay hom truoc la: "
        << setw(2) << setfill('0') << prev_day << "/"
        << setw(2) << setfill('0') << prev_month << "/"
        << prev_year << endl;

    int day_of_year = NgayThuN(day, month, year);
    cout << "Ngay " << setw(2) << setfill('0') << day << "/"
        << setw(2) << setfill('0') << month << "/" << year
        << " la ngay thu " << day_of_year << " trong nam." << endl;

    return 0;
}
