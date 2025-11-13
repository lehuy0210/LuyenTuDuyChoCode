/*
BÀI 37: TIỆM VÀNG
- Quản lý sản phẩm (nhẫn, vòng, dây chuyền...)
- Giá vàng theo ngày (mua vào/bán ra)
- Bán sản phẩm (tiền vàng + công)
- Thu mua vàng cũ
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
struct GiaVang {
    string ngay;
    float giaMuaVao;  // Giá mua vào (VNĐ/chỉ)
    float giaBanRa;   // Giá bán ra (VNĐ/chỉ)
};

struct SanPham {
    string ma, ten, loai;  // Nhan, Vong, DayTeo, BongTai...
    float trongLuong;       // Chỉ (1 chỉ = 3.75g)
    float tienCong;
    int tonKho;
};

struct HoaDonBan {
    string maHD, maSP, hoTenKH, sdt, ngay;
    float tienVang, tienCong, tongTien;
};

struct PhieuThuMua {
    string maPhieu, hoTenKH, loaiVang;
    float trongLuong, tongTien;
    string ngay;
};

// === DỮ LIỆU ===
GiaVang giaHienTai = {"13/11/2024", 7300000, 7400000};  // VNĐ/chỉ

SanPham dsSP[30] = {
    {"SP01", "Nhan vang tron tru", "Nhan", 2.5, 500000, 10},
    {"SP02", "Nhan vang da quy", "Nhan", 3.0, 2000000, 5},
    {"SP03", "Vong tay kim tien", "Vong", 5.0, 800000, 8},
    {"SP04", "Day chuyen nu", "DayTeo", 4.5, 600000, 12},
    {"SP05", "Bong tai tron", "BongTai", 1.5, 400000, 15}
};
int soSP = 5;

HoaDonBan* dsHD = NULL;
int soHD = 0;

PhieuThuMua* dsPhieu = NULL;
int soPhieu = 0;

// === CHỨC NĂNG ===
void XemGiaVang() {
    cout << "\n=== GIA VANG NGAY " << giaHienTai.ngay << " ===\n";
    cout << "Mua vao: " << FloatToStr(giaHienTai.giaMuaVao) << " VND/chi\n";
    cout << "Ban ra:  " << FloatToStr(giaHienTai.giaBanRa) << " VND/chi\n";
}

void DanhSachSanPham() {
    cout << "\n=== DANH SACH SAN PHAM ===\n";
    for (int i = 0; i < soSP; i++) {
        float tienVang = dsSP[i].trongLuong * giaHienTai.giaBanRa;
        float giaHienTai = tienVang + dsSP[i].tienCong;

        cout << (i+1) << ". " << dsSP[i].ten << " (" << dsSP[i].loai << ")\n";
        cout << "   Trong luong: " << FloatToStr(dsSP[i].trongLuong) << " chi\n";
        cout << "   Tien vang: " << FloatToStr(tienVang) << " VND\n";
        cout << "   Tien cong: " << FloatToStr(dsSP[i].tienCong) << " VND\n";
        cout << "   GIA BAN: " << FloatToStr(giaHienTai) << " VND\n";
        cout << "   Ton kho: " << dsSP[i].tonKho << "\n\n";
    }
}

void BanSanPham() {
    cout << "\n=== BAN SAN PHAM ===\n";
    DanhSachSanPham();

    cout << "Chon san pham: "; int c; cin >> c; c--;
    if (c < 0 || c >= soSP || dsSP[c].tonKho == 0) {
        cout << "Khong hop le hoac het hang!\n";
        return;
    }

    HoaDonBan hd;
    hd.maHD = "HD" + IntToStr(soHD + 1);
    hd.maSP = dsSP[c].ma;

    cout << "Ho ten khach: "; cin.ignore(); getline(cin, hd.hoTenKH);
    cout << "SDT: "; getline(cin, hd.sdt);
    cout << "Ngay (dd/mm/yyyy): "; cin >> hd.ngay;

    hd.tienVang = dsSP[c].trongLuong * giaHienTai.giaBanRa;
    hd.tienCong = dsSP[c].tienCong;
    hd.tongTien = hd.tienVang + hd.tienCong;

    dsSP[c].tonKho--;

    cout << "\n--- HOA DON ---\n";
    cout << "San pham: " << dsSP[c].ten << "\n";
    cout << "Trong luong: " << FloatToStr(dsSP[c].trongLuong) << " chi\n";
    cout << "Tien vang: " << FloatToStr(hd.tienVang) << " VND\n";
    cout << "Tien cong: " << FloatToStr(hd.tienCong) << " VND\n";
    cout << "TONG: " << FloatToStr(hd.tongTien) << " VND\n";

    HoaDonBan* tmp = new HoaDonBan[soHD + 1];
    for (int i = 0; i < soHD; i++) tmp[i] = dsHD[i];
    tmp[soHD] = hd;
    delete[] dsHD;
    dsHD = tmp;
    soHD++;

    cout << "\n[OK] Ma hoa don: " << hd.maHD << "\n";
}

void ThuMuaVang() {
    cout << "\n=== THU MUA VANG CU ===\n";
    XemGiaVang();

    PhieuThuMua phieu;
    phieu.maPhieu = "PM" + IntToStr(soPhieu + 1);

    cout << "\nHo ten khach: "; cin.ignore(); getline(cin, phieu.hoTenKH);
    cout << "Loai vang (Nhan/Vong/Day...): "; getline(cin, phieu.loaiVang);
    cout << "Trong luong (chi): "; cin >> phieu.trongLuong;
    cout << "Ngay (dd/mm/yyyy): "; cin >> phieu.ngay;

    phieu.tongTien = phieu.trongLuong * giaHienTai.giaMuaVao;

    cout << "\n--- PHIEU THU MUA ---\n";
    cout << "Loai: " << phieu.loaiVang << "\n";
    cout << "Trong luong: " << FloatToStr(phieu.trongLuong) << " chi\n";
    cout << "Gia mua vao: " << FloatToStr(giaHienTai.giaMuaVao) << " VND/chi\n";
    cout << "TONG THANH TOAN: " << FloatToStr(phieu.tongTien) << " VND\n";

    PhieuThuMua* tmp = new PhieuThuMua[soPhieu + 1];
    for (int i = 0; i < soPhieu; i++) tmp[i] = dsPhieu[i];
    tmp[soPhieu] = phieu;
    delete[] dsPhieu;
    dsPhieu = tmp;
    soPhieu++;

    cout << "\n[OK] Ma phieu: " << phieu.maPhieu << "\n";
}

void CapNhatGiaVang() {
    cout << "\n=== CAP NHAT GIA VANG ===\n";
    cout << "Ngay (dd/mm/yyyy): "; cin >> giaHienTai.ngay;
    cout << "Gia mua vao (VND/chi): "; cin >> giaHienTai.giaMuaVao;
    cout << "Gia ban ra (VND/chi): "; cin >> giaHienTai.giaBanRa;
    cout << "\n[OK] Da cap nhat gia vang!\n";
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== TIEM VANG =====\n";
        cout << "1. Xem gia vang\n";
        cout << "2. Danh sach san pham\n";
        cout << "3. Ban san pham\n";
        cout << "4. Thu mua vang cu\n";
        cout << "5. Cap nhat gia vang\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) XemGiaVang();
        else if (c == 2) DanhSachSanPham();
        else if (c == 3) BanSanPham();
        else if (c == 4) ThuMuaVang();
        else if (c == 5) CapNhatGiaVang();
        else if (c == 0) break;
    }

    delete[] dsHD;
    delete[] dsPhieu;
    return 0;
}
