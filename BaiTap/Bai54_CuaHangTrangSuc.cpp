/*
BÀI 54: CỬA HÀNG TRANG SỨC
- Kim cương, đá quý
- Giám định chất lượng
- Chứng nhận
- Trade-in (thu cũ đổi mới)
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

struct TrangSuc {
    string ma, ten, loai;  // "NhanKimCuong", "VongDaQuy"
    float trongLuong, gia;
    string chungNhan;  // GIA, IGI...
    bool conHang;
};

TrangSuc dsTS[10] = {
    {"TS01", "Nhan kim cuong 1 carat", "NhanKimCuong", 0.5, 85000000, "GIA", true},
    {"TS02", "Vong ruby do", "VongDaQuy", 3.2, 45000000, "IGI", true},
    {"TS03", "Day co sapphire xanh", "DayCo", 2.8, 65000000, "GIA", true}
};
int soTS = 3;

void BanTrangSuc() {
    cout << "\n=== BAN TRANG SUC ===\n";
    for (int i = 0; i < soTS; i++) {
        if (dsTS[i].conHang) {
            cout << (i+1) << ". " << dsTS[i].ten << "\n";
            cout << "   Trong luong: " << dsTS[i].trongLuong << "g | Gia: "
                 << IntToStr((int)(dsTS[i].gia/1000000)) << " trieu VND\n";
            cout << "   Chung nhan: " << dsTS[i].chungNhan << "\n";
        }
    }

    cout << "Chon: "; int c; cin >> c; c--;

    cout << "Thu cu doi moi? (1=Co, 0=Khong): "; int trade; cin >> trade;
    float giaGiam = 0;
    if (trade == 1) {
        cout << "Gia thu cu (trieu): "; int cu; cin >> cu;
        giaGiam = cu * 1000000;
    }

    float giaCuoi = dsTS[c].gia - giaGiam;
    dsTS[c].conHang = false;

    cout << "\n[OK] Tong thanh toan: " << IntToStr((int)(giaCuoi/1000000)) << " trieu VND\n";
}

int main() {
    while (true) {
        cout << "\n1. Ban trang suc | 0. Thoat\nChon: "; int c; cin >> c;
        if (c == 1) BanTrangSuc();
        else break;
    }
    return 0;
}
