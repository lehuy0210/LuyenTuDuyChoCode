/*
BÀI 40: QUÁN TRÀ SỮA
- Menu đa dạng (trà, trái cây, sữa chua...)
- Tùy chọn topping (trân châu, thạch, pudding...)
- Size (M, L, XL)
- Giảm giá mua nhiều (mua 2 tặng 1)
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
struct DoUong {
    string ma, ten, loai;  // "TraSua", "TraiCay", "SuaChua"
    float giaM, giaL, giaXL;
};

struct Topping {
    string ma, ten;
    float gia;
};

struct ChiTietDon {
    string maDU, tenDU;
    string size;
    string maTopping[5];
    int soTopping;
    float giaMonChinh, giaTopping, tongGia;
};

struct HoaDon {
    string maHD, hoTenKH;
    ChiTietDon dsMon[20];
    int soMon;
    float tongTien;
};

// === DỮ LIỆU ===
DoUong dsMenu[20] = {
    {"D01", "Tra sua tran chau duong den", "TraSua", 35000, 40000, 45000},
    {"D02", "Tra sua socola", "TraSua", 38000, 43000, 48000},
    {"D03", "Tra dao", "TraiCay", 30000, 35000, 40000},
    {"D04", "Tra vai", "TraiCay", 32000, 37000, 42000},
    {"D05", "Sua chua nep cam", "SuaChua", 35000, 40000, 45000},
    {"D06", "Matcha da xay", "Matcha", 40000, 45000, 50000}
};
int soMenu = 6;

Topping dsTopping[10] = {
    {"T01", "Tran chau trang", 8000},
    {"T02", "Tran chau den", 8000},
    {"T03", "Thach rau cau", 8000},
    {"T04", "Pudding", 10000},
    {"T05", "Kem cheese", 12000}
};
int soTopping = 5;

HoaDon* dsHD = NULL;
int soHD = 0;

// === CHỨC NĂNG ===
void HienMenu() {
    cout << "\n=== MENU ===\n";
    for (int i = 0; i < soMenu; i++) {
        cout << (i+1) << ". " << dsMenu[i].ten << " (" << dsMenu[i].loai << ")\n";
        cout << "   M: " << FloatToStr(dsMenu[i].giaM) << " | "
             << "L: " << FloatToStr(dsMenu[i].giaL) << " | "
             << "XL: " << FloatToStr(dsMenu[i].giaXL) << " VND\n";
    }
}

void HienTopping() {
    cout << "\nTopping:\n";
    for (int i = 0; i < soTopping; i++) {
        cout << (i+1) << ". " << dsTopping[i].ten << " - "
             << FloatToStr(dsTopping[i].gia) << " VND\n";
    }
}

void DatMon() {
    cout << "\n=== DAT MON ===\n";

    HoaDon hd;
    hd.maHD = "HD" + IntToStr(soHD + 1);
    cout << "Ho ten (co the bo trong): "; cin.ignore(); getline(cin, hd.hoTenKH);
    if (hd.hoTenKH == "") hd.hoTenKH = "Khach le";

    hd.soMon = 0;
    hd.tongTien = 0;

    while (true) {
        HienMenu();
        cout << "\nChon do uong (0 = ket thuc): "; int c; cin >> c;
        if (c == 0) break;
        c--;

        if (c < 0 || c >= soMenu) {
            cout << "Khong hop le!\n";
            continue;
        }

        ChiTietDon ct;
        ct.maDU = dsMenu[c].ma;
        ct.tenDU = dsMenu[c].ten;

        cout << "Size (M/L/XL): "; cin >> ct.size;
        if (ct.size == "M" || ct.size == "m") ct.giaMonChinh = dsMenu[c].giaM;
        else if (ct.size == "L" || ct.size == "l") ct.giaMonChinh = dsMenu[c].giaL;
        else ct.giaMonChinh = dsMenu[c].giaXL;

        ct.size = (ct.size == "m") ? "M" : (ct.size == "l" ? "L" : "XL");

        // Topping
        HienTopping();
        cout << "So loai topping (toi da 5): "; cin >> ct.soTopping;
        ct.giaTopping = 0;
        for (int i = 0; i < ct.soTopping && i < 5; i++) {
            cout << "Chon topping " << (i+1) << ": "; int t; cin >> t; t--;
            if (t >= 0 && t < soTopping) {
                ct.maTopping[i] = dsTopping[t].ma;
                ct.giaTopping += dsTopping[t].gia;
            }
        }

        ct.tongGia = ct.giaMonChinh + ct.giaTopping;

        hd.dsMon[hd.soMon] = ct;
        hd.soMon++;
        hd.tongTien += ct.tongGia;

        cout << "[OK] Da them mon!\n";
    }

    if (hd.soMon == 0) {
        cout << "Khong co mon nao!\n";
        return;
    }

    // Khuyến mãi mua 2 tặng 1 (áp dụng cho món rẻ nhất)
    if (hd.soMon >= 3) {
        float minGia = hd.dsMon[0].tongGia;
        for (int i = 1; i < hd.soMon; i++) {
            if (hd.dsMon[i].tongGia < minGia) {
                minGia = hd.dsMon[i].tongGia;
            }
        }
        hd.tongTien -= minGia;
        cout << "\n>>> MUA 2 TANG 1! Giam " << FloatToStr(minGia) << " VND\n";
    }

    cout << "\n--- HOA DON ---\n";
    cout << "Ma HD: " << hd.maHD << " | KH: " << hd.hoTenKH << "\n\n";
    for (int i = 0; i < hd.soMon; i++) {
        cout << (i+1) << ". " << hd.dsMon[i].tenDU << " (" << hd.dsMon[i].size << ")\n";
        if (hd.dsMon[i].soTopping > 0) {
            cout << "   Topping: +" << FloatToStr(hd.dsMon[i].giaTopping) << " VND\n";
        }
        cout << "   Tong: " << FloatToStr(hd.dsMon[i].tongGia) << " VND\n";
    }
    cout << "\nTONG CONG: " << FloatToStr(hd.tongTien) << " VND\n";

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
        cout << "\n===== QUAN TRA SUA =====\n";
        cout << "1. Dat mon\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DatMon();
        else if (c == 0) break;
    }

    delete[] dsHD;
    return 0;
}
