/*
BÀI 14: QUẢN LÝ CỬA HÀNG ĐIỆN THOẠI
- Quản lý sản phẩm (iPhone, Samsung, Xiaomi...)
- Nhập hàng (cập nhật tồn kho)
- Bán hàng (IMEI, bảo hành 12 tháng)
- Bảo hành (kiểm tra IMEI, trạng thái)
- Thống kê: Doanh thu, SP bán chạy
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int StrToInt(const string& str) {
    int result = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') result = result * 10 + (str[i] - '0');
    }
    return result;
}

string IntToStr(int num) {
    if (num == 0) return "0";
    string result = "";
    while (num > 0) { result = char('0' + num % 10) + result; num /= 10; }
    return result;
}

float StrToFloat(const string& str) {
    float result = 0.0, dec = 0.0;
    int decDigits = 0;
    bool hasDec = false;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '.') hasDec = true;
        else if (str[i] >= '0' && str[i] <= '9') {
            if (!hasDec) result = result * 10 + (str[i] - '0');
            else { dec = dec * 10 + (str[i] - '0'); decDigits++; }
        }
    }
    for (int i = 0; i < decDigits; i++) dec /= 10;
    return result + dec;
}

string FloatToStr(float num) {
    int intPart = (int)num;
    return IntToStr(intPart);
}

struct DienThoai {
    string maSP;
    string tenSP;
    string hangSX;
    float giaBan;
    int tonKho;
};

struct DonBan {
    string maDon;
    string maSP;
    string IMEI;
    string ngayBan;
    string ngayHetBH;
    float giaBan;
};

DienThoai* dsDT = NULL;
int soLuongDT = 0;
DonBan* dsDonBan = NULL;
int soLuongDon = 0;

void DocDienThoai() {
    ifstream f("DienThoai.txt");
    if (!f.is_open()) return;
    string line;
    getline(f, line);
    while (getline(f, line)) if (!line.empty()) soLuongDT++;
    f.clear(); f.seekg(0); getline(f, line);
    dsDT = new DienThoai[soLuongDT];
    int idx = 0;
    while (getline(f, line) && idx < soLuongDT) {
        if (line.empty()) continue;
        int p1 = line.find(','), p2 = line.find(',', p1+1), p3 = line.find(',', p2+1), p4 = line.find(',', p3+1);
        dsDT[idx].maSP = line.substr(0, p1);
        dsDT[idx].tenSP = line.substr(p1+1, p2-p1-1);
        dsDT[idx].hangSX = line.substr(p2+1, p3-p2-1);
        dsDT[idx].giaBan = StrToFloat(line.substr(p3+1, p4-p3-1));
        dsDT[idx].tonKho = StrToInt(line.substr(p4+1));
        idx++;
    }
    soLuongDT = idx;
    f.close();
}

void BanHang() {
    cout << "\n=== BAN DIEN THOAI ===\n";
    for (int i = 0; i < soLuongDT; i++) {
        cout << (i+1) << ". " << dsDT[i].tenSP << " - " << FloatToStr(dsDT[i].giaBan) << " VND (Con: " << dsDT[i].tonKho << ")\n";
    }
    cout << "Chon SP: "; int chon; cin >> chon; chon--;
    if (chon < 0 || chon >= soLuongDT || dsDT[chon].tonKho == 0) { cout << "Loi!\n"; return; }

    DonBan db;
    db.maDon = "DB" + IntToStr(soLuongDon + 1);
    db.maSP = dsDT[chon].maSP;
    cout << "Nhap IMEI: "; cin >> db.IMEI;
    cout << "Ngay ban (dd/mm/yyyy): "; cin >> db.ngayBan;
    cout << "Ngay het BH (dd/mm/yyyy): "; cin >> db.ngayHetBH;
    db.giaBan = dsDT[chon].giaBan;

    dsDT[chon].tonKho--;

    DonBan* temp = new DonBan[soLuongDon + 1];
    for (int i = 0; i < soLuongDon; i++) temp[i] = dsDonBan[i];
    temp[soLuongDon] = db;
    delete[] dsDonBan; dsDonBan = temp; soLuongDon++;

    cout << "\n[OK] Da ban! IMEI: " << db.IMEI << "\nBao hanh den: " << db.ngayHetBH << "\n";
}

void KiemTraBaoHanh() {
    cout << "\nNhap IMEI: "; string imei; cin >> imei;
    for (int i = 0; i < soLuongDon; i++) {
        if (dsDonBan[i].IMEI == imei) {
            cout << "San pham: " << dsDonBan[i].maSP << "\nNgay ban: " << dsDonBan[i].ngayBan
                 << "\nBao hanh den: " << dsDonBan[i].ngayHetBH << "\n";
            return;
        }
    }
    cout << "Khong tim thay!\n";
}

void Menu() {
    cout << "\n1. Ban hang\n2. Kiem tra bao hanh\n0. Thoat\nChon: ";
}

int main() {
    DocDienThoai();
    while (true) {
        Menu();
        int chon; cin >> chon;
        if (chon == 1) BanHang();
        else if (chon == 2) KiemTraBaoHanh();
        else if (chon == 0) break;
    }
    delete[] dsDT; delete[] dsDonBan;
    return 0;
}
