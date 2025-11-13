/*
BÀI 32: CỬA HÀNG ĐIỆN MÁY
- Quản lý sản phẩm (tivi, tủ lạnh, máy giặt...)
- Bán hàng (trả góp 0%, bảo hành)
- Bảo hành (theo IMEI/Serial)
- Thống kê sản phẩm bán chạy
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
    string ma, ten, hang, model;
    float gia;
    int tonKho;
    int thangBaoHanh;  // 12, 24, 36 tháng
    int daBan;
};

struct HoaDonBan {
    string maHD, maSP, hoTenKH, sdt, ngayMua;
    string serial;  // IMEI/Serial number
    bool traGop;
    int kyTraGop;  // 0, 6, 12, 24 tháng
    float tongTien, tienHangThang;
};

// === DỮ LIỆU ===
SanPham dsSP[30] = {
    {"SP01", "Tivi Samsung 43 inch", "Samsung", "UA43T6500", 8500000, 20, 24, 0},
    {"SP02", "Tu lanh LG 420L", "LG", "GR-B422PS", 12000000, 15, 12, 0},
    {"SP03", "May giat Electrolux 9kg", "Electrolux", "EWF9025", 9500000, 10, 24, 0},
    {"SP04", "Dieu hoa Daikin 1.5HP", "Daikin", "FTC35NV1V", 11000000, 12, 36, 0},
    {"SP05", "Lo vi song Panasonic", "Panasonic", "NN-ST34", 2500000, 25, 12, 0}
};
int soSP = 5;

HoaDonBan* dsHD = NULL;
int soHD = 0;

// === CHỨC NĂNG ===
void DanhSachSanPham() {
    cout << "\n=== DANH SACH SAN PHAM ===\n";
    for (int i = 0; i < soSP; i++) {
        cout << (i+1) << ". " << dsSP[i].ten << " (" << dsSP[i].hang << " "
             << dsSP[i].model << ")\n";
        cout << "   Gia: " << FloatToStr(dsSP[i].gia) << " VND | Ton: "
             << dsSP[i].tonKho << " | BH: " << dsSP[i].thangBaoHanh << " thang\n";
    }
}

void BanHang() {
    cout << "\n=== BAN HANG ===\n";
    DanhSachSanPham();

    cout << "\nChon san pham: "; int c; cin >> c; c--;
    if (c < 0 || c >= soSP || dsSP[c].tonKho == 0) {
        cout << "Khong hop le hoac het hang!\n";
        return;
    }

    HoaDonBan hd;
    hd.maHD = "HD" + IntToStr(soHD + 1);
    hd.maSP = dsSP[c].ma;

    cout << "Ho ten khach: "; cin.ignore(); getline(cin, hd.hoTenKH);
    cout << "SDT: "; getline(cin, hd.sdt);
    cout << "Ngay mua (dd/mm/yyyy): "; cin >> hd.ngayMua;
    cout << "Serial/IMEI: "; cin >> hd.serial;

    cout << "\nHinh thuc thanh toan:\n";
    cout << "1. Tien mat (giam 3%)\n";
    cout << "2. Tra gop 0% (6, 12, 24 thang)\n";
    cout << "Chon: "; int loai; cin >> loai;

    hd.tongTien = dsSP[c].gia;

    if (loai == 1) {
        hd.traGop = false;
        hd.kyTraGop = 0;
        hd.tongTien *= 0.97;  // Giảm 3%
        hd.tienHangThang = 0;
        cout << "\n>>> GIAM 3% khi tra tien mat!\n";
    } else {
        hd.traGop = true;
        cout << "So ky tra gop (6/12/24): "; cin >> hd.kyTraGop;
        hd.tienHangThang = hd.tongTien / hd.kyTraGop;
        cout << "\n>>> Tra gop 0%: " << FloatToStr(hd.tienHangThang)
             << " VND x " << hd.kyTraGop << " thang\n";
    }

    dsSP[c].tonKho--;
    dsSP[c].daBan++;

    cout << "\n[OK] Ma hoa don: " << hd.maHD << "\n";
    cout << "Tong tien: " << FloatToStr(hd.tongTien) << " VND\n";
    cout << "Bao hanh: " << dsSP[c].thangBaoHanh << " thang\n";

    HoaDonBan* tmp = new HoaDonBan[soHD + 1];
    for (int i = 0; i < soHD; i++) tmp[i] = dsHD[i];
    tmp[soHD] = hd;
    delete[] dsHD;
    dsHD = tmp;
    soHD++;
}

void KiemTraBaoHanh() {
    cout << "\n=== KIEM TRA BAO HANH ===\n";
    cout << "Serial/IMEI: "; string serial; cin >> serial;

    for (int i = 0; i < soHD; i++) {
        if (dsHD[i].serial == serial) {
            cout << "\nThong tin bao hanh:\n";
            cout << "Ma HD: " << dsHD[i].maHD << "\n";
            cout << "Khach hang: " << dsHD[i].hoTenKH << " | SDT: " << dsHD[i].sdt << "\n";
            cout << "Ngay mua: " << dsHD[i].ngayMua << "\n";

            // Tìm sản phẩm
            for (int j = 0; j < soSP; j++) {
                if (dsSP[j].ma == dsHD[i].maSP) {
                    cout << "San pham: " << dsSP[j].ten << "\n";
                    cout << "Thoi han bao hanh: " << dsSP[j].thangBaoHanh << " thang\n";
                    break;
                }
            }
            return;
        }
    }

    cout << "Khong tim thay thong tin bao hanh!\n";
}

void ThongKe() {
    cout << "\n=== THONG KE SAN PHAM BAN CHAY ===\n";

    // Sắp xếp theo số lượng bán (bubble sort)
    for (int i = 0; i < soSP - 1; i++) {
        for (int j = i + 1; j < soSP; j++) {
            if (dsSP[j].daBan > dsSP[i].daBan) {
                SanPham temp = dsSP[i];
                dsSP[i] = dsSP[j];
                dsSP[j] = temp;
            }
        }
    }

    cout << "\nTop 5 san pham ban chay:\n";
    for (int i = 0; i < 5 && i < soSP; i++) {
        if (dsSP[i].daBan > 0) {
            cout << (i+1) << ". " << dsSP[i].ten << " - Da ban: "
                 << dsSP[i].daBan << " san pham\n";
        }
    }
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== CUA HANG DIEN MAY =====\n";
        cout << "1. Danh sach san pham\n";
        cout << "2. Ban hang\n";
        cout << "3. Kiem tra bao hanh\n";
        cout << "4. Thong ke san pham ban chay\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachSanPham();
        else if (c == 2) BanHang();
        else if (c == 3) KiemTraBaoHanh();
        else if (c == 4) ThongKe();
        else if (c == 0) break;
    }

    delete[] dsHD;
    return 0;
}
