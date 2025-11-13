/*
BÀI 27: CỬA HÀNG THÚ CƯNG
- Quản lý thú cưng (chó, mèo, cá, chim...)
- Bán thú cưng (giống, tuổi, giá)
- Dịch vụ spa/grooming (tắm, cắt tỉa, nhuộm)
- Khám sức khỏe định kỳ
*/

#include <iostream>
#include <string>
using namespace std;

// === HÀM TỰ VIẾT ===
int StrToInt(const string& str) {
    int result = 0, sign = 1, i = 0;
    if (str[0] == '-') { sign = -1; i = 1; }
    for (; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') result = result * 10 + (str[i] - '0');
    }
    return result * sign;
}

string IntToStr(int num) {
    if (num == 0) return "0";
    string result = "";
    bool neg = num < 0;
    if (neg) num = -num;
    while (num > 0) {
        result = char('0' + num % 10) + result;
        num /= 10;
    }
    return neg ? "-" + result : result;
}

float StrToFloat(const string& str) {
    float result = 0, sign = 1;
    int i = 0;
    if (str[0] == '-') { sign = -1; i = 1; }
    bool afterDot = false;
    float divisor = 1;
    for (; i < str.length(); i++) {
        if (str[i] == '.') afterDot = true;
        else if (str[i] >= '0' && str[i] <= '9') {
            if (afterDot) {
                divisor *= 10;
                result += (str[i] - '0') / divisor;
            } else {
                result = result * 10 + (str[i] - '0');
            }
        }
    }
    return result * sign;
}

string FloatToStr(float num) {
    int intPart = (int)num;
    int decPart = (int)((num - intPart) * 100);
    if (decPart < 0) decPart = -decPart;
    return IntToStr(intPart) + "." + (decPart < 10 ? "0" : "") + IntToStr(decPart);
}

// === CẤU TRÚC ===
struct ThuCung {
    string ma, loai, giong, mau;
    int tuoi;
    float gia;
    bool daBan;
};

struct DichVu {
    string ma, ten;
    float gia;
};

struct HoaDonDichVu {
    string maHD, hoTenKH, sdt;
    string maDV;
    string ngay;
    float tongTien;
};

// === DỮ LIỆU ===
ThuCung dsThuCung[50] = {
    {"TC01", "Cho", "Corgi", "Vang", 3, 8000000, false},
    {"TC02", "Cho", "Husky", "Xam trang", 2, 12000000, false},
    {"TC03", "Meo", "Anh long ngan", "Xam", 1, 5000000, false},
    {"TC04", "Meo", "Ba Tu", "Trang", 2, 7000000, false},
    {"TC05", "Ca", "Rong", "Do", 1, 500000, false}
};
int soThuCung = 5;

DichVu dsDV[10] = {
    {"DV01", "Tam + say", 150000},
    {"DV02", "Cat tia long", 200000},
    {"DV03", "Nhuom long", 300000},
    {"DV04", "Kham suc khoe", 250000},
    {"DV05", "Tiem phong", 180000}
};
int soDV = 5;

HoaDonDichVu* dsHD = NULL;
int soHD = 0;

// === CHỨC NĂNG ===
void DanhSachThuCung() {
    cout << "\n=== DANH SACH THU CUNG ===\n";
    for (int i = 0; i < soThuCung; i++) {
        if (!dsThuCung[i].daBan) {
            cout << (i+1) << ". " << dsThuCung[i].loai << " " << dsThuCung[i].giong
                 << " | " << dsThuCung[i].mau << " | " << dsThuCung[i].tuoi << " thang"
                 << " | " << FloatToStr(dsThuCung[i].gia) << " VND\n";
        }
    }
}

void BanThuCung() {
    cout << "\n=== BAN THU CUNG ===\n";
    DanhSachThuCung();

    cout << "\nChon thu cung: "; int c; cin >> c; c--;
    if (c < 0 || c >= soThuCung || dsThuCung[c].daBan) {
        cout << "Khong hop le!\n";
        return;
    }

    cout << "Ho ten khach: "; string hoTen; cin.ignore(); getline(cin, hoTen);
    cout << "SDT: "; string sdt; getline(cin, sdt);

    dsThuCung[c].daBan = true;

    cout << "\n[OK] Da ban " << dsThuCung[c].loai << " " << dsThuCung[c].giong
         << " cho khach " << hoTen << "\n";
    cout << "Tong tien: " << FloatToStr(dsThuCung[c].gia) << " VND\n";
}

void DichVuSpa() {
    cout << "\n=== DICH VU SPA/GROOMING ===\n";

    cout << "Ho ten khach: "; string hoTen; cin.ignore(); getline(cin, hoTen);
    cout << "SDT: "; string sdt; getline(cin, sdt);

    cout << "\nDanh sach dich vu:\n";
    for (int i = 0; i < soDV; i++) {
        cout << (i+1) << ". " << dsDV[i].ten << " - " << FloatToStr(dsDV[i].gia) << " VND\n";
    }

    cout << "\nChon dich vu: "; int c; cin >> c; c--;
    if (c < 0 || c >= soDV) {
        cout << "Khong hop le!\n";
        return;
    }

    HoaDonDichVu hd;
    hd.maHD = "HD" + IntToStr(soHD + 1);
    hd.hoTenKH = hoTen;
    hd.sdt = sdt;
    hd.maDV = dsDV[c].ma;
    hd.tongTien = dsDV[c].gia;
    cout << "Ngay thuc hien: "; cin >> hd.ngay;

    HoaDonDichVu* tmp = new HoaDonDichVu[soHD + 1];
    for (int i = 0; i < soHD; i++) tmp[i] = dsHD[i];
    tmp[soHD] = hd;
    delete[] dsHD;
    dsHD = tmp;
    soHD++;

    cout << "\n[OK] Da dat lich dich vu: " << dsDV[c].ten << "\n";
    cout << "Tong tien: " << FloatToStr(hd.tongTien) << " VND\n";
}

void DoanhThu() {
    cout << "\n=== THONG KE DOANH THU ===\n";

    float doanhThuBan = 0;
    int soLuongBan = 0;
    for (int i = 0; i < soThuCung; i++) {
        if (dsThuCung[i].daBan) {
            doanhThuBan += dsThuCung[i].gia;
            soLuongBan++;
        }
    }

    float doanhThuDV = 0;
    for (int i = 0; i < soHD; i++) {
        doanhThuDV += dsHD[i].tongTien;
    }

    cout << "1. Ban thu cung: " << soLuongBan << " con - "
         << FloatToStr(doanhThuBan) << " VND\n";
    cout << "2. Dich vu: " << soHD << " luot - "
         << FloatToStr(doanhThuDV) << " VND\n";
    cout << "\nTONG: " << FloatToStr(doanhThuBan + doanhThuDV) << " VND\n";
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== CUA HANG THU CUNG =====\n";
        cout << "1. Danh sach thu cung\n";
        cout << "2. Ban thu cung\n";
        cout << "3. Dich vu spa/grooming\n";
        cout << "4. Thong ke doanh thu\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachThuCung();
        else if (c == 2) BanThuCung();
        else if (c == 3) DichVuSpa();
        else if (c == 4) DoanhThu();
        else if (c == 0) break;
    }

    delete[] dsHD;
    return 0;
}
