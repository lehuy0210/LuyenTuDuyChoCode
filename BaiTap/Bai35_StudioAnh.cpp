/*
BÀI 35: STUDIO ẢNH
- Đặt lịch chụp (profile, cưới, gia đình...)
- Chọn gói dịch vụ (số ảnh, phục trang, trang điểm)
- Thanh toán (đặt cọc 30%)
- In ảnh sau khi chụp
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
struct GoiChup {
    string maGoi, tenGoi;
    int soAnh;
    bool coPhucTrang, coTrangDiem;
    float gia;
};

struct LichChup {
    string maLich, hoTenKH, sdt;
    string maGoi, ngayChup, gioChup;
    float tongTien, daDongCoc, conLai;
    string trangThai;  // "DaDatCoc", "DaChup", "HoanThanh"
};

// === DỮ LIỆU ===
GoiChup dsGoi[10] = {
    {"G01", "Profile co ban", 20, false, false, 500000},
    {"G02", "Profile cao cap", 50, true, true, 1500000},
    {"G03", "Gia dinh nho", 30, false, false, 2000000},
    {"G04", "Cuoi phong anh", 100, true, true, 8000000},
    {"G05", "Cuoi ngoai canh", 150, true, true, 15000000}
};
int soGoi = 5;

LichChup* dsLich = NULL;
int soLich = 0;

// === CHỨC NĂNG ===
void DanhSachGoi() {
    cout << "\n=== DANH SACH GOI CHUP ===\n";
    for (int i = 0; i < soGoi; i++) {
        cout << (i+1) << ". " << dsGoi[i].tenGoi << "\n";
        cout << "   So anh: " << dsGoi[i].soAnh << " | Phuc trang: "
             << (dsGoi[i].coPhucTrang ? "Co" : "Khong") << " | Trang diem: "
             << (dsGoi[i].coTrangDiem ? "Co" : "Khong") << "\n";
        cout << "   Gia: " << FloatToStr(dsGoi[i].gia) << " VND\n\n";
    }
}

void DatLich() {
    cout << "\n=== DAT LICH CHUP ===\n";
    DanhSachGoi();

    cout << "Chon goi: "; int c; cin >> c; c--;
    if (c < 0 || c >= soGoi) {
        cout << "Khong hop le!\n";
        return;
    }

    LichChup lich;
    lich.maLich = "L" + IntToStr(soLich + 1);
    lich.maGoi = dsGoi[c].maGoi;
    lich.tongTien = dsGoi[c].gia;

    cout << "\nHo ten khach: "; cin.ignore(); getline(cin, lich.hoTenKH);
    cout << "SDT: "; getline(cin, lich.sdt);
    cout << "Ngay chup (dd/mm/yyyy): "; cin >> lich.ngayChup;
    cout << "Gio chup (HH:MM): "; cin >> lich.gioChup;

    // Đặt cọc 30%
    lich.daDongCoc = lich.tongTien * 0.30;
    lich.conLai = lich.tongTien - lich.daDongCoc;
    lich.trangThai = "DaDatCoc";

    cout << "\n--- HOA DON DAT COC ---\n";
    cout << "Ma lich: " << lich.maLich << "\n";
    cout << "Goi: " << dsGoi[c].tenGoi << "\n";
    cout << "Ngay chup: " << lich.ngayChup << " luc " << lich.gioChup << "\n";
    cout << "Tong tien: " << FloatToStr(lich.tongTien) << " VND\n";
    cout << "Dat coc (30%): " << FloatToStr(lich.daDongCoc) << " VND\n";
    cout << "Con lai: " << FloatToStr(lich.conLai) << " VND\n";

    LichChup* tmp = new LichChup[soLich + 1];
    for (int i = 0; i < soLich; i++) tmp[i] = dsLich[i];
    tmp[soLich] = lich;
    delete[] dsLich;
    dsLich = tmp;
    soLich++;

    cout << "\n[OK] Dat lich thanh cong!\n";
}

void ThanhToanConLai() {
    cout << "\n=== THANH TOAN CON LAI ===\n";
    cout << "Ma lich: "; string ma; cin >> ma;

    for (int i = 0; i < soLich; i++) {
        if (dsLich[i].maLich == ma) {
            if (dsLich[i].trangThai == "HoanThanh") {
                cout << "Lich nay da hoan thanh!\n";
                return;
            }

            cout << "\n--- THONG TIN LICH ---\n";
            cout << "Khach: " << dsLich[i].hoTenKH << "\n";
            cout << "Ngay chup: " << dsLich[i].ngayChup << "\n";
            cout << "Tong tien: " << FloatToStr(dsLich[i].tongTien) << " VND\n";
            cout << "Da dong: " << FloatToStr(dsLich[i].daDongCoc) << " VND\n";
            cout << "Con lai: " << FloatToStr(dsLich[i].conLai) << " VND\n";

            cout << "\nXac nhan thanh toan? (1=Co, 0=Khong): "; int cf; cin >> cf;

            if (cf == 1) {
                dsLich[i].daDongCoc = dsLich[i].tongTien;
                dsLich[i].conLai = 0;
                dsLich[i].trangThai = "HoanThanh";
                cout << "\n[OK] Da thanh toan day du!\n";
            }
            return;
        }
    }

    cout << "Khong tim thay lich!\n";
}

void DanhSachLich() {
    cout << "\n=== DANH SACH LICH CHUP ===\n";
    for (int i = 0; i < soLich; i++) {
        cout << dsLich[i].maLich << " | " << dsLich[i].hoTenKH << " | "
             << dsLich[i].ngayChup << " " << dsLich[i].gioChup << " | "
             << dsLich[i].trangThai << " | Con: "
             << FloatToStr(dsLich[i].conLai) << " VND\n";
    }
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== STUDIO ANH =====\n";
        cout << "1. Danh sach goi chup\n";
        cout << "2. Dat lich chup\n";
        cout << "3. Thanh toan con lai\n";
        cout << "4. Danh sach lich\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachGoi();
        else if (c == 2) DatLich();
        else if (c == 3) ThanhToanConLai();
        else if (c == 4) DanhSachLich();
        else if (c == 0) break;
    }

    delete[] dsLich;
    return 0;
}
