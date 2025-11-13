/*
===============================================
    BÀI 13: HỆ THỐNG QUẢN LÝ TRƯỜNG HỌC
===============================================
Mô tả: Quản lý học sinh, lớp, điểm, học phí
Tính năng:
- Quản lý học sinh (mã HS, tên, ngày sinh, lớp)
- Quản lý lớp học (mã lớp, tên lớp, sĩ số)
- Nhập điểm (toán, văn, anh, lý, hóa)
- Tính điểm TB, xếp loại (Giỏi/Khá/TB/Yếu)
- Học phí (theo học kỳ, miễn giảm cho HS giỏi)
- Thống kê: Điểm TB lớp, số HS giỏi/khá/TB/yếu
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

string Trim(const string& str) {
    int start = 0;
    int end = str.length() - 1;
    while (start <= end && (str[start] == ' ' || str[start] == '\t')) start++;
    while (end >= start && (str[end] == ' ' || str[end] == '\t')) end--;
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

struct LopHoc {
    string maLop;         // L10A1, L10A2...
    string tenLop;        // "10A1", "10A2"
    int siSo;             // 40
};

struct HocSinh {
    string maHS;          // HS001, HS002...
    string hoTen;         // "Nguyen Van A"
    string ngaySinh;      // "15/01/2010"
    string maLop;         // L10A1
    float diemToan;       // 8.5
    float diemVan;        // 7.0
    float diemAnh;        // 9.0
    float diemLy;         // 8.0
    float diemHoa;        // 7.5
    float diemTB;         // Điểm trung bình
    string xepLoai;       // "Gioi", "Kha", "TrungBinh", "Yeu"
};

struct HocPhi {
    string maHP;          // HP001
    string maHS;          // HS001
    string hocKy;         // "HK1_2024-2025"
    float hocPhiGoc;      // 3000000
    float mienGiam;       // 500000 (miễn giảm)
    float daThanhToan;    // 2500000
    string trangThai;     // "DaThanhToan", "ChuaThanhToan"
};

// ==================== GLOBAL DATA ====================

LopHoc* dsLopHoc = NULL;
int soLuongLop = 0;

HocSinh* dsHocSinh = NULL;
int soLuongHS = 0;

HocPhi* dsHocPhi = NULL;
int soLuongHP = 0;

// ==================== FILE OPERATIONS ====================

void DocLopHoc() {
    ifstream file("DanhSachLopHoc.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file DanhSachLopHoc.txt\n";
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
        if (count >= 3) {
            dsLopHoc[index].maLop = fields[0];
            dsLopHoc[index].tenLop = fields[1];
            dsLopHoc[index].siSo = StrToInt(fields[2]);
            index++;
        }
    }
    soLuongLop = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongLop << " lop hoc\n";
}

void DocHocSinh() {
    ifstream file("DanhSachHocSinh.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file DanhSachHocSinh.txt\n";
        return;
    }
    string line;
    getline(file, line);
    soLuongHS = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        soLuongHS++;
    }
    file.clear();
    file.seekg(0);
    getline(file, line);
    dsHocSinh = new HocSinh[soLuongHS];
    int index = 0;
    while (getline(file, line) && index < soLuongHS) {
        if (line.empty()) continue;
        string fields[15];
        int count;
        ParseCSV(line, fields, count);
        if (count >= 10) {
            dsHocSinh[index].maHS = fields[0];
            dsHocSinh[index].hoTen = fields[1];
            dsHocSinh[index].ngaySinh = fields[2];
            dsHocSinh[index].maLop = fields[3];
            dsHocSinh[index].diemToan = StrToFloat(fields[4]);
            dsHocSinh[index].diemVan = StrToFloat(fields[5]);
            dsHocSinh[index].diemAnh = StrToFloat(fields[6]);
            dsHocSinh[index].diemLy = StrToFloat(fields[7]);
            dsHocSinh[index].diemHoa = StrToFloat(fields[8]);
            dsHocSinh[index].diemTB = StrToFloat(fields[9]);
            if (count >= 11) {
                dsHocSinh[index].xepLoai = fields[10];
            }
            index++;
        }
    }
    soLuongHS = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongHS << " hoc sinh\n";
}

void GhiHocSinh() {
    ofstream file("DanhSachHocSinh.txt");
    if (!file.is_open()) {
        cout << "[LOI] Khong the ghi file DanhSachHocSinh.txt\n";
        return;
    }
    file << "MaHS,HoTen,NgaySinh,MaLop,DiemToan,DiemVan,DiemAnh,DiemLy,DiemHoa,DiemTB,XepLoai\n";
    for (int i = 0; i < soLuongHS; i++) {
        file << dsHocSinh[i].maHS << ","
             << dsHocSinh[i].hoTen << ","
             << dsHocSinh[i].ngaySinh << ","
             << dsHocSinh[i].maLop << ","
             << FloatToStr(dsHocSinh[i].diemToan, 1) << ","
             << FloatToStr(dsHocSinh[i].diemVan, 1) << ","
             << FloatToStr(dsHocSinh[i].diemAnh, 1) << ","
             << FloatToStr(dsHocSinh[i].diemLy, 1) << ","
             << FloatToStr(dsHocSinh[i].diemHoa, 1) << ","
             << FloatToStr(dsHocSinh[i].diemTB, 1) << ","
             << dsHocSinh[i].xepLoai << "\n";
    }
    file.close();
}

// ==================== BUSINESS LOGIC ====================

string TaoMaHSMoi() {
    int maxNum = 0;
    for (int i = 0; i < soLuongHS; i++) {
        if (dsHocSinh[i].maHS.length() >= 4 && dsHocSinh[i].maHS[0] == 'H') {
            string numStr = dsHocSinh[i].maHS.substr(2);
            int num = StrToInt(numStr);
            if (num > maxNum) maxNum = num;
        }
    }
    string ma = "HS";
    int newNum = maxNum + 1;
    if (newNum < 10) ma += "000";
    else if (newNum < 100) ma += "00";
    else if (newNum < 1000) ma += "0";
    ma += IntToStr(newNum);
    return ma;
}

HocSinh* TimHocSinh(const string& maHS) {
    for (int i = 0; i < soLuongHS; i++) {
        if (dsHocSinh[i].maHS == maHS) {
            return &dsHocSinh[i];
        }
    }
    return NULL;
}

void TinhDiemTBVaXepLoai(HocSinh& hs) {
    hs.diemTB = (hs.diemToan + hs.diemVan + hs.diemAnh + hs.diemLy + hs.diemHoa) / 5.0;

    if (hs.diemTB >= 8.0) {
        hs.xepLoai = "Gioi";
    } else if (hs.diemTB >= 6.5) {
        hs.xepLoai = "Kha";
    } else if (hs.diemTB >= 5.0) {
        hs.xepLoai = "TrungBinh";
    } else {
        hs.xepLoai = "Yeu";
    }
}

void ThemHocSinh() {
    cout << "\n========== THEM HOC SINH MOI ==========\n";

    HocSinh hsMoi;
    hsMoi.maHS = TaoMaHSMoi();

    cout << "Ma HS (tu dong): " << hsMoi.maHS << "\n";

    cout << "Nhap ho ten: ";
    cin.ignore();
    getline(cin, hsMoi.hoTen);

    cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    getline(cin, hsMoi.ngaySinh);

    cout << "\nDanh sach lop:\n";
    for (int i = 0; i < soLuongLop; i++) {
        cout << (i + 1) << ". " << dsLopHoc[i].tenLop << "\n";
    }

    cout << "Chon lop (1-" << soLuongLop << "): ";
    string input;
    getline(cin, input);
    int chon = StrToInt(input) - 1;

    if (chon < 0 || chon >= soLuongLop) {
        cout << "[LOI] Lua chon khong hop le!\n";
        return;
    }

    hsMoi.maLop = dsLopHoc[chon].maLop;

    // Khởi tạo điểm = 0
    hsMoi.diemToan = 0;
    hsMoi.diemVan = 0;
    hsMoi.diemAnh = 0;
    hsMoi.diemLy = 0;
    hsMoi.diemHoa = 0;
    hsMoi.diemTB = 0;
    hsMoi.xepLoai = "ChuaNhap";

    cout << "\n[THANH CONG] Da them hoc sinh!\n";
    cout << "Ma HS: " << hsMoi.maHS << "\n";
    cout << "Ho ten: " << hsMoi.hoTen << "\n";
    cout << "Lop: " << dsLopHoc[chon].tenLop << "\n";

    HocSinh* temp = new HocSinh[soLuongHS + 1];
    for (int i = 0; i < soLuongHS; i++) {
        temp[i] = dsHocSinh[i];
    }
    temp[soLuongHS] = hsMoi;
    delete[] dsHocSinh;
    dsHocSinh = temp;
    soLuongHS++;

    GhiHocSinh();
}

void NhapDiem() {
    cout << "\n========== NHAP DIEM HOC SINH ==========\n";

    cout << "Nhap ma hoc sinh: ";
    string maHS;
    cin >> maHS;

    HocSinh* hs = TimHocSinh(maHS);
    if (hs == NULL) {
        cout << "[LOI] Khong tim thay hoc sinh!\n";
        return;
    }

    cout << "\nHoc sinh: " << hs->hoTen << " (" << hs->maHS << ")\n";

    cout << "Nhap diem Toan (0-10): ";
    string input;
    cin >> input;
    hs->diemToan = StrToFloat(input);

    cout << "Nhap diem Van (0-10): ";
    cin >> input;
    hs->diemVan = StrToFloat(input);

    cout << "Nhap diem Anh (0-10): ";
    cin >> input;
    hs->diemAnh = StrToFloat(input);

    cout << "Nhap diem Ly (0-10): ";
    cin >> input;
    hs->diemLy = StrToFloat(input);

    cout << "Nhap diem Hoa (0-10): ";
    cin >> input;
    hs->diemHoa = StrToFloat(input);

    TinhDiemTBVaXepLoai(*hs);

    cout << "\n[THANH CONG] Da nhap diem!\n";
    cout << "Diem TB: " << FloatToStr(hs->diemTB, 2) << "\n";
    cout << "Xep loai: " << hs->xepLoai << "\n";

    GhiHocSinh();
}

void HienThiDanhSachHocSinh() {
    cout << "\n========== DANH SACH HOC SINH ==========\n";

    if (soLuongHS == 0) {
        cout << "Chua co hoc sinh nao!\n";
        return;
    }

    cout << "Ma     | Ho Ten                | Lop   | Diem TB | Xep Loai\n";
    cout << "-------------------------------------------------------------------\n";

    for (int i = 0; i < soLuongHS; i++) {
        cout << dsHocSinh[i].maHS << " | ";

        string ten = dsHocSinh[i].hoTen;
        if (ten.length() > 21) ten = ten.substr(0, 18) + "...";
        cout << ten;
        for (int j = ten.length(); j < 21; j++) cout << " ";
        cout << " | ";

        string tenLop = "";
        for (int j = 0; j < soLuongLop; j++) {
            if (dsLopHoc[j].maLop == dsHocSinh[i].maLop) {
                tenLop = dsLopHoc[j].tenLop;
                break;
            }
        }
        cout << tenLop;
        for (int j = tenLop.length(); j < 5; j++) cout << " ";
        cout << " | ";

        cout << FloatToStr(dsHocSinh[i].diemTB, 2);
        for (int j = FloatToStr(dsHocSinh[i].diemTB, 2).length(); j < 7; j++) cout << " ";
        cout << " | ";

        cout << dsHocSinh[i].xepLoai << "\n";
    }
}

void XemBangDiem() {
    cout << "\n========== BANG DIEM HOC SINH ==========\n";

    cout << "Nhap ma hoc sinh: ";
    string maHS;
    cin >> maHS;

    HocSinh* hs = TimHocSinh(maHS);
    if (hs == NULL) {
        cout << "[LOI] Khong tim thay hoc sinh!\n";
        return;
    }

    cout << "\n========== BANG DIEM ==========\n";
    cout << "Ma HS: " << hs->maHS << "\n";
    cout << "Ho ten: " << hs->hoTen << "\n";
    cout << "Ngay sinh: " << hs->ngaySinh << "\n";

    string tenLop = "";
    for (int i = 0; i < soLuongLop; i++) {
        if (dsLopHoc[i].maLop == hs->maLop) {
            tenLop = dsLopHoc[i].tenLop;
            break;
        }
    }
    cout << "Lop: " << tenLop << "\n";
    cout << "----------------------------\n";
    cout << "Toan: " << FloatToStr(hs->diemToan, 1) << "\n";
    cout << "Van:  " << FloatToStr(hs->diemVan, 1) << "\n";
    cout << "Anh:  " << FloatToStr(hs->diemAnh, 1) << "\n";
    cout << "Ly:   " << FloatToStr(hs->diemLy, 1) << "\n";
    cout << "Hoa:  " << FloatToStr(hs->diemHoa, 1) << "\n";
    cout << "----------------------------\n";
    cout << "DIEM TB: " << FloatToStr(hs->diemTB, 2) << "\n";
    cout << "XEP LOAI: " << hs->xepLoai << "\n";
    cout << "===============================\n";
}

void ThongKeLop() {
    cout << "\n========== THONG KE THEO LOP ==========\n";

    cout << "Chon lop:\n";
    for (int i = 0; i < soLuongLop; i++) {
        cout << (i + 1) << ". " << dsLopHoc[i].tenLop << "\n";
    }

    cout << "Lua chon: ";
    string input;
    getline(cin, input);
    int chon = StrToInt(input) - 1;

    if (chon < 0 || chon >= soLuongLop) {
        cout << "[LOI] Lua chon khong hop le!\n";
        return;
    }

    string maLop = dsLopHoc[chon].maLop;

    int soGioi = 0, soKha = 0, soTB = 0, soYeu = 0;
    float tongDiemTB = 0;
    int soHSLop = 0;

    for (int i = 0; i < soLuongHS; i++) {
        if (dsHocSinh[i].maLop == maLop) {
            soHSLop++;
            tongDiemTB += dsHocSinh[i].diemTB;

            if (dsHocSinh[i].xepLoai == "Gioi") soGioi++;
            else if (dsHocSinh[i].xepLoai == "Kha") soKha++;
            else if (dsHocSinh[i].xepLoai == "TrungBinh") soTB++;
            else if (dsHocSinh[i].xepLoai == "Yeu") soYeu++;
        }
    }

    cout << "\n========== THONG KE LOP " << dsLopHoc[chon].tenLop << " ==========\n";
    cout << "Tong so HS: " << soHSLop << "\n";
    if (soHSLop > 0) {
        cout << "Diem TB lop: " << FloatToStr(tongDiemTB / soHSLop, 2) << "\n";
    }
    cout << "----------------------------\n";
    cout << "So HS Gioi: " << soGioi << "\n";
    cout << "So HS Kha: " << soKha << "\n";
    cout << "So HS Trung binh: " << soTB << "\n";
    cout << "So HS Yeu: " << soYeu << "\n";
}

// ==================== MENU ====================

void Menu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "   HE THONG QUAN LY TRUONG HOC\n";
    cout << "========================================\n";
    cout << "1. Them hoc sinh moi\n";
    cout << "2. Hien thi danh sach hoc sinh\n";
    cout << "3. Nhap diem\n";
    cout << "4. Xem bang diem\n";
    cout << "5. Thong ke theo lop\n";
    cout << "0. Thoat\n";
    cout << "========================================\n";
    cout << "Lua chon: ";
}

// ==================== MAIN ====================

int main() {
    cout << "\n*** Dang khoi tao he thong ***\n";

    DocLopHoc();
    DocHocSinh();

    cout << "*** Khoi tao hoan tat ***\n";

    while (true) {
        Menu();

        string luaChon;
        getline(cin, luaChon);

        if (luaChon == "1") {
            ThemHocSinh();
        } else if (luaChon == "2") {
            HienThiDanhSachHocSinh();
        } else if (luaChon == "3") {
            NhapDiem();
        } else if (luaChon == "4") {
            XemBangDiem();
        } else if (luaChon == "5") {
            ThongKeLop();
        } else if (luaChon == "0") {
            cout << "\nCam on ban da su dung he thong!\n";
            break;
        } else {
            cout << "[LOI] Lua chon khong hop le!\n";
        }
    }

    // Giải phóng bộ nhớ
    delete[] dsLopHoc;
    delete[] dsHocSinh;
    delete[] dsHocPhi;

    return 0;
}
