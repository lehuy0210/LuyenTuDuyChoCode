/*
BÀI 50: QUẢN LÝ KHO HÀNG
- Nhập/xuất hàng
- Kiểm kê tồn kho
- Cảnh báo hàng sắp hết
- Báo cáo nhập xuất tồn
*/

#include <iostream>
#include <string>
using namespace std;

string IntToStr(int num) {
    if (num == 0) return "0";
    string result = "";
    while (num > 0) { result = char('0' + num % 10) + result; num /= 10; }
    return result;
}

struct SanPham {
    string ma, ten;
    int tonKho, toiThieu;
    float giaNhap, giaXuat;
};

struct PhieuNhap {
    string maPN, ngay;
    string maSP;
    int soLuong;
    float tongTien;
};

struct PhieuXuat {
    string maPX, ngay;
    string maSP;
    int soLuong;
};

SanPham dsSP[20] = {
    {"SP01", "But bi xanh", 100, 20, 3000, 5000},
    {"SP02", "Vo ghi A4", 50, 10, 30000, 45000},
    {"SP03", "Bang dinh", 15, 10, 5000, 8000}
};
int soSP = 3;

PhieuNhap* dsPN = NULL; int soPN = 0;
PhieuXuat* dsPX = NULL; int soPX = 0;

void NhapHang() {
    cout << "\n=== NHAP HANG ===\n";
    for (int i = 0; i < soSP; i++)
        cout << (i+1) << ". " << dsSP[i].ten << " (Ton: " << dsSP[i].tonKho << ")\n";

    cout << "Chon SP: "; int c; cin >> c; c--;
    PhieuNhap pn;
    pn.maPN = "PN" + IntToStr(soPN + 1);
    pn.maSP = dsSP[c].ma;
    cout << "So luong nhap: "; cin >> pn.soLuong;
    cout << "Ngay (dd/mm/yyyy): "; cin >> pn.ngay;

    pn.tongTien = pn.soLuong * dsSP[c].giaNhap;
    dsSP[c].tonKho += pn.soLuong;

    cout << "[OK] Nhap " << pn.soLuong << " " << dsSP[c].ten << "\n";

    PhieuNhap* tmp = new PhieuNhap[soPN + 1];
    for (int i = 0; i < soPN; i++) tmp[i] = dsPN[i];
    tmp[soPN] = pn;
    delete[] dsPN; dsPN = tmp; soPN++;
}

void XuatHang() {
    cout << "\n=== XUAT HANG ===\n";
    for (int i = 0; i < soSP; i++)
        cout << (i+1) << ". " << dsSP[i].ten << " (Ton: " << dsSP[i].tonKho << ")\n";

    cout << "Chon SP: "; int c; cin >> c; c--;
    PhieuXuat px;
    px.maPX = "PX" + IntToStr(soPX + 1);
    px.maSP = dsSP[c].ma;
    cout << "So luong xuat: "; cin >> px.soLuong;

    if (px.soLuong > dsSP[c].tonKho) {
        cout << "Khong du hang!\n";
        return;
    }

    cout << "Ngay (dd/mm/yyyy): "; cin >> px.ngay;
    dsSP[c].tonKho -= px.soLuong;

    cout << "[OK] Xuat " << px.soLuong << " " << dsSP[c].ten << "\n";

    PhieuXuat* tmp = new PhieuXuat[soPX + 1];
    for (int i = 0; i < soPX; i++) tmp[i] = dsPX[i];
    tmp[soPX] = px;
    delete[] dsPX; dsPX = tmp; soPX++;
}

void CanhBao() {
    cout << "\n=== CANH BAO TON KHO ===\n";
    for (int i = 0; i < soSP; i++) {
        if (dsSP[i].tonKho < dsSP[i].toiThieu) {
            cout << ">>> " << dsSP[i].ten << ": Con " << dsSP[i].tonKho
                 << " (Toi thieu: " << dsSP[i].toiThieu << ")\n";
        }
    }
}

int main() {
    while (true) {
        cout << "\n1. Nhap hang | 2. Xuat hang | 3. Canh bao | 0. Thoat\nChon: ";
        int c; cin >> c;
        if (c == 1) NhapHang();
        else if (c == 2) XuatHang();
        else if (c == 3) CanhBao();
        else break;
    }
    delete[] dsPN; delete[] dsPX;
    return 0;
}
