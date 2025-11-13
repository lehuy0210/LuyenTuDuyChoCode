/*
BÀI 51: RẠP CHIẾU PHIM IMAX
- Ghế VIP/Thường, giá khác nhau
- Suất chiếu (sáng/chiều/tối)
- Combo bắp nước
- Đặt vé online
*/

#include <iostream>
#include <string>
using namespace std;

string IntToStr(int n) {
    if (n == 0) return "0";
    string s = "";
    while (n > 0) { s = char('0' + n % 10) + s; n /= 10; }
    return s;
}

string FloatToStr(float n) {
    return IntToStr((int)n);
}

struct Phim { string ma, ten, theLoai; int thoiLuong; };
struct SuatChieu { string maSC, maPhim, gio; float giaVIP, giaThuong; };

Phim dsPhim[5] = {
    {"P01", "Avatar 3", "Sci-Fi", 180},
    {"P02", "Fast X", "Action", 150}
};
int soPhim = 2;

SuatChieu dsSC[10] = {
    {"SC01", "P01", "10:00", 200000, 150000},
    {"SC02", "P01", "14:00", 250000, 180000},
    {"SC03", "P01", "19:00", 300000, 220000}
};
int soSC = 3;

void DatVe() {
    cout << "\n=== DAT VE ===\n";
    for (int i = 0; i < soSC; i++) {
        for (int j = 0; j < soPhim; j++) {
            if (dsSC[i].maPhim == dsPhim[j].ma) {
                cout << (i+1) << ". " << dsPhim[j].ten << " - " << dsSC[i].gio
                     << " | VIP: " << FloatToStr(dsSC[i].giaVIP)
                     << " | Thuong: " << FloatToStr(dsSC[i].giaThuong) << "\n";
            }
        }
    }
    cout << "Chon: "; int c; cin >> c; c--;
    cout << "So ve VIP: "; int vip; cin >> vip;
    cout << "So ve Thuong: "; int th; cin >> th;

    float tong = vip * dsSC[c].giaVIP + th * dsSC[c].giaThuong;
    cout << "Combo bap nuoc (1=Co 50k, 0=Khong): "; int cb; cin >> cb;
    if (cb) tong += 50000 * (vip + th);

    cout << "\n[OK] Tong: " << FloatToStr(tong) << " VND\n";
}

int main() {
    while (true) {
        cout << "\n1. Dat ve | 0. Thoat\nChon: "; int c; cin >> c;
        if (c == 1) DatVe();
        else break;
    }
    return 0;
}
