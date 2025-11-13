/*
===============================================
    BÀI 11: HỆ THỐNG QUẢN LÝ SIÊU THỊ
===============================================
Mô tả: Quản lý hàng hóa, kho, nhập xuất, bán hàng
Tính năng:
- Quản lý sản phẩm (mã vạch, tên, giá, tồn kho)
- Quản lý danh mục (Thực phẩm, Đồ uống, Gia dụng...)
- Nhập hàng (cập nhật tồn kho)
- Bán hàng (quét mã vạch, giỏ hàng)
- Khuyến mãi: Giảm giá %, mua X tặng Y
- Hóa đơn: VAT 10%, thẻ thành viên giảm 5%
- Thống kê: Doanh thu, sản phẩm bán chạy, sắp hết hàng
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

struct SanPham {
    string maSP;          // SP001, SP002...
    string maVach;        // Barcode: 8934567890123
    string tenSP;         // "Sua tuoi Vinamilk"
    string danhMuc;       // "Thuc pham", "Do uong", "Gia dung"
    float giaBan;         // 12000
    int tonKho;           // 50
    int nguongCanhBao;    // 10 (cảnh báo khi tồn kho < 10)
};

struct ChiTietHoaDon {
    string maSP;          // SP001
    int soLuong;          // 2
    float donGia;         // 12000
    float thanhTien;      // 24000
};

struct HoaDon {
    string maHD;          // HD001, HD002...
    string ngayBan;       // "15/01/2025"
    string gioBan;        // "14:30"
    int soMat;            // Số mặt hàng
    ChiTietHoaDon* dsMatHang; // Mảng động
    float tongTien;       // Tổng trước thuế
    float VAT;            // 10%
    float giamGiaTV;      // Giảm giá thẻ thành viên 5%
    float thanhToan;      // Tổng cuối
    bool coTheTV;         // Có thẻ thành viên không
};

struct PhieuNhap {
    string maPN;          // PN001, PN002...
    string ngayNhap;      // "15/01/2025"
    string nhaCungCap;    // "Vinamilk"
    int soMat;            // Số mặt hàng
    ChiTietHoaDon* dsMatHang; // Mảng động (tái sử dụng struct)
    float tongTien;       // Tổng tiền nhập
};

// ==================== GLOBAL DATA ====================

SanPham* dsSanPham = NULL;
int soLuongSP = 0;

HoaDon* dsHoaDon = NULL;
int soLuongHD = 0;

PhieuNhap* dsPhieuNhap = NULL;
int soLuongPN = 0;

// ==================== FILE OPERATIONS ====================

void DocSanPham() {
    ifstream file("DanhSachSanPhamSieuThi.txt");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong tim thay file DanhSachSanPhamSieuThi.txt\n";
        return;
    }
    string line;
    getline(file, line);
    soLuongSP = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        soLuongSP++;
    }
    file.clear();
    file.seekg(0);
    getline(file, line);
    dsSanPham = new SanPham[soLuongSP];
    int index = 0;
    while (getline(file, line) && index < soLuongSP) {
        if (line.empty()) continue;
        string fields[10];
        int count;
        ParseCSV(line, fields, count);
        if (count >= 7) {
            dsSanPham[index].maSP = fields[0];
            dsSanPham[index].maVach = fields[1];
            dsSanPham[index].tenSP = fields[2];
            dsSanPham[index].danhMuc = fields[3];
            dsSanPham[index].giaBan = StrToFloat(fields[4]);
            dsSanPham[index].tonKho = StrToInt(fields[5]);
            dsSanPham[index].nguongCanhBao = StrToInt(fields[6]);
            index++;
        }
    }
    soLuongSP = index;
    file.close();
    cout << "[OK] Doc duoc " << soLuongSP << " san pham\n";
}

void GhiSanPham() {
    ofstream file("DanhSachSanPhamSieuThi.txt");
    if (!file.is_open()) {
        cout << "[LOI] Khong the ghi file DanhSachSanPhamSieuThi.txt\n";
        return;
    }
    file << "MaSP,MaVach,TenSP,DanhMuc,GiaBan,TonKho,NguongCanhBao\n";
    for (int i = 0; i < soLuongSP; i++) {
        file << dsSanPham[i].maSP << ","
             << dsSanPham[i].maVach << ","
             << dsSanPham[i].tenSP << ","
             << dsSanPham[i].danhMuc << ","
             << FloatToStr(dsSanPham[i].giaBan, 0) << ","
             << dsSanPham[i].tonKho << ","
             << dsSanPham[i].nguongCanhBao << "\n";
    }
    file.close();
}

// ==================== BUSINESS LOGIC ====================

string TaoMaHDMoi() {
    int maxNum = 0;
    for (int i = 0; i < soLuongHD; i++) {
        if (dsHoaDon[i].maHD.length() >= 4 && dsHoaDon[i].maHD[0] == 'H') {
            string numStr = dsHoaDon[i].maHD.substr(2);
            int num = StrToInt(numStr);
            if (num > maxNum) maxNum = num;
        }
    }
    string ma = "HD";
    int newNum = maxNum + 1;
    if (newNum < 10) ma += "00";
    else if (newNum < 100) ma += "0";
    ma += IntToStr(newNum);
    return ma;
}

string TaoMaPNMoi() {
    int maxNum = 0;
    for (int i = 0; i < soLuongPN; i++) {
        if (dsPhieuNhap[i].maPN.length() >= 4 && dsPhieuNhap[i].maPN[0] == 'P') {
            string numStr = dsPhieuNhap[i].maPN.substr(2);
            int num = StrToInt(numStr);
            if (num > maxNum) maxNum = num;
        }
    }
    string ma = "PN";
    int newNum = maxNum + 1;
    if (newNum < 10) ma += "00";
    else if (newNum < 100) ma += "0";
    ma += IntToStr(newNum);
    return ma;
}

void HienThiDanhSachSanPham() {
    cout << "\n========== DANH SACH SAN PHAM ==========\n";
    if (soLuongSP == 0) {
        cout << "Chua co san pham nao!\n";
        return;
    }
    cout << "Ma    | Ma Vach       | Ten San Pham            | Gia Ban  | Ton Kho\n";
    cout << "-----------------------------------------------------------------------------\n";
    for (int i = 0; i < soLuongSP; i++) {
        cout << dsSanPham[i].maSP << " | ";
        cout << dsSanPham[i].maVach << " | ";
        string ten = dsSanPham[i].tenSP;
        if (ten.length() > 23) ten = ten.substr(0, 20) + "...";
        cout << ten;
        for (int j = ten.length(); j < 23; j++) cout << " ";
        cout << " | ";
        cout << FloatToStr(dsSanPham[i].giaBan, 0);
        for (int j = FloatToStr(dsSanPham[i].giaBan, 0).length(); j < 8; j++) cout << " ";
        cout << " | ";
        cout << dsSanPham[i].tonKho;
        if (dsSanPham[i].tonKho < dsSanPham[i].nguongCanhBao) {
            cout << " [SAP HET!]";
        }
        cout << "\n";
    }
}

SanPham* TimSanPhamTheoMaVach(const string& maVach) {
    for (int i = 0; i < soLuongSP; i++) {
        if (dsSanPham[i].maVach == maVach) {
            return &dsSanPham[i];
        }
    }
    return NULL;
}

void NhapHang() {
    cout << "\n========== NHAP HANG ==========\n";

    PhieuNhap pnMoi;
    pnMoi.maPN = TaoMaPNMoi();

    cout << "Ma phieu (tu dong): " << pnMoi.maPN << "\n";

    cout << "Nhap ngay nhap (dd/mm/yyyy): ";
    cin >> pnMoi.ngayNhap;

    cout << "Nhap nha cung cap: ";
    cin.ignore();
    getline(cin, pnMoi.nhaCungCap);

    cout << "Nhap so mat hang: ";
    string input;
    getline(cin, input);
    pnMoi.soMat = StrToInt(input);

    pnMoi.dsMatHang = new ChiTietHoaDon[pnMoi.soMat];
    pnMoi.tongTien = 0;

    for (int i = 0; i < pnMoi.soMat; i++) {
        cout << "\n--- Mat hang " << (i + 1) << " ---\n";

        cout << "Nhap ma vach: ";
        string maVach;
        getline(cin, maVach);

        SanPham* sp = TimSanPhamTheoMaVach(maVach);
        if (sp == NULL) {
            cout << "[LOI] Khong tim thay san pham!\n";
            i--;
            continue;
        }

        pnMoi.dsMatHang[i].maSP = sp->maSP;

        cout << "San pham: " << sp->tenSP << "\n";
        cout << "Ton kho hien tai: " << sp->tonKho << "\n";

        cout << "Nhap so luong nhap: ";
        getline(cin, input);
        pnMoi.dsMatHang[i].soLuong = StrToInt(input);

        cout << "Nhap gia nhap: ";
        getline(cin, input);
        pnMoi.dsMatHang[i].donGia = StrToFloat(input);

        pnMoi.dsMatHang[i].thanhTien = pnMoi.dsMatHang[i].soLuong * pnMoi.dsMatHang[i].donGia;
        pnMoi.tongTien += pnMoi.dsMatHang[i].thanhTien;

        // Cập nhật tồn kho
        sp->tonKho += pnMoi.dsMatHang[i].soLuong;

        cout << "[OK] Thanh tien: " << FloatToStr(pnMoi.dsMatHang[i].thanhTien, 0) << " VND\n";
    }

    cout << "\n========== PHIEU NHAP ==========\n";
    cout << "Ma phieu: " << pnMoi.maPN << "\n";
    cout << "Ngay nhap: " << pnMoi.ngayNhap << "\n";
    cout << "Nha cung cap: " << pnMoi.nhaCungCap << "\n";
    cout << "Tong tien: " << FloatToStr(pnMoi.tongTien, 0) << " VND\n";
    cout << "================================\n";

    PhieuNhap* temp = new PhieuNhap[soLuongPN + 1];
    for (int i = 0; i < soLuongPN; i++) {
        temp[i] = dsPhieuNhap[i];
    }
    temp[soLuongPN] = pnMoi;
    delete[] dsPhieuNhap;
    dsPhieuNhap = temp;
    soLuongPN++;

    GhiSanPham();
    cout << "[THANH CONG] Da nhap hang!\n";
}

void BanHang() {
    cout << "\n========== BAN HANG ==========\n";

    HoaDon hdMoi;
    hdMoi.maHD = TaoMaHDMoi();

    cout << "Ma hoa don (tu dong): " << hdMoi.maHD << "\n";

    cout << "Nhap ngay ban (dd/mm/yyyy): ";
    cin >> hdMoi.ngayBan;

    cout << "Nhap gio ban (HH:MM): ";
    cin >> hdMoi.gioBan;

    cout << "Khach hang co the thanh vien? (1: Co, 0: Khong): ";
    string input;
    cin >> input;
    hdMoi.coTheTV = (StrToInt(input) == 1);

    cout << "\nQuet ma vach san pham (nhap '0' de ket thuc):\n";

    ChiTietHoaDon gioHang[100];
    int soMat = 0;

    while (true) {
        cout << "\nQuet ma vach: ";
        string maVach;
        cin >> maVach;

        if (maVach == "0") break;

        SanPham* sp = TimSanPhamTheoMaVach(maVach);
        if (sp == NULL) {
            cout << "[LOI] Khong tim thay san pham!\n";
            continue;
        }

        cout << "San pham: " << sp->tenSP << " - " << FloatToStr(sp->giaBan, 0) << " VND\n";
        cout << "Ton kho: " << sp->tonKho << "\n";

        cout << "Nhap so luong: ";
        cin >> input;
        int soLuong = StrToInt(input);

        if (soLuong > sp->tonKho) {
            cout << "[LOI] Khong du hang trong kho!\n";
            continue;
        }

        // Kiểm tra đã có trong giỏ chưa
        bool timThay = false;
        for (int i = 0; i < soMat; i++) {
            if (gioHang[i].maSP == sp->maSP) {
                gioHang[i].soLuong += soLuong;
                gioHang[i].thanhTien = gioHang[i].soLuong * gioHang[i].donGia;
                timThay = true;
                cout << "[OK] Da cap nhat so luong trong gio hang\n";
                break;
            }
        }

        if (!timThay) {
            gioHang[soMat].maSP = sp->maSP;
            gioHang[soMat].soLuong = soLuong;
            gioHang[soMat].donGia = sp->giaBan;
            gioHang[soMat].thanhTien = soLuong * sp->giaBan;
            soMat++;
            cout << "[OK] Da them vao gio hang\n";
        }

        // Cập nhật tồn kho
        sp->tonKho -= soLuong;
    }

    if (soMat == 0) {
        cout << "[LOI] Gio hang trong!\n";
        return;
    }

    hdMoi.soMat = soMat;
    hdMoi.dsMatHang = new ChiTietHoaDon[soMat];

    hdMoi.tongTien = 0;
    for (int i = 0; i < soMat; i++) {
        hdMoi.dsMatHang[i] = gioHang[i];
        hdMoi.tongTien += gioHang[i].thanhTien;
    }

    hdMoi.VAT = hdMoi.tongTien * 0.1;  // VAT 10%

    if (hdMoi.coTheTV) {
        hdMoi.giamGiaTV = hdMoi.tongTien * 0.05;  // Giảm 5%
    } else {
        hdMoi.giamGiaTV = 0;
    }

    hdMoi.thanhToan = hdMoi.tongTien + hdMoi.VAT - hdMoi.giamGiaTV;

    // In hóa đơn
    cout << "\n========== HOA DON ==========\n";
    cout << "Ma hoa don: " << hdMoi.maHD << "\n";
    cout << "Ngay: " << hdMoi.ngayBan << " " << hdMoi.gioBan << "\n";
    cout << "----------------------------\n";

    for (int i = 0; i < hdMoi.soMat; i++) {
        string tenSP = "";
        for (int j = 0; j < soLuongSP; j++) {
            if (dsSanPham[j].maSP == hdMoi.dsMatHang[i].maSP) {
                tenSP = dsSanPham[j].tenSP;
                break;
            }
        }
        cout << tenSP << "\n";
        cout << "  " << hdMoi.dsMatHang[i].soLuong << " x "
             << FloatToStr(hdMoi.dsMatHang[i].donGia, 0) << " = "
             << FloatToStr(hdMoi.dsMatHang[i].thanhTien, 0) << " VND\n";
    }

    cout << "----------------------------\n";
    cout << "Tong tien: " << FloatToStr(hdMoi.tongTien, 0) << " VND\n";
    cout << "VAT (10%): " << FloatToStr(hdMoi.VAT, 0) << " VND\n";

    if (hdMoi.coTheTV) {
        cout << "Giam gia TV (5%): -" << FloatToStr(hdMoi.giamGiaTV, 0) << " VND\n";
    }

    cout << "----------------------------\n";
    cout << "THANH TOAN: " << FloatToStr(hdMoi.thanhToan, 0) << " VND\n";
    cout << "============================\n";

    HoaDon* temp = new HoaDon[soLuongHD + 1];
    for (int i = 0; i < soLuongHD; i++) {
        temp[i] = dsHoaDon[i];
    }
    temp[soLuongHD] = hdMoi;
    delete[] dsHoaDon;
    dsHoaDon = temp;
    soLuongHD++;

    GhiSanPham();
    cout << "[THANH CONG] Da tao hoa don!\n";
}

void ThongKeDoanhThu() {
    cout << "\n========== THONG KE DOANH THU ==========\n";

    if (soLuongHD == 0) {
        cout << "Chua co hoa don nao!\n";
        return;
    }

    float tongDoanhThu = 0;
    for (int i = 0; i < soLuongHD; i++) {
        tongDoanhThu += dsHoaDon[i].thanhToan;
    }

    cout << "Tong so hoa don: " << soLuongHD << "\n";
    cout << "Tong doanh thu: " << FloatToStr(tongDoanhThu, 0) << " VND\n";
    cout << "Doanh thu TB/hoa don: " << FloatToStr(tongDoanhThu / soLuongHD, 0) << " VND\n";
}

void KiemTraSapHetHang() {
    cout << "\n========== SAN PHAM SAP HET HANG ==========\n";

    bool coSPSapHet = false;
    for (int i = 0; i < soLuongSP; i++) {
        if (dsSanPham[i].tonKho < dsSanPham[i].nguongCanhBao) {
            cout << "- " << dsSanPham[i].tenSP << " (Ma: " << dsSanPham[i].maSP << ")\n";
            cout << "  Ton kho: " << dsSanPham[i].tonKho << " (Nguong: "
                 << dsSanPham[i].nguongCanhBao << ")\n\n";
            coSPSapHet = true;
        }
    }

    if (!coSPSapHet) {
        cout << "Tat ca san pham deu du hang.\n";
    }
}

// ==================== MENU ====================

void Menu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "   HE THONG QUAN LY SIEU THI\n";
    cout << "========================================\n";
    cout << "1. Hien thi danh sach san pham\n";
    cout << "2. Nhap hang\n";
    cout << "3. Ban hang\n";
    cout << "4. Thong ke doanh thu\n";
    cout << "5. Kiem tra san pham sap het\n";
    cout << "0. Thoat\n";
    cout << "========================================\n";
    cout << "Lua chon: ";
}

// ==================== MAIN ====================

int main() {
    cout << "\n*** Dang khoi tao he thong ***\n";

    DocSanPham();

    cout << "*** Khoi tao hoan tat ***\n";

    while (true) {
        Menu();

        string luaChon;
        getline(cin, luaChon);

        if (luaChon == "1") {
            HienThiDanhSachSanPham();
        } else if (luaChon == "2") {
            NhapHang();
        } else if (luaChon == "3") {
            BanHang();
        } else if (luaChon == "4") {
            ThongKeDoanhThu();
        } else if (luaChon == "5") {
            KiemTraSapHetHang();
        } else if (luaChon == "0") {
            cout << "\nCam on ban da su dung he thong!\n";
            break;
        } else {
            cout << "[LOI] Lua chon khong hop le!\n";
        }
    }

    // Giải phóng bộ nhớ
    delete[] dsSanPham;
    for (int i = 0; i < soLuongHD; i++) {
        delete[] dsHoaDon[i].dsMatHang;
    }
    delete[] dsHoaDon;
    for (int i = 0; i < soLuongPN; i++) {
        delete[] dsPhieuNhap[i].dsMatHang;
    }
    delete[] dsPhieuNhap;

    return 0;
}
