/*
BÀI 60: PHÒNG KHÁM THÚ Y
- Khám bệnh thú cưng
- Tiêm phòng
- Phẫu thuật
*/

#include <iostream>
#include <string>
using namespace std;

string IntToStr(int n) { if (!n) return "0"; string s = ""; while (n > 0) { s = char('0' + n % 10) + s; n /= 10; } return s; }

struct DichVu { string ma, ten; float gia; };

DichVu dsDV[10] = {
    {"DV01", "Kham tong quat", 200000},
    {"DV02", "Tiem phong 4 benh", 250000},
    {"DV03", "Tay giun", 100000},
    {"DV04", "Phau thuat triet san", 1500000}
};
int soDV = 4;

void DangKy() {
    cout << "\n=== PHONG KHAM THU Y ===\n";
    for (int i = 0; i < soDV; i++)
        cout << (i+1) << ". " << dsDV[i].ten << " - " << IntToStr((int)dsDV[i].gia) << " VND\n";

    cout << "\nChon dich vu: "; int c; cin >> c; c--;
    cout << "Ten thu cung: "; string ten; cin.ignore(); getline(cin, ten);
    cout << "Loai (Cho/Meo): "; string loai; getline(cin, loai);

    cout << "\n[OK] Dat lich thanh cong | Chi phi: " << IntToStr((int)dsDV[c].gia) << " VND\n";
}

int main() {
    while (true) {
        cout << "\n1. Dang ky kham | 0. Thoat\nChon: "; int c; cin >> c;
        if (c == 1) DangKy();
        else break;
    }
    return 0;
}
