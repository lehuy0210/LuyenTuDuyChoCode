/*
BÀI 49: PHÒNG TẬP DANCE
- Lớp theo thể loại (Hip-hop, Kpop, Ballet...)
- Gói tập (1 tháng, 3 tháng, 6 tháng)
- Điểm danh buổi học
- Giáo viên
*/

#include <iostream>
#include <string>
using namespace std;

string IntToStr(int num) {
    if (num == 0) return "0";
    string result = "";
    while (num > 0) { result = char('0' + num % 10) + result; num /= 10; }
    return result;
}

string FloatToStr(float num) {
    return IntToStr((int)num);
}

struct LopHoc {
    string maLop, tenLop, giaoVien, theLoai;
    string lichHoc;  // "T2,T4,T6 18h-20h"
    float hocPhi1Thang, hocPhi3Thang, hocPhi6Thang;
};

struct HocVien {
    string maHV, hoTen, sdt, maLop;
    int goiThang;  // 1, 3, hoac 6
    int soBuoiDiemDanh;
};

LopHoc dsLop[10] = {
    {"L01", "Hip-hop co ban", "Minh Anh", "Hip-hop", "T2,T4,T6 18h", 1200000, 3200000, 6000000},
    {"L02", "Kpop Dance", "Thu Trang", "Kpop", "T3,T5,T7 19h", 1500000, 4000000, 7500000},
    {"L03", "Ballet", "Lan Huong", "Ballet", "T2,T4 17h", 2000000, 5500000, 10000000}
};
int soLop = 3;

HocVien* dsHV = NULL;
int soHV = 0;

void DangKy() {
    cout << "\n=== DANG KY LOP DANCE ===\n";
    for (int i = 0; i < soLop; i++) {
        cout << (i+1) << ". " << dsLop[i].tenLop << " (" << dsLop[i].theLoai << ")\n";
        cout << "   GV: " << dsLop[i].giaoVien << " | Lich: " << dsLop[i].lichHoc << "\n";
        cout << "   1 thang: " << FloatToStr(dsLop[i].hocPhi1Thang) << " | "
             << "3 thang: " << FloatToStr(dsLop[i].hocPhi3Thang) << " | "
             << "6 thang: " << FloatToStr(dsLop[i].hocPhi6Thang) << "\n\n";
    }

    cout << "Chon lop: "; int c; cin >> c; c--;
    HocVien hv;
    hv.maHV = "HV" + IntToStr(soHV + 1);
    hv.maLop = dsLop[c].maLop;

    cout << "Ho ten: "; cin.ignore(); getline(cin, hv.hoTen);
    cout << "SDT: "; getline(cin, hv.sdt);
    cout << "Goi (1/3/6 thang): "; cin >> hv.goiThang;
    hv.soBuoiDiemDanh = 0;

    float hocPhi = (hv.goiThang == 1) ? dsLop[c].hocPhi1Thang :
                   (hv.goiThang == 3) ? dsLop[c].hocPhi3Thang : dsLop[c].hocPhi6Thang;

    cout << "\n[OK] Ma HV: " << hv.maHV << " | Hoc phi: " << FloatToStr(hocPhi) << " VND\n";

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
