#include <iostream>
#include <string>
using namespace std;

string IntToStr(int num) {
    if (num == 0) return "0";
    string result = "";
    bool isNegative = false;
    if (num < 0) { isNegative = true; num = -num; }
    while (num > 0) {
        result = char('0' + num % 10) + result;
        num /= 10;
    }
    if (isNegative) result = "-" + result;
    return result;
}

string FloatToStr(float num) {
    int intPart = (int)num;
    float decimalPart = num - intPart;
    if (decimalPart < 0) decimalPart = -decimalPart;
    int dec = (int)(decimalPart * 100 + 0.5);
    return IntToStr(intPart) + "." + (dec < 10 ? "0" : "") + IntToStr(dec);
}

struct SanPham {
    string ma;
    string ten;
    float gia;
    int soLuong;
};

struct HoaDon {
    string maHD;
    string maSP;
    int soLuong;
    float tongTien;
};

const int MAX_SP = 50;
const int MAX_HD = 100;
SanPham dsSP[MAX_SP];
HoaDon dsHD[MAX_HD];
int soSP = 0;
int soHD = 0;

void ThemSanPham() {
    SanPham sp;
    sp.ma = "SP" + IntToStr(1001 + soSP);
    cout << "\nMa san pham: " << sp.ma << "\n";
    cout << "Ten: "; cin.ignore(); getline(cin, sp.ten);
    cout << "Gia: "; cin >> sp.gia;
    cout << "So luong: "; cin >> sp.soLuong;
    dsSP[soSP++] = sp;
    cout << ">>> Them thanh cong!\n";
}

void TaoHoaDon() {
    HoaDon hd;
    hd.maHD = "HD" + IntToStr(2001 + soHD);
    
    cout << "\n===== TAO HOA DON =====\n";
    cout << "Ma hoa don: " << hd.maHD << "\n";
    
    cout << "\nDanh sach san pham:\n";
    for (int i = 0; i < soSP; i++) {
        cout << dsSP[i].ma << " - " << dsSP[i].ten << " - " << FloatToStr(dsSP[i].gia) << " VND\n";
    }
    
    cout << "\nMa san pham: "; cin >> hd.maSP;
    cout << "So luong: "; cin >> hd.soLuong;
    
    float giaSP = 0;
    for (int i = 0; i < soSP; i++) {
        if (dsSP[i].ma == hd.maSP) {
            giaSP = dsSP[i].gia;
            break;
        }
    }
    
    hd.tongTien = giaSP * hd.soLuong;
    dsHD[soHD++] = hd;
    
    cout << "\n>>> Tong tien: " << FloatToStr(hd.tongTien) << " VND\n";
}

int main() {
    int chon;
    do {
        cout << "\n===== SYSTEM =====\n";
        cout << "1. Them san pham\n";
        cout << "2. Tao hoa don\n";
        cout << "0. Thoat\n";
        cout << "Chon: "; cin >> chon;
        
        switch(chon) {
            case 1: ThemSanPham(); break;
            case 2: TaoHoaDon(); break;
        }
    } while (chon != 0);
    
    return 0;
}
