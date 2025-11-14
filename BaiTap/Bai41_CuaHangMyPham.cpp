/*
BÀI 41: CỬA HÀNG MỸ PHẨM
- Quản lý sản phẩm (son, phấn, sữa rửa mặt...)
- Kiểm tra hạn sử dụng
- Giảm giá combo (mua set)
- Tích điểm thành viên
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

string FloatToStr(float num) {
    int intPart = (int)num;
    int decPart = (int)((num - intPart) * 100);
    if (decPart < 0) decPart = -decPart;
    return IntToStr(intPart) + "." + (decPart < 10 ? "0" : "") + IntToStr(decPart);
}

// === CẤU TRÚC ===
struct SanPham {
    string ma, ten, hang, loai;  // "Son", "Phan", "SRM", "KemDuong"
    float gia;
    int tonKho;
    string hanSD;  // mm/yyyy
};

struct ComboSet {
    string maCombo, tenCombo;
    string maSP[5];
    int soSP;
    float giaGoc, giaCombo;  // Giá combo rẻ hơn mua lẻ
};

struct ThanhVien {
    string maTV, hoTen, sdt;
    int diemTichLuy;
};

// === DỮ LIỆU ===
SanPham dsSP[30] = {
    {"SP01", "Son Kem Lia 3CE", "3CE", "Son", 450000, 20, "12/2025"},
    {"SP02", "Phan nuoc Laneige", "Laneige", "Phan", 680000, 15, "06/2026"},
    {"SP03", "Sua rua mat Cetaphil", "Cetaphil", "SRM", 250000, 30, "03/2025"},
    {"SP04", "Kem duong Klairs", "Klairs", "KemDuong", 380000, 25, "09/2025"},
    {"SP05", "Mascara Maybelline", "Maybelline", "Mascara", 180000, 40, "12/2024"}
};
int soSP = 5;

ComboSet dsCombo[10] = {
    {"C01", "Combo Trang diem co ban",
     {"SP01", "SP02", "SP05"}, 3, 1310000, 1100000},
    {"C02", "Combo Cham soc da",
     {"SP03", "SP04"}, 2, 630000, 550000}
};
int soCombo = 2;

ThanhVien* dsTV = NULL;
int soTV = 0;

// === CHỨC NĂNG ===
void DanhSachSanPham() {
    cout << "\n=== DANH SACH SAN PHAM ===\n";
    for (int i = 0; i < soSP; i++) {
        cout << (i+1) << ". " << dsSP[i].ten << " (" << dsSP[i].hang << ")\n";
        cout << "   Loai: " << dsSP[i].loai << " | Gia: "
             << FloatToStr(dsSP[i].gia) << " VND | Ton: "
             << dsSP[i].tonKho << " | HSD: " << dsSP[i].hanSD << "\n";
    }
}

void DanhSachCombo() {
    cout << "\n=== COMBO SET (TIET KIEM) ===\n";
    for (int i = 0; i < soCombo; i++) {
        cout << (i+1) << ". " << dsCombo[i].tenCombo << "\n";
        cout << "   Bao gom: ";
        for (int j = 0; j < dsCombo[i].soSP; j++) {
            // Tìm tên sản phẩm
            for (int k = 0; k < soSP; k++) {
                if (dsSP[k].ma == dsCombo[i].maSP[j]) {
                    cout << dsSP[k].ten;
                    if (j < dsCombo[i].soSP - 1) cout << ", ";
                    break;
                }
            }
        }
        cout << "\n   Gia goc: " << FloatToStr(dsCombo[i].giaGoc)
             << " VND -> Gia combo: " << FloatToStr(dsCombo[i].giaCombo)
             << " VND [TIET KIEM "
             << FloatToStr(dsCombo[i].giaGoc - dsCombo[i].giaCombo) << " VND]\n\n";
    }
}

void MuaHang() {
    cout << "\n=== MUA HANG ===\n";
    cout << "1. Mua san pham le\n2. Mua combo\nChon: "; int loai; cin >> loai;

    float tongTien = 0;

    if (loai == 1) {
        DanhSachSanPham();
        cout << "\nChon san pham: "; int c; cin >> c; c--;
        if (c < 0 || c >= soSP || dsSP[c].tonKho == 0) {
            cout << "Khong hop le!\n";
            return;
        }
        cout << "So luong: "; int sl; cin >> sl;
        if (sl > dsSP[c].tonKho) {
            cout << "Khong du hang!\n";
            return;
        }
        tongTien = dsSP[c].gia * sl;
        dsSP[c].tonKho -= sl;
    } else {
        DanhSachCombo();
        cout << "\nChon combo: "; int c; cin >> c; c--;
        if (c < 0 || c >= soCombo) {
            cout << "Khong hop le!\n";
            return;
        }
        // Kiểm tra tồn kho
        bool duHang = true;
        for (int i = 0; i < dsCombo[c].soSP; i++) {
            for (int j = 0; j < soSP; j++) {
                if (dsSP[j].ma == dsCombo[c].maSP[i] && dsSP[j].tonKho == 0) {
                    duHang = false;
                    break;
                }
            }
        }
        if (!duHang) {
            cout << "Combo het hang!\n";
            return;
        }
        // Trừ tồn kho
        for (int i = 0; i < dsCombo[c].soSP; i++) {
            for (int j = 0; j < soSP; j++) {
                if (dsSP[j].ma == dsCombo[c].maSP[i]) {
                    dsSP[j].tonKho--;
                    break;
                }
            }
        }
        tongTien = dsCombo[c].giaCombo;
    }

    cout << "\nLa thanh vien? (1=Co, 0=Khong): "; int tv; cin >> tv;
    if (tv == 1) {
        cout << "Ma thanh vien: "; string maTV; cin >> maTV;
        for (int i = 0; i < soTV; i++) {
            if (dsTV[i].maTV == maTV) {
                // Tích điểm (100 VND = 1 điểm)
                int diemThem = (int)(tongTien / 100);
                dsTV[i].diemTichLuy += diemThem;
                cout << ">>> Tich duoc " << diemThem << " diem! Tong diem: "
                     << dsTV[i].diemTichLuy << "\n";
                break;
            }
        }
    }

    cout << "\n[OK] Tong tien: " << FloatToStr(tongTien) << " VND\n";
}

void DangKyThanhVien() {
    cout << "\n=== DANG KY THANH VIEN ===\n";
    ThanhVien tv;
    tv.maTV = "TV" + IntToStr(soTV + 1);
    cout << "Ho ten: "; cin.ignore(); getline(cin, tv.hoTen);
    cout << "SDT: "; getline(cin, tv.sdt);
    tv.diemTichLuy = 0;

    cout << "\n[OK] Ma thanh vien: " << tv.maTV << "\n";

    ThanhVien* tmp = new ThanhVien[soTV + 1];
    for (int i = 0; i < soTV; i++) tmp[i] = dsTV[i];
    tmp[soTV] = tv;
    delete[] dsTV;
    dsTV = tmp;
    soTV++;
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== CUA HANG MY PHAM =====\n";
        cout << "1. Danh sach san pham\n";
        cout << "2. Danh sach combo\n";
        cout << "3. Mua hang\n";
        cout << "4. Dang ky thanh vien\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachSanPham();
        else if (c == 2) DanhSachCombo();
        else if (c == 3) MuaHang();
        else if (c == 4) DangKyThanhVien();
        else if (c == 0) break;
    }

    delete[] dsTV;
    return 0;
}
