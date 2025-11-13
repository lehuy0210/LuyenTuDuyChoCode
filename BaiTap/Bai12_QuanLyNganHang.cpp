/*
===============================================
    BÀI 12: HỆ THỐNG QUẢN LÝ NGÂN HÀNG
===============================================
Mô tả: Quản lý tài khoản, giao dịch, chuyển tiền
Tính năng:
- Mở tài khoản (STK tự động, tên, CMND, số dư ban đầu)
- Gửi tiền (deposit)
- Rút tiền (withdrawal)
- Chuyển khoản (transfer)
- Kiểm tra số dư (balance)
- Lịch sử giao dịch
- Tính lãi suất (0.5%/tháng cho số dư > 10 triệu)
- Thống kê: Tổng tiền gửi, tài khoản lớn nhất
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

struct TaiKhoan {
    string soTK;          // 1234567890
    string hoTen;         // "Nguyen Van A"
    string CMND;          // "123456789"
    string sdt;           // "0912345678"
    float soDu;           // 5000000
    string ngayMo;        // "15/01/2025"
    string trangThai;     // "HoatDong", "Khoa"
};

struct GiaoDich {
    string maGD;          // GD001, GD002...
    string soTK;          // 1234567890
    string loaiGD;        // "GuiTien", "RutTien", "ChuyenKhoan"
    float soTien;         // 1000000
    string soTKNhan;      // Số TK nhận (nếu chuyển khoản)
    string ngayGD;        // "15/01/2025"
    string gioGD;         // "14:30"
    string moTa;          // "Rut tien tai ATM"
};

// ==================== GLOBAL DATA ====================

TaiKhoan* dsTaiKhoan = NULL;
int soLuongTK = 0;

GiaoDich* dsGiaoDich = NULL;
int soLuongGD = 0;

// ==================== FILE OPERATIONS ====================

void DocTaiKhoan() {
    ifstream file("DanhSachTaiKhoan.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file DanhSachTaiKhoan.txt\n";
        return;
    }
    string line;
    getline(file, line);
    soLuongTK = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        soLuongTK++;
    }
    file.clear();
    file.seekg(0);
    getline(file, line);
    dsTaiKhoan = new TaiKhoan[soLuongTK];
    int index = 0;
    while (getline(file, line) && index < soLuongTK) {
        if (line.empty()) continue;
        string fields[10];
        int count;
        ParseCSV(line, fields, count);
        if (count >= 7) {
            dsTaiKhoan[index].soTK = fields[0];
            dsTaiKhoan[index].hoTen = fields[1];
            dsTaiKhoan[index].CMND = fields[2];
            dsTaiKhoan[index].sdt = fields[3];
            dsTaiKhoan[index].soDu = StrToFloat(fields[4]);
            dsTaiKhoan[index].ngayMo = fields[5];
            dsTaiKhoan[index].trangThai = fields[6];
            index++;
        }
    }
    soLuongTK = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongTK << " tai khoan\n";
}

void GhiTaiKhoan() {
    ofstream file("DanhSachTaiKhoan.txt");
    if (!file.is_open()) {
        cout << "[LOI] Khong the ghi file DanhSachTaiKhoan.txt\n";
        return;
    }
    file << "SoTK,HoTen,CMND,SDT,SoDu,NgayMo,TrangThai\n";
    for (int i = 0; i < soLuongTK; i++) {
        file << dsTaiKhoan[i].soTK << ","
             << dsTaiKhoan[i].hoTen << ","
             << dsTaiKhoan[i].CMND << ","
             << dsTaiKhoan[i].sdt << ","
             << FloatToStr(dsTaiKhoan[i].soDu, 0) << ","
             << dsTaiKhoan[i].ngayMo << ","
             << dsTaiKhoan[i].trangThai << "\n";
    }
    file.close();
}

// ==================== BUSINESS LOGIC ====================

string TaoSoTKMoi() {
    // Tạo STK 10 số
    int maxNum = 1000000000;
    for (int i = 0; i < soLuongTK; i++) {
        int num = StrToInt(dsTaiKhoan[i].soTK);
        if (num >= maxNum) maxNum = num + 1;
    }
    return IntToStr(maxNum);
}

string TaoMaGDMoi() {
    int maxNum = 0;
    for (int i = 0; i < soLuongGD; i++) {
        if (dsGiaoDich[i].maGD.length() >= 4 && dsGiaoDich[i].maGD[0] == 'G') {
            string numStr = dsGiaoDich[i].maGD.substr(2);
            int num = StrToInt(numStr);
            if (num > maxNum) maxNum = num;
        }
    }
    string ma = "GD";
    int newNum = maxNum + 1;
    if (newNum < 10) ma += "000";
    else if (newNum < 100) ma += "00";
    else if (newNum < 1000) ma += "0";
    ma += IntToStr(newNum);
    return ma;
}

TaiKhoan* TimTaiKhoan(const string& soTK) {
    for (int i = 0; i < soLuongTK; i++) {
        if (dsTaiKhoan[i].soTK == soTK) {
            return &dsTaiKhoan[i];
        }
    }
    return NULL;
}

void LuuGiaoDich(const GiaoDich& gd) {
    GiaoDich* temp = new GiaoDich[soLuongGD + 1];
    for (int i = 0; i < soLuongGD; i++) {
        temp[i] = dsGiaoDich[i];
    }
    temp[soLuongGD] = gd;
    delete[] dsGiaoDich;
    dsGiaoDich = temp;
    soLuongGD++;
}

void MoTaiKhoan() {
    cout << "\n========== MO TAI KHOAN MOI ==========\n";

    TaiKhoan tkMoi;
    tkMoi.soTK = TaoSoTKMoi();

    cout << "So tai khoan (tu dong): " << tkMoi.soTK << "\n";

    cout << "Nhap ho ten: ";
    cin.ignore();
    getline(cin, tkMoi.hoTen);

    cout << "Nhap CMND: ";
    getline(cin, tkMoi.CMND);

    cout << "Nhap so dien thoai: ";
    getline(cin, tkMoi.sdt);

    cout << "Nhap so du ban dau (VND): ";
    string input;
    getline(cin, input);
    tkMoi.soDu = StrToFloat(input);

    if (tkMoi.soDu < 50000) {
        cout << "[LOI] So du toi thieu la 50,000 VND!\n";
        return;
    }

    cout << "Nhap ngay mo (dd/mm/yyyy): ";
    getline(cin, tkMoi.ngayMo);

    tkMoi.trangThai = "HoatDong";

    cout << "\n[THANH CONG] Da mo tai khoan!\n";
    cout << "So TK: " << tkMoi.soTK << "\n";
    cout << "Ho ten: " << tkMoi.hoTen << "\n";
    cout << "So du: " << FloatToStr(tkMoi.soDu, 0) << " VND\n";

    TaiKhoan* temp = new TaiKhoan[soLuongTK + 1];
    for (int i = 0; i < soLuongTK; i++) {
        temp[i] = dsTaiKhoan[i];
    }
    temp[soLuongTK] = tkMoi;
    delete[] dsTaiKhoan;
    dsTaiKhoan = temp;
    soLuongTK++;

    GhiTaiKhoan();

    // Lưu giao dịch mở tài khoản
    GiaoDich gd;
    gd.maGD = TaoMaGDMoi();
    gd.soTK = tkMoi.soTK;
    gd.loaiGD = "MoTaiKhoan";
    gd.soTien = tkMoi.soDu;
    gd.soTKNhan = "";
    gd.ngayGD = tkMoi.ngayMo;
    gd.gioGD = "00:00";
    gd.moTa = "Mo tai khoan";
    LuuGiaoDich(gd);
}

void GuiTien() {
    cout << "\n========== GUI TIEN ==========\n";

    cout << "Nhap so tai khoan: ";
    string soTK;
    cin >> soTK;

    TaiKhoan* tk = TimTaiKhoan(soTK);
    if (tk == NULL) {
        cout << "[LOI] Khong tim thay tai khoan!\n";
        return;
    }

    if (tk->trangThai != "HoatDong") {
        cout << "[LOI] Tai khoan da bi khoa!\n";
        return;
    }

    cout << "Chu tai khoan: " << tk->hoTen << "\n";
    cout << "So du hien tai: " << FloatToStr(tk->soDu, 0) << " VND\n";

    cout << "Nhap so tien gui (VND): ";
    string input;
    cin >> input;
    float soTien = StrToFloat(input);

    if (soTien <= 0) {
        cout << "[LOI] So tien khong hop le!\n";
        return;
    }

    tk->soDu += soTien;

    cout << "\n[THANH CONG] Da gui tien!\n";
    cout << "So tien gui: " << FloatToStr(soTien, 0) << " VND\n";
    cout << "So du moi: " << FloatToStr(tk->soDu, 0) << " VND\n";

    GhiTaiKhoan();

    // Lưu giao dịch
    GiaoDich gd;
    gd.maGD = TaoMaGDMoi();
    gd.soTK = soTK;
    gd.loaiGD = "GuiTien";
    gd.soTien = soTien;
    gd.soTKNhan = "";
    cout << "Nhap ngay giao dich (dd/mm/yyyy): ";
    cin >> gd.ngayGD;
    cout << "Nhap gio giao dich (HH:MM): ";
    cin >> gd.gioGD;
    gd.moTa = "Gui tien vao tai khoan";
    LuuGiaoDich(gd);
}

void RutTien() {
    cout << "\n========== RUT TIEN ==========\n";

    cout << "Nhap so tai khoan: ";
    string soTK;
    cin >> soTK;

    TaiKhoan* tk = TimTaiKhoan(soTK);
    if (tk == NULL) {
        cout << "[LOI] Khong tim thay tai khoan!\n";
        return;
    }

    if (tk->trangThai != "HoatDong") {
        cout << "[LOI] Tai khoan da bi khoa!\n";
        return;
    }

    cout << "Chu tai khoan: " << tk->hoTen << "\n";
    cout << "So du hien tai: " << FloatToStr(tk->soDu, 0) << " VND\n";

    cout << "Nhap so tien rut (VND): ";
    string input;
    cin >> input;
    float soTien = StrToFloat(input);

    if (soTien <= 0) {
        cout << "[LOI] So tien khong hop le!\n";
        return;
    }

    if (soTien > tk->soDu) {
        cout << "[LOI] So du khong du!\n";
        return;
    }

    if (tk->soDu - soTien < 50000) {
        cout << "[LOI] So du toi thieu phai la 50,000 VND!\n";
        return;
    }

    tk->soDu -= soTien;

    cout << "\n[THANH CONG] Da rut tien!\n";
    cout << "So tien rut: " << FloatToStr(soTien, 0) << " VND\n";
    cout << "So du moi: " << FloatToStr(tk->soDu, 0) << " VND\n";

    GhiTaiKhoan();

    // Lưu giao dịch
    GiaoDich gd;
    gd.maGD = TaoMaGDMoi();
    gd.soTK = soTK;
    gd.loaiGD = "RutTien";
    gd.soTien = soTien;
    gd.soTKNhan = "";
    cout << "Nhap ngay giao dich (dd/mm/yyyy): ";
    cin >> gd.ngayGD;
    cout << "Nhap gio giao dich (HH:MM): ";
    cin >> gd.gioGD;
    gd.moTa = "Rut tien tu tai khoan";
    LuuGiaoDich(gd);
}

void ChuyenKhoan() {
    cout << "\n========== CHUYEN KHOAN ==========\n";

    cout << "Nhap so TK nguon: ";
    string soTKNguon;
    cin >> soTKNguon;

    TaiKhoan* tkNguon = TimTaiKhoan(soTKNguon);
    if (tkNguon == NULL) {
        cout << "[LOI] Khong tim thay tai khoan nguon!\n";
        return;
    }

    if (tkNguon->trangThai != "HoatDong") {
        cout << "[LOI] Tai khoan nguon da bi khoa!\n";
        return;
    }

    cout << "Chu TK nguon: " << tkNguon->hoTen << "\n";
    cout << "So du: " << FloatToStr(tkNguon->soDu, 0) << " VND\n";

    cout << "\nNhap so TK nhan: ";
    string soTKNhan;
    cin >> soTKNhan;

    if (soTKNguon == soTKNhan) {
        cout << "[LOI] Khong the chuyen cho chinh minh!\n";
        return;
    }

    TaiKhoan* tkNhan = TimTaiKhoan(soTKNhan);
    if (tkNhan == NULL) {
        cout << "[LOI] Khong tim thay tai khoan nhan!\n";
        return;
    }

    if (tkNhan->trangThai != "HoatDong") {
        cout << "[LOI] Tai khoan nhan da bi khoa!\n";
        return;
    }

    cout << "Chu TK nhan: " << tkNhan->hoTen << "\n";

    cout << "\nNhap so tien chuyen (VND): ";
    string input;
    cin >> input;
    float soTien = StrToFloat(input);

    if (soTien <= 0) {
        cout << "[LOI] So tien khong hop le!\n";
        return;
    }

    float phiChuyen = soTien * 0.001;  // Phí 0.1%
    if (phiChuyen < 1000) phiChuyen = 1000;  // Tối thiểu 1000 VND

    float tongTru = soTien + phiChuyen;

    if (tongTru > tkNguon->soDu) {
        cout << "[LOI] So du khong du!\n";
        cout << "Can: " << FloatToStr(tongTru, 0) << " VND (bao gom phi "
             << FloatToStr(phiChuyen, 0) << " VND)\n";
        return;
    }

    if (tkNguon->soDu - tongTru < 50000) {
        cout << "[LOI] So du toi thieu phai la 50,000 VND!\n";
        return;
    }

    // Thực hiện chuyển khoản
    tkNguon->soDu -= tongTru;
    tkNhan->soDu += soTien;

    cout << "\n[THANH CONG] Chuyen khoan thanh cong!\n";
    cout << "So tien chuyen: " << FloatToStr(soTien, 0) << " VND\n";
    cout << "Phi chuyen khoan: " << FloatToStr(phiChuyen, 0) << " VND\n";
    cout << "So du moi: " << FloatToStr(tkNguon->soDu, 0) << " VND\n";

    GhiTaiKhoan();

    // Lưu giao dịch
    GiaoDich gd;
    gd.maGD = TaoMaGDMoi();
    gd.soTK = soTKNguon;
    gd.loaiGD = "ChuyenKhoan";
    gd.soTien = soTien;
    gd.soTKNhan = soTKNhan;
    cout << "Nhap ngay giao dich (dd/mm/yyyy): ";
    cin >> gd.ngayGD;
    cout << "Nhap gio giao dich (HH:MM): ";
    cin >> gd.gioGD;
    gd.moTa = "Chuyen khoan den " + tkNhan->hoTen;
    LuuGiaoDich(gd);
}

void KiemTraSoDu() {
    cout << "\n========== KIEM TRA SO DU ==========\n";

    cout << "Nhap so tai khoan: ";
    string soTK;
    cin >> soTK;

    TaiKhoan* tk = TimTaiKhoan(soTK);
    if (tk == NULL) {
        cout << "[LOI] Khong tim thay tai khoan!\n";
        return;
    }

    cout << "\n========== THONG TIN TAI KHOAN ==========\n";
    cout << "So TK: " << tk->soTK << "\n";
    cout << "Chu TK: " << tk->hoTen << "\n";
    cout << "CMND: " << tk->CMND << "\n";
    cout << "SDT: " << tk->sdt << "\n";
    cout << "So du: " << FloatToStr(tk->soDu, 0) << " VND\n";
    cout << "Ngay mo: " << tk->ngayMo << "\n";
    cout << "Trang thai: " << tk->trangThai << "\n";
    cout << "=========================================\n";
}

void HienThiLichSuGiaoDich() {
    cout << "\n========== LICH SU GIAO DICH ==========\n";

    cout << "Nhap so tai khoan: ";
    string soTK;
    cin >> soTK;

    TaiKhoan* tk = TimTaiKhoan(soTK);
    if (tk == NULL) {
        cout << "[LOI] Khong tim thay tai khoan!\n";
        return;
    }

    cout << "\nChu TK: " << tk->hoTen << "\n";
    cout << "So TK: " << tk->soTK << "\n\n";

    bool coGD = false;
    for (int i = 0; i < soLuongGD; i++) {
        if (dsGiaoDich[i].soTK == soTK) {
            cout << "Ma GD: " << dsGiaoDich[i].maGD << "\n";
            cout << "Ngay: " << dsGiaoDich[i].ngayGD << " " << dsGiaoDich[i].gioGD << "\n";
            cout << "Loai: " << dsGiaoDich[i].loaiGD << "\n";
            cout << "So tien: " << FloatToStr(dsGiaoDich[i].soTien, 0) << " VND\n";
            if (dsGiaoDich[i].soTKNhan != "") {
                cout << "TK nhan: " << dsGiaoDich[i].soTKNhan << "\n";
            }
            cout << "Mo ta: " << dsGiaoDich[i].moTa << "\n";
            cout << "----------------------------\n";
            coGD = true;
        }
    }

    if (!coGD) {
        cout << "Chua co giao dich nao!\n";
    }
}

void ThongKe() {
    cout << "\n========== THONG KE HE THONG ==========\n";

    if (soLuongTK == 0) {
        cout << "Chua co tai khoan nao!\n";
        return;
    }

    float tongTienGui = 0;
    float maxSoDu = 0;
    string tkLonNhat = "";

    for (int i = 0; i < soLuongTK; i++) {
        tongTienGui += dsTaiKhoan[i].soDu;
        if (dsTaiKhoan[i].soDu > maxSoDu) {
            maxSoDu = dsTaiKhoan[i].soDu;
            tkLonNhat = dsTaiKhoan[i].hoTen;
        }
    }

    cout << "Tong so tai khoan: " << soLuongTK << "\n";
    cout << "Tong tien gui: " << FloatToStr(tongTienGui, 0) << " VND\n";
    cout << "So du TB/tai khoan: " << FloatToStr(tongTienGui / soLuongTK, 0) << " VND\n";
    cout << "Tai khoan lon nhat: " << tkLonNhat << " - "
         << FloatToStr(maxSoDu, 0) << " VND\n";
    cout << "Tong so giao dich: " << soLuongGD << "\n";
}

// ==================== MENU ====================

void Menu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "   HE THONG QUAN LY NGAN HANG\n";
    cout << "========================================\n";
    cout << "1. Mo tai khoan moi\n";
    cout << "2. Gui tien\n";
    cout << "3. Rut tien\n";
    cout << "4. Chuyen khoan\n";
    cout << "5. Kiem tra so du\n";
    cout << "6. Lich su giao dich\n";
    cout << "7. Thong ke\n";
    cout << "0. Thoat\n";
    cout << "========================================\n";
    cout << "Lua chon: ";
}

// ==================== MAIN ====================

int main() {
    cout << "\n*** Dang khoi tao he thong ***\n";

    DocTaiKhoan();

    cout << "*** Khoi tao hoan tat ***\n";

    while (true) {
        Menu();

        string luaChon;
        getline(cin, luaChon);

        if (luaChon == "1") {
            MoTaiKhoan();
        } else if (luaChon == "2") {
            GuiTien();
        } else if (luaChon == "3") {
            RutTien();
        } else if (luaChon == "4") {
            ChuyenKhoan();
        } else if (luaChon == "5") {
            KiemTraSoDu();
        } else if (luaChon == "6") {
            HienThiLichSuGiaoDich();
        } else if (luaChon == "7") {
            ThongKe();
        } else if (luaChon == "0") {
            cout << "\nCam on ban da su dung he thong!\n";
            break;
        } else {
            cout << "[LOI] Lua chon khong hop le!\n";
        }
    }

    // Giải phóng bộ nhớ
    delete[] dsTaiKhoan;
    delete[] dsGiaoDich;

    return 0;
}
