#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Kiểu dữ liệu để lưu thông tin về ngày
struct Date {
    int day, month, year;

    // Kiểm tra ngày hợp lệ
    bool isValid() const {
        return isDayValid() && isMonthValid() && year >= 0;
    }

    // Kiểm tra tính hợp lệ của ngày
    bool isDayValid() const {
        if (day <= 0) return false;
        if (month == 2) {
            return (isLeap() ? day <= 29 : day <= 28);
        }
        return day <= daysInMonth();
    }

    // Kiểm tra tháng hợp lệ
    bool isMonthValid() const {
        return month >= 1 && month <= 12;
    }

    // Kiểm tra năm nhuận
    bool isLeap() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // Số ngày trong tháng
    int daysInMonth() const {
        switch (month) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
            case 4: case 6: case 9: case 11: return 30;
            case 2: return isLeap() ? 29 : 28;
            default: return 0; // Không hợp lệ
        }
    }
};

// Kiểu dữ liệu để lưu thông tin sổ tiết kiệm
struct SavingsAccount {
    string accountNumber; // Mã sổ
    string accountType; // Loại tiết kiệm
    string customerName; // Họ tên khách hàng
    long long identityNumber; // Chứng minh nhân dân
    Date openingDate; // Ngày mở sổ
    double depositAmount; // Số tiền gửi
    double interestRate; // Lãi suất

    // Hàm kiểm tra mã sổ hợp lệ
    bool isAccountNumberValid() const {
        return !accountNumber.empty() && accountNumber.size() <= 5 && all_of(accountNumber.begin(), accountNumber.end(), [](char c) { return isalnum(c); });
    }

    // Hàm kiểm tra CMND hợp lệ
    bool isIdentityNumberValid() const {
        string idStr = to_string(identityNumber);
        return (idStr.size() == 9 || idStr.size() == 12); // Kiểm tra độ dài CMND
    }

    // Hàm kiểm tra họ tên hợp lệ
    bool isCustomerNameValid() const {
        return !customerName.empty() && customerName.size() <= 30 && all_of(customerName.begin(), customerName.end(), [](char c) { return isalpha(c) || isspace(c); });
    }

    // Hàm kiểm tra số tiền gửi hợp lệ
    bool isDepositAmountValid() const {
        return depositAmount > 0;
    }

    // Hàm xuất thông tin sổ tiết kiệm
    void displayInfo() const {
        cout << "Mã sổ: " << accountNumber << endl;
        cout << "Loại tiết kiệm: " << accountType << endl;
        cout << "Họ tên khách hàng: " << customerName << endl;
        cout << "CMND: " << identityNumber << endl;
        cout << "Ngày mở sổ: " << openingDate.day << "/" << openingDate.month << "/" << openingDate.year << endl;
        cout << "Số tiền gửi: " << fixed << setprecision(2) << depositAmount << endl;
        cout << "Lãi suất: " << interestRate << "%" << endl;
        cout << "--------------------------------" << endl;
    }

    // Hàm tính lãi suất
    double calculateInterest(int months) const {
        return depositAmount * interestRate * months / 12 / 100;
    }
};

// Hàm nhập thông tin ngày
Date inputDate() {
    Date date;
    while (true) {
        cout << "Nhập ngày (dd mm yyyy): ";
        cin >> date.day >> date.month >> date.year;
        if (date.isValid()) break;
        cout << "Ngày không hợp lệ! Vui lòng nhập lại." << endl;
    }
    return date;
}

// Hàm nhập thông tin sổ tiết kiệm
SavingsAccount inputSavingsAccount() {
    SavingsAccount acc;
    cin.ignore();
    while (true) {
        cout << "Nhập mã sổ: ";
        getline(cin, acc.accountNumber);
        if (acc.isAccountNumberValid()) break;
        cout << "Mã sổ không hợp lệ! Vui lòng nhập lại." << endl;
    }
    cout << "Nhập loại tiết kiệm: ";
    getline(cin, acc.accountType);
    while (true) {
        cout << "Nhập họ tên khách hàng: ";
        getline(cin, acc.customerName);
        if (acc.isCustomerNameValid()) break;
        cout << "Họ tên không hợp lệ! Vui lòng nhập lại." << endl;
    }
    while (true) {
        cout << "Nhập CMND: ";
        cin >> acc.identityNumber;
        if (acc.isIdentityNumberValid()) break;
        cout << "CMND không hợp lệ! Vui lòng nhập lại." << endl;
    }
    acc.openingDate = inputDate();
    while (true) {
        cout << "Nhập số tiền gửi: ";
        cin >> acc.depositAmount;
        if (acc.isDepositAmountValid()) break;
        cout << "Số tiền gửi không hợp lệ! Vui lòng nhập lại." << endl;
    }
    cout << "Nhập lãi suất (%/năm): ";
    cin >> acc.interestRate;
    return acc;
}

// Hàm tính tiền lãi theo thời gian gửi
double calculateTotalInterest(const SavingsAccount& acc, const Date& currentDate) {
    int months = (currentDate.year - acc.openingDate.year) * 12 + (currentDate.month - acc.openingDate.month);
    return acc.calculateInterest(months);
}

