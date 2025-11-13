/*
BÀI 29: SHOP QUẦN ÁO
- Quản lý sản phẩm (loại, size, màu, giá)
- Bán hàng (chọn nhiều món)
- Giảm giá (mua > 3 món -10%, > 5 món -15%)
- Đổi trả hàng trong 7 ngày
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
    string ma, ten, loai, mau;
    string size;  // S, M, L, XL
    float gia;
    int tonKho;
};

struct ChiTietHD {
    string maSP;
    int soLuong;
};

struct HoaDon {
    string maHD, hoTenKH, sdt, ngayMua;
    ChiTietHD dsChiTiet[20];
    int soMon;
    float tongTien;
    bool daDoiTra;
};

// === DỮ LIỆU ===
SanPham dsSP[30] = {
    {"SP01", "Ao thun co tron", "Ao", "Trang", "M", 150000, 50},
    {"SP02", "Ao thun co tron", "Ao", "Den", "L", 150000, 40},
    {"SP03", "Ao somi", "Ao", "Xanh", "M", 280000, 30},
    {"SP04", "Quan jean", "Quan", "Xanh", "30", 350000, 25},
    {"SP05", "Quan kaki", "Quan", "Be", "31", 320000, 20},
    {"SP06", "Dam maxi", "Dam", "Do", "M", 450000, 15},
    {"SP07", "Vay ngan", "Vay", "Den", "S", 220000, 18}
};
int soSP = 7;

HoaDon* dsHD = NULL;
int soHD = 0;

// === CHỨC NĂNG ===
void DanhSachSanPham() {
    cout << "\n=== DANH SACH SAN PHAM ===\n";
    for (int i = 0; i < soSP; i++) {
        cout << (i+1) << ". " << dsSP[i].ten << " | " << dsSP[i].mau
             << " | Size " << dsSP[i].size << " | "
             << FloatToStr(dsSP[i].gia) << " VND | Ton: " << dsSP[i].tonKho << "\n";
    }
}

void BanHang() {
    cout << "\n=== BAN HANG ===\n";

    HoaDon hd;
    hd.maHD = "HD" + IntToStr(soHD + 1);
    cout << "Ho ten khach: "; cin.ignore(); getline(cin, hd.hoTenKH);
    cout << "SDT: "; getline(cin, hd.sdt);
    cout << "Ngay mua (dd/mm/yyyy): "; cin >> hd.ngayMua;

    hd.soMon = 0;
    hd.tongTien = 0;
    hd.daDoiTra = false;

    while (true) {
        DanhSachSanPham();
        cout << "\nChon san pham (0 de ket thuc): "; int c; cin >> c;
        if (c == 0) break;
        c--;

        if (c < 0 || c >= soSP) {
            cout << "Khong hop le!\n";
            continue;
        }

        cout << "So luong: "; int sl; cin >> sl;

        if (sl > dsSP[c].tonKho) {
            cout << "Khong du hang!\n";
            continue;
        }

        // Thêm vào chi tiết
        hd.dsChiTiet[hd.soMon].maSP = dsSP[c].ma;
        hd.dsChiTiet[hd.soMon].soLuong = sl;
        hd.soMon++;

        dsSP[c].tonKho -= sl;
        hd.tongTien += dsSP[c].gia * sl;

        cout << "[OK] Da them " << dsSP[c].ten << "\n";
    }

    if (hd.soMon == 0) {
        cout << "Khong co san pham nao!\n";
        return;
    }

    // Áp dụng giảm giá
    float giamGia = 0;
    if (hd.soMon >= 5) {
        giamGia = 0.15;
        cout << "\n>>> GIAM 15% khi mua >= 5 mon!\n";
    } else if (hd.soMon >= 3) {
        giamGia = 0.10;
        cout << "\n>>> GIAM 10% khi mua >= 3 mon!\n";
    }

    if (giamGia > 0) {
        hd.tongTien *= (1 - giamGia);
    }

    cout << "\n[OK] Tong tien: " << FloatToStr(hd.tongTien) << " VND\n";
    cout << "Ma hoa don: " << hd.maHD << " (luu lai de doi tra)\n";

    HoaDon* tmp = new HoaDon[soHD + 1];
    for (int i = 0; i < soHD; i++) tmp[i] = dsHD[i];
    tmp[soHD] = hd;
    delete[] dsHD;
    dsHD = tmp;
    soHD++;
}

void DoiTraHang() {
    cout << "\n=== DOI TRA HANG ===\n";
    cout << "Ma hoa don: "; string maHD; cin >> maHD;

    for (int i = 0; i < soHD; i++) {
        if (dsHD[i].maHD == maHD) {
            if (dsHD[i].daDoiTra) {
                cout << "Hoa don nay da doi tra roi!\n";
                return;
            }

            cout << "\nHoa don:\n";
            cout << "Khach: " << dsHD[i].hoTenKH << " | Ngay mua: " << dsHD[i].ngayMua << "\n";
            cout << "Tong tien: " << FloatToStr(dsHD[i].tongTien) << " VND\n";
            cout << "\nXac nhan doi tra? (1=Co, 0=Khong): "; int cf; cin >> cf;

            if (cf == 1) {
                // Hoàn lại tồn kho
                for (int j = 0; j < dsHD[i].soMon; j++) {
                    for (int k = 0; k < soSP; k++) {
                        if (dsSP[k].ma == dsHD[i].dsChiTiet[j].maSP) {
                            dsSP[k].tonKho += dsHD[i].dsChiTiet[j].soLuong;
                            break;
                        }
                    }
                }

                dsHD[i].daDoiTra = true;
                cout << "\n[OK] Da doi tra hang, hoan tien " << FloatToStr(dsHD[i].tongTien) << " VND\n";
            }
            return;
        }
    }

    cout << "Khong tim thay hoa don!\n";
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== SHOP QUAN AO =====\n";
        cout << "1. Danh sach san pham\n";
        cout << "2. Ban hang\n";
        cout << "3. Doi tra hang\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachSanPham();
        else if (c == 2) BanHang();
        else if (c == 3) DoiTraHang();
        else if (c == 0) break;
    }

    delete[] dsHD;
    return 0;
}
