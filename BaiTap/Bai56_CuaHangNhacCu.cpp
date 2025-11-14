/*
BÀI 56: CỬA HÀNG NHẠC CỤ
- Guitar, Piano, Drum...
- Thuê/Mua
- Bảo hành
*/

#include <iostream>
#include <string>
using namespace std;

string IntToStr(int n) { if (!n) return "0"; string s = ""; while (n > 0) { s = char('0' + n % 10) + s; n /= 10; } return s; }

struct NhacCu { string ma, ten, loai; float giaBan, giaThue; int baoHanh; bool conHang; };

NhacCu dsNC[10] = {
    {"NC01", "Guitar Acoustic Yamaha F310", "Guitar", 3500000, 200000, 12, true},
    {"NC02", "Piano Yamaha U1", "Piano", 85000000, 2000000, 24, true},
    {"NC03", "Drum Pearl Export", "Drum", 18000000, 800000, 12, true}
};
int soNC = 3;

void MuaThue() {
    cout << "\n=== MUA/THUE NHAC CU ===\n";
    for (int i = 0; i < soNC; i++) {
        if (dsNC[i].conHang) {
            cout << (i+1) << ". " << dsNC[i].ten << "\n";
            cout << "   Mua: " << IntToStr((int)dsNC[i].giaBan) << " | Thue/thang: " << IntToStr((int)dsNC[i].giaThue) << " VND\n";
        }
    }
    cout << "Chon: "; int c; cin >> c; c--;
    cout << "1=Mua, 2=Thue: "; int loai; cin >> loai;

    if (loai == 1) {
        dsNC[c].conHang = false;
        cout << "\n[OK] Mua " << dsNC[c].ten << " | BH: " << dsNC[c].baoHanh << " thang\n";
    } else {
        cout << "So thang thue: "; int thang; cin >> thang;
        cout << "\n[OK] Thue " << dsNC[c].ten << " | Tong: " << IntToStr((int)(dsNC[c].giaThue * thang)) << " VND\n";
    }
}

int main() {
    while (true) {
        cout << "\n1. Mua/Thue | 0. Thoat\nChon: "; int c; cin >> c;
        if (c == 1) MuaThue();
        else break;
    }
    return 0;
}
