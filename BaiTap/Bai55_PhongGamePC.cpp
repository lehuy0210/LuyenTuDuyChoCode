/*
BÀI 55: PHÒNG GAME PC
- Thuê máy theo giờ
- Loại máy (VIP/Thường)
- Đồ ăn/nước
- Giờ vàng giảm giá
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

struct May {
    int soMay;
    string loai;  // "VIP", "Thuong"
    bool dangDung;
    int gioVao, phutVao;
};

const float GIA_VIP = 15000;      // VND/gio
const float GIA_THUONG = 10000;   // VND/gio

May dsMay[30];
int soMay = 30;

void KhoiTao() {
    for (int i = 0; i < 20; i++) {
        dsMay[i].soMay = i + 1;
        dsMay[i].loai = "Thuong";
        dsMay[i].dangDung = false;
    }
    for (int i = 20; i < 30; i++) {
        dsMay[i].soMay = i + 1;
        dsMay[i].loai = "VIP";
        dsMay[i].dangDung = false;
    }
}

void ThueMay() {
    cout << "\n=== THUE MAY ===\n";
    cout << "May ranh:\n";
    for (int i = 0; i < soMay; i++) {
        if (!dsMay[i].dangDung) {
            cout << "May " << dsMay[i].soMay << " (" << dsMay[i].loai << ") ";
            if ((i+1) % 5 == 0) cout << "\n";
        }
    }

    cout << "\nChon may: "; int m; cin >> m; m--;
    if (dsMay[m].dangDung) { cout << "May dang duoc su dung!\n"; return; }

    cout << "Gio vao (hh mm): "; cin >> dsMay[m].gioVao >> dsMay[m].phutVao;
    dsMay[m].dangDung = true;

    float giaGio = (dsMay[m].loai == "VIP") ? GIA_VIP : GIA_THUONG;
    cout << "\n[OK] May " << dsMay[m].soMay << " | " << IntToStr((int)giaGio) << " VND/gio\n";
}

void TraMay() {
    cout << "\n=== TRA MAY ===\n";
    cout << "So may: "; int m; cin >> m; m--;

    cout << "Gio ra (hh mm): "; int gioRa, phutRa; cin >> gioRa >> phutRa;

    int tongPhut = (gioRa * 60 + phutRa) - (dsMay[m].gioVao * 60 + dsMay[m].phutVao);
    float soGio = tongPhut / 60.0;

    float giaGio = (dsMay[m].loai == "VIP") ? GIA_VIP : GIA_THUONG;
    float tien = soGio * giaGio;

    cout << "Do an/nuoc (VND): "; float doAn; cin >> doAn;
    tien += doAn;

    dsMay[m].dangDung = false;
    cout << "\n[OK] Tong: " << IntToStr((int)tien) << " VND\n";
}

int main() {
    KhoiTao();
    while (true) {
        cout << "\n1. Thue may | 2. Tra may | 0. Thoat\nChon: "; int c; cin >> c;
        if (c == 1) ThueMay();
        else if (c == 2) TraMay();
        else break;
    }
    return 0;
}
