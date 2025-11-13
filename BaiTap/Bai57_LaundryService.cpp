/*
BÀI 57: GIẶT ỦI EXPRESS
- Giặt theo kg
- Express (gấp đôi giá)
- Ủi thêm
*/

#include <iostream>
#include <string>
using namespace std;

string IntToStr(int n) { if (!n) return "0"; string s = ""; while (n > 0) { s = char('0' + n % 10) + s; n /= 10; } return s; }

const float GIA_GIAT_KG = 25000;
const float GIA_UI_THEM = 15000;

void TaoPhieu() {
    cout << "\n=== GIAT UI EXPRESS ===\n";
    cout << "Khoi luong (kg): "; float kg; cin >> kg;
    cout << "Express (<4h)? (1=Co, 0=Khong): "; int ex; cin >> ex;
    cout << "Ui them? (1=Co, 0=Khong): "; int ui; cin >> ui;

    float tien = kg * GIA_GIAT_KG;
    if (ex) tien *= 2;
    if (ui) tien += GIA_UI_THEM * kg;

    cout << "\n[OK] Tong: " << IntToStr((int)tien) << " VND\n";
}

int main() {
    while (true) {
        cout << "\n1. Tao phieu | 0. Thoat\nChon: "; int c; cin >> c;
        if (c == 1) TaoPhieu();
        else break;
    }
    return 0;
}
