/*
BÀI 53: QUẢN LÝ NHÀ XE
- Bán vé xe khách (tuyến, ghế)
- Loại xe (giường nằm, ghế ngồi)
- Điểm đón trả
- Thời gian xuất bến
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

struct ChuyenXe {
    string maCX, tuyen, loaiXe;  // "GiuongNam", "GheNgoi"
    string gioDi;
    float gia;
    int soGhe, gheConLai;
};

struct VeXe {
    string maVe, maCX, hoTen, sdt, gheSo, diemDon;
};

ChuyenXe dsCX[10] = {
    {"CX01", "HCM-DaLat", "GiuongNam", "22:00", 280000, 40, 40},
    {"CX02", "HCM-VungTau", "GheNgoi", "07:00", 120000, 45, 45},
    {"CX03", "HCM-NhaTrang", "GiuongNam", "21:00", 350000, 36, 36}
};
int soCX = 3;

VeXe* dsVe = NULL;
int soVe = 0;

void DatVe() {
    cout << "\n=== DAT VE XE ===\n";
    for (int i = 0; i < soCX; i++) {
        cout << (i+1) << ". " << dsCX[i].tuyen << " (" << dsCX[i].loaiXe << ")\n";
        cout << "   Gio di: " << dsCX[i].gioDi << " | Gia: " << IntToStr((int)dsCX[i].gia)
             << " VND | Con " << dsCX[i].gheConLai << " cho\n";
    }

    cout << "Chon chuyen: "; int c; cin >> c; c--;
    if (dsCX[c].gheConLai == 0) { cout << "Het cho!\n"; return; }

    VeXe ve;
    ve.maVe = "VE" + IntToStr(soVe + 1);
    ve.maCX = dsCX[c].maCX;

    cout << "Ho ten: "; cin.ignore(); getline(cin, ve.hoTen);
    cout << "SDT: "; getline(cin, ve.sdt);
    cout << "So ghe: "; getline(cin, ve.gheSo);
    cout << "Diem don: "; getline(cin, ve.diemDon);

    dsCX[c].gheConLai--;

    cout << "\n[OK] Ma ve: " << ve.maVe << " | Gia: " << IntToStr((int)dsCX[c].gia) << " VND\n";

    VeXe* tmp = new VeXe[soVe + 1];
    for (int i = 0; i < soVe; i++) tmp[i] = dsVe[i];
    tmp[soVe] = ve;
    delete[] dsVe; dsVe = tmp; soVe++;
}

int main() {
    while (true) {
        cout << "\n1. Dat ve | 0. Thoat\nChon: "; int c; cin >> c;
        if (c == 1) DatVe();
        else break;
    }
    delete[] dsVe;
    return 0;
}
