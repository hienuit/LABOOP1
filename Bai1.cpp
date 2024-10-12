#include<iostream>
using namespace std;

struct PhanSo {
	int tu, mau;
    //khai báo hai thành phần của 1 phân số

};

void Nhap(PhanSo &x) {
    //câu lệnh do while để nhập tử và mẫu và kiểm tra giá trị mẫu, mẫu=0 thì nhập lại
    do {
        cout<<"Nhap phan so:"<<endl;
		cout << "Nhap tu:"; cin >> x.tu;
		cout << "Nhap mau:"; cin >> x.mau;

	} while (x.mau == 0);
}

int gcd(int a, int b) {
    //hàm tính ước chung lớn nhất của hai số
	if (b == 0) return a;
	return gcd(b, a % b);
}
//Hàm chuẩn hóa cho phân số, nếu mẫu = 0 thì đưa về dạng -a/b;
void ChuanHoa(PhanSo &x){
    if(x.mau<0){
        x.mau=-x.mau;
        x.tu=-x.tu;
    }
}

void RutGon(PhanSo &x) {
    //kiểm tra ước chung lớn nhất nếu =1 thì phân số đã tối giản, không thì rút gọn
    //đầu vào : một phân số có thể chưa rút gọn hoặc đã tối giản
    //đầu ra: một phân số đã tối giản
    if(gcd(x.tu,x.mau)!=1){
        cout<<"Phan so "<<x.tu<<'/'<<x.mau<<" sau khi rút gọn là: ";
	    int _gcd = gcd(x.tu, x.mau);
	    x.tu = x.tu / _gcd;
	    x.mau = x.mau / _gcd;
        ChuanHoa(x);
    cout<<x.tu<<'/'<<x.mau<<endl;
    }
    else{
        ChuanHoa(x);
        cout<<"Phan so "<<x.tu<<'/'<<x.mau<<" da toi gian";
    }
}

int main() {

    PhanSo x;
	Nhap(x);
	RutGon(x);
    return 0;
}