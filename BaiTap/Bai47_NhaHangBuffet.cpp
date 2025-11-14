/*
BÀI 47: NHÀ HÀNG BUFFET
- Tính tiền theo đầu người
- Giá khác nhau: Trẻ em/Người lớn/Cao tuổi
- Giờ vàng vs giờ thường
- Giới hạn thời gian (90 phút)
*/

#include <iostream>
#include <string>
using namespace std;

// === HÀM TỰ VIẾT ===
string IntToStr(int num) {
    if (num == 0) return "0";
    string result = "";
    bool neg = num < 0;
    if (neg) num = -num;
    while (num > 0) {
        result = char('0' + num % 10) + result;
        num /= 10;
    }
    return neg ? "-" + result : result;
}

string FloatToStr(float num) {
    int intPart = (int)num;
    int decPart = (int)((num - intPart) * 100);
    if (decPart < 0) decPart = -decPart;
    return IntToStr(intPart) + "." + (decPart < 10 ? "0" : "") + IntToStr(decPart);
}

// === DỮ LIỆU ===
const float GIA_TRE_EM = 199000;       // < 12 tuổi
const float GIA_NGUOI_LON = 399000;    // 12-60 tuổi
const float GIA_CAO_TUOI = 299000;     // > 60 tuổi

struct HoaDon {
    string maHD, hoTenKH, sdt;
    int soTreEm, soNguoiLon, soCaoTuoi;
    string gioVao;
    bool gioVang;  // 11h-13h, 17h-19h
    float tongTien;
};

HoaDon* dsHD = NULL;
int soHD = 0;

// === CHỨC NĂNG ===
void DatBan() {
    cout << "\n=== DAT BAN BUFFET ===\n";
    cout << "\n--- BANG GIA ---\n";
    cout << "Tre em (< 12 tuoi): " << FloatToStr(GIA_TRE_EM) << " VND\n";
    cout << "Nguoi lon (12-60): " << FloatToStr(GIA_NGUOI_LON) << " VND\n";
    cout << "Cao tuoi (> 60): " << FloatToStr(GIA_CAO_TUOI) << " VND\n";
    cout << "\nGio vang (+20%): 11h-13h, 17h-19h\n";

    HoaDon hd;
    hd.maHD = "HD" + IntToStr(soHD + 1);

    cout << "\nHo ten: "; cin.ignore(); getline(cin, hd.hoTenKH);
    cout << "SDT: "; getline(cin, hd.sdt);

    cout << "\nSo nguoi:\n";
    cout << "Tre em: "; cin >> hd.soTreEm;
    cout << "Nguoi lon: "; cin >> hd.soNguoiLon;
    cout << "Cao tuoi: "; cin >> hd.soCaoTuoi;

    cout << "Gio vao (HH): "; cin >> hd.gioVao;
    int gio = (hd.gioVao[0] - '0') * 10 + (hd.gioVao[1] - '0');

    // Kiểm tra giờ vàng
    hd.gioVang = (gio >= 11 && gio < 13) || (gio >= 17 && gio < 19);

    hd.tongTien = hd.soTreEm * GIA_TRE_EM +
                  hd.soNguoiLon * GIA_NGUOI_LON +
                  hd.soCaoTuoi * GIA_CAO_TUOI;

    if (hd.gioVang) {
        hd.tongTien *= 1.20;  // +20% giờ vàng
        cout << "\n>>> GIO VANG (+20%)\n";
    }

    cout << "\n--- HOA DON ---\n";
    cout << "Ma HD: " << hd.maHD << "\n";
    cout << "Tong khach: " << (hd.soTreEm + hd.soNguoiLon + hd.soCaoTuoi) << " nguoi\n";
    cout << "TONG TIEN: " << FloatToStr(hd.tongTien) << " VND\n";
    cout << "Thoi gian: 90 phut\n";

    HoaDon* tmp = new HoaDon[soHD + 1];
    for (int i = 0; i < soHD; i++) tmp[i] = dsHD[i];
    tmp[soHD] = hd;
    delete[] dsHD;
    dsHD = tmp;
    soHD++;

    cout << "\n[OK] Dat ban thanh cong! Chuc ngon mieng!\n";
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== NHA HANG BUFFET =====\n";
        cout << "1. Dat ban\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DatBan();
        else if (c == 0) break;
    }

    delete[] dsHD;
    return 0;
}
