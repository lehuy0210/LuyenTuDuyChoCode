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

struct ThuCung {
    string ma;
    string ten;
    string loai;        // "Cho", "Meo", "Chim"...
    int tuoi;
    float canNang;
    string chuSoHuu;
    string sdt;
};

struct PhieuKham {
    string maPK;
    string maThuCung;
    string ngayKham;
    string trieuChung;
    string chuanDoan;
    float tienKham;
    float tienThuoc;
    float tongTien;
};

const int MAX_TC = 100;
const int MAX_PK = 100;
ThuCung dsTC[MAX_TC];
PhieuKham dsPK[MAX_PK];
int soTC = 0;
int soPK = 0;

void DangKyThuCung() {
    ThuCung tc;
    tc.ma = "TC" + IntToStr(1001 + soTC);
    
    cout << "\n===== DANG KY THU CUNG =====\n";
    cout << "Ma thu cung: " << tc.ma << "\n";
    cout << "Ten thu cung: "; cin.ignore(); getline(cin, tc.ten);
    cout << "Loai (Cho/Meo/Chim...): "; getline(cin, tc.loai);
    cout << "Tuoi: "; cin >> tc.tuoi;
    cout << "Can nang (kg): "; cin >> tc.canNang;
    cout << "Chu so huu: "; cin.ignore(); getline(cin, tc.chuSoHuu);
    cout << "So dien thoai: "; getline(cin, tc.sdt);
    
    dsTC[soTC++] = tc;
    cout << "\n>>> Dang ky thanh cong! Ma thu cung: " << tc.ma << "\n";
}

void KhamBenh() {
    string ma;
    cout << "\n===== KHAM BENH =====\n";
    cout << "Ma thu cung: "; cin >> ma;
    
    int idx = -1;
    for (int i = 0; i < soTC; i++) {
        if (dsTC[i].ma == ma) {
            idx = i;
            break;
        }
    }
    
    if (idx == -1) {
        cout << "Khong tim thay thu cung!\n";
        return;
    }
    
    PhieuKham pk;
    pk.maPK = "PK" + IntToStr(2001 + soPK);
    pk.maThuCung = ma;
    
    cout << "Ten thu cung: " << dsTC[idx].ten << " (" << dsTC[idx].loai << ")\n";
    cout << "Chu: " << dsTC[idx].chuSoHuu << "\n\n";
    
    cout << "Ngay kham (dd/mm/yyyy): "; cin >> pk.ngayKham;
    cout << "Trieu chung: "; cin.ignore(); getline(cin, pk.trieuChung);
    cout << "Chuan doan: "; getline(cin, pk.chuanDoan);
    cout << "Tien kham: "; cin >> pk.tienKham;
    cout << "Tien thuoc: "; cin >> pk.tienThuoc;
    
    pk.tongTien = pk.tienKham + pk.tienThuoc;
    
    dsPK[soPK++] = pk;
    
    cout << "\n----- HOA DON KHAM BENH -----\n";
    cout << "Ma phieu kham: " << pk.maPK << "\n";
    cout << "Thu cung: " << dsTC[idx].ten << "\n";
    cout << "Tien kham: " << FloatToStr(pk.tienKham) << " VND\n";
    cout << "Tien thuoc: " << FloatToStr(pk.tienThuoc) << " VND\n";
    cout << "Tong tien: " << FloatToStr(pk.tongTien) << " VND\n";
}

void HienThiThuCung() {
    cout << "\n===== DANH SACH THU CUNG =====\n";
    for (int i = 0; i < soTC; i++) {
        cout << dsTC[i].ma << " - " << dsTC[i].ten << " (" << dsTC[i].loai << ")\n";
        cout << "  Tuoi: " << dsTC[i].tuoi << " - Can nang: " << FloatToStr(dsTC[i].canNang) << " kg\n";
        cout << "  Chu: " << dsTC[i].chuSoHuu << " - SDT: " << dsTC[i].sdt << "\n\n";
    }
}

int main() {
    int chon;
    do {
        cout << "\n===== PHONG KHAM THU Y =====\n";
        cout << "1. Dang ky thu cung moi\n";
        cout << "2. Kham benh\n";
        cout << "3. Hien thi danh sach thu cung\n";
        cout << "0. Thoat\n";
        cout << "Chon: "; cin >> chon;
        
        switch(chon) {
            case 1: DangKyThuCung(); break;
            case 2: KhamBenh(); break;
            case 3: HienThiThuCung(); break;
        }
    } while (chon != 0);
    
    return 0;
}
