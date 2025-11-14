/*
BÀI 16: QUẢN LÝ QUÁN CAFÉ
- Quản lý bàn (trống/đang sử dụng)
- Menu (cà phê, trà, bánh)
- Order (chọn bàn, món, số lượng)
- Thanh toán (tính tiền, VAT 10%)
- Thống kê doanh thu
*/

#include <iostream>
#include <string>
using namespace std;

int StrToInt(const string& s) {
    int r = 0; for (char c : s) if (c >= '0' && c <= '9') r = r * 10 + (c - '0'); return r;
}
string IntToStr(int n) {
    if (n == 0) return "0"; string r = ""; while (n) { r = char('0' + n % 10) + r; n /= 10; } return r;
}
float StrToFloat(const string& s) {
    float r = 0, d = 0; int dd = 0; bool hd = false;
    for (char c : s) {
        if (c == '.') hd = true;
        else if (c >= '0' && c <= '9') {
            if (!hd) r = r * 10 + (c - '0');
            else { d = d * 10 + (c - '0'); dd++; }
        }
    }
    for (int i = 0; i < dd; i++) d /= 10;
    return r + d;
}

struct Mon {
    string ma, ten;
    float gia;
};

struct Ban {
    int so;
    string tt; // "Trong", "DangSD"
    float tien;
};

Mon menu[10] = {
    {"M01", "Ca phe den", 25000},
    {"M02", "Ca phe sua", 30000},
    {"M03", "Tra dao", 35000},
    {"M04", "Banh ngot", 40000}
};
int soMon = 4;

Ban dsBan[20];
int soBan = 10;

void KhoiTao() {
    for (int i = 0; i < soBan; i++) {
        dsBan[i].so = i + 1;
        dsBan[i].tt = "Trong";
        dsBan[i].tien = 0;
    }
}

void Order() {
    cout << "\n=== ORDER ===\n";
    cout << "Danh sach ban:\n";
    for (int i = 0; i < soBan; i++) {
        cout << "Ban " << dsBan[i].so << ": " << dsBan[i].tt << "\n";
    }
    cout << "Chon ban: "; int b; cin >> b; b--;
    if (b < 0 || b >= soBan) return;

    dsBan[b].tt = "DangSD";

    while (true) {
        cout << "\nMenu:\n";
        for (int i = 0; i < soMon; i++) cout << (i+1) << ". " << menu[i].ten << " - " << menu[i].gia << " VND\n";
        cout << "0. Xong\nChon: ";
        int c; cin >> c;
        if (c == 0) break;
        c--;
        if (c < 0 || c >= soMon) continue;
        cout << "So luong: "; int sl; cin >> sl;
        dsBan[b].tien += menu[c].gia * sl;
        cout << "[OK] Them " << menu[c].ten << " x" << sl << "\n";
    }
    cout << "\n[OK] Tong tam tinh: " << dsBan[b].tien << " VND\n";
}

void ThanhToan() {
    cout << "Ban so: "; int b; cin >> b; b--;
    if (b < 0 || b >= soBan || dsBan[b].tt == "Trong") { cout << "Ban trong!\n"; return; }

    float vat = dsBan[b].tien * 0.1;
    float tong = dsBan[b].tien + vat;

    cout << "\n=== HOA DON ===\n";
    cout << "Ban: " << (b+1) << "\n";
    cout << "Tien mon: " << dsBan[b].tien << " VND\n";
    cout << "VAT (10%): " << vat << " VND\n";
    cout << "TONG: " << tong << " VND\n";

    dsBan[b].tt = "Trong";
    dsBan[b].tien = 0;
    cout << "[OK] Da thanh toan!\n";
}

int main() {
    KhoiTao();
    while (true) {
        cout << "\n1. Order\n2. Thanh toan\n0. Thoat\nChon: ";
        int c; cin >> c;
        if (c == 1) Order();
        else if (c == 2) ThanhToan();
        else if (c == 0) break;
    }
    return 0;
}
