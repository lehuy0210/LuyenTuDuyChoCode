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

string GetCurrentDateTime() {
    time_t now = time(0);
    tm* dt = localtime(&now);

    string result = IntToStr(dt->tm_mday) + "/"
                  + IntToStr(dt->tm_mon + 1) + "/"
                  + IntToStr(dt->tm_year + 1900) + " "
                  + IntToStr(dt->tm_hour) + ":"
                  + IntToStr(dt->tm_min) + ":"
                  + IntToStr(dt->tm_sec);

    return result;
}

// ========== CAU TRUC DU LIEU ==========

struct MonAn {
    string maMonAn;
    string tenMonAn;
    string loai;  // Khai vi, Mon chinh, Trang mieng, Nuoc uong
    float donGia;
    bool conMon;
};

struct BanAn {
    int soBan;
    int soChoNgoi;
    string trangThai;  // Trong, DangPhucVu, DaDat
};

struct ChiTietOrder {
    string maMonAn;
    string tenMonAn;
    float donGia;
    int soLuong;
    string ghiChu;  // Vi du: "Khong hanh", "It cay"
    float thanhTien;
};

struct Order {
    string maOrder;
    int soBan;
    string ngayGio;
    ChiTietOrder* dsChiTiet;
    int soLuongChiTiet;
    float tongTien;
    float phiPhucVu;  // 10% service charge
    float thue;       // 8% VAT
    float tienTip;
    float tongThanhToan;
    string trangThai;  // DangPhucVu, DaThanhToan
};

// ========== FILE I/O ==========

void DocFileMenu(MonAn* dsMenu, int& demMenu, const string& file) {
    try {
        ifstream inFile(file);
        if (!inFile.is_open()) {
            throw runtime_error("Khong the mo file menu");
        }

        demMenu = 0;
        string line;
        getline(inFile, line); // Skip header

        while (getline(inFile, line) && demMenu < 100) {
            string parts[5] = {"", "", "", "", ""};
            int pos = 0;

            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    pos++;
                    if (pos >= 5) break;
                } else {
                    parts[pos] += line[i];
                }
            }

            dsMenu[demMenu].maMonAn = parts[0];
            dsMenu[demMenu].tenMonAn = parts[1];
            dsMenu[demMenu].loai = parts[2];
            dsMenu[demMenu].donGia = StrToFloat(parts[3]);
            dsMenu[demMenu].conMon = (parts[4] == "1" || parts[4] == "true");

            demMenu++;
        }

        inFile.close();
        cout << "Doc menu thanh cong: " << demMenu << " mon" << endl;

    } catch (exception& e) {
        cout << "Loi doc file: " << e.what() << endl;
    }
}

void DocFileBanAn(BanAn* dsBan, int& demBan, const string& file) {
    try {
        ifstream inFile(file);
        if (!inFile.is_open()) {
            throw runtime_error("Khong the mo file ban an");
        }

        demBan = 0;
        string line;
        getline(inFile, line); // Skip header

        while (getline(inFile, line) && demBan < 50) {
            string parts[3] = {"", "", ""};
            int pos = 0;

            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    pos++;
                    if (pos >= 3) break;
                } else {
                    parts[pos] += line[i];
                }
            }

            dsBan[demBan].soBan = StrToInt(parts[0]);
            dsBan[demBan].soChoNgoi = StrToInt(parts[1]);
            dsBan[demBan].trangThai = parts[2];

            demBan++;
        }

        inFile.close();
        cout << "Doc danh sach ban thanh cong: " << demBan << " ban" << endl;

    } catch (exception& e) {
        cout << "Loi doc file: " << e.what() << endl;
    }
}

void LuuFileBanAn(BanAn* dsBan, int demBan, const string& file) {
    try {
        ofstream outFile(file);
        if (!outFile.is_open()) {
            throw runtime_error("Khong the luu file ban an");
        }

        outFile << "SoBan,SoChoNgoi,TrangThai" << endl;

        for (int i = 0; i < demBan; i++) {
            outFile << dsBan[i].soBan << ","
                    << dsBan[i].soChoNgoi << ","
                    << dsBan[i].trangThai << endl;
        }

        outFile.close();

    } catch (exception& e) {
        cout << "Loi luu file: " << e.what() << endl;
    }
}

// ========== HIEN THI ==========

void HienThiMenu(MonAn* dsMenu, int demMenu) {
    cout << "\n===== MENU NHA HANG =====" << endl;

    // Hien thi theo loai
    string loais[] = {"KhaiVi", "MonChinh", "TrangMieng", "NuocUong"};
    string tenLoais[] = {"KHAI VI", "MON CHINH", "TRANG MIENG", "NUOC UONG"};

    for (int l = 0; l < 4; l++) {
        cout << "\n--- " << tenLoais[l] << " ---" << endl;
        cout << "Ma\tTen Mon\t\t\tDon Gia\t\tTinh Trang" << endl;
        cout << "----------------------------------------------------------------" << endl;

        for (int i = 0; i < demMenu; i++) {
            if (dsMenu[i].loai == loais[l]) {
                cout << dsMenu[i].maMonAn << "\t"
                     << dsMenu[i].tenMonAn << "\t\t"
                     << dsMenu[i].donGia << "\t\t"
                     << (dsMenu[i].conMon ? "Con mon" : "Het mon") << endl;
            }
        }
    }
    cout << endl;
}

