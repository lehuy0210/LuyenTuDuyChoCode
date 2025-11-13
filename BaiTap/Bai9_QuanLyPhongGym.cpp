/*
===============================================
    BÀI 9: HỆ THỐNG QUẢN LÝ PHÒNG TẬP GYM
===============================================
Mô tả: Quản lý hội viên, gói tập, lớp học, PT
Tính năng:
- Đăng ký hội viên (tên, tuổi, SĐT, email)
- Gói thành viên (1 tháng, 3 tháng, 1 năm, VIP)
- Điểm danh (check-in/check-out)
- Đăng ký lớp học (Yoga, Zumba, Boxing...)
- Đặt lịch Personal Trainer (PT)
- Thuê tủ đồ & khăn
- Thống kê: Doanh thu, lớp học phổ biến, giờ cao điểm
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

// Tính số ngày giữa 2 ngày (đơn giản hóa)
int TinhSoNgay(const string& ngayBatDau, const string& ngayKetThuc) {
    string fields1[3], fields2[3];
    int count;

    string temp = ngayBatDau;
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '/') temp[i] = ',';
    }
    ParseCSV(temp, fields1, count);

    temp = ngayKetThuc;
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '/') temp[i] = ',';
    }
    ParseCSV(temp, fields2, count);

    int ngay1 = StrToInt(fields1[0]);
    int thang1 = StrToInt(fields1[1]);
    int nam1 = StrToInt(fields1[2]);

    int ngay2 = StrToInt(fields2[0]);
    int thang2 = StrToInt(fields2[1]);
    int nam2 = StrToInt(fields2[2]);

    int tongNgay1 = nam1 * 365 + thang1 * 30 + ngay1;
    int tongNgay2 = nam2 * 365 + thang2 * 30 + ngay2;

    return tongNgay2 - tongNgay1;
}

// So sánh ngày (trả về: -1 nếu ngay1 < ngay2, 0 nếu bằng, 1 nếu ngay1 > ngay2)
int SoSanhNgay(const string& ngay1, const string& ngay2) {
    int soNgay = TinhSoNgay(ngay1, ngay2);
    if (soNgay < 0) return 1;
    if (soNgay > 0) return -1;
    return 0;
}

// ==================== STRUCTS ====================

struct GoiTap {
    string maGoi;         // G001, G002...
    string tenGoi;        // "1 Thang", "3 Thang", "1 Nam", "VIP"
    int soThang;          // 1, 3, 12...
    float giaGoi;         // 500000, 1200000, 5000000
    string moTa;          // Mô tả quyền lợi
};

struct HoiVien {
    string maHV;          // HV001, HV002...
    string hoTen;         // "Nguyen Van A"
    int tuoi;             // 25
    string sdt;           // "0912345678"
    string email;         // "a@example.com"
    string maGoi;         // G001 (gói đang sử dụng)
    string ngayDangKy;    // "15/01/2025"
    string ngayHetHan;    // "15/02/2025"
    string trangThai;     // "HoatDong", "HetHan"
};

struct LopHoc {
    string maLop;         // L001, L002...
    string tenLop;        // "Yoga", "Zumba", "Boxing"...
    string giangVien;     // "Tran Thi B"
    string ngayHoc;       // "16/01/2025"
    string gioHoc;        // "06:00", "18:30"...
    int soChoToiDa;       // 20, 30...
    int soCho DaDangKy;   // Số người đã đăng ký
    float phiThamGia;     // 50000, 100000 (nếu có)
};

struct DangKyLop {
    string maDK;          // DKL001
    string maHV;          // HV001
    string maLop;         // L001
    string ngayDangKy;    // "15/01/2025"
    bool daThamGia;       // true/false
};

struct LichPT {
    string maLichPT;      // PT001, PT002...
    string maHV;          // HV001
    string tenPT;         // "Nguyen Van C"
    string ngayTap;       // "16/01/2025"
    string gioTap;        // "07:00"
    int soPhut;           // 60, 90, 120
    float phiPT;          // 300000/buổi
};

struct DiemDanh {
    string maDD;          // DD001
    string maHV;          // HV001
    string ngay;          // "15/01/2025"
    string gioVao;        // "06:30"
    string gioRa;         // "08:00"
};

struct ThueThietBi {
    string maThuê;        // TTB001
    string maHV;          // HV001
    string loaiTB;        // "TuDo", "Khan"
    string ngayThue;      // "15/01/2025"
    int soLuong;          // 1, 2...
    float phiThue;        // 20000, 10000
};

// ==================== GLOBAL DATA ====================

GoiTap* dsGoiTap = NULL;
int soLuongGoi = 0;

HoiVien* dsHoiVien = NULL;
int soLuongHV = 0;

LopHoc* dsLopHoc = NULL;
int soLuongLop = 0;

DangKyLop* dsDangKyLop = NULL;
int soLuongDKLop = 0;

LichPT* dsLichPT = NULL;
int soLuongPT = 0;

DiemDanh* dsDiemDanh = NULL;
int soLuongDD = 0;

ThueThietBi* dsThueThietBi = NULL;
int soLuongThue = 0;

// ==================== FILE OPERATIONS ====================

void DocGoiTap() {
    ifstream file("GoiTap.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file GoiTap.txt\n";
        return;
    }

    string line;
    getline(file, line);

    soLuongGoi = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        soLuongGoi++;
    }

    file.clear();
    file.seekg(0);
    getline(file, line);

    dsGoiTap = new GoiTap[soLuongGoi];
    int index = 0;

    while (getline(file, line) && index < soLuongGoi) {
        if (line.empty()) continue;

        string fields[10];
        int count;
        ParseCSV(line, fields, count);

        if (count >= 5) {
            dsGoiTap[index].maGoi = fields[0];
            dsGoiTap[index].tenGoi = fields[1];
            dsGoiTap[index].soThang = StrToInt(fields[2]);
            dsGoiTap[index].giaGoi = StrToFloat(fields[3]);
            dsGoiTap[index].moTa = fields[4];
            index++;
        }
    }

    soLuongGoi = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongGoi << " goi tap\n";
}

void DocHoiVien() {
    ifstream file("DanhSachHoiVien.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file DanhSachHoiVien.txt\n";
        return;
    }

    string line;
    getline(file, line);

    soLuongHV = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        soLuongHV++;
    }

    file.clear();
    file.seekg(0);
    getline(file, line);

    dsHoiVien = new HoiVien[soLuongHV];
    int index = 0;

    while (getline(file, line) && index < soLuongHV) {
        if (line.empty()) continue;

        string fields[10];
        int count;
        ParseCSV(line, fields, count);

        if (count >= 9) {
            dsHoiVien[index].maHV = fields[0];
            dsHoiVien[index].hoTen = fields[1];
            dsHoiVien[index].tuoi = StrToInt(fields[2]);
            dsHoiVien[index].sdt = fields[3];
            dsHoiVien[index].email = fields[4];
            dsHoiVien[index].maGoi = fields[5];
            dsHoiVien[index].ngayDangKy = fields[6];
            dsHoiVien[index].ngayHetHan = fields[7];
            dsHoiVien[index].trangThai = fields[8];
            index++;
        }
    }

    soLuongHV = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongHV << " hoi vien\n";
}

void GhiHoiVien() {
    ofstream file("DanhSachHoiVien.txt");
    if (!file.is_open()) {
        cout << "[LOI] Khong the ghi file DanhSachHoiVien.txt\n";
        return;
    }

    file << "MaHV,HoTen,Tuoi,SDT,Email,MaGoi,NgayDangKy,NgayHetHan,TrangThai\n";

    for (int i = 0; i < soLuongHV; i++) {
        file << dsHoiVien[i].maHV << ","
             << dsHoiVien[i].hoTen << ","
             << dsHoiVien[i].tuoi << ","
             << dsHoiVien[i].sdt << ","
             << dsHoiVien[i].email << ","
             << dsHoiVien[i].maGoi << ","
             << dsHoiVien[i].ngayDangKy << ","
             << dsHoiVien[i].ngayHetHan << ","
             << dsHoiVien[i].trangThai << "\n";
    }

    file.close();
}

void DocLopHoc() {
    ifstream file("LopHoc.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file LopHoc.txt\n";
        return;
    }

    string line;
    getline(file, line);

    soLuongLop = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        soLuongLop++;
    }

    file.clear();
    file.seekg(0);
    getline(file, line);

    dsLopHoc = new LopHoc[soLuongLop];
    int index = 0;

    while (getline(file, line) && index < soLuongLop) {
        if (line.empty()) continue;

        string fields[10];
        int count;
        ParseCSV(line, fields, count);

        if (count >= 8) {
            dsLopHoc[index].maLop = fields[0];
            dsLopHoc[index].tenLop = fields[1];
            dsLopHoc[index].giangVien = fields[2];
            dsLopHoc[index].ngayHoc = fields[3];
            dsLopHoc[index].gioHoc = fields[4];
            dsLopHoc[index].soChoToiDa = StrToInt(fields[5]);
            dsLopHoc[index].soChoDaDangKy = StrToInt(fields[6]);
            dsLopHoc[index].phiThamGia = StrToFloat(fields[7]);
            index++;
        }
    }

    soLuongLop = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongLop << " lop hoc\n";
}

void GhiLopHoc() {
    ofstream file("LopHoc.txt");
    if (!file.is_open()) {
        cout << "[LOI] Khong the ghi file LopHoc.txt\n";
        return;
    }

    file << "MaLop,TenLop,GiangVien,NgayHoc,GioHoc,SoChoToiDa,SoChoDaDangKy,PhiThamGia\n";

    for (int i = 0; i < soLuongLop; i++) {
        file << dsLopHoc[i].maLop << ","
             << dsLopHoc[i].tenLop << ","
             << dsLopHoc[i].giangVien << ","
             << dsLopHoc[i].ngayHoc << ","
             << dsLopHoc[i].gioHoc << ","
             << dsLopHoc[i].soChoToiDa << ","
             << dsLopHoc[i].soChoDaDangKy << ","
             << FloatToStr(dsLopHoc[i].phiThamGia, 0) << "\n";
    }

    file.close();
}

// ==================== BUSINESS LOGIC ====================

string TaoMaHVMoi() {
    int maxNum = 0;
    for (int i = 0; i < soLuongHV; i++) {
        if (dsHoiVien[i].maHV.length() >= 4 && dsHoiVien[i].maHV[0] == 'H') {
            string numStr = dsHoiVien[i].maHV.substr(2);
            int num = StrToInt(numStr);
            if (num > maxNum) maxNum = num;
        }
    }

    string ma = "HV";
    int newNum = maxNum + 1;

    if (newNum < 10) ma += "00";
    else if (newNum < 100) ma += "0";

    ma += IntToStr(newNum);
    return ma;
}

string TaoMaDKLopMoi() {
    int maxNum = 0;
    for (int i = 0; i < soLuongDKLop; i++) {
        if (dsDangKyLop[i].maDK.length() >= 5) {
            string numStr = dsDangKyLop[i].maDK.substr(3);
            int num = StrToInt(numStr);
            if (num > maxNum) maxNum = num;
        }
    }

    string ma = "DKL";
    int newNum = maxNum + 1;

    if (newNum < 10) ma += "00";
    else if (newNum < 100) ma += "0";

    ma += IntToStr(newNum);
    return ma;
}

string TaoMaPTMoi() {
    int maxNum = 0;
    for (int i = 0; i < soLuongPT; i++) {
        if (dsLichPT[i].maLichPT.length() >= 4) {
            string numStr = dsLichPT[i].maLichPT.substr(2);
            int num = StrToInt(numStr);
            if (num > maxNum) maxNum = num;
        }
    }

    string ma = "PT";
    int newNum = maxNum + 1;

    if (newNum < 10) ma += "00";
    else if (newNum < 100) ma += "0";

    ma += IntToStr(newNum);
    return ma;
}

// Tính ngày hết hạn dựa trên ngày đăng ký và số tháng
string TinhNgayHetHan(const string& ngayDangKy, int soThang) {
    string fields[3];
    int count;

    string temp = ngayDangKy;
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '/') temp[i] = ',';
    }
    ParseCSV(temp, fields, count);

    int ngay = StrToInt(fields[0]);
    int thang = StrToInt(fields[1]);
    int nam = StrToInt(fields[2]);

    thang += soThang;

    while (thang > 12) {
        thang -= 12;
        nam++;
    }

    string result = "";
    if (ngay < 10) result += "0";
    result += IntToStr(ngay) + "/";
    if (thang < 10) result += "0";
    result += IntToStr(thang) + "/";
    result += IntToStr(nam);

    return result;
}

void HienThiGoiTap() {
    cout << "\n========== GOI TAP CO SAN ==========\n";

    for (int i = 0; i < soLuongGoi; i++) {
        cout << (i + 1) << ". " << dsGoiTap[i].tenGoi << " - "
             << FloatToStr(dsGoiTap[i].giaGoi, 0) << " VND\n";
        cout << "   " << dsGoiTap[i].moTa << "\n\n";
    }
}

void DangKyHoiVien() {
    cout << "\n========== DANG KY HOI VIEN MOI ==========\n";

    HoiVien hvMoi;
    hvMoi.maHV = TaoMaHVMoi();

    cout << "Ma hoi vien (tu dong): " << hvMoi.maHV << "\n";

    cout << "Nhap ho ten: ";
    cin.ignore();
    getline(cin, hvMoi.hoTen);

    cout << "Nhap tuoi: ";
    string input;
    getline(cin, input);
    hvMoi.tuoi = StrToInt(input);

    cout << "Nhap so dien thoai: ";
    getline(cin, hvMoi.sdt);

    cout << "Nhap email: ";
    getline(cin, hvMoi.email);

    cout << "Nhap ngay dang ky (dd/mm/yyyy): ";
    getline(cin, hvMoi.ngayDangKy);

    HienThiGoiTap();

    cout << "Chon goi tap (1-" << soLuongGoi << "): ";
    getline(cin, input);
    int chon = StrToInt(input) - 1;

    if (chon < 0 || chon >= soLuongGoi) {
        cout << "[LOI] Lua chon khong hop le!\n";
        return;
    }

    hvMoi.maGoi = dsGoiTap[chon].maGoi;
    hvMoi.ngayHetHan = TinhNgayHetHan(hvMoi.ngayDangKy, dsGoiTap[chon].soThang);
    hvMoi.trangThai = "HoatDong";

    cout << "\n========== THONG TIN DANG KY ==========\n";
    cout << "Ma hoi vien: " << hvMoi.maHV << "\n";
    cout << "Ho ten: " << hvMoi.hoTen << "\n";
    cout << "Goi tap: " << dsGoiTap[chon].tenGoi << "\n";
    cout << "Gia: " << FloatToStr(dsGoiTap[chon].giaGoi, 0) << " VND\n";
    cout << "Ngay dang ky: " << hvMoi.ngayDangKy << "\n";
    cout << "Ngay het han: " << hvMoi.ngayHetHan << "\n";
    cout << "=======================================\n";

    HoiVien* temp = new HoiVien[soLuongHV + 1];
    for (int i = 0; i < soLuongHV; i++) {
        temp[i] = dsHoiVien[i];
    }
    temp[soLuongHV] = hvMoi;

    delete[] dsHoiVien;
    dsHoiVien = temp;
    soLuongHV++;

    GhiHoiVien();
    cout << "[THANH CONG] Dang ky hoi vien thanh cong!\n";
}

void HienThiDanhSachHoiVien() {
    cout << "\n========== DANH SACH HOI VIEN ==========\n";

    if (soLuongHV == 0) {
        cout << "Chua co hoi vien nao!\n";
        return;
    }

    cout << "Ma    | Ho Ten                | Tuoi | Goi Tap   | Het Han    | Trang Thai\n";
    cout << "---------------------------------------------------------------------------------\n";

    for (int i = 0; i < soLuongHV; i++) {
        cout << dsHoiVien[i].maHV << " | ";

        string ten = dsHoiVien[i].hoTen;
        if (ten.length() > 21) ten = ten.substr(0, 18) + "...";
        cout << ten;
        for (int j = ten.length(); j < 21; j++) cout << " ";
        cout << " | ";

        cout << dsHoiVien[i].tuoi;
        for (int j = IntToStr(dsHoiVien[i].tuoi).length(); j < 4; j++) cout << " ";
        cout << " | ";

        string tenGoi = "";
        for (int j = 0; j < soLuongGoi; j++) {
            if (dsGoiTap[j].maGoi == dsHoiVien[i].maGoi) {
                tenGoi = dsGoiTap[j].tenGoi;
                break;
            }
        }
        if (tenGoi.length() > 9) tenGoi = tenGoi.substr(0, 6) + "...";
        cout << tenGoi;
        for (int j = tenGoi.length(); j < 9; j++) cout << " ";
        cout << " | ";

        cout << dsHoiVien[i].ngayHetHan << " | ";
        cout << dsHoiVien[i].trangThai << "\n";
    }
}

void HienThiLopHoc() {
    cout << "\n========== LICH LOP HOC ==========\n";

    if (soLuongLop == 0) {
        cout << "Chua co lop hoc nao!\n";
        return;
    }

    for (int i = 0; i < soLuongLop; i++) {
        cout << (i + 1) << ". " << dsLopHoc[i].tenLop << "\n";
        cout << "   GV: " << dsLopHoc[i].giangVien << "\n";
        cout << "   Ngay: " << dsLopHoc[i].ngayHoc << " - Gio: " << dsLopHoc[i].gioHoc << "\n";
        cout << "   So cho: " << dsLopHoc[i].soChoDaDangKy << "/" << dsLopHoc[i].soChoToiDa << "\n";
        cout << "   Phi: " << FloatToStr(dsLopHoc[i].phiThamGia, 0) << " VND\n\n";
    }
}

void DangKyLopHoc() {
    cout << "\n========== DANG KY LOP HOC ==========\n";

    cout << "Nhap ma hoi vien: ";
    string maHV;
    cin >> maHV;

    bool timThayHV = false;
    for (int i = 0; i < soLuongHV; i++) {
        if (dsHoiVien[i].maHV == maHV) {
            if (dsHoiVien[i].trangThai != "HoatDong") {
                cout << "[LOI] Hoi vien da het han! Vui long gia han goi tap.\n";
                return;
            }
            timThayHV = true;
            break;
        }
    }

    if (!timThayHV) {
        cout << "[LOI] Khong tim thay hoi vien!\n";
        return;
    }

    HienThiLopHoc();

    cout << "Chon lop hoc (1-" << soLuongLop << "): ";
    string input;
    cin >> input;
    int chon = StrToInt(input) - 1;

    if (chon < 0 || chon >= soLuongLop) {
        cout << "[LOI] Lua chon khong hop le!\n";
        return;
    }

    if (dsLopHoc[chon].soChoDaDangKy >= dsLopHoc[chon].soChoToiDa) {
        cout << "[LOI] Lop hoc da day!\n";
        return;
    }

    // Kiểm tra đã đăng ký chưa
    for (int i = 0; i < soLuongDKLop; i++) {
        if (dsDangKyLop[i].maHV == maHV && dsDangKyLop[i].maLop == dsLopHoc[chon].maLop) {
            cout << "[LOI] Ban da dang ky lop hoc nay roi!\n";
            return;
        }
    }

    DangKyLop dkMoi;
    dkMoi.maDK = TaoMaDKLopMoi();
    dkMoi.maHV = maHV;
    dkMoi.maLop = dsLopHoc[chon].maLop;
    dkMoi.ngayDangKy = dsLopHoc[chon].ngayHoc;
    dkMoi.daThamGia = false;

    DangKyLop* temp = new DangKyLop[soLuongDKLop + 1];
    for (int i = 0; i < soLuongDKLop; i++) {
        temp[i] = dsDangKyLop[i];
    }
    temp[soLuongDKLop] = dkMoi;

    delete[] dsDangKyLop;
    dsDangKyLop = temp;
    soLuongDKLop++;

    dsLopHoc[chon].soChoDaDangKy++;
    GhiLopHoc();

    cout << "[THANH CONG] Dang ky lop hoc thanh cong!\n";
    cout << "Lop: " << dsLopHoc[chon].tenLop << "\n";
    cout << "Ngay: " << dsLopHoc[chon].ngayHoc << " - Gio: " << dsLopHoc[chon].gioHoc << "\n";
}

void DatLichPT() {
    cout << "\n========== DAT LICH PERSONAL TRAINER ==========\n";

    cout << "Nhap ma hoi vien: ";
    string maHV;
    cin >> maHV;

    bool timThayHV = false;
    for (int i = 0; i < soLuongHV; i++) {
        if (dsHoiVien[i].maHV == maHV) {
            if (dsHoiVien[i].trangThai != "HoatDong") {
                cout << "[LOI] Hoi vien da het han!\n";
                return;
            }
            timThayHV = true;
            break;
        }
    }

    if (!timThayHV) {
        cout << "[LOI] Khong tim thay hoi vien!\n";
        return;
    }

    LichPT ptMoi;
    ptMoi.maLichPT = TaoMaPTMoi();
    ptMoi.maHV = maHV;

    cout << "Nhap ten PT: ";
    cin.ignore();
    getline(cin, ptMoi.tenPT);

    cout << "Nhap ngay tap (dd/mm/yyyy): ";
    getline(cin, ptMoi.ngayTap);

    cout << "Nhap gio tap (HH:MM): ";
    getline(cin, ptMoi.gioTap);

    cout << "Nhap so phut (60, 90, 120): ";
    string input;
    getline(cin, input);
    ptMoi.soPhut = StrToInt(input);

    // Giá PT: 5000 VND/phút
    ptMoi.phiPT = ptMoi.soPhut * 5000;

    cout << "\n========== THONG TIN DAT LICH PT ==========\n";
    cout << "Ma lich: " << ptMoi.maLichPT << "\n";
    cout << "PT: " << ptMoi.tenPT << "\n";
    cout << "Ngay: " << ptMoi.ngayTap << " - Gio: " << ptMoi.gioTap << "\n";
    cout << "Thoi luong: " << ptMoi.soPhut << " phut\n";
    cout << "Phi: " << FloatToStr(ptMoi.phiPT, 0) << " VND\n";
    cout << "==========================================\n";

    LichPT* temp = new LichPT[soLuongPT + 1];
    for (int i = 0; i < soLuongPT; i++) {
        temp[i] = dsLichPT[i];
    }
    temp[soLuongPT] = ptMoi;

    delete[] dsLichPT;
    dsLichPT = temp;
    soLuongPT++;

    cout << "[THANH CONG] Dat lich PT thanh cong!\n";
}

void ThongKeDoanhThu() {
    cout << "\n========== THONG KE DOANH THU ==========\n";

    float tongDoanhThuGoiTap = 0;
    for (int i = 0; i < soLuongHV; i++) {
        for (int j = 0; j < soLuongGoi; j++) {
            if (dsHoiVien[i].maGoi == dsGoiTap[j].maGoi) {
                tongDoanhThuGoiTap += dsGoiTap[j].giaGoi;
                break;
            }
        }
    }

    float tongDoanhThuLop = 0;
    for (int i = 0; i < soLuongDKLop; i++) {
        for (int j = 0; j < soLuongLop; j++) {
            if (dsDangKyLop[i].maLop == dsLopHoc[j].maLop) {
                tongDoanhThuLop += dsLopHoc[j].phiThamGia;
                break;
            }
        }
    }

    float tongDoanhThuPT = 0;
    for (int i = 0; i < soLuongPT; i++) {
        tongDoanhThuPT += dsLichPT[i].phiPT;
    }

    float tongDoanhThu = tongDoanhThuGoiTap + tongDoanhThuLop + tongDoanhThuPT;

    cout << "Tong so hoi vien: " << soLuongHV << "\n";
    cout << "Doanh thu goi tap: " << FloatToStr(tongDoanhThuGoiTap, 0) << " VND\n";
    cout << "Doanh thu lop hoc: " << FloatToStr(tongDoanhThuLop, 0) << " VND\n";
    cout << "Doanh thu PT: " << FloatToStr(tongDoanhThuPT, 0) << " VND\n";
    cout << "---------------------------------------\n";
    cout << "TONG DOANH THU: " << FloatToStr(tongDoanhThu, 0) << " VND\n";
}

// ==================== MENU ====================

void Menu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "   HE THONG QUAN LY PHONG TAP GYM\n";
    cout << "========================================\n";
    cout << "1. Quan ly hoi vien\n";
    cout << "   1.1. Dang ky hoi vien moi\n";
    cout << "   1.2. Hien thi danh sach hoi vien\n";
    cout << "2. Quan ly lop hoc\n";
    cout << "   2.1. Hien thi lich lop hoc\n";
    cout << "   2.2. Dang ky lop hoc\n";
    cout << "3. Dat lich Personal Trainer\n";
    cout << "4. Thong ke doanh thu\n";
    cout << "0. Thoat\n";
    cout << "========================================\n";
    cout << "Lua chon: ";
}

// ==================== MAIN ====================

int main() {
    cout << "\n*** Dang khoi tao he thong ***\n";

    DocGoiTap();
    DocHoiVien();
    DocLopHoc();

    cout << "*** Khoi tao hoan tat ***\n";

    while (true) {
        Menu();

        string luaChon;
        getline(cin, luaChon);

        if (luaChon == "1.1") {
            DangKyHoiVien();
        } else if (luaChon == "1.2") {
            HienThiDanhSachHoiVien();
        } else if (luaChon == "2.1") {
            HienThiLopHoc();
        } else if (luaChon == "2.2") {
            DangKyLopHoc();
        } else if (luaChon == "3") {
            DatLichPT();
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
    delete[] dsGoiTap;
    delete[] dsHoiVien;
    delete[] dsLopHoc;
    delete[] dsDangKyLop;
    delete[] dsLichPT;
    delete[] dsDiemDanh;
    delete[] dsThueThietBi;

    return 0;
}
