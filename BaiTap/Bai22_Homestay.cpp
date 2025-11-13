/*
BÀI 22: HOMESTAY/AIRBNB
- Quản lý phòng (tên, loại, giá/đêm, tiện nghi)
- Đặt phòng (check-in/out, số đêm)
- Review/rating (1-5 sao)
- Thống kê phòng được ưa thích
*/

#include <iostream>
#include <string>
using namespace std;

struct Phong { string ma, ten, loai; float giaDem; string tienNghi; float rating; int soDat; };
struct DatPhong { string ma, maPhong, hoTen, checkIn, checkOut; int soDem; float tongTien; };

Phong dsPhong[10] = {
    {"P01", "Phong view bien", "Deluxe", 800000, "TV, AC, WiFi", 4.8, 0},
    {"P02", "Phong gia dinh", "Family", 1200000, "2 giuong, bep", 4.5, 0}
};
int soPhong = 2;
DatPhong* dsDP = NULL;
int soDP = 0;

void DatPhong() {
    cout << "\n=== DAT PHONG ===\n";
    for (int i = 0; i < soPhong; i++) cout << (i+1) << ". " << dsPhong[i].ten << " - " << dsPhong[i].giaDem << "/dem - Rating: " << dsPhong[i].rating << "\n";
    int c; cin >> c; c--;
    DatPhong dp;
    dp.ma = "DP" + to_string(soDP + 1);
    dp.maPhong = dsPhong[c].ma;
    cout << "Ho ten: "; cin.ignore(); getline(cin, dp.hoTen);
    cout << "Check-in (dd/mm/yyyy): "; cin >> dp.checkIn;
    cout << "Check-out (dd/mm/yyyy): "; cin >> dp.checkOut;
    cout << "So dem: "; cin >> dp.soDem;
    dp.tongTien = dsPhong[c].giaDem * dp.soDem;

    dsPhong[c].soDat++;

    DatPhong* tmp = new DatPhong[soDP + 1];
    for (int i = 0; i < soDP; i++) tmp[i] = dsDP[i];
    tmp[soDP] = dp;
    delete[] dsDP; dsDP = tmp; soDP++;

    cout << "[OK] Ma dat: " << dp.ma << "\nTong: " << dp.tongTien << " VND\n";
}

int main() {
    while (true) {
        cout << "\n1. Dat phong\n0. Thoat\nChon: ";
        int c; cin >> c;
        if (c == 1) DatPhong();
        else if (c == 0) break;
    }
    delete[] dsDP;
    return 0;
}
