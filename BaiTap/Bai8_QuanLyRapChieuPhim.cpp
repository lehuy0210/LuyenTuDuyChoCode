/*
===============================================
    BÀI 8: HỆ THỐNG QUẢN LÝ RẠP CHIẾU PHIM
===============================================
Mô tả: Quản lý phim, lịch chiếu, đặt vé, ghế ngồi
Tính năng:
- Quản lý phim (tên, thể loại, thời lượng, đánh giá)
- Quản lý phòng chiếu và ghế ngồi
- Lịch chiếu phim (ngày, giờ, phòng)
- Đặt vé (chọn ghế, loại vé: Thường/VIP/Học sinh)
- Bán combo đồ ăn/nước uống
- Thống kê doanh thu
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ==================== UTILITY FUNCTIONS ====================

// Chuyển string sang int (không dùng stoi)
int StrToInt(const string& str) {
    int result = 0;
    int start = 0;
    bool isNegative = false;

    if (str[0] == '-') {
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

// Chuyển int sang string (không dùng to_string)
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

// Chuyển float sang string
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

// Chuyển string sang float
float StrToFloat(const string& str) {
    float result = 0.0;
    float decimalPart = 0.0;
    int decimalDigits = 0;
    bool hasDecimal = false;
    bool isNegative = false;
    int start = 0;

    if (str[0] == '-') {
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

// Chuyển chuỗi sang chữ hoa
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

// Tìm kiếm substring (không phân biệt hoa thường)
bool ContainsIgnoreCase(const string& text, const string& search) {
    return ToUpper(text).find(ToUpper(search)) != string::npos;
}

// Xóa khoảng trắng đầu cuối
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

// Parse CSV line
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

struct Phim {
    string maPhim;        // P001, P002...
    string tenPhim;       // "Avengers", "Doraemon"...
    string theLoai;       // "Hành động", "Hoạt hình"...
    int thoiLuong;        // Phút (120, 90...)
    float danhGia;        // 8.5, 9.0...
};

struct PhongChieu {
    int soPhong;          // 1, 2, 3...
    int soHangGhe;        // Số hàng (A, B, C... -> 10 hàng)
    int soGheMoiHang;     // Số ghế mỗi hàng (10 ghế)
    string* trangThaiGhe; // Mảng trạng thái: "Trong", "DaDat"
};

struct LichChieu {
    string maLich;        // LC001, LC002...
    string maPhim;        // P001
    int soPhong;          // 1
    string ngayChieu;     // "15/01/2025"
    string gioChieu;      // "14:30", "19:00"...
};

struct Ve {
    string maVe;          // V001, V002...
    string maLich;        // LC001
    string viTriGhe;      // "A5", "B10"...
    string loaiVe;        // "Thuong", "VIP", "HocSinh"
    float giaVe;          // 70000, 120000, 50000...
};

struct Combo {
    string maCombo;       // CB001, CB002...
    string tenCombo;      // "Bắp nước", "Combo đôi"...
    float giaCombo;       // 50000, 80000...
};

struct DonHang {
    string maDon;         // DH001, DH002...
    string ngayDat;       // "15/01/2025"
    string gioData;        // "10:30"
    string hoTenKhach;    // Tên khách hàng
    string sdt;           // Số điện thoại
    int soVe;             // Số vé đặt
    Ve* danhSachVe;       // Mảng vé
    int soCombo;          // Số combo
    Combo* danhSachCombo; // Mảng combo
    float tongTien;       // Tổng tiền
};

// ==================== GLOBAL DATA ====================

Phim* dsPhim = NULL;
int soLuongPhim = 0;

PhongChieu* dsPhongChieu = NULL;
int soLuongPhong = 0;

LichChieu* dsLichChieu = NULL;
int soLuongLich = 0;

Combo* dsCombo = NULL;
int soLuongCombo = 0;

DonHang* dsDonHang = NULL;
int soLuongDon = 0;

// ==================== FILE OPERATIONS ====================

void DocDanhSachPhim() {
    ifstream file("DanhSachPhim.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file DanhSachPhim.txt\n";
        return;
    }

    string line;
    getline(file, line); // Bỏ dòng tiêu đề

    soLuongPhim = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        soLuongPhim++;
    }

    file.clear();
    file.seekg(0);
    getline(file, line); // Bỏ dòng tiêu đề

    dsPhim = new Phim[soLuongPhim];
    int index = 0;

    while (getline(file, line) && index < soLuongPhim) {
        if (line.empty()) continue;

        string fields[10];
        int count;
        ParseCSV(line, fields, count);

        if (count >= 5) {
            dsPhim[index].maPhim = fields[0];
            dsPhim[index].tenPhim = fields[1];
            dsPhim[index].theLoai = fields[2];
            dsPhim[index].thoiLuong = StrToInt(fields[3]);
            dsPhim[index].danhGia = StrToFloat(fields[4]);
            index++;
        }
    }

    soLuongPhim = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongPhim << " phim\n";
}

void GhiDanhSachPhim() {
    ofstream file("DanhSachPhim.txt");
    if (!file.is_open()) {
        cout << "[LOI] Khong the ghi file DanhSachPhim.txt\n";
        return;
    }

    file << "MaPhim,TenPhim,TheLoai,ThoiLuong,DanhGia\n";

    for (int i = 0; i < soLuongPhim; i++) {
        file << dsPhim[i].maPhim << ","
             << dsPhim[i].tenPhim << ","
             << dsPhim[i].theLoai << ","
             << dsPhim[i].thoiLuong << ","
             << FloatToStr(dsPhim[i].danhGia, 1) << "\n";
    }

    file.close();
}

void DocDanhSachPhongChieu() {
    ifstream file("DanhSachPhongChieu.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file DanhSachPhongChieu.txt\n";
        return;
    }

    string line;
    getline(file, line); // Bỏ tiêu đề

    soLuongPhong = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        soLuongPhong++;
    }

    file.clear();
    file.seekg(0);
    getline(file, line);

    dsPhongChieu = new PhongChieu[soLuongPhong];
    int index = 0;

    while (getline(file, line) && index < soLuongPhong) {
        if (line.empty()) continue;

        string fields[10];
        int count;
        ParseCSV(line, fields, count);

        if (count >= 3) {
            dsPhongChieu[index].soPhong = StrToInt(fields[0]);
            dsPhongChieu[index].soHangGhe = StrToInt(fields[1]);
            dsPhongChieu[index].soGheMoiHang = StrToInt(fields[2]);

            int tongGhe = dsPhongChieu[index].soHangGhe * dsPhongChieu[index].soGheMoiHang;
            dsPhongChieu[index].trangThaiGhe = new string[tongGhe];

            for (int i = 0; i < tongGhe; i++) {
                dsPhongChieu[index].trangThaiGhe[i] = "Trong";
            }

            index++;
        }
    }

    soLuongPhong = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongPhong << " phong chieu\n";
}

void DocLichChieu() {
    ifstream file("LichChieu.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file LichChieu.txt\n";
        return;
    }

    string line;
    getline(file, line);

    soLuongLich = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        soLuongLich++;
    }

    file.clear();
    file.seekg(0);
    getline(file, line);

    dsLichChieu = new LichChieu[soLuongLich];
    int index = 0;

    while (getline(file, line) && index < soLuongLich) {
        if (line.empty()) continue;

        string fields[10];
        int count;
        ParseCSV(line, fields, count);

        if (count >= 5) {
            dsLichChieu[index].maLich = fields[0];
            dsLichChieu[index].maPhim = fields[1];
            dsLichChieu[index].soPhong = StrToInt(fields[2]);
            dsLichChieu[index].ngayChieu = fields[3];
            dsLichChieu[index].gioChieu = fields[4];
            index++;
        }
    }

    soLuongLich = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongLich << " lich chieu\n";
}

void GhiLichChieu() {
    ofstream file("LichChieu.txt");
    if (!file.is_open()) {
        cout << "[LOI] Khong the ghi file LichChieu.txt\n";
        return;
    }

    file << "MaLich,MaPhim,SoPhong,NgayChieu,GioChieu\n";

    for (int i = 0; i < soLuongLich; i++) {
        file << dsLichChieu[i].maLich << ","
             << dsLichChieu[i].maPhim << ","
             << dsLichChieu[i].soPhong << ","
             << dsLichChieu[i].ngayChieu << ","
             << dsLichChieu[i].gioChieu << "\n";
    }

    file.close();
}

void DocDanhSachCombo() {
    ifstream file("DanhSachCombo.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file DanhSachCombo.txt\n";
        return;
    }

    string line;
    getline(file, line);

    soLuongCombo = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        soLuongCombo++;
    }

    file.clear();
    file.seekg(0);
    getline(file, line);

    dsCombo = new Combo[soLuongCombo];
    int index = 0;

    while (getline(file, line) && index < soLuongCombo) {
        if (line.empty()) continue;

        string fields[10];
        int count;
        ParseCSV(line, fields, count);

        if (count >= 3) {
            dsCombo[index].maCombo = fields[0];
            dsCombo[index].tenCombo = fields[1];
            dsCombo[index].giaCombo = StrToFloat(fields[2]);
            index++;
        }
    }

    soLuongCombo = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongCombo << " combo\n";
}

// ==================== BUSINESS LOGIC ====================

string TaoMaPhimMoi() {
    int maxNum = 0;
    for (int i = 0; i < soLuongPhim; i++) {
        if (dsPhim[i].maPhim.length() >= 4 && dsPhim[i].maPhim[0] == 'P') {
            string numStr = dsPhim[i].maPhim.substr(1);
            int num = StrToInt(numStr);
            if (num > maxNum) maxNum = num;
        }
    }

    string ma = "P";
    int newNum = maxNum + 1;

    if (newNum < 10) ma += "00";
    else if (newNum < 100) ma += "0";

    ma += IntToStr(newNum);
    return ma;
}

string TaoMaLichMoi() {
    int maxNum = 0;
    for (int i = 0; i < soLuongLich; i++) {
        if (dsLichChieu[i].maLich.length() >= 4 && dsLichChieu[i].maLich[0] == 'L') {
            string numStr = dsLichChieu[i].maLich.substr(2);
            int num = StrToInt(numStr);
            if (num > maxNum) maxNum = num;
        }
    }

    string ma = "LC";
    int newNum = maxNum + 1;

    if (newNum < 10) ma += "00";
    else if (newNum < 100) ma += "0";

    ma += IntToStr(newNum);
    return ma;
}

string TaoMaDonMoi() {
    int maxNum = 0;
    for (int i = 0; i < soLuongDon; i++) {
        if (dsDonHang[i].maDon.length() >= 4 && dsDonHang[i].maDon[0] == 'D') {
            string numStr = dsDonHang[i].maDon.substr(2);
            int num = StrToInt(numStr);
            if (num > maxNum) maxNum = num;
        }
    }

    string ma = "DH";
    int newNum = maxNum + 1;

    if (newNum < 10) ma += "00";
    else if (newNum < 100) ma += "0";

    ma += IntToStr(newNum);
    return ma;
}

void ThemPhim() {
    cout << "\n========== THEM PHIM MOI ==========\n";

    Phim phimMoi;
    phimMoi.maPhim = TaoMaPhimMoi();

    cout << "Ma phim (tu dong): " << phimMoi.maPhim << "\n";

    cout << "Nhap ten phim: ";
    cin.ignore();
    getline(cin, phimMoi.tenPhim);

    cout << "Nhap the loai: ";
    getline(cin, phimMoi.theLoai);

    cout << "Nhap thoi luong (phut): ";
    string input;
    getline(cin, input);
    phimMoi.thoiLuong = StrToInt(input);

    cout << "Nhap danh gia (0-10): ";
    getline(cin, input);
    phimMoi.danhGia = StrToFloat(input);

    Phim* temp = new Phim[soLuongPhim + 1];
    for (int i = 0; i < soLuongPhim; i++) {
        temp[i] = dsPhim[i];
    }
    temp[soLuongPhim] = phimMoi;

    delete[] dsPhim;
    dsPhim = temp;
    soLuongPhim++;

    GhiDanhSachPhim();
    cout << "[THANH CONG] Da them phim: " << phimMoi.tenPhim << "\n";
}

void HienThiDanhSachPhim() {
    cout << "\n========== DANH SACH PHIM ==========\n";

    if (soLuongPhim == 0) {
        cout << "Chua co phim nao!\n";
        return;
    }

    cout << "Ma    | Ten Phim                | The Loai        | TL(p) | Danh Gia\n";
    cout << "----------------------------------------------------------------------\n";

    for (int i = 0; i < soLuongPhim; i++) {
        cout << dsPhim[i].maPhim << " | ";

        string ten = dsPhim[i].tenPhim;
        if (ten.length() > 23) ten = ten.substr(0, 20) + "...";
        cout << ten;
        for (int j = ten.length(); j < 23; j++) cout << " ";
        cout << " | ";

        string loai = dsPhim[i].theLoai;
        if (loai.length() > 15) loai = loai.substr(0, 12) + "...";
        cout << loai;
        for (int j = loai.length(); j < 15; j++) cout << " ";
        cout << " | ";

        cout << dsPhim[i].thoiLuong;
        for (int j = IntToStr(dsPhim[i].thoiLuong).length(); j < 5; j++) cout << " ";
        cout << " | ";

        cout << FloatToStr(dsPhim[i].danhGia, 1) << "/10\n";
    }
}

void ThemLichChieu() {
    cout << "\n========== THEM LICH CHIEU ==========\n";

    HienThiDanhSachPhim();

    LichChieu lichMoi;
    lichMoi.maLich = TaoMaLichMoi();

    cout << "\nMa lich (tu dong): " << lichMoi.maLich << "\n";

    cout << "Nhap ma phim: ";
    cin >> lichMoi.maPhim;

    bool timThay = false;
    for (int i = 0; i < soLuongPhim; i++) {
        if (dsPhim[i].maPhim == lichMoi.maPhim) {
            timThay = true;
            break;
        }
    }

    if (!timThay) {
        cout << "[LOI] Khong tim thay phim!\n";
        return;
    }

    cout << "Nhap so phong (1-" << soLuongPhong << "): ";
    string input;
    cin >> input;
    lichMoi.soPhong = StrToInt(input);

    if (lichMoi.soPhong < 1 || lichMoi.soPhong > soLuongPhong) {
        cout << "[LOI] So phong khong hop le!\n";
        return;
    }

    cout << "Nhap ngay chieu (dd/mm/yyyy): ";
    cin >> lichMoi.ngayChieu;

    cout << "Nhap gio chieu (HH:MM): ";
    cin >> lichMoi.gioChieu;

    LichChieu* temp = new LichChieu[soLuongLich + 1];
    for (int i = 0; i < soLuongLich; i++) {
        temp[i] = dsLichChieu[i];
    }
    temp[soLuongLich] = lichMoi;

    delete[] dsLichChieu;
    dsLichChieu = temp;
    soLuongLich++;

    GhiLichChieu();
    cout << "[THANH CONG] Da them lich chieu!\n";
}

void HienThiLichChieu() {
    cout << "\n========== LICH CHIEU PHIM ==========\n";

    if (soLuongLich == 0) {
        cout << "Chua co lich chieu nao!\n";
        return;
    }

    cout << "Ma Lich | Ma Phim | Ten Phim                | Phong | Ngay       | Gio  \n";
    cout << "--------------------------------------------------------------------------\n";

    for (int i = 0; i < soLuongLich; i++) {
        cout << dsLichChieu[i].maLich << "   | ";
        cout << dsLichChieu[i].maPhim << "   | ";

        string tenPhim = "";
        for (int j = 0; j < soLuongPhim; j++) {
            if (dsPhim[j].maPhim == dsLichChieu[i].maPhim) {
                tenPhim = dsPhim[j].tenPhim;
                break;
            }
        }

        if (tenPhim.length() > 23) tenPhim = tenPhim.substr(0, 20) + "...";
        cout << tenPhim;
        for (int j = tenPhim.length(); j < 23; j++) cout << " ";
        cout << " | ";

        cout << dsLichChieu[i].soPhong << "     | ";
        cout << dsLichChieu[i].ngayChieu << " | ";
        cout << dsLichChieu[i].gioChieu << "\n";
    }
}

string ChuyenSoThanhHangGhe(int soGhe, int soGheMoiHang) {
    int hang = soGhe / soGheMoiHang;
    int ghe = soGhe % soGheMoiHang + 1;

    char hangChar = 'A' + hang;
    return string(1, hangChar) + IntToStr(ghe);
}

int ChuyenHangGheThanhSo(const string& viTri, int soGheMoiHang) {
    if (viTri.length() < 2) return -1;

    char hang = viTri[0];
    if (hang < 'A' || hang > 'Z') return -1;

    int hangNum = hang - 'A';
    int gheNum = StrToInt(viTri.substr(1)) - 1;

    return hangNum * soGheMoiHang + gheNum;
}

void HienThiSoDoGhe(int soPhong, const string& maLich) {
    PhongChieu* phong = NULL;
    for (int i = 0; i < soLuongPhong; i++) {
        if (dsPhongChieu[i].soPhong == soPhong) {
            phong = &dsPhongChieu[i];
            break;
        }
    }

    if (phong == NULL) {
        cout << "[LOI] Khong tim thay phong!\n";
        return;
    }

    cout << "\n========== SO DO GHE PHONG " << soPhong << " ==========\n";
    cout << "                MAN HINH\n";
    cout << "=====================================\n\n";

    for (int hang = 0; hang < phong->soHangGhe; hang++) {
        cout << char('A' + hang) << "  ";

        for (int ghe = 0; ghe < phong->soGheMoiHang; ghe++) {
            int index = hang * phong->soGheMoiHang + ghe;

            if (phong->trangThaiGhe[index] == "Trong") {
                cout << "[_] ";
            } else {
                cout << "[X] ";
            }
        }

        cout << "\n";
    }

    cout << "\n   ";
    for (int i = 1; i <= phong->soGheMoiHang; i++) {
        if (i < 10) cout << " " << i << "  ";
        else cout << i << "  ";
    }
    cout << "\n\n";
    cout << "[_] = Trong    [X] = Da dat\n";
}

void DatVe() {
    cout << "\n========== DAT VE XEM PHIM ==========\n";

    HienThiLichChieu();

    if (soLuongLich == 0) return;

    cout << "\nNhap ma lich chieu: ";
    string maLich;
    cin >> maLich;

    LichChieu* lich = NULL;
    for (int i = 0; i < soLuongLich; i++) {
        if (dsLichChieu[i].maLich == maLich) {
            lich = &dsLichChieu[i];
            break;
        }
    }

    if (lich == NULL) {
        cout << "[LOI] Khong tim thay lich chieu!\n";
        return;
    }

    PhongChieu* phong = NULL;
    for (int i = 0; i < soLuongPhong; i++) {
        if (dsPhongChieu[i].soPhong == lich->soPhong) {
            phong = &dsPhongChieu[i];
            break;
        }
    }

    HienThiSoDoGhe(lich->soPhong, maLich);

    DonHang donMoi;
    donMoi.maDon = TaoMaDonMoi();
    donMoi.ngayDat = lich->ngayChieu;
    donMoi.gioData = lich->gioChieu;

    cout << "\nNhap ho ten khach hang: ";
    cin.ignore();
    getline(cin, donMoi.hoTenKhach);

    cout << "Nhap so dien thoai: ";
    getline(cin, donMoi.sdt);

    cout << "Nhap so luong ve: ";
    string input;
    getline(cin, input);
    donMoi.soVe = StrToInt(input);

    donMoi.danhSachVe = new Ve[donMoi.soVe];

    float tongTienVe = 0;

    for (int i = 0; i < donMoi.soVe; i++) {
        cout << "\n--- Ve " << (i + 1) << " ---\n";

        Ve veMoi;
        veMoi.maVe = donMoi.maDon + "_V" + IntToStr(i + 1);
        veMoi.maLich = maLich;

        cout << "Nhap vi tri ghe (VD: A5, B10): ";
        getline(cin, veMoi.viTriGhe);

        int indexGhe = ChuyenHangGheThanhSo(veMoi.viTriGhe, phong->soGheMoiHang);

        if (indexGhe < 0 || indexGhe >= phong->soHangGhe * phong->soGheMoiHang) {
            cout << "[LOI] Vi tri ghe khong hop le!\n";
            i--;
            continue;
        }

        if (phong->trangThaiGhe[indexGhe] == "DaDat") {
            cout << "[LOI] Ghe da duoc dat!\n";
            i--;
            continue;
        }

        cout << "Chon loai ve:\n";
        cout << "  1. Ve thuong (70000 VND)\n";
        cout << "  2. Ve VIP (120000 VND)\n";
        cout << "  3. Ve hoc sinh (50000 VND)\n";
        cout << "Lua chon: ";
        getline(cin, input);
        int loaiVe = StrToInt(input);

        if (loaiVe == 1) {
            veMoi.loaiVe = "Thuong";
            veMoi.giaVe = 70000;
        } else if (loaiVe == 2) {
            veMoi.loaiVe = "VIP";
            veMoi.giaVe = 120000;
        } else if (loaiVe == 3) {
            veMoi.loaiVe = "HocSinh";
            veMoi.giaVe = 50000;
        } else {
            cout << "[LOI] Lua chon khong hop le!\n";
            i--;
            continue;
        }

        phong->trangThaiGhe[indexGhe] = "DaDat";
        donMoi.danhSachVe[i] = veMoi;
        tongTienVe += veMoi.giaVe;

        cout << "[OK] Dat ghe " << veMoi.viTriGhe << " thanh cong!\n";
    }

    cout << "\n========== BAN COMBO ==========\n";
    cout << "Danh sach combo:\n";
    for (int i = 0; i < soLuongCombo; i++) {
        cout << "  " << (i + 1) << ". " << dsCombo[i].tenCombo
             << " - " << FloatToStr(dsCombo[i].giaCombo, 0) << " VND\n";
    }

    cout << "\nNhap so luong combo (0 neu khong): ";
    getline(cin, input);
    donMoi.soCombo = StrToInt(input);

    float tongTienCombo = 0;

    if (donMoi.soCombo > 0) {
        donMoi.danhSachCombo = new Combo[donMoi.soCombo];

        for (int i = 0; i < donMoi.soCombo; i++) {
            cout << "Chon combo thu " << (i + 1) << " (1-" << soLuongCombo << "): ";
            getline(cin, input);
            int chon = StrToInt(input) - 1;

            if (chon < 0 || chon >= soLuongCombo) {
                cout << "[LOI] Lua chon khong hop le!\n";
                i--;
                continue;
            }

            donMoi.danhSachCombo[i] = dsCombo[chon];
            tongTienCombo += dsCombo[chon].giaCombo;
        }
    } else {
        donMoi.danhSachCombo = NULL;
    }

    donMoi.tongTien = tongTienVe + tongTienCombo;

    cout << "\n========== HOA DON ==========\n";
    cout << "Ma don: " << donMoi.maDon << "\n";
    cout << "Khach hang: " << donMoi.hoTenKhach << "\n";
    cout << "SDT: " << donMoi.sdt << "\n";
    cout << "----------------------------\n";
    cout << "Tong tien ve: " << FloatToStr(tongTienVe, 0) << " VND\n";
    cout << "Tong tien combo: " << FloatToStr(tongTienCombo, 0) << " VND\n";
    cout << "----------------------------\n";
    cout << "TONG CONG: " << FloatToStr(donMoi.tongTien, 0) << " VND\n";
    cout << "============================\n";

    DonHang* temp = new DonHang[soLuongDon + 1];
    for (int i = 0; i < soLuongDon; i++) {
        temp[i] = dsDonHang[i];
    }
    temp[soLuongDon] = donMoi;

    delete[] dsDonHang;
    dsDonHang = temp;
    soLuongDon++;

    cout << "\n[THANH CONG] Dat ve thanh cong!\n";
}

void ThongKeDoanhThu() {
    cout << "\n========== THONG KE DOANH THU ==========\n";

    if (soLuongDon == 0) {
        cout << "Chua co don hang nao!\n";
        return;
    }

    float tongDoanhThu = 0;
    int tongVe = 0;

    for (int i = 0; i < soLuongDon; i++) {
        tongDoanhThu += dsDonHang[i].tongTien;
        tongVe += dsDonHang[i].soVe;
    }

    cout << "Tong so don hang: " << soLuongDon << "\n";
    cout << "Tong so ve ban: " << tongVe << "\n";
    cout << "Tong doanh thu: " << FloatToStr(tongDoanhThu, 0) << " VND\n";
    cout << "Doanh thu trung binh/don: " << FloatToStr(tongDoanhThu / soLuongDon, 0) << " VND\n";
}

// ==================== MENU ====================

void Menu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "   HE THONG QUAN LY RAP CHIEU PHIM\n";
    cout << "========================================\n";
    cout << "1. Quan ly phim\n";
    cout << "   1.1. Them phim moi\n";
    cout << "   1.2. Hien thi danh sach phim\n";
    cout << "2. Quan ly lich chieu\n";
    cout << "   2.1. Them lich chieu\n";
    cout << "   2.2. Hien thi lich chieu\n";
    cout << "3. Dat ve\n";
    cout << "4. Thong ke doanh thu\n";
    cout << "0. Thoat\n";
    cout << "========================================\n";
    cout << "Lua chon: ";
}

// ==================== MAIN ====================

int main() {
    cout << "\n*** Dang khoi tao he thong ***\n";

    DocDanhSachPhim();
    DocDanhSachPhongChieu();
    DocLichChieu();
    DocDanhSachCombo();

    cout << "*** Khoi tao hoan tat ***\n";

    while (true) {
        Menu();

        string luaChon;
        getline(cin, luaChon);

        if (luaChon == "1.1") {
            ThemPhim();
        } else if (luaChon == "1.2") {
            HienThiDanhSachPhim();
        } else if (luaChon == "2.1") {
            ThemLichChieu();
        } else if (luaChon == "2.2") {
            HienThiLichChieu();
        } else if (luaChon == "3") {
            DatVe();
        } else if (luaChon == "4") {
            ThongKeDoanhThu();
        } else if (luaChon == "0") {
            cout << "\nCam on ban da su dung he thong!\n";
            break;
        } else {
            cout << "[LOI] Lua chon khong hop le!\n";
        }
    }

    // Giải phóng bộ nhớ
    delete[] dsPhim;

    for (int i = 0; i < soLuongPhong; i++) {
        delete[] dsPhongChieu[i].trangThaiGhe;
    }
    delete[] dsPhongChieu;

    delete[] dsLichChieu;
    delete[] dsCombo;

    for (int i = 0; i < soLuongDon; i++) {
        delete[] dsDonHang[i].danhSachVe;
        if (dsDonHang[i].danhSachCombo != NULL) {
            delete[] dsDonHang[i].danhSachCombo;
        }
    }
    delete[] dsDonHang;

    return 0;
}