void HienThiBanAn(BanAn* dsBan, int demBan) {
    cout << "\n===== DANH SACH BAN AN =====" << endl;
    cout << "So Ban\tSo Cho\tTrang Thai" << endl;
    cout << "--------------------------------" << endl;

    for (int i = 0; i < demBan; i++) {
        cout << dsBan[i].soBan << "\t"
             << dsBan[i].soChoNgoi << "\t"
             << dsBan[i].trangThai << endl;
    }
    cout << endl;
}

// ========== TIM KIEM ==========

int TimMonAnTheoMa(MonAn* dsMenu, int demMenu, const string& ma) {
    for (int i = 0; i < demMenu; i++) {
        if (dsMenu[i].maMonAn == ma) {
            return i;
        }
    }
    return -1;
}

int TimBanTheoSo(BanAn* dsBan, int demBan, int soBan) {
    for (int i = 0; i < demBan; i++) {
        if (dsBan[i].soBan == soBan) {
            return i;
        }
    }
    return -1;
}

// ========== TAO ORDER ==========

void TaoOrder(MonAn* dsMenu, int demMenu, BanAn* dsBan, int demBan, int& soOrder) {
    try {
        cout << "\n===== TAO ORDER MOI =====" << endl;

        // Chon ban
        HienThiBanAn(dsBan, demBan);

        int soBan;
        cout << "Chon so ban: ";
        cin >> soBan;

        int viTriBan = TimBanTheoSo(dsBan, demBan, soBan);
        if (viTriBan == -1) {
            cout << "Khong tim thay ban!" << endl;
            return;
        }

        if (dsBan[viTriBan].trangThai != "Trong") {
            cout << "Ban dang duoc su dung hoac da dat!" << endl;
            return;
        }

        // Tao order
        Order order;
        soOrder++;
        order.maOrder = "ORD" + IntToStr(soOrder);
        order.soBan = soBan;
        order.ngayGio = GetCurrentDateTime();
        order.dsChiTiet = new ChiTietOrder[50];
        order.soLuongChiTiet = 0;
        order.tongTien = 0.0;
        order.trangThai = "DangPhucVu";

        // Dat ban
        dsBan[viTriBan].trangThai = "DangPhucVu";

        // Goi mon
        char tiepTuc = 'y';
        do {
            HienThiMenu(dsMenu, demMenu);

            string maMon;
            cout << "Nhap ma mon: ";
            cin >> maMon;

            int viTriMon = TimMonAnTheoMa(dsMenu, demMenu, maMon);

            if (viTriMon == -1) {
                cout << "Khong tim thay mon!" << endl;
                continue;
            }

            if (!dsMenu[viTriMon].conMon) {
                cout << "Mon da het!" << endl;
                continue;
            }

            int soLuong;
            cout << "Nhap so luong: ";
            cin >> soLuong;

            if (soLuong <= 0) {
                cout << "So luong khong hop le!" << endl;
                continue;
            }

            // Ghi chu
            string ghiChu;
            cout << "Ghi chu (Enter de bo qua): ";
            cin.ignore();
            getline(cin, ghiChu);

            // Them vao order
            ChiTietOrder ct;
            ct.maMonAn = dsMenu[viTriMon].maMonAn;
            ct.tenMonAn = dsMenu[viTriMon].tenMonAn;
            ct.donGia = dsMenu[viTriMon].donGia;
            ct.soLuong = soLuong;
            ct.ghiChu = ghiChu;
            ct.thanhTien = ct.donGia * soLuong;

            order.dsChiTiet[order.soLuongChiTiet] = ct;
            order.soLuongChiTiet++;
            order.tongTien += ct.thanhTien;

            cout << "Da them mon vao order!" << endl;

            cout << "Tiep tuc goi mon? (y/n): ";
            cin >> tiepTuc;

        } while (tiepTuc == 'y' || tiepTuc == 'Y');

        if (order.soLuongChiTiet == 0) {
            cout << "Order rong, huy tao!" << endl;
            dsBan[viTriBan].trangThai = "Trong";
            delete[] order.dsChiTiet;
            return;
        }

        // Tinh toan
        order.phiPhucVu = order.tongTien * 0.10;  // 10%
        order.thue = (order.tongTien + order.phiPhucVu) * 0.08;  // 8%
        order.tienTip = 0.0;  // Se nhap khi thanh toan
        order.tongThanhToan = order.tongTien + order.phiPhucVu + order.thue;

        // In order
        cout << "\n========================================" << endl;
        cout << "       NHA HANG XYZ" << endl;
        cout << "========================================" << endl;
        cout << "Ma Order: " << order.maOrder << endl;
        cout << "Ban so: " << order.soBan << endl;
        cout << "Ngay gio: " << order.ngayGio << endl;
        cout << "----------------------------------------" << endl;
        cout << "STT\tMa\tTen Mon\t\tSL\tDon Gia\t\tThanh Tien" << endl;
        cout << "----------------------------------------" << endl;

        for (int i = 0; i < order.soLuongChiTiet; i++) {
            cout << (i + 1) << "\t"
                 << order.dsChiTiet[i].maMonAn << "\t"
                 << order.dsChiTiet[i].tenMonAn << "\t"
                 << order.dsChiTiet[i].soLuong << "\t"
                 << order.dsChiTiet[i].donGia << "\t\t"
                 << order.dsChiTiet[i].thanhTien << endl;

            if (order.dsChiTiet[i].ghiChu.length() > 0) {
                cout << "\t\t* Ghi chu: " << order.dsChiTiet[i].ghiChu << endl;
            }
        }

        cout << "----------------------------------------" << endl;
        cout << "Tong tien:\t\t\t\t" << order.tongTien << " VND" << endl;
        cout << "Phi phuc vu (10%):\t\t\t" << order.phiPhucVu << " VND" << endl;
        cout << "Thue (8%):\t\t\t\t" << order.thue << " VND" << endl;
        cout << "========================================" << endl;
        cout << "TONG THANH TOAN:\t\t\t" << order.tongThanhToan << " VND" << endl;
        cout << "========================================" << endl;

        // Luu order vao file
        try {
            ofstream outFile("Order_" + order.maOrder + ".txt");
            if (outFile.is_open()) {
                outFile << "========================================" << endl;
                outFile << "       NHA HANG XYZ" << endl;
                outFile << "========================================" << endl;
                outFile << "Ma Order: " << order.maOrder << endl;
                outFile << "Ban so: " << order.soBan << endl;
                outFile << "Ngay gio: " << order.ngayGio << endl;
                outFile << "----------------------------------------" << endl;
                outFile << "STT\tMa\tTen Mon\t\tSL\tDon Gia\t\tThanh Tien" << endl;
                outFile << "----------------------------------------" << endl;

                for (int i = 0; i < order.soLuongChiTiet; i++) {
                    outFile << (i + 1) << "\t"
                           << order.dsChiTiet[i].maMonAn << "\t"
                           << order.dsChiTiet[i].tenMonAn << "\t"
                           << order.dsChiTiet[i].soLuong << "\t"
                           << order.dsChiTiet[i].donGia << "\t\t"
                           << order.dsChiTiet[i].thanhTien << endl;

                    if (order.dsChiTiet[i].ghiChu.length() > 0) {
                        outFile << "\t\t* Ghi chu: " << order.dsChiTiet[i].ghiChu << endl;
                    }
                }

                outFile << "----------------------------------------" << endl;
                outFile << "Tong tien:\t\t\t\t" << order.tongTien << " VND" << endl;
                outFile << "Phi phuc vu (10%):\t\t\t" << order.phiPhucVu << " VND" << endl;
                outFile << "Thue (8%):\t\t\t\t" << order.thue << " VND" << endl;
                outFile << "========================================" << endl;
                outFile << "TONG THANH TOAN:\t\t\t" << order.tongThanhToan << " VND" << endl;
                outFile << "========================================" << endl;
                outFile << "\n   CAM ON QUY KHACH!" << endl;
                outFile << "   HEN GAP LAI!" << endl;

                outFile.close();
                cout << "\nDa luu order: Order_" << order.maOrder << ".txt" << endl;
            }
        } catch (exception& e) {
            cout << "Loi luu order: " << e.what() << endl;
        }

        // Cap nhat trang thai ban
        LuuFileBanAn(dsBan, demBan, "DanhSachBanAn.txt");

        // Giai phong bo nho
        delete[] order.dsChiTiet;

    } catch (exception& e) {
        cout << "Loi: " << e.what() << endl;
    }
}

