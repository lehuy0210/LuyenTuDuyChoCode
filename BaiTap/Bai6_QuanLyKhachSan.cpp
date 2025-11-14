#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// ========== HAM TU VIET ==========

int StrToInt(const string& str) {
    int result = 0;
    bool negative = false;
    int start = 0;
    if (str.length() > 0 && str[0] == '-') {
        negative = true;
        start = 1;
    }
    for (int i = start; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            break;
        }
    }
    return negative ? -result : result;
}

float StrToFloat(const string& str) {
    float result = 0.0;
    float decimal = 0.0;
    int decimalPos = 0;
    bool hasDecimal = false;
    bool negative = false;
    int start = 0;
    if (str.length() > 0 && str[0] == '-') {
        negative = true;
        start = 1;
    }
    for (int i = start; i < str.length(); i++) {
        if (str[i] == '.' || str[i] == ',') {
            hasDecimal = true;
            continue;
        }
        if (str[i] >= '0' && str[i] <= '9') {
            if (!hasDecimal) {
                result = result * 10 + (str[i] - '0');
            } else {
                decimalPos++;
                decimal = decimal * 10 + (str[i] - '0');
            }
        }
    }
    for (int i = 0; i < decimalPos; i++) {
        decimal = decimal / 10.0;
    }
    result = result + decimal;
    return negative ? -result : result;
}

string IntToStr(int num) {
    if (num == 0) return "0";
    string result = "";
    bool negative = false;
    if (num < 0) {
        negative = true;
        num = -num;
    }
    while (num > 0) {
        result = char('0' + (num % 10)) + result;
        num = num / 10;
    }
    if (negative) {
        result = '-' + result;
    }
    return result;
}

string FloatToStr(float num) {
    int intPart = (int)num;
    string result = IntToStr(intPart);
    float decimalPart = num - intPart;
    if (decimalPart < 0) decimalPart = -decimalPart;
    int decimal = (int)((decimalPart * 100) + 0.5);
    result = result + ".";
    if (decimal < 10) {
        result = result + "0";
    }
    result = result + IntToStr(decimal);
    return result;
}

string GetCurrentDate() {
    time_t now = time(0);
    tm* dt = localtime(&now);
    return IntToStr(dt->tm_mday) + "/" + IntToStr(dt->tm_mon + 1) + "/" + IntToStr(dt->tm_year + 1900);
}

// ========== CAU TRUC DU LIEU ==========

struct Phong {
    string maPhong;
    string loaiPhong;    // Standard, Deluxe, Suite
    int soGiuong;
    float giaPhong;      // Gia theo dem
    string trangThai;    // Trong, DaDat, DangO
    string moTa;
};

struct KhachHang {
    string maCMND;
    string hoTen;
    string soDienThoai;
    string quocTich;
};

struct DatPhong {
    string maDatPhong;
    string maPhong;
    string maCMND;
    string tenKH;
    string ngayNhan;     // dd/mm/yyyy
    string ngayTra;      // dd/mm/yyyy
    int soNgay;
    int soNguoi;
    float tienCoc;
    string trangThai;    // DaDat, DaCheckIn, DaCheckOut, DaHuy
};

struct HoaDon {
    string maHoaDon;
    string maDatPhong;
    string maPhong;
    string tenKH;
    string ngayCheckIn;
    string ngayCheckOut;
    int soNgay;
    float tienPhong;
    float tienDichVu;    // Giat la, mini bar, etc
    float tienCoc;
    float tongTien;
    float conLai;
};

// ========== FILE I/O ==========

void DocFilePhong(Phong* dsPhong, int& demPhong, const string& file) {
    try {
        ifstream inFile(file);
        if (!inFile.is_open()) {
            throw runtime_error("Khong the mo file phong");
        }
        demPhong = 0;
        string line;
        getline(inFile, line); // Skip header
        while (getline(inFile, line) && demPhong < 100) {
            string parts[6] = {"", "", "", "", "", ""};
            int pos = 0;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    pos++;
                    if (pos >= 6) break;
                } else {
                    parts[pos] += line[i];
                }
            }
            dsPhong[demPhong].maPhong = parts[0];
            dsPhong[demPhong].loaiPhong = parts[1];
            dsPhong[demPhong].soGiuong = StrToInt(parts[2]);
            dsPhong[demPhong].giaPhong = StrToFloat(parts[3]);
            dsPhong[demPhong].trangThai = parts[4];
            dsPhong[demPhong].moTa = parts[5];
            demPhong++;
        }
        inFile.close();
        cout << "Doc file phong thanh cong: " << demPhong << " phong" << endl;
    } catch (exception& e) {
        cout << "Loi doc file: " << e.what() << endl;
    }
}

