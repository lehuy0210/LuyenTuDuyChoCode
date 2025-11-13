/*
BÀI 59: CỬA HÀNG GỐM SỨ
- Tách, bát, đĩa handmade
- Đặt làm theo yêu cầu
*/

#include <iostream>
#include <string>
using namespace std;

string IntToStr(int n) { if (!n) return "0"; string s = ""; while (n > 0) { s = char('0' + n % 10) + s; n /= 10; } return s; }

struct GomSu { string ma, ten; float gia; int ton; };

GomSu dsGS[10] = {
    {"GS01", "Tach tra gom Bat Trang", 180000, 30},
    {"GS02", "Bo bat dia 6 mon", 850000, 15},
    {"GS03", "Binh hoa gom cao 30cm", 650000, 8}
};
int soGS = 3;

void Mua() {
    cout << "\n=== MUA GOM SU ===\n";
    for (int i = 0; i < soGS; i++)
        cout << (i+1) << ". " << dsGS[i].ten << " - " << IntToStr((int)dsGS[i].gia) << " VND (Ton: " << dsGS[i].ton << ")\n";

    cout << "Chon: "; int c; cin >> c; c--;
    cout << "So luong: "; int sl; cin >> sl;

    if (sl > dsGS[c].ton) { cout << "Khong du!\n"; return; }
    dsGS[c].ton -= sl;

    cout << "\n[OK] Tong: " << IntToStr((int)(dsGS[c].gia * sl)) << " VND\n";
}

int main() {
    while (true) {
        cout << "\n1. Mua | 0. Thoat\nChon: "; int c; cin >> c;
        if (c == 1) Mua();
        else break;
    }
    return 0;
}
