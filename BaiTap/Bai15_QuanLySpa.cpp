/*
BÀI 15: QUẢN LÝ SPA/SALON
- Đăng ký khách hàng
- Gói liệu trình (5 buổi, 10 buổi, 20 buổi)
- Đặt lịch spa (ngày, giờ, dịch vụ)
- Điểm danh sử dụng (trừ số buổi còn lại)
- Thống kê
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int StrToInt(const string& s) {
    int r = 0; for (char c : s) if (c >= '0' && c <= '9') r = r * 10 + (c - '0'); return r;
}
string IntToStr(int n) {
    if (n == 0) return "0"; string r = ""; while (n) { r = char('0' + n % 10) + r; n /= 10; } return r;
}

struct GoiSpa {
    string maGoi;
    string tenGoi;
    int soBuoi;
    float giaGoi;
};

struct KhachHang {
    string maKH;
    string hoTen;
    string sdt;
    string maGoi;
    int buoiDaSuDung;
};

GoiSpa dsGoi[10] = {
    {"G01", "Goi 5 buoi", 5, 1500000},
    {"G02", "Goi 10 buoi", 10, 2500000},
    {"G03", "Goi 20 buoi", 20, 4000000}
};
int soGoi = 3;

KhachHang* dsKH = NULL;
int soKH = 0;

void DangKy() {
    cout << "\n=== DANG KY GOI SPA ===\n";
    KhachHang kh;
    kh.maKH = "KH" + IntToStr(soKH + 1);
    cout << "Ho ten: "; cin.ignore(); getline(cin, kh.hoTen);
    cout << "SDT: "; getline(cin, kh.sdt);
    cout << "\nGoi spa:\n";
    for (int i = 0; i < soGoi; i++) cout << (i+1) << ". " << dsGoi[i].tenGoi << " - " << dsGoi[i].giaGoi << " VND\n";
    cout << "Chon: "; int c; cin >> c; c--;
    kh.maGoi = dsGoi[c].maGoi;
    kh.buoiDaSuDung = 0;

    KhachHang* t = new KhachHang[soKH + 1];
    for (int i = 0; i < soKH; i++) t[i] = dsKH[i];
    t[soKH] = kh;
    delete[] dsKH; dsKH = t; soKH++;

    cout << "\n[OK] Ma KH: " << kh.maKH << "\nGoi: " << dsGoi[c].tenGoi << " (" << dsGoi[c].soBuoi << " buoi)\n";
}

void DiemDanh() {
    cout << "\nNhap ma KH: "; string ma; cin >> ma;
    for (int i = 0; i < soKH; i++) {
        if (dsKH[i].maKH == ma) {
            int soBuoiGoi = 0;
            for (int j = 0; j < soGoi; j++) {
                if (dsGoi[j].maGoi == dsKH[i].maGoi) { soBuoiGoi = dsGoi[j].soBuoi; break; }
            }
            int conLai = soBuoiGoi - dsKH[i].buoiDaSuDung;
            if (conLai <= 0) { cout << "Het luot!\n"; return; }
            dsKH[i].buoiDaSuDung++;
            cout << "[OK] Diem danh thanh cong!\nCon lai: " << (conLai - 1) << " buoi\n";
            return;
        }
    }
    cout << "Khong tim thay!\n";
}

int main() {
    while (true) {
        cout << "\n1. Dang ky\n2. Diem danh\n0. Thoat\nChon: ";
        int c; cin >> c;
        if (c == 1) DangKy();
        else if (c == 2) DiemDanh();
        else if (c == 0) break;
    }
    delete[] dsKH;
    return 0;
}
