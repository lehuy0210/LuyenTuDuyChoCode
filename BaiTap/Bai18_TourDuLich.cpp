/*
BÀI 18: TOUR DU LỊCH
- Quản lý tour (tên, điểm đến, số ngày, giá)
- Đăng ký tour (họ tên, số người, ngày đi)
- Tính giá (người lớn 100%, trẻ em 70%)
- Thống kê tour phổ biến
*/

#include <iostream>
#include <string>
using namespace std;

int StrToInt(const string& s) { int r = 0; for (char c : s) if (c >= '0' && c <= '9') r = r * 10 + (c - '0'); return r; }

struct Tour { string ma, ten, diaDiem; int soNgay; float gia; };
struct DangKy { string maDK, maTour, hoTen, ngayDi; int nguoiLon, treEm; float tongTien; };

Tour dsTour[10] = {
    {"T01", "Ha Long 2N1D", "Ha Long", 2, 3000000},
    {"T02", "Da Lat 3N2D", "Da Lat", 3, 4500000},
    {"T03", "Phu Quoc 4N3D", "Phu Quoc", 4, 8000000}
};
int soTour = 3;
DangKy* dsDK = NULL;
int soDK = 0;

void DangKyTour() {
    cout << "\n=== DANG KY TOUR ===\n";
    for (int i = 0; i < soTour; i++) cout << (i+1) << ". " << dsTour[i].ten << " - " << dsTour[i].gia << " VND/nguoi\n";
    cout << "Chon: "; int c; cin >> c; c--;

    DangKy dk;
    dk.maDK = "DK" + to_string(soDK + 1);
    dk.maTour = dsTour[c].ma;
    cout << "Ho ten: "; cin.ignore(); getline(cin, dk.hoTen);
    cout << "Ngay di (dd/mm/yyyy): "; cin >> dk.ngayDi;
    cout << "So nguoi lon: "; cin >> dk.nguoiLon;
    cout << "So tre em: "; cin >> dk.treEm;

    dk.tongTien = dsTour[c].gia * dk.nguoiLon + dsTour[c].gia * 0.7 * dk.treEm;

    DangKy* tmp = new DangKy[soDK + 1];
    for (int i = 0; i < soDK; i++) tmp[i] = dsDK[i];
    tmp[soDK] = dk;
    delete[] dsDK; dsDK = tmp; soDK++;

    cout << "\n[OK] Ma DK: " << dk.maDK << "\nTong tien: " << dk.tongTien << " VND\n";
}

int main() {
    while (true) {
        cout << "\n1. Dang ky tour\n0. Thoat\nChon: ";
        int c; cin >> c;
        if (c == 1) DangKyTour();
        else if (c == 0) break;
    }
    delete[] dsDK;
    return 0;
}
