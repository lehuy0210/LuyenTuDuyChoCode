/*
BÀI 38: QUẢN LÝ SÂN BOWLING
- Đặt làn (theo giờ)
- Thuê giày bowling
- Gọi đồ ăn/nước
- Tính điểm (game scoring)
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
struct Lan {
    int soLan;
    bool dangDung;
    string hoTenKH;
    int gioVao, phutVao;
};

struct DonThue {
    string maDon;
    int soLan;
    string hoTenKH, sdt;
    int soNguoi;
    float tienLan, tienGiay, tienDoAn, tongTien;
};

// === DỮ LIỆU ===
Lan dsLan[12];
int soLan = 12;

const float GIA_LAN_GIO = 150000;  // 150k/giờ
const float GIA_GIAY = 30000;      // 30k/đôi

DonThue* dsDon = NULL;
int soDon = 0;

void KhoiTaoLan() {
    for (int i = 0; i < soLan; i++) {
        dsLan[i].soLan = i + 1;
        dsLan[i].dangDung = false;
        dsLan[i].hoTenKH = "";
        dsLan[i].gioVao = 0;
        dsLan[i].phutVao = 0;
    }
}

// === CHỨC NĂNG ===
void DanhSachLan() {
    cout << "\n=== DANH SACH LAN ===\n";
    for (int i = 0; i < soLan; i++) {
        cout << "Lan " << dsLan[i].soLan << ": ";
        if (dsLan[i].dangDung) {
            cout << "DANG DUNG (KH: " << dsLan[i].hoTenKH << ")\n";
        } else {
            cout << "TRONG\n";
        }
    }
}

void DatLan() {
    cout << "\n=== DAT LAN ===\n";
    DanhSachLan();

    cout << "\nChon lan (1-12): "; int lan; cin >> lan;
    if (lan < 1 || lan > soLan || dsLan[lan-1].dangDung) {
        cout << "Lan khong hop le hoac dang duoc su dung!\n";
        return;
    }

    DonThue don;
    don.maDon = "DT" + IntToStr(soDon + 1);
    don.soLan = lan;

    cout << "Ho ten: "; cin.ignore(); getline(cin, don.hoTenKH);
    cout << "SDT: "; getline(cin, don.sdt);
    cout << "So nguoi choi: "; cin >> don.soNguoi;

    cout << "So gio choi: "; int soGio; cin >> soGio;
    don.tienLan = soGio * GIA_LAN_GIO;

    // Thuê giày
    cout << "Thue giay? (so doi, 0 = khong): "; int soGiay; cin >> soGiay;
    don.tienGiay = soGiay * GIA_GIAY;

    // Đồ ăn/nước
    cout << "\nDo an/nuoc:\n";
    cout << "1. Nuoc ngot (25k): "; int nuoc; cin >> nuoc;
    cout << "2. Snack (30k): "; int snack; cin >> snack;
    cout << "3. Pizza (150k): "; int pizza; cin >> pizza;
    don.tienDoAn = nuoc * 25000 + snack * 30000 + pizza * 150000;

    don.tongTien = don.tienLan + don.tienGiay + don.tienDoAn;

    dsLan[lan-1].dangDung = true;
    dsLan[lan-1].hoTenKH = don.hoTenKH;
    cout << "Gio vao (hh mm): "; cin >> dsLan[lan-1].gioVao >> dsLan[lan-1].phutVao;

    cout << "\n--- HOA DON ---\n";
    cout << "Lan " << lan << " | " << don.soNguoi << " nguoi\n";
    cout << "Tien lan: " << FloatToStr(don.tienLan) << " VND\n";
    cout << "Tien giay: " << FloatToStr(don.tienGiay) << " VND\n";
    cout << "Tien do an: " << FloatToStr(don.tienDoAn) << " VND\n";
    cout << "TONG: " << FloatToStr(don.tongTien) << " VND\n";

    DonThue* tmp = new DonThue[soDon + 1];
    for (int i = 0; i < soDon; i++) tmp[i] = dsDon[i];
    tmp[soDon] = don;
    delete[] dsDon;
    dsDon = tmp;
    soDon++;

    cout << "\n[OK] Ma don: " << don.maDon << "\n";
}

void TraLan() {
    cout << "\n=== TRA LAN ===\n";
    cout << "So lan: "; int lan; cin >> lan;

    if (lan < 1 || lan > soLan || !dsLan[lan-1].dangDung) {
        cout << "Lan khong hop le!\n";
        return;
    }

    dsLan[lan-1].dangDung = false;
    dsLan[lan-1].hoTenKH = "";
    dsLan[lan-1].gioVao = 0;
    dsLan[lan-1].phutVao = 0;

    cout << "[OK] Da tra lan " << lan << "\n";
}

// === MAIN ===
int main() {
    KhoiTaoLan();

    while (true) {
        cout << "\n===== BOWLING ALLEY =====\n";
        cout << "1. Danh sach lan\n";
        cout << "2. Dat lan\n";
        cout << "3. Tra lan\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachLan();
        else if (c == 2) DatLan();
        else if (c == 3) TraLan();
        else if (c == 0) break;
    }

    delete[] dsDon;
    return 0;
}
