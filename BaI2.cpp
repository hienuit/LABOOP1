#include<iostream>
#include<math.h>
using namespace std;

struct PhanSo {
	//khai báo hai thành phần của phân số
	int tu, mau;

};

void Nhap(PhanSo &x, PhanSo &y) {
	//kiểm tra giá trị mấu số, nếu mẫu số =0 thì nhập lại
    do {
        cout<<"Nhap phan so thu nhat:"<<endl;
		cout << "Nhap tu:"; cin >> x.tu;
		cout << "Nhap mau:"; cin >> x.mau;

	} while (x.mau == 0);


	do {
        cout<<"Nhap phan so thu hai:"<<endl;
		cout << "Nhap tu:"; cin >> y.tu;
		cout << "Nhap mau:"; cin >> y.mau;

	} while (y.mau == 0);

}
int gcd(int a, int b) {
	//hàm tính ước chung lớn nhất của hai số
	if (b == 0) return a;
	return gcd(b, a % b);
}

void RutGon(PhanSo &x) {
	//hàm rút gọn phân số, kết quả sẽ ra một phân số tối giản
    if(abs(gcd(x.tu,x.mau))!=1){
    cout<<"Phan so "<<x.tu<<'/'<<x.mau<<" sau khi rút gọn là: ";
	int _gcd = gcd(x.tu, x.mau);
	x.tu = x.tu / _gcd;
	x.mau = x.mau / _gcd;
	if (x.mau < 0) {
		x.tu = -x.tu;
		x.mau = -x.mau;
	}
    cout<<x.tu<<'/'<<x.mau<<endl;
    }


}

void SoSanh(PhanSo x, PhanSo y) {
	//quy đồng hai phân số và so sánh cái nào lớn hơn thì phân số lớn hơn
	int a = x.tu * y.mau;
	int b = y.tu * x.mau;
	if (a > b) cout << "Phan so " << x.tu << '/' << x.mau << " lon nhat";
	else if(a<b) cout << "Phan so " << y.tu << '/' << y.mau << " lon nhat";
	else cout<<"Phan so thu nhat bang phan so thu hai";
}

int main() {

	PhanSo x, y;
	Nhap(x, y);
	RutGon(x);
	RutGon(y);
	SoSanh(x, y);
	return 0;
}