// Hàm tìm kiếm sổ tiết kiệm
SavingsAccount* searchSavingsAccount(vector<SavingsAccount>& accountList, const string& keyword) {
    for (SavingsAccount& acc : accountList) {
        if (acc.accountNumber == keyword || to_string(acc.identityNumber) == keyword) {
            return &acc;
        }
    }
    return nullptr;
}

// Hàm liệt kê sổ tiết kiệm mở trong khoảng thời gian xác định
void listSavingsAccountsInPeriod(const vector<SavingsAccount>& accountList, const Date& startDate, const Date& endDate) {
    cout << "Danh sách tài khoản mở trong khoảng thời gian:" << endl;
    for (const SavingsAccount& acc : accountList) {
        if ((acc.openingDate.year > startDate.year || (acc.openingDate.year == startDate.year && acc.openingDate.month >= startDate.month)) &&
            (acc.openingDate.year < endDate.year || (acc.openingDate.year == endDate.year && acc.openingDate.month <= endDate.month))) {
            acc.displayInfo();
        }
    }
}

// Hàm sắp xếp theo số tiền gửi giảm dần
void sortByDepositAmountDescending(vector<SavingsAccount>& accountList) {
    sort(accountList.begin(), accountList.end(), [](const SavingsAccount& a, const SavingsAccount& b) {
        return b.depositAmount < a.depositAmount;
    });
}

// Hàm sắp xếp theo ngày mở sổ tăng dần
void sortByOpeningDateAscending(vector<SavingsAccount>& accountList) {
    sort(accountList.begin(), accountList.end(), [](const SavingsAccount& a, const SavingsAccount& b) {
        if (a.openingDate.year != b.openingDate.year)
            return a.openingDate.year < b.openingDate.year;
        if (a.openingDate.month != b.openingDate.month)
            return a.openingDate.month < b.openingDate.month;
        return a.openingDate.day < b.openingDate.day;
    });
}

// Hàm rút tiền
void withdrawFromAccount(SavingsAccount& acc) {
    double amount;
    cout << "Nhập số tiền muốn rút: ";
    cin >> amount;
    if (amount > acc.depositAmount) {
        cout << "Số tiền rút không được lớn hơn số tiền gửi!" << endl;
        return;
    }
    
    // Nếu rút trước hạn, cảnh báo
    if (amount < acc.depositAmount) {
        double reducedInterestRate = 0.5; // Lãi suất giảm
        cout << "Rút trước hạn, lãi suất sẽ được tính với " << reducedInterestRate << "%/năm." << endl;
        acc.interestRate = reducedInterestRate; // Cập nhật lãi suất
    }

    acc.depositAmount -= amount;
    cout << "Rút tiền thành công! Số tiền hiện tại trong sổ: " << acc.depositAmount << endl;
}

int main() {
    vector<SavingsAccount> savingsAccounts; // Danh sách các sổ tiết kiệm
    int choice;

    do {
        cout << "----- CHƯƠNG TRÌNH QUẢN LÝ SỔ TIẾT KIỆM -----" << endl;
        cout << "1. Nhập sổ tiết kiệm" << endl;
        cout << "2. Tìm kiếm sổ tiết kiệm" << endl;
        cout << "3. Liệt kê sổ tiết kiệm mở trong khoảng thời gian" << endl;
        cout << "4. Sắp xếp theo số tiền gửi" << endl;
        cout << "5. Sắp xếp theo ngày mở sổ" << endl;
        cout << "6. Rút tiền" << endl;
        cout << "0. Thoát" << endl;
        cout << "Chọn chức năng: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                SavingsAccount acc = inputSavingsAccount();
                savingsAccounts.push_back(acc);
                cout << "Nhập thành công!" << endl;
                break;
            }
            case 2: {
                string keyword;
                cout << "Nhập mã sổ hoặc CMND cần tìm: ";
                cin >> keyword;
                SavingsAccount* acc = searchSavingsAccount(savingsAccounts, keyword);
                if (acc) {
                    acc->displayInfo();
                } else {
                    cout << "Không tìm thấy sổ tiết kiệm!" << endl;
                }
                break;
            }
            case 3: {
                Date startDate, endDate;
                cout << "Nhập ngày bắt đầu:" << endl;
                startDate = inputDate();
                cout << "Nhập ngày kết thúc:" << endl;
                endDate = inputDate();
                listSavingsAccountsInPeriod(savingsAccounts, startDate, endDate);
                break;
            }
            case 4: {
                sortByDepositAmountDescending(savingsAccounts);
                cout << "Sổ tiết kiệm đã được sắp xếp theo số tiền gửi giảm dần!" << endl;
                break;
            }
            case 5: {
                sortByOpeningDateAscending(savingsAccounts);
                cout << "Sổ tiết kiệm đã được sắp xếp theo ngày mở sổ tăng dần!" << endl;
                break;
            }
            case 6: {
                string keyword;
                cout << "Nhập mã sổ cần rút tiền: ";
                cin >> keyword;
                SavingsAccount* acc = searchSavingsAccount(savingsAccounts, keyword);
                if (acc) {
                    withdrawFromAccount(*acc);
                } else {
                    cout << "Không tìm thấy sổ tiết kiệm!" << endl;
                }
                break;
            }
            case 0:
                cout << "Thoát chương trình!" << endl;
                break;
            default:
                cout << "Lựa chọn không hợp lệ!" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
