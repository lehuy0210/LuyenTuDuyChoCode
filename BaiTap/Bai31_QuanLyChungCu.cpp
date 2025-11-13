/*
BÀI 31: QUẢN LÝ CHUNG CƯ
- Quản lý căn hộ (tầng, số phòng, diện tích)
- Cư dân (thông tin, số người ở)
- Phí quản lý (theo m2 + xe + dịch vụ)
- Thanh toán và nhắc nợ
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
struct CanHo {
    string maCanHo;  // VD: "A1505" = Toa A, tang 15, can 05
    float dienTich;
    string chuHo;
    string sdt;
    int soNguoi;
    int soXeMay, soOto;
    bool daThanhToan;
};

struct HoaDonPhi {
    string maHD, maCanHo, thang;
    float phiQuanLy, phiXe, phiDichVu, tongPhi;
};

// === DỮ LIỆU ===
CanHo dsCanHo[50] = {
    {"A1201", 65, "Nguyen Van A", "0901234567", 4, 1, 1, false},
    {"A1202", 80, "Tran Thi B", "0907654321", 3, 2, 0, false},
    {"B0501", 55, "Le Van C", "0912345678", 2, 1, 0, true},
    {"B0502", 95, "Pham Thi D", "0909876543", 5, 2, 1, false}
};
int soCanHo = 4;

HoaDonPhi* dsHD = NULL;
int soHD = 0;

// Bảng giá
const float GIA_QUAN_LY_M2 = 15000;  // 15k/m2/tháng
const float GIA_XE_MAY = 70000;      // 70k/xe máy/tháng
const float GIA_OTO = 1200000;       // 1.2 triệu/ô tô/tháng

// === CHỨC NĂNG ===
void DanhSachCanHo() {
    cout << "\n=== DANH SACH CAN HO ===\n";
    for (int i = 0; i < soCanHo; i++) {
        cout << (i+1) << ". " << dsCanHo[i].maCanHo << " | "
             << FloatToStr(dsCanHo[i].dienTich) << " m2 | Chu ho: "
             << dsCanHo[i].chuHo << " | " << dsCanHo[i].soNguoi << " nguoi | "
             << "XM:" << dsCanHo[i].soXeMay << " OT:" << dsCanHo[i].soOto << " | "
             << (dsCanHo[i].daThanhToan ? "DA TT" : "CHUA TT") << "\n";
    }
}

void TinhPhiThang() {
    cout << "\n=== TINH PHI THANG ===\n";
    cout << "Ma can ho: "; string ma; cin >> ma;

    for (int i = 0; i < soCanHo; i++) {
        if (dsCanHo[i].maCanHo == ma) {
            cout << "Thang (mm/yyyy): "; string thang; cin >> thang;

            HoaDonPhi hd;
            hd.maHD = "PHI" + IntToStr(soHD + 1);
            hd.maCanHo = ma;
            hd.thang = thang;

            // Phí quản lý
            hd.phiQuanLy = dsCanHo[i].dienTich * GIA_QUAN_LY_M2;

            // Phí xe
            hd.phiXe = dsCanHo[i].soXeMay * GIA_XE_MAY + dsCanHo[i].soOto * GIA_OTO;

            // Phí dịch vụ (điện, nước - ví dụ)
            cout << "Phi dich vu (dien, nuoc...): "; cin >> hd.phiDichVu;

            hd.tongPhi = hd.phiQuanLy + hd.phiXe + hd.phiDichVu;

            cout << "\n--- HOA DON PHI ---\n";
            cout << "Can ho: " << ma << " (" << dsCanHo[i].chuHo << ")\n";
            cout << "Thang: " << thang << "\n\n";
            cout << "1. Phi quan ly: " << FloatToStr(dsCanHo[i].dienTich) << " m2 x "
                 << FloatToStr(GIA_QUAN_LY_M2) << " = "
                 << FloatToStr(hd.phiQuanLy) << " VND\n";
            cout << "2. Phi xe:\n";
            cout << "   - Xe may: " << dsCanHo[i].soXeMay << " x "
                 << FloatToStr(GIA_XE_MAY) << " = "
                 << FloatToStr(dsCanHo[i].soXeMay * GIA_XE_MAY) << " VND\n";
            cout << "   - Oto: " << dsCanHo[i].soOto << " x "
                 << FloatToStr(GIA_OTO) << " = "
                 << FloatToStr(dsCanHo[i].soOto * GIA_OTO) << " VND\n";
            cout << "3. Phi dich vu: " << FloatToStr(hd.phiDichVu) << " VND\n";
            cout << "\nTONG: " << FloatToStr(hd.tongPhi) << " VND\n";

            HoaDonPhi* tmp = new HoaDonPhi[soHD + 1];
            for (int j = 0; j < soHD; j++) tmp[j] = dsHD[j];
            tmp[soHD] = hd;
            delete[] dsHD;
            dsHD = tmp;
            soHD++;

            cout << "\nMa hoa don: " << hd.maHD << "\n";
            return;
        }
    }

    cout << "Khong tim thay can ho!\n";
}

void ThanhToan() {
    cout << "\n=== THANH TOAN ===\n";
    cout << "Ma hoa don: "; string maHD; cin >> maHD;

    for (int i = 0; i < soHD; i++) {
        if (dsHD[i].maHD == maHD) {
            for (int j = 0; j < soCanHo; j++) {
                if (dsCanHo[j].maCanHo == dsHD[i].maCanHo) {
                    dsCanHo[j].daThanhToan = true;
                    cout << "\n[OK] Da thanh toan hoa don " << maHD << "\n";
                    cout << "So tien: " << FloatToStr(dsHD[i].tongPhi) << " VND\n";
                    return;
                }
            }
        }
    }

    cout << "Khong tim thay hoa don!\n";
}

void DanhSachNo() {
    cout << "\n=== DANH SACH CAN HO CON NO ===\n";
    bool coNo = false;
    for (int i = 0; i < soCanHo; i++) {
        if (!dsCanHo[i].daThanhToan) {
            cout << dsCanHo[i].maCanHo << " | " << dsCanHo[i].chuHo
                 << " | SDT: " << dsCanHo[i].sdt << "\n";
            coNo = true;
        }
    }
    if (!coNo) {
        cout << "Tat ca can ho da thanh toan!\n";
    }
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== QUAN LY CHUNG CU =====\n";
        cout << "1. Danh sach can ho\n";
        cout << "2. Tinh phi thang\n";
        cout << "3. Thanh toan\n";
        cout << "4. Danh sach con no\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachCanHo();
        else if (c == 2) TinhPhiThang();
        else if (c == 3) ThanhToan();
        else if (c == 4) DanhSachNo();
        else if (c == 0) break;
    }

    delete[] dsHD;
    return 0;
}
