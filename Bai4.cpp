#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;
long long giaithua(int n){
    //hàm tính giai thừa của một số nguyên
    if(n==1){
        return 1;

    }
    return n*giaithua(n-1);

}
int main(){
    int i=0;
    double x;
    double k=0.00001;//độ chính xác
    double s=0,s1=0,s2=0;
    cout<<"nhập x (tính theo độ): ";
    cin>>x;
    //kiểm tra các giá trị đặc biệt
     if (fmod(x, 360) == 0) {
        cout << "Kết quả của sin(x) là: 0" << endl;
        return 0;
    }
    if (fmod(x, 180) == 0 && fmod(x, 360) != 0) {
        cout << "Kết quả của sin(x) là: 0" << endl;
        return 0;
    }
    if (fmod(x, 90) == 0 && fmod(x, 180) != 0) {
        cout << "Kết quả của sin(x) là: " << ((fmod(x, 360) == 90) ? 1 : -1) << endl;
        return 0;
    }

    x=x*M_PI/180;//đổi độ về radian
    
    do{
        s1=s2;
        s=s+(pow(-1,i)*pow(x,2*i+1))/giaithua(2*i+1); //khai triển talor
        s2=s;
        i++;
    }while(fabs(s2-s1)>k);//kiểm tra đến khi nào độ chính xác không vượt qua 0.00001 thì dừng lại 
    cout<<"Kết quả của sin(x) là: "<<s2;
}