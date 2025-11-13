/*
BÀI 58: NHÀ HÀNG LẨU
- Buffet lẩu
- Giá theo người + giờ vàng
*/

#include <iostream>
#include <string>
using namespace std;

string IntToStr(int n) { if (!n) return "0"; string s = ""; while (n > 0) { s = char('0' + n % 10) + s; n /= 10; } return s; }

const float GIA_NGUOI = 299000;

void DatBan() {
    cout << "\n=== NHA HANG LAU ===\n";
    cout << "So nguoi: "; int n; cin >> n;
    cout << "Gio (HH): "; int gio; cin >> gio;

    float tong = n * GIA_NGUOI;
    if (gio >= 11 && gio < 13 || gio >= 17 && gio < 19) {
        tong *= 1.15;
        cout << ">>> Gio vang +15%\n";
    }

    cout << "\n[OK] Tong: " << IntToStr((int)tong) << " VND\n";
}

int main() {
    while (true) {
        cout << "\n1. Dat ban | 0. Thoat\nChon: "; int c; cin >> c;
        if (c == 1) DatBan();
        else break;
    }
    return 0;
}
