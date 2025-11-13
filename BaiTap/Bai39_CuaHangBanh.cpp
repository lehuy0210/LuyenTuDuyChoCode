/*
BÀI 39: CỬA HÀNG BÁNH
- Bán bánh sẵn (giảm giá cuối ngày)
- Đặt bánh sinh nhật (custom)
- In chữ lên bánh
- Giao hàng
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
struct BanhSan {
    string ma, ten;
    float gia;
    int tonKho;
    int gioDangBan;  // Giờ hiện tại để tính giảm giá
};

struct DonDatBanh {
    string maDon, hoTenKH, sdt;
    string loaiBanh;  // "Mousse", "Tiramisu", "RedVelvet"...
    int soTang;       // 1, 2, 3 tầng
    string viRim;     // Vị kem phủ
    string chuInLen;
    float giaBanh, phiInChu, phiGiao, tongTien;
    string ngayDat, ngayNhan;
};

// === DỮ LIỆU ===
BanhSan dsBanhSan[20] = {
    {"B01", "Banh mi sandwich", 35000, 20, 8},
    {"B02", "Banh croissant", 25000, 30, 8},
    {"B03", "Banh su kem", 15000, 50, 8},
    {"B04", "Banh flan", 40000, 15, 8},
    {"B05", "Banh bong lan trung muoi", 120000, 10, 8}
};
int soBanhSan = 5;

DonDatBanh* dsDonDat = NULL;
int soDonDat = 0;

// Bảng giá bánh custom
const float GIA_1_TANG = 350000;
const float GIA_2_TANG = 650000;
const float GIA_3_TANG = 950000;
const float PHI_IN_CHU = 50000;

// === CHỨC NĂNG ===
void BanBanhSan() {
    cout << "\n=== BAN BANH SAN ===\n";
    cout << "Gio hien tai: "; int gioHT; cin >> gioHT;

    cout << "\nDanh sach banh:\n";
    for (int i = 0; i < soBanhSan; i++) {
        float giaHienTai = dsBanhSan[i].gia;

        // Giảm giá cuối ngày
        if (gioHT >= 20) {
            giaHienTai *= 0.50;  // Giảm 50% sau 20h
            cout << (i+1) << ". " << dsBanhSan[i].ten << " - "
                 << FloatToStr(giaHienTai) << " VND [GIAM 50%!] (Con: "
                 << dsBanhSan[i].tonKho << ")\n";
        } else if (gioHT >= 18) {
            giaHienTai *= 0.70;  // Giảm 30% sau 18h
            cout << (i+1) << ". " << dsBanhSan[i].ten << " - "
                 << FloatToStr(giaHienTai) << " VND [GIAM 30%] (Con: "
                 << dsBanhSan[i].tonKho << ")\n";
        } else {
            cout << (i+1) << ". " << dsBanhSan[i].ten << " - "
                 << FloatToStr(giaHienTai) << " VND (Con: "
                 << dsBanhSan[i].tonKho << ")\n";
        }
    }

    cout << "\nChon banh (0 = huy): "; int c; cin >> c;
    if (c == 0) return;
    c--;

    if (c < 0 || c >= soBanhSan || dsBanhSan[c].tonKho == 0) {
        cout << "Khong hop le hoac het hang!\n";
        return;
    }

    cout << "So luong: "; int sl; cin >> sl;
    if (sl > dsBanhSan[c].tonKho) {
        cout << "Khong du hang!\n";
        return;
    }

    float giaHienTai = dsBanhSan[c].gia;
    if (gioHT >= 20) giaHienTai *= 0.50;
    else if (gioHT >= 18) giaHienTai *= 0.70;

    float tongTien = giaHienTai * sl;

    dsBanhSan[c].tonKho -= sl;

    cout << "\n[OK] Tong tien: " << FloatToStr(tongTien) << " VND\n";
}

void DatBanhSinhNhat() {
    cout << "\n=== DAT BANH SINH NHAT (CUSTOM) ===\n";

    DonDatBanh don;
    don.maDon = "DD" + IntToStr(soDonDat + 1);

    cout << "Ho ten: "; cin.ignore(); getline(cin, don.hoTenKH);
    cout << "SDT: "; getline(cin, don.sdt);

    cout << "\nLoai banh:\n";
    cout << "1. Mousse\n2. Tiramisu\n3. Red Velvet\n4. Black Forest\n";
    cout << "Chon: "; int loai; cin >> loai;
    if (loai == 1) don.loaiBanh = "Mousse";
    else if (loai == 2) don.loaiBanh = "Tiramisu";
    else if (loai == 3) don.loaiBanh = "Red Velvet";
    else don.loaiBanh = "Black Forest";

    cout << "\nSo tang (1/2/3): "; cin >> don.soTang;
    if (don.soTang == 1) don.giaBanh = GIA_1_TANG;
    else if (don.soTang == 2) don.giaBanh = GIA_2_TANG;
    else don.giaBanh = GIA_3_TANG;

    cout << "Vi rim (Chocolate/Vanilla/Strawberry): "; cin.ignore(); getline(cin, don.viRim);

    cout << "Chu in len banh (de trong neu khong): "; getline(cin, don.chuInLen);
    don.phiInChu = (don.chuInLen == "") ? 0 : PHI_IN_CHU;

    cout << "\nGiao hang?\n";
    cout << "1. Giao tan noi (30k)\n2. Tu den lay (0k)\n";
    cout << "Chon: "; int giao; cin >> giao;
    don.phiGiao = (giao == 1) ? 30000 : 0;

    cout << "Ngay dat (dd/mm/yyyy): "; cin >> don.ngayDat;
    cout << "Ngay nhan (dd/mm/yyyy): "; cin >> don.ngayNhan;

    don.tongTien = don.giaBanh + don.phiInChu + don.phiGiao;

    cout << "\n--- DON DAT BANH ---\n";
    cout << "Ma don: " << don.maDon << "\n";
    cout << "Loai: " << don.loaiBanh << " " << don.soTang << " tang\n";
    cout << "Vi rim: " << don.viRim << "\n";
    if (don.chuInLen != "") {
        cout << "Chu: \"" << don.chuInLen << "\" (+50k)\n";
    }
    cout << "Ngay nhan: " << don.ngayNhan << "\n";
    cout << "TONG: " << FloatToStr(don.tongTien) << " VND\n";

    DonDatBanh* tmp = new DonDatBanh[soDonDat + 1];
    for (int i = 0; i < soDonDat; i++) tmp[i] = dsDonDat[i];
    tmp[soDonDat] = don;
    delete[] dsDonDat;
    dsDonDat = tmp;
    soDonDat++;

    cout << "\n[OK] Dat banh thanh cong!\n";
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== CUA HANG BANH =====\n";
        cout << "1. Ban banh san\n";
        cout << "2. Dat banh sinh nhat (custom)\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) BanBanhSan();
        else if (c == 2) DatBanhSinhNhat();
        else if (c == 0) break;
    }

    delete[] dsDonDat;
    return 0;
}
