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

int StrToInt(const string& str) {
    int result = 0, sign = 1, i = 0;
    if (str[0] == '-') { sign = -1; i = 1; }
    for (; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result * sign;
}

string FloatToStr(float num) {
    int intPart = (int)num;
    float decimalPart = num - intPart;
    if (decimalPart < 0) decimalPart = -decimalPart;
    int dec = (int)(decimalPart * 100 + 0.5);
    return IntToStr(intPart) + "." + (dec < 10 ? "0" : "") + IntToStr(dec);
}

struct QuaTang {
    string ma;
    string ten;
    string loai;     // "Hoa", "Chocolate", "Gau bong", "Hop qua"
    float gia;
    bool conHang;
};

struct DonHang {
    string maDH;
    string nguoiGui;
    string nguoiNhan;
    string sdtNhan;
    string diaChiNhan;
    string loiChuc;
    string maSP;
    int soLuong;
    float phiShip;
    float tongTien;
    string trangThai;  // "Cho xu ly", "Dang giao", "Da giao"
};

const int MAX_SP = 50;
const int MAX_DH = 100;
QuaTang dsSP[MAX_SP];
DonHang dsDH[MAX_DH];
int soSP = 0;
int soDH = 0;

void KhoiTaoSanPham() {
    dsSP[soSP++] = {"QT001", "Bo hoa hong", "Hoa", 350000, true};
    dsSP[soSP++] = {"QT002", "Bo hoa tulip", "Hoa", 450000, true};
    dsSP[soSP++] = {"QT003", "Chocolate Ferrero", "Chocolate", 250000, true};
    dsSP[soSP++] = {"QT004", "Gau bong 50cm", "Gau bong", 180000, true};
    dsSP[soSP++] = {"QT005", "Hop qua mix", "Hop qua", 550000, true};
}

void HienThiSanPham() {
    cout << "\n===== DANH SACH QUA TANG =====\n";
    for (int i = 0; i < soSP; i++) {
        cout << dsSP[i].ma << " - " << dsSP[i].ten << " - " << FloatToStr(dsSP[i].gia) 
             << " VND - " << (dsSP[i].conHang ? "Con hang" : "Het hang") << "\n";
    }
}

void DatHang() {
    DonHang dh;
    dh.maDH = "DH" + IntToStr(1001 + soDH);
    
    cout << "\n===== DAT HANG QUA TANG =====\n";
    cout << "Ma don hang: " << dh.maDH << "\n";
    cout << "Nguoi gui (ten): "; cin.ignore(); getline(cin, dh.nguoiGui);
    cout << "Nguoi nhan (ten): "; getline(cin, dh.nguoiNhan);
    cout << "SDT nguoi nhan: "; getline(cin, dh.sdtNhan);
    cout << "Dia chi giao hang: "; getline(cin, dh.diaChiNhan);
    cout << "Loi chuc (khong bat buoc): "; getline(cin, dh.loiChuc);
    
    HienThiSanPham();
    cout << "Chon ma qua tang: "; cin >> dh.maSP;
    cout << "So luong: "; cin >> dh.soLuong;
    
    float giaSP = 0;
    for (int i = 0; i < soSP; i++) {
        if (dsSP[i].ma == dh.maSP) {
            giaSP = dsSP[i].gia;
            break;
        }
    }
    
    // Phí ship cố định
    dh.phiShip = 30000;
    
    // Giảm phí ship nếu đơn hàng > 500k
    float tienHang = giaSP * dh.soLuong;
    if (tienHang >= 500000) {
        dh.phiShip = 0;  // Free ship
        cout << "\n>>> Mien phi ship cho don hang tren 500k!\n";
    }
    
    dh.tongTien = tienHang + dh.phiShip;
    dh.trangThai = "Cho xu ly";
    
    dsDH[soDH++] = dh;
    
    cout << "\n----- HOA DON -----\n";
    cout << "Don hang: " << dh.maDH << "\n";
    cout << "Tien hang: " << FloatToStr(tienHang) << " VND\n";
    cout << "Phi ship: " << FloatToStr(dh.phiShip) << " VND\n";
    cout << "Tong tien: " << FloatToStr(dh.tongTien) << " VND\n";
    cout << "Trang thai: " << dh.trangThai << "\n";
}

void TraCuuDonHang() {
    string maDH;
    cout << "\n===== TRA CUU DON HANG =====\n";
    cout << "Ma don hang: "; cin >> maDH;
    
    for (int i = 0; i < soDH; i++) {
        if (dsDH[i].maDH == maDH) {
            cout << "\n----- THONG TIN DON HANG -----\n";
            cout << "Ma DH: " << dsDH[i].maDH << "\n";
            cout << "Nguoi gui: " << dsDH[i].nguoiGui << "\n";
            cout << "Nguoi nhan: " << dsDH[i].nguoiNhan << "\n";
            cout << "SDT: " << dsDH[i].sdtNhan << "\n";
            cout << "Dia chi: " << dsDH[i].diaChiNhan << "\n";
            cout << "Loi chuc: " << dsDH[i].loiChuc << "\n";
            cout << "Tong tien: " << FloatToStr(dsDH[i].tongTien) << " VND\n";
            cout << "Trang thai: " << dsDH[i].trangThai << "\n";
            return;
        }
    }
    cout << "Khong tim thay don hang!\n";
}

int main() {
    KhoiTaoSanPham();
    
    int chon;
    do {
        cout << "\n===== SHOP QUA TANG ONLINE =====\n";
        cout << "1. Xem san pham\n";
        cout << "2. Dat hang\n";
        cout << "3. Tra cuu don hang\n";
        cout << "0. Thoat\n";
        cout << "Chon: "; cin >> chon;
        
        switch(chon) {
            case 1: HienThiSanPham(); break;
            case 2: DatHang(); break;
            case 3: TraCuuDonHang(); break;
        }
    } while (chon != 0);
    
    return 0;
}
