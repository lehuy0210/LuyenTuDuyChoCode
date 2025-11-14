/*
===============================================
    BÀI 10: HỆ THỐNG QUẢN LÝ GIẶT LÀ
===============================================
Mô tả: Quản lý khách hàng, đơn giặt, dịch vụ, giao nhận
Tính năng:
- Đăng ký khách hàng (tên, SĐT, địa chỉ)
- Dịch vụ: Giặt, là, giặt khô, giặt nhanh
- Tính giá theo kg hoặc số lượng
- Trạng thái đơn: Nhận, đang giặt, đang sấy, hoàn thành, đã giao
- Giao nhận tại nhà (phí giao hàng)
- Dịch vụ gấp (express): +50% giá
- Thống kê: Doanh thu, dịch vụ phổ biến, đơn chưa hoàn thành
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ==================== UTILITY FUNCTIONS ====================

int StrToInt(const string& str) {
    int result = 0;
    int start = 0;
    bool isNegative = false;

    if (str.length() > 0 && str[0] == '-') {
        isNegative = true;
        start = 1;
    }

    for (int i = start; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }

    return isNegative ? -result : result;
}

string IntToStr(int num) {
    if (num == 0) return "0";

    string result = "";
    bool isNegative = false;

    if (num < 0) {
        isNegative = true;
        num = -num;
    }

    while (num > 0) {
        result = char('0' + num % 10) + result;
        num /= 10;
    }

    if (isNegative) result = "-" + result;
    return result;
}

float StrToFloat(const string& str) {
    float result = 0.0;
    float decimalPart = 0.0;
    int decimalDigits = 0;
    bool hasDecimal = false;
    bool isNegative = false;
    int start = 0;

    if (str.length() > 0 && str[0] == '-') {
        isNegative = true;
        start = 1;
    }

    for (int i = start; i < str.length(); i++) {
        if (str[i] == '.') {
            hasDecimal = true;
        } else if (str[i] >= '0' && str[i] <= '9') {
            if (!hasDecimal) {
                result = result * 10 + (str[i] - '0');
            } else {
                decimalPart = decimalPart * 10 + (str[i] - '0');
                decimalDigits++;
            }
        }
    }

    for (int i = 0; i < decimalDigits; i++) {
        decimalPart /= 10;
    }

    result += decimalPart;
    return isNegative ? -result : result;
}

string FloatToStr(float num, int decimalPlaces = 2) {
    int intPart = (int)num;
    float fracPart = num - intPart;

    if (fracPart < 0) fracPart = -fracPart;

    string result = IntToStr(intPart) + ".";

    for (int i = 0; i < decimalPlaces; i++) {
        fracPart *= 10;
        int digit = (int)fracPart;
        result += char('0' + digit);
        fracPart -= digit;
    }

    return result;
}

string ToUpper(const string& str) {
    string result = "";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            result += char(str[i] - 32);
        } else {
            result += str[i];
        }
    }
    return result;
}

bool ContainsIgnoreCase(const string& text, const string& search) {
    return ToUpper(text).find(ToUpper(search)) != string::npos;
}

string Trim(const string& str) {
    int start = 0;
    int end = str.length() - 1;

    while (start <= end && (str[start] == ' ' || str[start] == '\t')) {
        start++;
    }

    while (end >= start && (str[end] == ' ' || str[end] == '\t')) {
        end--;
    }

    if (start > end) return "";
    return str.substr(start, end - start + 1);
}

void ParseCSV(const string& line, string fields[], int& count) {
    count = 0;
    string currentField = "";

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',') {
            fields[count++] = Trim(currentField);
            currentField = "";
        } else {
            currentField += line[i];
        }
    }

    if (currentField.length() > 0 || line[line.length()-1] == ',') {
        fields[count++] = Trim(currentField);
    }
}

// ==================== STRUCTS ====================

struct KhachHang {
    string maKH;          // KH001, KH002...
    string hoTen;         // "Nguyen Van A"
    string sdt;           // "0912345678"
    string diaChi;        // "123 Nguyen Trai, Q.1"
};

struct DichVu {
    string maDV;          // DV001, DV002...
    string tenDV;         // "Giat Thuong", "Giat Kho", "Ui"
    string donVi;         // "kg", "cai"
    float donGia;         // 20000/kg, 15000/cai
    string moTa;          // Mô tả dịch vụ
};

struct ChiTietDon {
    string maDV;          // Mã dịch vụ
    float soLuong;        // Số kg hoặc số cái
    float thanhTien;      // Thành tiền = soLuong × donGia
};

struct DonGiat {
    string maDon;         // DG001, DG002...
    string maKH;          // KH001
    string ngayNhan;      // "15/01/2025"
    string gioNhan;       // "08:30"
    string ngayHenTra;    // "17/01/2025"
    string gioHenTra;     // "14:00"
    int soLuongDV;        // Số dịch vụ trong đơn
    ChiTietDon* dsDichVu; // Mảng động các dịch vụ
    bool giaoNhan;        // true = giao nhận tại nhà
    bool dichVuGap;       // true = dịch vụ gấp (+50%)
    float phiGiaoNhan;    // 30000
    float tongTien;       // Tổng tiền
    string trangThai;     // "Nhan", "DangGiat", "DangSay", "HoanThanh", "DaGiao"
};

// ==================== GLOBAL DATA ====================

KhachHang* dsKhachHang = NULL;
int soLuongKH = 0;

DichVu* dsDichVu = NULL;
int soLuongDV = 0;

DonGiat* dsDonGiat = NULL;
int soLuongDon = 0;

// ==================== FILE OPERATIONS ====================

void DocKhachHang() {
    ifstream file("DanhSachKhachHang.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file DanhSachKhachHang.txt\n";
        return;
    }

    string line;
    getline(file, line);

    soLuongKH = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        soLuongKH++;
    }

    file.clear();
    file.seekg(0);
    getline(file, line);

    dsKhachHang = new KhachHang[soLuongKH];
    int index = 0;

    while (getline(file, line) && index < soLuongKH) {
        if (line.empty()) continue;

        string fields[10];
        int count;
        ParseCSV(line, fields, count);

        if (count >= 4) {
            dsKhachHang[index].maKH = fields[0];
            dsKhachHang[index].hoTen = fields[1];
            dsKhachHang[index].sdt = fields[2];
            dsKhachHang[index].diaChi = fields[3];
            index++;
        }
    }

    soLuongKH = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongKH << " khach hang\n";
}

void GhiKhachHang() {
    ofstream file("DanhSachKhachHang.txt");
    if (!file.is_open()) {
        cout << "[LOI] Khong the ghi file DanhSachKhachHang.txt\n";
        return;
    }

    file << "MaKH,HoTen,SDT,DiaChi\n";

    for (int i = 0; i < soLuongKH; i++) {
        file << dsKhachHang[i].maKH << ","
             << dsKhachHang[i].hoTen << ","
             << dsKhachHang[i].sdt << ","
             << dsKhachHang[i].diaChi << "\n";
    }

    file.close();
}

void DocDichVu() {
    ifstream file("DichVu.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file DichVu.txt\n";
        return;
    }

    string line;
    getline(file, line);

    soLuongDV = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        soLuongDV++;
    }

    file.clear();
    file.seekg(0);
    getline(file, line);

    dsDichVu = new DichVu[soLuongDV];
    int index = 0;

    while (getline(file, line) && index < soLuongDV) {
        if (line.empty()) continue;

        string fields[10];
        int count;
        ParseCSV(line, fields, count);

        if (count >= 5) {
            dsDichVu[index].maDV = fields[0];
            dsDichVu[index].tenDV = fields[1];
            dsDichVu[index].donVi = fields[2];
            dsDichVu[index].donGia = StrToFloat(fields[3]);
            dsDichVu[index].moTa = fields[4];
            index++;
        }
    }

    soLuongDV = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongDV << " dich vu\n";
}

// ==================== BUSINESS LOGIC ====================

string TaoMaKHMoi() {
    int maxNum = 0;
    for (int i = 0; i < soLuongKH; i++) {
        if (dsKhachHang[i].maKH.length() >= 4 && dsKhachHang[i].maKH[0] == 'K') {
            string numStr = dsKhachHang[i].maKH.substr(2);
            int num = StrToInt(numStr);
            if (num > maxNum) maxNum = num;
        }
    }

    string ma = "KH";
    int newNum = maxNum + 1;

    if (newNum < 10) ma += "00";
    else if (newNum < 100) ma += "0";

    ma += IntToStr(newNum);
    return ma;
}

string TaoMaDonMoi() {
    int maxNum = 0;
    for (int i = 0; i < soLuongDon; i++) {
        if (dsDonGiat[i].maDon.length() >= 4 && dsDonGiat[i].maDon[0] == 'D') {
            string numStr = dsDonGiat[i].maDon.substr(2);
            int num = StrToInt(numStr);
            if (num > maxNum) maxNum = num;
        }
    }

    string ma = "DG";
    int newNum = maxNum + 1;

    if (newNum < 10) ma += "00";
    else if (newNum < 100) ma += "0";

    ma += IntToStr(newNum);
    return ma;
}

void ThemKhachHang() {
    cout << "\n========== THEM KHACH HANG MOI ==========\n";

    KhachHang khMoi;
    khMoi.maKH = TaoMaKHMoi();

    cout << "Ma khach hang (tu dong): " << khMoi.maKH << "\n";

    cout << "Nhap ho ten: ";
    cin.ignore();
    getline(cin, khMoi.hoTen);

    cout << "Nhap so dien thoai: ";
    getline(cin, khMoi.sdt);

    cout << "Nhap dia chi: ";
    getline(cin, khMoi.diaChi);

    KhachHang* temp = new KhachHang[soLuongKH + 1];
    for (int i = 0; i < soLuongKH; i++) {
        temp[i] = dsKhachHang[i];
    }
    temp[soLuongKH] = khMoi;

    delete[] dsKhachHang;
    dsKhachHang = temp;
    soLuongKH++;

    GhiKhachHang();
    cout << "[THANH CONG] Da them khach hang: " << khMoi.hoTen << "\n";
}

void HienThiDanhSachKhachHang() {
    cout << "\n========== DANH SACH KHACH HANG ==========\n";

    if (soLuongKH == 0) {
        cout << "Chua co khach hang nao!\n";
        return;
    }

    cout << "Ma    | Ho Ten                | SDT          | Dia Chi\n";
    cout << "-----------------------------------------------------------------------\n";

    for (int i = 0; i < soLuongKH; i++) {
        cout << dsKhachHang[i].maKH << " | ";

        string ten = dsKhachHang[i].hoTen;
        if (ten.length() > 21) ten = ten.substr(0, 18) + "...";
        cout << ten;
        for (int j = ten.length(); j < 21; j++) cout << " ";
        cout << " | ";

        cout << dsKhachHang[i].sdt;
        for (int j = dsKhachHang[i].sdt.length(); j < 12; j++) cout << " ";
        cout << " | ";

        string dc = dsKhachHang[i].diaChi;
        if (dc.length() > 30) dc = dc.substr(0, 27) + "...";
        cout << dc << "\n";
    }
}

void HienThiDichVu() {
    cout << "\n========== DANH SACH DICH VU ==========\n";

    for (int i = 0; i < soLuongDV; i++) {
        cout << (i + 1) << ". " << dsDichVu[i].tenDV << " - "
             << FloatToStr(dsDichVu[i].donGia, 0) << " VND/" << dsDichVu[i].donVi << "\n";
        cout << "   " << dsDichVu[i].moTa << "\n\n";
    }
}

void TaoDonGiat() {
    cout << "\n========== TAO DON GIAT MOI ==========\n";

    // 1. Tìm hoặc tạo khách hàng
    cout << "Nhap so dien thoai khach hang: ";
    string sdtTimKiem;
    cin >> sdtTimKiem;

    KhachHang* khachHang = NULL;
    for (int i = 0; i < soLuongKH; i++) {
        if (dsKhachHang[i].sdt == sdtTimKiem) {
            khachHang = &dsKhachHang[i];
            cout << "Tim thay khach hang: " << khachHang->hoTen << "\n";
            break;
        }
    }

    if (khachHang == NULL) {
        cout << "Khach hang moi. Vui long nhap thong tin:\n";

        KhachHang khMoi;
        khMoi.maKH = TaoMaKHMoi();
        khMoi.sdt = sdtTimKiem;

        cout << "Nhap ho ten: ";
        cin.ignore();
        getline(cin, khMoi.hoTen);

        cout << "Nhap dia chi: ";
        getline(cin, khMoi.diaChi);

        KhachHang* temp = new KhachHang[soLuongKH + 1];
        for (int i = 0; i < soLuongKH; i++) {
            temp[i] = dsKhachHang[i];
        }
        temp[soLuongKH] = khMoi;

        delete[] dsKhachHang;
        dsKhachHang = temp;
        khachHang = &dsKhachHang[soLuongKH];
        soLuongKH++;

        GhiKhachHang();
        cout << "[OK] Da them khach hang moi: " << khMoi.hoTen << "\n";
    }

    // 2. Tạo đơn giặt
    DonGiat donMoi;
    donMoi.maDon = TaoMaDonMoi();
    donMoi.maKH = khachHang->maKH;

    cout << "\nMa don (tu dong): " << donMoi.maDon << "\n";

    cout << "Nhap ngay nhan (dd/mm/yyyy): ";
    cin >> donMoi.ngayNhan;

    cout << "Nhap gio nhan (HH:MM): ";
    cin >> donMoi.gioNhan;

    cout << "Nhap ngay hen tra (dd/mm/yyyy): ";
    cin >> donMoi.ngayHenTra;

    cout << "Nhap gio hen tra (HH:MM): ";
    cin >> donMoi.gioHenTra;

    // 3. Chọn dịch vụ
    HienThiDichVu();

    cout << "Nhap so luong dich vu: ";
    string input;
    cin >> input;
    donMoi.soLuongDV = StrToInt(input);

    donMoi.dsDichVu = new ChiTietDon[donMoi.soLuongDV];

    float tongTienDV = 0;

    for (int i = 0; i < donMoi.soLuongDV; i++) {
        cout << "\n--- Dich vu " << (i + 1) << " ---\n";

        cout << "Chon dich vu (1-" << soLuongDV << "): ";
        cin >> input;
        int chon = StrToInt(input) - 1;

        if (chon < 0 || chon >= soLuongDV) {
            cout << "[LOI] Lua chon khong hop le!\n";
            i--;
            continue;
        }

        donMoi.dsDichVu[i].maDV = dsDichVu[chon].maDV;

        cout << "Nhap so luong (" << dsDichVu[chon].donVi << "): ";
        cin >> input;
        donMoi.dsDichVu[i].soLuong = StrToFloat(input);

        donMoi.dsDichVu[i].thanhTien = donMoi.dsDichVu[i].soLuong * dsDichVu[chon].donGia;
        tongTienDV += donMoi.dsDichVu[i].thanhTien;

        cout << "[OK] " << dsDichVu[chon].tenDV << " - "
             << FloatToStr(donMoi.dsDichVu[i].thanhTien, 0) << " VND\n";
    }

    // 4. Dịch vụ giao nhận
    cout << "\nGiao nhan tai nha? (1: Co, 0: Khong): ";
    cin >> input;
    donMoi.giaoNhan = (StrToInt(input) == 1);

    if (donMoi.giaoNhan) {
        donMoi.phiGiaoNhan = 30000;
    } else {
        donMoi.phiGiaoNhan = 0;
    }

    // 5. Dịch vụ gấp
    cout << "Dich vu gap (hoan thanh trong 24h, +50% gia)? (1: Co, 0: Khong): ";
    cin >> input;
    donMoi.dichVuGap = (StrToInt(input) == 1);

    // 6. Tính tổng tiền
    donMoi.tongTien = tongTienDV + donMoi.phiGiaoNhan;

    if (donMoi.dichVuGap) {
        donMoi.tongTien = donMoi.tongTien * 1.5;  // +50%
    }

    donMoi.trangThai = "Nhan";

    // 7. Hiển thị hóa đơn
    cout << "\n========== HOA DON ==========\n";
    cout << "Ma don: " << donMoi.maDon << "\n";
    cout << "Khach hang: " << khachHang->hoTen << "\n";
    cout << "SDT: " << khachHang->sdt << "\n";
    cout << "Dia chi: " << khachHang->diaChi << "\n";
    cout << "Ngay nhan: " << donMoi.ngayNhan << " " << donMoi.gioNhan << "\n";
    cout << "Ngay hen tra: " << donMoi.ngayHenTra << " " << donMoi.gioHenTra << "\n";
    cout << "----------------------------\n";

    cout << "Chi tiet dich vu:\n";
    for (int i = 0; i < donMoi.soLuongDV; i++) {
        string tenDV = "";
        for (int j = 0; j < soLuongDV; j++) {
            if (dsDichVu[j].maDV == donMoi.dsDichVu[i].maDV) {
                tenDV = dsDichVu[j].tenDV;
                break;
            }
        }

        cout << "  - " << tenDV << " x " << FloatToStr(donMoi.dsDichVu[i].soLuong, 1)
             << " = " << FloatToStr(donMoi.dsDichVu[i].thanhTien, 0) << " VND\n";
    }

    cout << "----------------------------\n";
    cout << "Tong tien dich vu: " << FloatToStr(tongTienDV, 0) << " VND\n";

    if (donMoi.giaoNhan) {
        cout << "Phi giao nhan: " << FloatToStr(donMoi.phiGiaoNhan, 0) << " VND\n";
    }

    if (donMoi.dichVuGap) {
        cout << "Dich vu gap (+50%): Ap dung\n";
    }

    cout << "----------------------------\n";
    cout << "TONG CONG: " << FloatToStr(donMoi.tongTien, 0) << " VND\n";
    cout << "============================\n";

    // 8. Lưu đơn
    DonGiat* temp = new DonGiat[soLuongDon + 1];
    for (int i = 0; i < soLuongDon; i++) {
        temp[i] = dsDonGiat[i];
    }
    temp[soLuongDon] = donMoi;

    delete[] dsDonGiat;
    dsDonGiat = temp;
    soLuongDon++;

    cout << "\n[THANH CONG] Da tao don giat!\n";
}

void HienThiDanhSachDon() {
    cout << "\n========== DANH SACH DON GIAT ==========\n";

    if (soLuongDon == 0) {
        cout << "Chua co don giat nao!\n";
        return;
    }

    cout << "Ma Don | Khach Hang            | Ngay Nhan  | Ngay Tra   | Trang Thai\n";
    cout << "-------------------------------------------------------------------------\n";

    for (int i = 0; i < soLuongDon; i++) {
        cout << dsDonGiat[i].maDon << "  | ";

        string tenKH = "";
        for (int j = 0; j < soLuongKH; j++) {
            if (dsKhachHang[j].maKH == dsDonGiat[i].maKH) {
                tenKH = dsKhachHang[j].hoTen;
                break;
            }
        }

        if (tenKH.length() > 21) tenKH = tenKH.substr(0, 18) + "...";
        cout << tenKH;
        for (int j = tenKH.length(); j < 21; j++) cout << " ";
        cout << " | ";

        cout << dsDonGiat[i].ngayNhan << " | ";
        cout << dsDonGiat[i].ngayHenTra << " | ";
        cout << dsDonGiat[i].trangThai << "\n";
    }
}

void CapNhatTrangThaiDon() {
    cout << "\n========== CAP NHAT TRANG THAI DON ==========\n";

    HienThiDanhSachDon();

    cout << "\nNhap ma don: ";
    string maDon;
    cin >> maDon;

    bool timThay = false;
    for (int i = 0; i < soLuongDon; i++) {
        if (dsDonGiat[i].maDon == maDon) {
            timThay = true;

            cout << "\nTrang thai hien tai: " << dsDonGiat[i].trangThai << "\n";
            cout << "Chon trang thai moi:\n";
            cout << "  1. Nhan\n";
            cout << "  2. DangGiat\n";
            cout << "  3. DangSay\n";
            cout << "  4. HoanThanh\n";
            cout << "  5. DaGiao\n";
            cout << "Lua chon: ";

            string input;
            cin >> input;
            int chon = StrToInt(input);

            if (chon == 1) dsDonGiat[i].trangThai = "Nhan";
            else if (chon == 2) dsDonGiat[i].trangThai = "DangGiat";
            else if (chon == 3) dsDonGiat[i].trangThai = "DangSay";
            else if (chon == 4) dsDonGiat[i].trangThai = "HoanThanh";
            else if (chon == 5) dsDonGiat[i].trangThai = "DaGiao";
            else {
                cout << "[LOI] Lua chon khong hop le!\n";
                return;
            }

            cout << "[THANH CONG] Da cap nhat trang thai: " << dsDonGiat[i].trangThai << "\n";
            break;
        }
    }

    if (!timThay) {
        cout << "[LOI] Khong tim thay don giat!\n";
    }
}

void ThongKeDoanhThu() {
    cout << "\n========== THONG KE DOANH THU ==========\n";

    if (soLuongDon == 0) {
        cout << "Chua co don giat nao!\n";
        return;
    }

    float tongDoanhThu = 0;
    int soDonHoanThanh = 0;
    int soDonDangXuLy = 0;

    for (int i = 0; i < soLuongDon; i++) {
        tongDoanhThu += dsDonGiat[i].tongTien;

        if (dsDonGiat[i].trangThai == "HoanThanh" || dsDonGiat[i].trangThai == "DaGiao") {
            soDonHoanThanh++;
        } else {
            soDonDangXuLy++;
        }
    }

    cout << "Tong so don: " << soLuongDon << "\n";
    cout << "  - Don hoan thanh: " << soDonHoanThanh << "\n";
    cout << "  - Don dang xu ly: " << soDonDangXuLy << "\n";
    cout << "---------------------------------------\n";
    cout << "Tong doanh thu: " << FloatToStr(tongDoanhThu, 0) << " VND\n";
    cout << "Doanh thu trung binh/don: " << FloatToStr(tongDoanhThu / soLuongDon, 0) << " VND\n";
}

// ==================== MENU ====================

void Menu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "   HE THONG QUAN LY GIAT LA\n";
    cout << "========================================\n";
    cout << "1. Quan ly khach hang\n";
    cout << "   1.1. Them khach hang\n";
    cout << "   1.2. Hien thi danh sach khach hang\n";
    cout << "2. Quan ly don giat\n";
    cout << "   2.1. Tao don giat moi\n";
    cout << "   2.2. Hien thi danh sach don\n";
    cout << "   2.3. Cap nhat trang thai don\n";
    cout << "3. Thong ke doanh thu\n";
    cout << "0. Thoat\n";
    cout << "========================================\n";
    cout << "Lua chon: ";
}

// ==================== MAIN ====================

int main() {
    cout << "\n*** Dang khoi tao he thong ***\n";

    DocKhachHang();
    DocDichVu();

    cout << "*** Khoi tao hoan tat ***\n";

    while (true) {
        Menu();

        string luaChon;
        getline(cin, luaChon);

        if (luaChon == "1.1") {
            ThemKhachHang();
        } else if (luaChon == "1.2") {
            HienThiDanhSachKhachHang();
        } else if (luaChon == "2.1") {
            TaoDonGiat();
        } else if (luaChon == "2.2") {
            HienThiDanhSachDon();
        } else if (luaChon == "2.3") {
            CapNhatTrangThaiDon();
        } else if (luaChon == "3") {
            ThongKeDoanhThu();
        } else if (luaChon == "0") {
            cout << "\nCam on ban da su dung he thong!\n";
            break;
        } else {
            cout << "[LOI] Lua chon khong hop le!\n";
        }
    }

    // Giải phóng bộ nhớ
    delete[] dsKhachHang;
    delete[] dsDichVu;

    for (int i = 0; i < soLuongDon; i++) {
        delete[] dsDonGiat[i].dsDichVu;
    }
    delete[] dsDonGiat;

    return 0;
}
