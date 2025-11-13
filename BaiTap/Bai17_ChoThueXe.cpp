/*
BÀI 17: CHO THUÊ XE
- Quản lý xe (biển số, loại xe, giá thuê/ngày)
- Đặt xe (ngày thuê, số ngày, đặt cọc 30%)
- Trả xe (tính tiền, trừ đặt cọc)
- Thống kê xe đang cho thuê
*/

#include <iostream>
#include <string>
using namespace std;

int StrToInt(const string& s) { int r = 0; for (char c : s) if (c >= '0' && c <= '9') r = r * 10 + (c - '0'); return r; }
string IntToStr(int n) { if (n == 0) return "0"; string r = ""; while (n) { r = char('0' + n % 10) + r; n /= 10; } return r; }

struct Xe { string bienSo, loai; float giaThue; string tt; };
struct ThueXe { string maThue, bienSo, ngayThue; int soNgay; float datCoc, tongTien; };

Xe dsXe[20] = {{"51A-12345", "Honda SH", 200000, "Trong"}, {"51B-67890", "Yamaha Exciter", 150000, "Trong"}, {"51C-11111", "Wave", 100000, "Trong"}};
int soXe = 3;
ThueXe* dsThue = NULL;
int soThue = 0;

void ThueXe() {
    cout << "\n=== THUE XE ===\n";
    for (int i = 0; i < soXe; i++) if (dsXe[i].tt == "Trong") cout << (i+1) << ". " << dsXe[i].bienSo << " - " << dsXe[i].loai << " - " << dsXe[i].giaThue << "/ngay\n";
    cout << "Chon: "; int c; cin >> c; c--;
    if (c < 0 || c >= soXe || dsXe[c].tt != "Trong") return;

    ThueXe t;
    t.maThue = "T" + IntToStr(soThue + 1);
    t.bienSo = dsXe[c].bienSo;
    cout << "Ngay thue: "; cin >> t.ngayThue;
    cout << "So ngay: "; cin >> t.soNgay;
    t.tongTien = dsXe[c].giaThue * t.soNgay;
    t.datCoc = t.tongTien * 0.3;

    dsXe[c].tt = "DangThue";

    ThueXe* tmp = new ThueXe[soThue + 1];
    for (int i = 0; i < soThue; i++) tmp[i] = dsThue[i];
    tmp[soThue] = t;
    delete[] dsThue; dsThue = tmp; soThue++;

    cout << "\n[OK] Ma thue: " << t.maThue << "\nDat coc: " << t.datCoc << " VND\nTong tien: " << t.tongTien << " VND\n";
}

void TraXe() {
    cout << "Nhap ma thue: "; string ma; cin >> ma;
    for (int i = 0; i < soThue; i++) {
        if (dsThue[i].maThue == ma) {
            for (int j = 0; j < soXe; j++) {
                if (dsXe[j].bienSo == dsThue[i].bienSo) dsXe[j].tt = "Trong";
            }
            float conLai = dsThue[i].tongTien - dsThue[i].datCoc;
            cout << "\n[OK] Tra xe thanh cong!\nTong tien: " << dsThue[i].tongTien << "\nDa dat coc: " << dsThue[i].datCoc << "\nCon lai: " << conLai << " VND\n";
            return;
        }
    }
    cout << "Khong tim thay!\n";
}

int main() {
    while (true) {
        cout << "\n1. Thue xe\n2. Tra xe\n0. Thoat\nChon: ";
        int c; cin >> c;
        if (c == 1) ThueXe();
        else if (c == 2) TraXe();
        else if (c == 0) break;
    }
    delete[] dsThue;
    return 0;
}
