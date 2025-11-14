/*
BÀI 42: CỬA HÀNG ĐỒ CHƠI
- Phân loại theo độ tuổi (0-3, 3-6, 6-12, 12+)
- Đồ chơi giáo dục, vận động, sáng tạo
- Gói quà (miễn phí hoặc có phí)
- Khuyến mãi sinh nhật
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
struct DoChoi {
    string ma, ten, loai;  // "GiaoDuc", "VanDong", "SangTao"
    string doTuoi;  // "0-3", "3-6", "6-12", "12+"
    float gia;
    int tonKho;
};

struct HoaDon {
    string maHD, hoTenKH, sdt;
    string maDC[20];
    int soLuong[20];
    int soMon;
    float tienHang, phiGoiQua, tongTien;
    bool laSinhNhat;
};

// === DỮ LIỆU ===
DoChoi dsDC[30] = {
    {"DC01", "Xep hinh Lego Classic", "SangTao", "6-12", 850000, 15},
    {"DC02", "Bo do choi bac si", "GiaoDuc", "3-6", 250000, 30},
    {"DC03", "Bup be Barbie", "SangTao", "3-6", 350000, 25},
    {"DC04", "Xe dieu khien tu xa", "VanDong", "6-12", 650000, 20},
    {"DC05", "Bo lap rap robot", "GiaoDuc", "12+", 1200000, 10},
    {"DC06", "Banh xich du tre em", "VanDong", "0-3", 180000, 40},
    {"DC07", "Bo ve tranh thuy mau", "SangTao", "3-6", 120000, 50}
};
int soDC = 7;

HoaDon* dsHD = NULL;
int soHD = 0;

// === CHỨC NĂNG ===
void DanhSachDoChoi() {
    cout << "\n=== DANH SACH DO CHOI ===\n";
    for (int i = 0; i < soDC; i++) {
        cout << (i+1) << ". " << dsDC[i].ten << "\n";
        cout << "   Loai: " << dsDC[i].loai << " | Do tuoi: " << dsDC[i].doTuoi
             << " | Gia: " << FloatToStr(dsDC[i].gia) << " VND | Ton: "
             << dsDC[i].tonKho << "\n";
    }
}

void TimTheoDoTuoi() {
    cout << "\n=== TIM DO CHOI THEO DO TUOI ===\n";
    cout << "1. 0-3 tuoi\n2. 3-6 tuoi\n3. 6-12 tuoi\n4. 12+ tuoi\n";
    cout << "Chon: "; int c; cin >> c;

    string doTuoi;
    if (c == 1) doTuoi = "0-3";
    else if (c == 2) doTuoi = "3-6";
    else if (c == 3) doTuoi = "6-12";
    else doTuoi = "12+";

    cout << "\nDo choi phu hop cho " << doTuoi << " tuoi:\n";
    for (int i = 0; i < soDC; i++) {
        if (dsDC[i].doTuoi == doTuoi) {
            cout << "- " << dsDC[i].ten << " (" << dsDC[i].loai << ") - "
                 << FloatToStr(dsDC[i].gia) << " VND\n";
        }
    }
}

void MuaHang() {
    cout << "\n=== MUA HANG ===\n";

    HoaDon hd;
    hd.maHD = "HD" + IntToStr(soHD + 1);
    cout << "Ho ten: "; cin.ignore(); getline(cin, hd.hoTenKH);
    cout << "SDT: "; getline(cin, hd.sdt);

    hd.soMon = 0;
    hd.tienHang = 0;

    while (true) {
        DanhSachDoChoi();
        cout << "\nChon do choi (0 = ket thuc): "; int c; cin >> c;
        if (c == 0) break;
        c--;

        if (c < 0 || c >= soDC) {
            cout << "Khong hop le!\n";
            continue;
        }

        cout << "So luong: "; int sl; cin >> sl;
        if (sl > dsDC[c].tonKho) {
            cout << "Khong du hang!\n";
            continue;
        }

        hd.maDC[hd.soMon] = dsDC[c].ma;
        hd.soLuong[hd.soMon] = sl;
        hd.soMon++;

        dsDC[c].tonKho -= sl;
        hd.tienHang += dsDC[c].gia * sl;

        cout << "[OK] Da them vao gio hang!\n";
    }

    if (hd.soMon == 0) {
        cout << "Khong co san pham nao!\n";
        return;
    }

    // Gói quà
    cout << "\nGoi qua:\n";
    cout << "1. Khong goi (0 VND)\n";
    cout << "2. Goi qua don gian (20,000 VND)\n";
    cout << "3. Goi qua cao cap (50,000 VND)\n";
    cout << "Chon: "; int goi; cin >> goi;

    if (goi == 2) hd.phiGoiQua = 20000;
    else if (goi == 3) hd.phiGoiQua = 50000;
    else hd.phiGoiQua = 0;

    // Khuyến mãi sinh nhật
    cout << "\nMua qua sinh nhat? (1=Co, 0=Khong): "; int sn; cin >> sn;
    hd.laSinhNhat = (sn == 1);

    hd.tongTien = hd.tienHang + hd.phiGoiQua;

    if (hd.laSinhNhat) {
        hd.tongTien *= 0.90;  // Giảm 10%
        cout << "\n>>> GIAM 10% CHO QUA SINH NHAT!\n";
    }

    cout << "\n--- HOA DON ---\n";
    cout << "Ma HD: " << hd.maHD << " | KH: " << hd.hoTenKH << "\n";
    cout << "Tien hang: " << FloatToStr(hd.tienHang) << " VND\n";
    cout << "Phi goi qua: " << FloatToStr(hd.phiGoiQua) << " VND\n";
    cout << "TONG: " << FloatToStr(hd.tongTien) << " VND\n";

    HoaDon* tmp = new HoaDon[soHD + 1];
    for (int i = 0; i < soHD; i++) tmp[i] = dsHD[i];
    tmp[soHD] = hd;
    delete[] dsHD;
    dsHD = tmp;
    soHD++;
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== CUA HANG DO CHOI =====\n";
        cout << "1. Danh sach do choi\n";
        cout << "2. Tim theo do tuoi\n";
        cout << "3. Mua hang\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachDoChoi();
        else if (c == 2) TimTheoDoTuoi();
        else if (c == 3) MuaHang();
        else if (c == 0) break;
    }

    delete[] dsHD;
    return 0;
}