void LuuFilePhong(Phong* dsPhong, int demPhong, const string& file) {
    try {
        ofstream outFile(file);
        if (!outFile.is_open()) {
            throw runtime_error("Khong the luu file");
        }
        outFile << "MaPhong,LoaiPhong,SoGiuong,GiaPhong,TrangThai,MoTa" << endl;
        for (int i = 0; i < demPhong; i++) {
            outFile << dsPhong[i].maPhong << ","
                    << dsPhong[i].loaiPhong << ","
                    << dsPhong[i].soGiuong << ","
                    << dsPhong[i].giaPhong << ","
                    << dsPhong[i].trangThai << ","
                    << dsPhong[i].moTa << endl;
        }
        outFile.close();
    } catch (exception& e) {
        cout << "Loi luu file: " << e.what() << endl;
    }
}

// ========== HIEN THI ==========

void HienThiPhong(Phong* dsPhong, int demPhong) {
    cout << "\n===== DANH SACH PHONG =====" << endl;
    cout << "Ma\tLoai\t\tGiuong\tGia/Dem\t\tTrang Thai" << endl;
    cout << "----------------------------------------------------------------" << endl;
    for (int i = 0; i < demPhong; i++) {
        cout << dsPhong[i].maPhong << "\t"
             << dsPhong[i].loaiPhong << "\t"
             << dsPhong[i].soGiuong << "\t"
             << dsPhong[i].giaPhong << "\t\t"
             << dsPhong[i].trangThai << endl;
    }
    cout << endl;
}

void HienThiPhongTrong(Phong* dsPhong, int demPhong) {
    cout << "\n===== PHONG TRONG =====" << endl;
    cout << "Ma\tLoai\t\tGiuong\tGia/Dem\t\tMo Ta" << endl;
    cout << "----------------------------------------------------------------" << endl;
    bool coPhongTrong = false;
    for (int i = 0; i < demPhong; i++) {
        if (dsPhong[i].trangThai == "Trong") {
            cout << dsPhong[i].maPhong << "\t"
                 << dsPhong[i].loaiPhong << "\t"
                 << dsPhong[i].soGiuong << "\t"
                 << dsPhong[i].giaPhong << "\t\t"
                 << dsPhong[i].moTa << endl;
            coPhongTrong = true;
        }
    }
    if (!coPhongTrong) {
        cout << "Khong co phong trong!" << endl;
    }
    cout << endl;
}

// ========== TIM KIEM ==========

int TimPhongTheoMa(Phong* dsPhong, int demPhong, const string& ma) {
    for (int i = 0; i < demPhong; i++) {
        if (dsPhong[i].maPhong == ma) {
            return i;
        }
    }
    return -1;
}

// ========== TINH SO NGAY ==========

int TinhSoNgay(const string& ngayBD, const string& ngayKT) {
    // Tinh don gian - trong thuc te can tinh chinh xac hon
    // Day chi la version don gian
    return 3; // Tam thoi tra ve 3 ngay
}

// ========== DAT PHONG ==========

