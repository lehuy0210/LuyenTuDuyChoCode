/*
BÀI 23: PHÒNG TẬP BOXING
- Đăng ký hội viên (gói tập: 1/3/6/12 tháng)
- Đặt lịch tập (ngày, giờ, huấn luyện viên)
- Thuê găng tay/bao cát
- Theo dõi tiến độ (cân nặng, sức mạnh)
*/

#include <iostream>
#include <string>
using namespace std;

struct HoiVien { string ma, hoTen; int thangTap; float canNang; string ngayDK, ngayHH; };
struct LichTap { string ma, maHV, ngay, gio, HLV; };

HoiVien* dsHV = NULL;
int soHV = 0;
LichTap* dsLT = NULL;
int soLT = 0;

void DangKyHV() {
    HoiVien hv;
    hv.ma = "HV" + to_string(soHV + 1);
    cout << "Ho ten: "; cin.ignore(); getline(cin, hv.hoTen);
    cout << "Goi tap (thang): "; cin >> hv.thangTap;
    cout << "Can nang (kg): "; cin >> hv.canNang;
    cout << "Ngay DK: "; cin >> hv.ngayDK;
    cout << "Ngay HH: "; cin >> hv.ngayHH;

    HoiVien* tmp = new HoiVien[soHV + 1];
    for (int i = 0; i < soHV; i++) tmp[i] = dsHV[i];
    tmp[soHV] = hv;
    delete[] dsHV; dsHV = tmp; soHV++;

    cout << "[OK] Ma HV: " << hv.ma << "\n";
}

int main() {
    while (true) {
        cout << "\n1. Dang ky HV\n0. Thoat\nChon: ";
        int c; cin >> c;
        if (c == 1) DangKyHV();
        else if (c == 0) break;
    }
    delete[] dsHV; delete[] dsLT;
    return 0;
}
