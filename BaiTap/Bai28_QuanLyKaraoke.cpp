/*
BÀI 28: QUẢN LÝ KARAOKE
- Quản lý phòng (VIP, Thường, loại)
- Đặt phòng và tính giờ
- Gọi đồ ăn/nước (menu)
- Thanh toán (tiền phòng + tiền đồ)
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
struct Phong {
    string soPhong, loai;
    int soChoNgoi;
    float giaGio;
    bool dangDung;
    string hoTenKH;
    int gioVao, phutVao;
};

struct MonAn {
    string ma, ten;
    float gia;
};

struct Order {
    string soPhong, maMon;
    int soLuong;
};

// === DỮ LIỆU ===
Phong dsPhong[15] = {
    {"P101", "Thuong", 6, 80000, false, "", 0, 0},
    {"P102", "Thuong", 8, 100000, false, "", 0, 0},
    {"P103", "Thuong", 10, 120000, false, "", 0, 0},
    {"P201", "VIP", 15, 200000, false, "", 0, 0},
    {"P202", "VIP", 20, 250000, false, "", 0, 0}
};
int soPhong = 5;

MonAn dsMenu[20] = {
    {"M01", "Tra dao", 25000},
    {"M02", "Nuoc ngot", 15000},
    {"M03", "Bia", 30000},
    {"M04", "Mi tom", 20000},
    {"M05", "Khoai tay chien", 35000},
    {"M06", "Muc rim", 45000},
    {"M07", "Dia hoa qua", 80000}
};
int soMenu = 7;

Order* dsOrder = NULL;
int soOrder = 0;

// === CHỨC NĂNG ===
void DanhSachPhong() {
    cout << "\n=== DANH SACH PHONG ===\n";
    for (int i = 0; i < soPhong; i++) {
        cout << dsPhong[i].soPhong << " | " << dsPhong[i].loai
             << " (" << dsPhong[i].soChoNgoi << " cho) | "
             << FloatToStr(dsPhong[i].giaGio) << " VND/gio | ";
        if (dsPhong[i].dangDung) {
            cout << "DANG SU DUNG (KH: " << dsPhong[i].hoTenKH << ")\n";
        } else {
            cout << "TRONG\n";
        }
    }
}

void DatPhong() {
    cout << "\n=== DAT PHONG ===\n";
    DanhSachPhong();

    cout << "\nChon phong: "; string sp; cin >> sp;

    for (int i = 0; i < soPhong; i++) {
        if (dsPhong[i].soPhong == sp) {
            if (dsPhong[i].dangDung) {
                cout << "Phong dang duoc su dung!\n";
                return;
            }

            cout << "Ho ten khach: "; cin.ignore(); getline(cin, dsPhong[i].hoTenKH);
            cout << "Gio vao (hh mm): "; cin >> dsPhong[i].gioVao >> dsPhong[i].phutVao;

            dsPhong[i].dangDung = true;

            cout << "\n[OK] Dat phong " << sp << " thanh cong!\n";
            cout << "Gia: " << FloatToStr(dsPhong[i].giaGio) << " VND/gio\n";
            return;
        }
    }

    cout << "Khong tim thay phong!\n";
}

void GoiMon() {
    cout << "\n=== GOI MON ===\n";
    cout << "So phong: "; string sp; cin >> sp;

    bool found = false;
    for (int i = 0; i < soPhong; i++) {
        if (dsPhong[i].soPhong == sp && dsPhong[i].dangDung) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Phong khong hop le!\n";
        return;
    }

    cout << "\n--- MENU ---\n";
    for (int i = 0; i < soMenu; i++) {
        cout << (i+1) << ". " << dsMenu[i].ten << " - "
             << FloatToStr(dsMenu[i].gia) << " VND\n";
    }

    cout << "\nChon mon: "; int c; cin >> c; c--;
    if (c < 0 || c >= soMenu) {
        cout << "Khong hop le!\n";
        return;
    }

    cout << "So luong: "; int sl; cin >> sl;

    Order ord;
    ord.soPhong = sp;
    ord.maMon = dsMenu[c].ma;
    ord.soLuong = sl;

    Order* tmp = new Order[soOrder + 1];
    for (int i = 0; i < soOrder; i++) tmp[i] = dsOrder[i];
    tmp[soOrder] = ord;
    delete[] dsOrder;
    dsOrder = tmp;
    soOrder++;

    cout << "\n[OK] Da goi " << sl << " " << dsMenu[c].ten << "\n";
}

void ThanhToan() {
    cout << "\n=== THANH TOAN ===\n";
    cout << "So phong: "; string sp; cin >> sp;

    for (int i = 0; i < soPhong; i++) {
        if (dsPhong[i].soPhong == sp && dsPhong[i].dangDung) {
            cout << "\n--- HOA DON ---\n";
            cout << "Phong: " << sp << " (" << dsPhong[i].loai << ")\n";
            cout << "Khach: " << dsPhong[i].hoTenKH << "\n";

            cout << "Gio ra (hh mm): "; int gioRa, phutRa; cin >> gioRa >> phutRa;

            int tongPhut = (gioRa * 60 + phutRa) - (dsPhong[i].gioVao * 60 + dsPhong[i].phutVao);
            float soGio = tongPhut / 60.0;
            if (tongPhut % 60 > 0) soGio += 0.5;  // Lẻ giờ tính thêm 0.5

            float tienPhong = soGio * dsPhong[i].giaGio;

            cout << "\n1. Tien phong:\n";
            cout << "   " << FloatToStr(soGio) << " gio x "
                 << FloatToStr(dsPhong[i].giaGio) << " = "
                 << FloatToStr(tienPhong) << " VND\n";

            // Tính tiền đồ ăn
            float tienDoAn = 0;
            cout << "\n2. Do an/nuoc:\n";
            for (int j = 0; j < soOrder; j++) {
                if (dsOrder[j].soPhong == sp) {
                    for (int k = 0; k < soMenu; k++) {
                        if (dsMenu[k].ma == dsOrder[j].maMon) {
                            float tt = dsOrder[j].soLuong * dsMenu[k].gia;
                            cout << "   - " << dsMenu[k].ten << " x" << dsOrder[j].soLuong
                                 << " = " << FloatToStr(tt) << " VND\n";
                            tienDoAn += tt;
                            break;
                        }
                    }
                }
            }

            float tongTien = tienPhong + tienDoAn;

            cout << "\n" << string(40, '=') << "\n";
            cout << "TONG CONG: " << FloatToStr(tongTien) << " VND\n";
            cout << string(40, '=') << "\n";

            // Trả phòng
            dsPhong[i].dangDung = false;
            dsPhong[i].hoTenKH = "";
            dsPhong[i].gioVao = 0;
            dsPhong[i].phutVao = 0;

            cout << "\n[OK] Thanh toan thanh cong!\n";
            return;
        }
    }

    cout << "Phong khong hop le!\n";
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== KARAOKE =====\n";
        cout << "1. Danh sach phong\n";
        cout << "2. Dat phong\n";
        cout << "3. Goi mon\n";
        cout << "4. Thanh toan\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachPhong();
        else if (c == 2) DatPhong();
        else if (c == 3) GoiMon();
        else if (c == 4) ThanhToan();
        else if (c == 0) break;
    }

    delete[] dsOrder;
    return 0;
}
