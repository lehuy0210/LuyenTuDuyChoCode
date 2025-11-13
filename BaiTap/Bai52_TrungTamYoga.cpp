/*
BÀI 52: TRUNG TÂM YOGA
- Lớp yoga (Hatha, Vinyasa, Ashtanga...)
- Gói tập theo tháng
- Private class vs Group class
- Tracking buổi tập
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

struct LopYoga { string ma, ten, hinhThuc, lichHoc; float giaThang; };
struct HocVien { string ma, hoTen, sdt, maLop; int soBuoi; };

LopYoga dsLop[5] = {
    {"L01", "Hatha Yoga co ban", "Group", "T2,T4,T6 6h", 800000},
    {"L02", "Vinyasa Flow", "Group", "T3,T5,T7 18h", 1000000},
    {"L03", "Private 1-1", "Private", "Theo lich", 3000000}
};
int soLop = 3;

HocVien* dsHV = NULL;
int soHV = 0;

void DangKy() {
    cout << "\n=== DANG KY YOGA ===\n";
    for (int i = 0; i < soLop; i++) {
        cout << (i+1) << ". " << dsLop[i].ten << " (" << dsLop[i].hinhThuc << ")\n";
        cout << "   Lich: " << dsLop[i].lichHoc << " | " << IntToStr((int)dsLop[i].giaThang) << " VND/thang\n";
    }

    cout << "Chon lop: "; int c; cin >> c; c--;
    HocVien hv;
    hv.ma = "HV" + IntToStr(soHV + 1);
    hv.maLop = dsLop[c].ma;
    hv.soBuoi = 0;

    cout << "Ho ten: "; cin.ignore(); getline(cin, hv.hoTen);
    cout << "SDT: "; getline(cin, hv.sdt);

    cout << "\n[OK] Ma HV: " << hv.ma << " | Hoc phi: " << IntToStr((int)dsLop[c].giaThang) << " VND\n";

    HocVien* tmp = new HocVien[soHV + 1];
    for (int i = 0; i < soHV; i++) tmp[i] = dsHV[i];
    tmp[soHV] = hv;
    delete[] dsHV; dsHV = tmp; soHV++;
}

int main() {
    while (true) {
        cout << "\n1. Dang ky | 0. Thoat\nChon: "; int c; cin >> c;
        if (c == 1) DangKy();
        else break;
    }
    delete[] dsHV;
    return 0;
}
