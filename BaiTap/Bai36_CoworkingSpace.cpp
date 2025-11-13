/*
BÀI 36: CO-WORKING SPACE
- Thuê chỗ (theo giờ, ngày, tháng)
- Các loại chỗ (bàn đơn, phòng họp, phòng riêng)
- Dịch vụ thêm (in ấn, cà phê, đỗ xe)
- Thẻ thành viên (ưu đãi)
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
struct ChoNgoi {
    string maViTri, loai;  // "BanDon", "PhongHop", "PhongRieng"
    int soChoNgoi;
    float giaGio, giaNgay, giaThang;
    bool dangDung;
};

struct ThanhVien {
    string maTV, hoTen, sdt, email;
    string loaiThe;  // "Basic", "Premium"
    float giamGia;   // 10% hoac 20%
};

struct DonThue {
    string maDon, maViTri, hoTenKH;
    string loaiThue;  // "Gio", "Ngay", "Thang"
    int soLuong;      // Số giờ/ngày/tháng
    float tienThue;
    float tienDichVu;
    float tongTien;
};

// === DỮ LIỆU ===
ChoNgoi dsViTri[20] = {
    {"D01", "BanDon", 1, 50000, 300000, 3000000, false},
    {"D02", "BanDon", 1, 50000, 300000, 3000000, false},
    {"M01", "PhongHop", 8, 200000, 1500000, 0, false},
    {"M02", "PhongHop", 12, 300000, 2000000, 0, false},
    {"P01", "PhongRieng", 4, 150000, 1000000, 8000000, false}
};
int soViTri = 5;

ThanhVien* dsTV = NULL;
int soTV = 0;

DonThue* dsDon = NULL;
int soDon = 0;

// === CHỨC NĂNG ===
void DanhSachViTri() {
    cout << "\n=== DANH SACH VI TRI ===\n";
    for (int i = 0; i < soViTri; i++) {
        cout << (i+1) << ". " << dsViTri[i].maViTri << " - " << dsViTri[i].loai;
        if (dsViTri[i].loai != "BanDon") {
            cout << " (" << dsViTri[i].soChoNgoi << " cho)";
        }
        cout << "\n   Gia gio: " << FloatToStr(dsViTri[i].giaGio) << " VND";
        cout << " | Gia ngay: " << FloatToStr(dsViTri[i].giaNgay) << " VND";
        if (dsViTri[i].giaThang > 0) {
            cout << " | Gia thang: " << FloatToStr(dsViTri[i].giaThang) << " VND";
        }
        cout << " | " << (dsViTri[i].dangDung ? "DANG DUNG" : "TRONG") << "\n\n";
    }
}

void ThueViTri() {
    cout << "\n=== THUE VI TRI ===\n";
    DanhSachViTri();

    cout << "Chon vi tri: "; int c; cin >> c; c--;
    if (c < 0 || c >= soViTri || dsViTri[c].dangDung) {
        cout << "Khong hop le hoac dang duoc su dung!\n";
        return;
    }

    DonThue don;
    don.maDon = "DT" + IntToStr(soDon + 1);
    don.maViTri = dsViTri[c].maViTri;

    cout << "Ho ten: "; cin.ignore(); getline(cin, don.hoTenKH);

    cout << "\nLoai thue:\n";
    cout << "1. Theo gio (" << FloatToStr(dsViTri[c].giaGio) << " VND/gio)\n";
    cout << "2. Theo ngay (" << FloatToStr(dsViTri[c].giaNgay) << " VND/ngay)\n";
    if (dsViTri[c].giaThang > 0) {
        cout << "3. Theo thang (" << FloatToStr(dsViTri[c].giaThang) << " VND/thang)\n";
    }
    cout << "Chon: "; int loai; cin >> loai;

    if (loai == 1) {
        don.loaiThue = "Gio";
        cout << "So gio: "; cin >> don.soLuong;
        don.tienThue = dsViTri[c].giaGio * don.soLuong;
    } else if (loai == 2) {
        don.loaiThue = "Ngay";
        cout << "So ngay: "; cin >> don.soLuong;
        don.tienThue = dsViTri[c].giaNgay * don.soLuong;
    } else if (loai == 3 && dsViTri[c].giaThang > 0) {
        don.loaiThue = "Thang";
        cout << "So thang: "; cin >> don.soLuong;
        don.tienThue = dsViTri[c].giaThang * don.soLuong;
    } else {
        cout << "Khong hop le!\n";
        return;
    }

    // Dịch vụ thêm
    cout << "\nDich vu them:\n";
    cout << "1. In an (10,000/trang): "; int soTrang; cin >> soTrang;
    cout << "2. Ca phe (30,000/ly): "; int lyCaPhe; cin >> lyCaPhe;
    cout << "3. Do xe (20,000/ngay): "; int doXe; cin >> doXe;

    don.tienDichVu = soTrang * 10000 + lyCaPhe * 30000 + doXe * 20000;

    don.tongTien = don.tienThue + don.tienDichVu;

    // Kiểm tra thành viên
    cout << "\nLa thanh vien? (1=Co, 0=Khong): "; int tv; cin >> tv;
    if (tv == 1) {
        cout << "Ma thanh vien: "; string maTV; cin >> maTV;
        for (int i = 0; i < soTV; i++) {
            if (dsTV[i].maTV == maTV) {
                don.tongTien *= (1 - dsTV[i].giamGia);
                cout << ">>> GIAM " << (dsTV[i].giamGia * 100) << "% cho thanh vien "
                     << dsTV[i].loaiThe << "!\n";
                break;
            }
        }
    }

    dsViTri[c].dangDung = true;

    cout << "\n[OK] Ma don: " << don.maDon << "\n";
    cout << "Tong tien: " << FloatToStr(don.tongTien) << " VND\n";

    DonThue* tmp = new DonThue[soDon + 1];
    for (int i = 0; i < soDon; i++) tmp[i] = dsDon[i];
    tmp[soDon] = don;
    delete[] dsDon;
    dsDon = tmp;
    soDon++;
}

void DangKyThanhVien() {
    cout << "\n=== DANG KY THANH VIEN ===\n";

    ThanhVien tv;
    tv.maTV = "TV" + IntToStr(soTV + 1);
    cout << "Ho ten: "; cin.ignore(); getline(cin, tv.hoTen);
    cout << "SDT: "; getline(cin, tv.sdt);
    cout << "Email: "; getline(cin, tv.email);

    cout << "\nLoai the:\n";
    cout << "1. Basic (giam 10%)\n";
    cout << "2. Premium (giam 20%)\n";
    cout << "Chon: "; int loai; cin >> loai;

    if (loai == 1) {
        tv.loaiThe = "Basic";
        tv.giamGia = 0.10;
    } else {
        tv.loaiThe = "Premium";
        tv.giamGia = 0.20;
    }

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
        cout << "\n===== CO-WORKING SPACE =====\n";
        cout << "1. Danh sach vi tri\n";
        cout << "2. Thue vi tri\n";
        cout << "3. Dang ky thanh vien\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachViTri();
        else if (c == 2) ThueViTri();
        else if (c == 3) DangKyThanhVien();
        else if (c == 0) break;
    }

    delete[] dsTV;
    delete[] dsDon;
    return 0;
}