// ========== MAIN ==========

int main() {
    cout << "=== HE THONG QUAN LY NHA HANG ===" << endl;

    const int MAX_MENU = 100;
    const int MAX_BAN = 50;

    MonAn* dsMenu = new MonAn[MAX_MENU];
    BanAn* dsBan = new BanAn[MAX_BAN];

    int demMenu = 0;
    int demBan = 0;
    int soOrder = 0;

    // Doc du lieu
    DocFileMenu(dsMenu, demMenu, "Menu.txt");
    DocFileBanAn(dsBan, demBan, "DanhSachBanAn.txt");

    if (demMenu == 0) {
        cout << "Canh bao: Chua co menu!" << endl;
    }

    if (demBan == 0) {
        cout << "Canh bao: Chua co ban an!" << endl;
    }

    // Menu
    int luaChon;
    do {
        cout << "\n========== MENU ==========" << endl;
        cout << "1. Hien thi menu" << endl;
        cout << "2. Hien thi danh sach ban" << endl;
        cout << "3. Tao order moi" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                HienThiMenu(dsMenu, demMenu);
                break;
            case 2:
                HienThiBanAn(dsBan, demBan);
                break;
            case 3:
                TaoOrder(dsMenu, demMenu, dsBan, demBan, soOrder);
                break;
            case 0:
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }

    } while (luaChon != 0);

    // Giai phong
    delete[] dsMenu;
    delete[] dsBan;

    return 0;
}
