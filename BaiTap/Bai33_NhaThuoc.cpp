/*
BÀI 33: NHÀ THUỐC
- Quản lý thuốc (tên, đơn vị, giá, hạn dùng)
- Bán thuốc (theo đơn/không đơn)
- Cảnh báo thuốc hết hạn/sắp hết
- Thống kê doanh thu theo loại thuốc
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
struct Thuoc {
    string ma, ten, loai;  // loai: "KeoDon", "KhongKeoDon"
    string donVi;  // Vien, Hop, Chai, Tuyp
    float gia;
    int tonKho;
    string hanDung;  // mm/yyyy
    int daBan;
};

struct HoaDon {
    string maHD, hoTenKH, sdt;
    string maThuoc[20];
    int soLuong[20];
    int soMon;
    float tongTien;
    string ngay;
};

// === DỮ LIỆU ===
Thuoc dsThuoc[50] = {
    {"T01", "Paracetamol 500mg", "KhongKeoDon", "Vien", 500, 500, "12/2025", 0},
    {"T02", "Amoxicillin 500mg", "KeoDon", "Vien", 2000, 300, "06/2025", 0},
    {"T03", "Vitamin C 1000mg", "KhongKeoDon", "Vien", 150, 1000, "03/2026", 0},
    {"T04", "Siro ho Prospan", "KhongKeoDon", "Chai", 85000, 50, "01/2025", 0},
    {"T05", "Dau Gio Con O", "KhongKeoDon", "Chai", 12000, 100, "12/2026", 0},
    {"T06", "Thuoc nhom mat", "KhongKeoDon", "Tuyp", 35000, 80, "09/2025", 0}
};
int soThuoc = 6;

HoaDon* dsHD = NULL;
int soHD = 0;

// === CHỨC NĂNG ===
void DanhSachThuoc() {
    cout << "\n=== DANH SACH THUOC ===\n";
    for (int i = 0; i < soThuoc; i++) {
        cout << (i+1) << ". " << dsThuoc[i].ten << " (" << dsThuoc[i].loai << ")\n";
        cout << "   " << FloatToStr(dsThuoc[i].gia) << " VND/" << dsThuoc[i].donVi
             << " | Ton: " << dsThuoc[i].tonKho << " | HSD: " << dsThuoc[i].hanDung << "\n";
    }
}

void BanThuoc() {
    cout << "\n=== BAN THUOC ===\n";

    HoaDon hd;
    hd.maHD = "HD" + IntToStr(soHD + 1);
    cout << "Ho ten khach (co the bo trong): "; cin.ignore(); getline(cin, hd.hoTenKH);
    if (hd.hoTenKH == "") hd.hoTenKH = "Khach le";
    cout << "SDT (co the bo trong): "; getline(cin, hd.sdt);
    cout << "Ngay (dd/mm/yyyy): "; cin >> hd.ngay;

    hd.soMon = 0;
    hd.tongTien = 0;

    while (true) {
        DanhSachThuoc();
        cout << "\nChon thuoc (0 de ket thuc): "; int c; cin >> c;
        if (c == 0) break;
        c--;

        if (c < 0 || c >= soThuoc) {
            cout << "Khong hop le!\n";
            continue;
        }

        // Kiểm tra thuốc kê đơn
        if (dsThuoc[c].loai == "KeoDon") {
            cout << ">>> CANH BAO: Thuoc keo don, can don bac si!\n";
            cout << "Co don? (1=Co, 0=Khong): "; int coDon; cin >> coDon;
            if (coDon == 0) {
                cout << "Khong ban duoc!\n";
                continue;
            }
        }

        cout << "So luong: "; int sl; cin >> sl;

        if (sl > dsThuoc[c].tonKho) {
            cout << "Khong du hang!\n";
            continue;
        }

        hd.maThuoc[hd.soMon] = dsThuoc[c].ma;
        hd.soLuong[hd.soMon] = sl;
        hd.soMon++;

        float tien = dsThuoc[c].gia * sl;
        hd.tongTien += tien;
        dsThuoc[c].tonKho -= sl;
        dsThuoc[c].daBan += sl;

        cout << "[OK] Da them " << dsThuoc[c].ten << "\n";
    }

    if (hd.soMon == 0) {
        cout << "Khong co thuoc nao!\n";
        return;
    }

    cout << "\n[OK] Tong tien: " << FloatToStr(hd.tongTien) << " VND\n";

    HoaDon* tmp = new HoaDon[soHD + 1];
    for (int i = 0; i < soHD; i++) tmp[i] = dsHD[i];
    tmp[soHD] = hd;
    delete[] dsHD;
    dsHD = tmp;
    soHD++;
}

void CanhBaoThuoc() {
    cout << "\n=== CANH BAO ===\n";

    // Thuốc sắp hết
    cout << "\n1. Thuoc sap het (ton < 50):\n";
    bool coSapHet = false;
    for (int i = 0; i < soThuoc; i++) {
        if (dsThuoc[i].tonKho < 50) {
            cout << "   - " << dsThuoc[i].ten << " (con " << dsThuoc[i].tonKho << ")\n";
            coSapHet = true;
        }
    }
    if (!coSapHet) cout << "   Khong co\n";

    // Thuốc hết hạn/sắp hết hạn (giả sử tháng hiện tại là 11/2024)
    cout << "\n2. Thuoc het han/sap het han:\n";
    cout << "   (Thang hien tai: 11/2024)\n";
    bool coHetHan = false;
    for (int i = 0; i < soThuoc; i++) {
        // Đơn giản hóa: chỉ cảnh báo nếu < 01/2025
        if (dsThuoc[i].hanDung <= "01/2025") {
            cout << "   - " << dsThuoc[i].ten << " (HSD: " << dsThuoc[i].hanDung << ")\n";
            coHetHan = true;
        }
    }
    if (!coHetHan) cout << "   Khong co\n";
}

void ThongKe() {
    cout << "\n=== THONG KE DOANH THU ===\n";

    float tongDoanhThu = 0;

    for (int i = 0; i < soThuoc; i++) {
        if (dsThuoc[i].daBan > 0) {
            float doanhThu = dsThuoc[i].daBan * dsThuoc[i].gia;
            cout << dsThuoc[i].ten << ": " << dsThuoc[i].daBan << " "
                 << dsThuoc[i].donVi << " - " << FloatToStr(doanhThu) << " VND\n";
            tongDoanhThu += doanhThu;
        }
    }

    cout << "\nTONG DOANH THU: " << FloatToStr(tongDoanhThu) << " VND\n";
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== NHA THUOC =====\n";
        cout << "1. Danh sach thuoc\n";
        cout << "2. Ban thuoc\n";
        cout << "3. Canh bao thuoc\n";
        cout << "4. Thong ke doanh thu\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachThuoc();
        else if (c == 2) BanThuoc();
        else if (c == 3) CanhBaoThuoc();
        else if (c == 4) ThongKe();
        else if (c == 0) break;
    }

    delete[] dsHD;
    return 0;
}
