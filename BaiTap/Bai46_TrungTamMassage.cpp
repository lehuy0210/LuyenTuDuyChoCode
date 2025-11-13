/*
BÀI 46: TRUNG TÂM MASSAGE
- Gói dịch vụ (massage, foot, body...)
- Đặt lịch theo giờ
- Chọn kỹ thuật viên
- Tip (tùy chọn)
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
struct GoiDichVu {
    string maGoi, tenGoi;
    int thoiLuong;  // Phút
    float gia;
};

struct KyThuatVien {
    string maKTV, hoTen;
    int namKinhNghiem;
    bool dangRanh;
};

struct LichHen {
    string maLich, hoTenKH, sdt;
    string maGoi, maKTV;
    string ngay, gio;
    float tongTien, tip;
};

// === DỮ LIỆU ===
GoiDichVu dsGoi[10] = {
    {"G01", "Massage toan than", 90, 350000},
    {"G02", "Massage foot", 45, 180000},
    {"G03", "Body massage + foot", 120, 480000},
    {"G04", "Massage dau", 30, 120000},
    {"G05", "Hot stone massage", 90, 550000}
};
int soGoi = 5;

KyThuatVien dsKTV[10] = {
    {"KTV01", "Nguyen Van A", 5, true},
    {"KTV02", "Tran Thi B", 3, true},
    {"KTV03", "Le Van C", 7, true},
    {"KTV04", "Pham Thi D", 4, false}
};
int soKTV = 4;

LichHen* dsLich = NULL;
int soLich = 0;

// === CHỨC NĂNG ===
void DanhSachGoi() {
    cout << "\n=== DANH SACH GOI DICH VU ===\n";
    for (int i = 0; i < soGoi; i++) {
        cout << (i+1) << ". " << dsGoi[i].tenGoi << "\n";
        cout << "   Thoi luong: " << dsGoi[i].thoiLuong << " phut | Gia: "
             << FloatToStr(dsGoi[i].gia) << " VND\n";
    }
}

void DatLich() {
    cout << "\n=== DAT LICH ===\n";
    DanhSachGoi();

    cout << "\nChon goi: "; int c; cin >> c; c--;
    if (c < 0 || c >= soGoi) {
        cout << "Khong hop le!\n";
        return;
    }

    LichHen lich;
    lich.maLich = "L" + IntToStr(soLich + 1);
    lich.maGoi = dsGoi[c].maGoi;

    cout << "\nHo ten: "; cin.ignore(); getline(cin, lich.hoTenKH);
    cout << "SDT: "; getline(cin, lich.sdt);
    cout << "Ngay (dd/mm/yyyy): "; cin >> lich.ngay;
    cout << "Gio (HH:MM): "; cin >> lich.gio;

    // Chọn kỹ thuật viên
    cout << "\nKy thuat vien ranh:\n";
    bool coKTVRanh = false;
    for (int i = 0; i < soKTV; i++) {
        if (dsKTV[i].dangRanh) {
            cout << (i+1) << ". " << dsKTV[i].hoTen << " ("
                 << dsKTV[i].namKinhNghiem << " nam KN)\n";
            coKTVRanh = true;
        }
    }

    if (!coKTVRanh) {
        cout << "Hien tai khong co KTV ranh!\n";
        return;
    }

    cout << "Chon KTV: "; int ktv; cin >> ktv; ktv--;
    if (ktv < 0 || ktv >= soKTV || !dsKTV[ktv].dangRanh) {
        cout << "Khong hop le!\n";
        return;
    }

    lich.maKTV = dsKTV[ktv].maKTV;
    dsKTV[ktv].dangRanh = false;

    lich.tongTien = dsGoi[c].gia;
    lich.tip = 0;

    cout << "\n[OK] Dat lich thanh cong!\n";
    cout << "Ma lich: " << lich.maLich << "\n";
    cout << "Thoi gian: " << lich.ngay << " " << lich.gio << "\n";
    cout << "KTV: " << dsKTV[ktv].hoTen << "\n";

    LichHen* tmp = new LichHen[soLich + 1];
    for (int i = 0; i < soLich; i++) tmp[i] = dsLich[i];
    tmp[soLich] = lich;
    delete[] dsLich;
    dsLich = tmp;
    soLich++;
}

void ThanhToan() {
    cout << "\n=== THANH TOAN ===\n";
    cout << "Ma lich: "; string ma; cin >> ma;

    for (int i = 0; i < soLich; i++) {
        if (dsLich[i].maLich == ma) {
            cout << "\n--- HOA DON ---\n";
            cout << "Khach: " << dsLich[i].hoTenKH << "\n";

            // Tìm tên gói
            for (int j = 0; j < soGoi; j++) {
                if (dsGoi[j].maGoi == dsLich[i].maGoi) {
                    cout << "Goi: " << dsGoi[j].tenGoi << " - "
                         << FloatToStr(dsGoi[j].gia) << " VND\n";
                    break;
                }
            }

            cout << "\nTip cho KTV (tu nguyen): "; cin >> dsLich[i].tip;
            dsLich[i].tongTien += dsLich[i].tip;

            cout << "\nTONG: " << FloatToStr(dsLich[i].tongTien) << " VND\n";
            cout << "[OK] Cam on quy khach!\n";
            return;
        }
    }

    cout << "Khong tim thay lich!\n";
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== TRUNG TAM MASSAGE =====\n";
        cout << "1. Danh sach goi dich vu\n";
        cout << "2. Dat lich\n";
        cout << "3. Thanh toan\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachGoi();
        else if (c == 2) DatLich();
        else if (c == 3) ThanhToan();
        else if (c == 0) break;
    }

    delete[] dsLich;
    return 0;
}