void DatPhong(Phong* dsPhong, int demPhong, int& soDatPhong) {
    try {
        cout << "\n===== DAT PHONG =====" << endl;

        // Hien thi phong trong
        HienThiPhongTrong(dsPhong, demPhong);

        string maPhong;
        cout << "Nhap ma phong: ";
        cin >> maPhong;

        int viTri = TimPhongTheoMa(dsPhong, demPhong, maPhong);
        if (viTri == -1) {
            cout << "Khong tim thay phong!" << endl;
            return;
        }

        if (dsPhong[viTri].trangThai != "Trong") {
            cout << "Phong khong trong!" << endl;
            return;
        }

        // Thong tin khach hang
        KhachHang kh;
        cout << "Nhap CMND/Passport: ";
        cin >> kh.maCMND;

        cout << "Nhap ho ten: ";
        cin.ignore();
        getline(cin, kh.hoTen);

        cout << "Nhap so dien thoai: ";
        cin >> kh.soDienThoai;

        cout << "Nhap quoc tich: ";
        cin >> kh.quocTich;

        // Thong tin dat phong
        DatPhong dat;
        soDatPhong++;
        dat.maDatPhong = "DP" + IntToStr(soDatPhong);
        dat.maPhong = maPhong;
        dat.maCMND = kh.maCMND;
        dat.tenKH = kh.hoTen;

        cout << "Nhap ngay nhan phong (dd/mm/yyyy): ";
        cin >> dat.ngayNhan;

        cout << "Nhap ngay tra phong (dd/mm/yyyy): ";
        cin >> dat.ngayTra;

        dat.soNgay = TinhSoNgay(dat.ngayNhan, dat.ngayTra);
        cout << "So ngay o: " << dat.soNgay << endl;

        cout << "Nhap so nguoi o: ";
        cin >> dat.soNguoi;

        // Tien coc 30%
        float tongTienDuKien = dsPhong[viTri].giaPhong * dat.soNgay;
        dat.tienCoc = tongTienDuKien * 0.30;

        cout << "Tong tien du kien: " << tongTienDuKien << " VND" << endl;
        cout << "Tien coc (30%): " << dat.tienCoc << " VND" << endl;

        dat.trangThai = "DaDat";

        // Cap nhat trang thai phong
        dsPhong[viTri].trangThai = "DaDat";

        // In phieu dat phong
        cout << "\n========================================" << endl;
        cout << "       KHACH SAN ABC" << endl;
        cout << "       123 Nguyen Hue, Q1" << endl;
        cout << "========================================" << endl;
        cout << "       PHIEU DAT PHONG" << endl;
        cout << "========================================" << endl;
        cout << "Ma dat phong: " << dat.maDatPhong << endl;
        cout << "Phong: " << dat.maPhong << " - " << dsPhong[viTri].loaiPhong << endl;
        cout << "Gia: " << dsPhong[viTri].giaPhong << " VND/dem" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Khach hang: " << kh.hoTen << endl;
        cout << "CMND/Passport: " << kh.maCMND << endl;
        cout << "Dien thoai: " << kh.soDienThoai << endl;
        cout << "Quoc tich: " << kh.quocTich << endl;
        cout << "----------------------------------------" << endl;
        cout << "Ngay nhan: " << dat.ngayNhan << endl;
        cout << "Ngay tra: " << dat.ngayTra << endl;
        cout << "So ngay: " << dat.soNgay << endl;
        cout << "So nguoi: " << dat.soNguoi << endl;
        cout << "----------------------------------------" << endl;
        cout << "Tong tien du kien: " << tongTienDuKien << " VND" << endl;
        cout << "Tien coc (30%): " << dat.tienCoc << " VND" << endl;
        cout << "========================================" << endl;
        cout << "Vui long den check-in truoc " << dat.ngayNhan << endl;
        cout << "========================================" << endl;

        // Luu dat phong
        try {
            ofstream outFile("DatPhong.txt", ios::app);
            if (outFile.is_open()) {
                outFile << dat.maDatPhong << ","
                        << dat.maPhong << ","
                        << dat.maCMND << ","
                        << dat.tenKH << ","
                        << dat.ngayNhan << ","
                        << dat.ngayTra << ","
                        << dat.soNgay << ","
                        << dat.soNguoi << ","
                        << dat.tienCoc << ","
                        << dat.trangThai << endl;
                outFile.close();
            }
        } catch (exception& e) {
            cout << "Loi luu dat phong: " << e.what() << endl;
        }

        // Luu file phong
        LuuFilePhong(dsPhong, demPhong, "DanhSachPhong.txt");

        cout << "\nDat phong thanh cong!" << endl;

    } catch (exception& e) {
        cout << "Loi: " << e.what() << endl;
    }
}

// ========== CHECK IN ==========

void CheckIn(Phong* dsPhong, int demPhong) {
    cout << "\n===== CHECK IN =====" << endl;

    string maDatPhong;
    cout << "Nhap ma dat phong: ";
    cin >> maDatPhong;

    // Tim dat phong trong file
    // (Don gian hoa: chi cap nhat trang thai phong)

    string maPhong;
    cout << "Nhap ma phong: ";
    cin >> maPhong;

    int viTri = TimPhongTheoMa(dsPhong, demPhong, maPhong);
    if (viTri == -1) {
        cout << "Khong tim thay phong!" << endl;
        return;
    }

    if (dsPhong[viTri].trangThai != "DaDat") {
        cout << "Phong chua duoc dat hoac dang co nguoi o!" << endl;
        return;
    }

    // Cap nhat trang thai
    dsPhong[viTri].trangThai = "DangO";

    LuuFilePhong(dsPhong, demPhong, "DanhSachPhong.txt");

    cout << "Check in thanh cong!" << endl;
    cout << "Chuc quy khach co trai nghiem tot tai khach san!" << endl;
}

// ========== CHECK OUT ==========

