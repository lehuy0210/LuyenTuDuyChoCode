/*
BÀI 44: SHOWROOM Ô TÔ
- Quản lý xe (hãng, model, năm, giá)
- Đặt cọc 30%
- Trả góp (36, 48, 60 tháng)
- Test drive (đặt lịch)
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
    int decPart = (int)((num - intPart) * 1000000);
    if (decPart < 0) decPart = -decPart;
    return IntToStr(intPart) + "." + IntToStr(decPart/1000);
}

// === CẤU TRÚC ===
struct Xe {
    string maXe, hang, model, mau;
    int namSX;
    float gia;  // VNĐ (tỷ)
    bool conHang;
};

struct DonDatXe {
    string maDon, maXe, hoTenKH, sdt;
    string hinhThucTT;  // "TienMat", "TraGop36", "TraGop48", "TraGop60"
    float datCoc, conLai, tienHangThang;
    string ngayDat;
};

struct LichTestDrive {
    string maLich, maXe, hoTenKH, sdt;
    string ngay, gio;
};

// === DỮ LIỆU ===
Xe dsXe[20] = {
    {"X01", "Honda", "City RS", "Trang", 2024, 599000000, true},
    {"X02", "Toyota", "Vios G", "Bac", 2024, 545000000, true},
    {"X03", "Mazda", "CX-5 2.0", "Do", 2024, 859000000, true},
    {"X04", "Hyundai", "Tucson 2.0", "Den", 2024, 879000000, true},
    {"X05", "Kia", "Seltos Luxury", "Xam", 2024, 679000000, false}
};
int soXe = 5;

DonDatXe* dsDon = NULL;
int soDon = 0;

LichTestDrive* dsLich = NULL;
int soLich = 0;

const float LAI_SUAT_NAM = 0.08;  // 8%/năm

// === CHỨC NĂNG ===
void DanhSachXe() {
    cout << "\n=== DANH SACH XE ===\n";
    for (int i = 0; i < soXe; i++) {
        cout << (i+1) << ". " << dsXe[i].hang << " " << dsXe[i].model
             << " (" << dsXe[i].namSX << ")\n";
        cout << "   Mau: " << dsXe[i].mau << " | Gia: "
             << FloatToStr(dsXe[i].gia/1000000) << " trieu VND | "
             << (dsXe[i].conHang ? "CON HANG" : "HET HANG") << "\n\n";
    }
}

void DatXe() {
    cout << "\n=== DAT XE ===\n";
    DanhSachXe();

    cout << "Chon xe: "; int c; cin >> c; c--;
    if (c < 0 || c >= soXe || !dsXe[c].conHang) {
        cout << "Khong hop le hoac het hang!\n";
        return;
    }

    DonDatXe don;
    don.maDon = "DD" + IntToStr(soDon + 1);
    don.maXe = dsXe[c].maXe;

    cout << "\nHo ten: "; cin.ignore(); getline(cin, don.hoTenKH);
    cout << "SDT: "; getline(cin, don.sdt);
    cout << "Ngay dat (dd/mm/yyyy): "; cin >> don.ngayDat;

    // Hình thức thanh toán
    cout << "\nHinh thuc thanh toan:\n";
    cout << "1. Tien mat (giam 2%)\n";
    cout << "2. Tra gop 36 thang (LS 8%/nam)\n";
    cout << "3. Tra gop 48 thang (LS 8%/nam)\n";
    cout << "4. Tra gop 60 thang (LS 8%/nam)\n";
    cout << "Chon: "; int loai; cin >> loai;

    float giaXe = dsXe[c].gia;

    if (loai == 1) {
        don.hinhThucTT = "TienMat";
        giaXe *= 0.98;  // Giảm 2%
        don.datCoc = giaXe * 0.30;
        don.conLai = giaXe - don.datCoc;
        don.tienHangThang = 0;
        cout << "\n>>> GIAM 2% khi tra tien mat!\n";
    } else {
        int soThang = (loai == 2) ? 36 : (loai == 3) ? 48 : 60;
        don.hinhThucTT = "TraGop" + IntToStr(soThang);

        don.datCoc = giaXe * 0.30;  // Đặt cọc 30%
        float soTienVay = giaXe - don.datCoc;

        // Tính trả góp với lãi suất
        float laiSuatThang = LAI_SUAT_NAM / 12;
        don.tienHangThang = soTienVay * laiSuatThang * pow(1 + laiSuatThang, soThang) / (pow(1 + laiSuatThang, soThang) - 1);
        don.conLai = don.tienHangThang * soThang;

        cout << "\n>>> Tra gop " << soThang << " thang\n";
        cout << "Tien hang thang: ~" << FloatToStr(don.tienHangThang/1000000)
             << " trieu VND\n";
    }

    cout << "\n--- DON DAT XE ---\n";
    cout << "Ma don: " << don.maDon << "\n";
    cout << "Xe: " << dsXe[c].hang << " " << dsXe[c].model << "\n";
    cout << "Dat coc (30%): " << FloatToStr(don.datCoc/1000000) << " trieu VND\n";
    cout << "Con lai: " << FloatToStr(don.conLai/1000000) << " trieu VND\n";

    dsXe[c].conHang = false;

    DonDatXe* tmp = new DonDatXe[soDon + 1];
    for (int i = 0; i < soDon; i++) tmp[i] = dsDon[i];
    tmp[soDon] = don;
    delete[] dsDon;
    dsDon = tmp;
    soDon++;

    cout << "\n[OK] Dat xe thanh cong!\n";
}

void DatLichTestDrive() {
    cout << "\n=== DAT LICH TEST DRIVE ===\n";
    DanhSachXe();

    cout << "Chon xe muon lai thu: "; int c; cin >> c; c--;
    if (c < 0 || c >= soXe) {
        cout << "Khong hop le!\n";
        return;
    }

    LichTestDrive lich;
    lich.maLich = "TD" + IntToStr(soLich + 1);
    lich.maXe = dsXe[c].maXe;

    cout << "\nHo ten: "; cin.ignore(); getline(cin, lich.hoTenKH);
    cout << "SDT: "; getline(cin, lich.sdt);
    cout << "Ngay (dd/mm/yyyy): "; cin >> lich.ngay;
    cout << "Gio (HH:MM): "; cin >> lich.gio;

    cout << "\n[OK] Da dat lich test drive!\n";
    cout << "Ma lich: " << lich.maLich << "\n";
    cout << "Xe: " << dsXe[c].hang << " " << dsXe[c].model << "\n";
    cout << "Thoi gian: " << lich.ngay << " luc " << lich.gio << "\n";

    LichTestDrive* tmp = new LichTestDrive[soLich + 1];
    for (int i = 0; i < soLich; i++) tmp[i] = dsLich[i];
    tmp[soLich] = lich;
    delete[] dsLich;
    dsLich = tmp;
    soLich++;
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== SHOWROOM O TO =====\n";
        cout << "1. Danh sach xe\n";
        cout << "2. Dat xe\n";
        cout << "3. Dat lich test drive\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachXe();
        else if (c == 2) DatXe();
        else if (c == 3) DatLichTestDrive();
        else if (c == 0) break;
    }

    delete[] dsDon;
    delete[] dsLich;
    return 0;
}

float pow(float base, int exp) {
    float result = 1;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}