void CheckOut(Phong* dsPhong, int demPhong, int& soHoaDon) {
    try {
        cout << "\n===== CHECK OUT =====" << endl;

        string maPhong;
        cout << "Nhap ma phong: ";
        cin >> maPhong;

        int viTri = TimPhongTheoMa(dsPhong, demPhong, maPhong);
        if (viTri == -1) {
            cout << "Khong tim thay phong!" << endl;
            return;
        }

        if (dsPhong[viTri].trangThai != "DangO") {
            cout << "Phong khong co nguoi o!" << endl;
            return;
        }

        // Tao hoa don
        HoaDon hd;
        soHoaDon++;
        hd.maHoaDon = "HD" + IntToStr(soHoaDon);
        hd.maPhong = maPhong;

        cout << "Nhap ten khach: ";
        cin.ignore();
        getline(cin, hd.tenKH);

        cout << "Nhap ngay check in (dd/mm/yyyy): ";
        cin >> hd.ngayCheckIn;

        hd.ngayCheckOut = GetCurrentDate();

        cout << "Nhap so ngay o: ";
        cin >> hd.soNgay;

        hd.tienPhong = dsPhong[viTri].giaPhong * hd.soNgay;

        cout << "Nhap tien dich vu (0 neu khong co): ";
        cin >> hd.tienDichVu;

        cout << "Nhap tien coc da tra: ";
        cin >> hd.tienCoc;

        hd.tongTien = hd.tienPhong + hd.tienDichVu;
        hd.conLai = hd.tongTien - hd.tienCoc;

        // In hoa don
        cout << "\n========================================" << endl;
        cout << "       KHACH SAN ABC" << endl;
        cout << "========================================" << endl;
        cout << "       HOA DON THANH TOAN" << endl;
        cout << "========================================" << endl;
        cout << "Ma hoa don: " << hd.maHoaDon << endl;
        cout << "Phong: " << hd.maPhong << " - " << dsPhong[viTri].loaiPhong << endl;
        cout << "Khach hang: " << hd.tenKH << endl;
        cout << "----------------------------------------" << endl;
        cout << "Check in: " << hd.ngayCheckIn << endl;
        cout << "Check out: " << hd.ngayCheckOut << endl;
        cout << "So ngay o: " << hd.soNgay << endl;
        cout << "----------------------------------------" << endl;
        cout << "Tien phong: " << hd.tienPhong << " VND" << endl;
        cout << "Tien dich vu: " << hd.tienDichVu << " VND" << endl;
        cout << "Tong tien: " << hd.tongTien << " VND" << endl;
        cout << "Tien coc: " << hd.tienCoc << " VND" << endl;
        cout << "========================================" << endl;
        cout << "CON LAI: " << hd.conLai << " VND" << endl;
        cout << "========================================" << endl;
        cout << "\n   CAM ON QUY KHACH!" << endl;
        cout << "   HEN GAP LAI!" << endl;

        // Luu hoa don
        try {
            ofstream outFile("HoaDon_" + hd.maHoaDon + ".txt");
            if (outFile.is_open()) {
                outFile << "========================================" << endl;
                outFile << "       HOA DON THANH TOAN" << endl;
                outFile << "========================================" << endl;
                outFile << "Ma: " << hd.maHoaDon << endl;
                outFile << "Phong: " << hd.maPhong << endl;
                outFile << "Khach: " << hd.tenKH << endl;
                outFile << "Tong tien: " << hd.tongTien << " VND" << endl;
                outFile << "Con lai: " << hd.conLai << " VND" << endl;
                outFile.close();
            }
        } catch (exception& e) {
            cout << "Loi luu hoa don: " << e.what() << endl;
        }

        // Cap nhat trang thai phong
        dsPhong[viTri].trangThai = "Trong";
        LuuFilePhong(dsPhong, demPhong, "DanhSachPhong.txt");

        cout << "\nCheck out thanh cong!" << endl;

    } catch (exception& e) {
        cout << "Loi: " << e.what() << endl;
    }
}

// ========== MAIN ==========

int main() {
    cout << "=== HE THONG QUAN LY KHACH SAN ===" << endl;

    const int MAX = 100;
    Phong* dsPhong = new Phong[MAX];
    int demPhong = 0;
    int soDatPhong = 0;
    int soHoaDon = 0;

    // Doc du lieu
    DocFilePhong(dsPhong, demPhong, "DanhSachPhong.txt");

    if (demPhong == 0) {
        cout << "Canh bao: Chua co danh sach phong!" << endl;
    }

    // Menu
    int luaChon;
    do {
        cout << "\n========== MENU ==========" << endl;
        cout << "1. Hien thi danh sach phong" << endl;
        cout << "2. Hien thi phong trong" << endl;
        cout << "3. Dat phong" << endl;
        cout << "4. Check in" << endl;
        cout << "5. Check out" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                HienThiPhong(dsPhong, demPhong);
                break;
            case 2:
                HienThiPhongTrong(dsPhong, demPhong);
                break;
            case 3:
                DatPhong(dsPhong, demPhong, soDatPhong);
                break;
            case 4:
                CheckIn(dsPhong, demPhong);
                break;
            case 5:
                CheckOut(dsPhong, demPhong, soHoaDon);
                break;
            case 0:
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }

    } while (luaChon != 0);

    // Giai phong
    delete[] dsPhong;

    return 0;
}
