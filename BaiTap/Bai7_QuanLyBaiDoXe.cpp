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
    return IntToStr(dt->tm_mday) + "/" + IntToStr(dt->tm_mon + 1) + "/"
           + IntToStr(dt->tm_year + 1900) + " "
           + IntToStr(dt->tm_hour) + ":" + IntToStr(dt->tm_min);
}

void GetCurrentTime(int& gio, int& phut) {
    time_t now = time(0);
    tm* dt = localtime(&now);
    gio = dt->tm_hour;
    phut = dt->tm_min;
}

// ========== CAU TRUC DU LIEU ==========

struct ChoDoXe {
    int soCho;
    string loaiXe;      // XeMay, OTo
    string trangThai;   // Trong, DangSuDung
    string bienSo;      // Biển số xe đang đỗ
};

struct BangGia {
    string loaiXe;
    float giaGio1;      // Giờ đầu
    float giaGioTiep;   // Giờ tiếp theo
    float giaQuaDem;    // Qua đêm (22h-6h)
};

struct VeGuiXe {
    string maVe;
    string bienSo;
    string loaiXe;
    int soCho;
    string gioVao;
    string gioRa;
    int soGio;
    float tienGui;
};

// ========== FILE I/O ==========

void DocFileChoDoXe(ChoDoXe* dsCho, int& demCho, const string& file) {
    try {
        ifstream inFile(file);
        if (!inFile.is_open()) {
            throw runtime_error("Khong the mo file cho do xe");
        }
        demCho = 0;
        string line;
        getline(inFile, line); // Skip header
        while (getline(inFile, line) && demCho < 200) {
            string parts[4] = {"", "", "", ""};
            int pos = 0;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    pos++;
                    if (pos >= 4) break;
                } else {
                    parts[pos] += line[i];
                }
            }
            dsCho[demCho].soCho = StrToInt(parts[0]);
            dsCho[demCho].loaiXe = parts[1];
            dsCho[demCho].trangThai = parts[2];
            dsCho[demCho].bienSo = parts[3];
            demCho++;
        }
        inFile.close();
        cout << "Doc file cho do xe thanh cong: " << demCho << " cho" << endl;
    } catch (exception& e) {
        cout << "Loi doc file: " << e.what() << endl;
    }
}

void LuuFileChoDoXe(ChoDoXe* dsCho, int demCho, const string& file) {
    try {
        ofstream outFile(file);
        if (!outFile.is_open()) {
            throw runtime_error("Khong the luu file");
        }
        outFile << "SoCho,LoaiXe,TrangThai,BienSo" << endl;
        for (int i = 0; i < demCho; i++) {
            outFile << dsCho[i].soCho << ","
                    << dsCho[i].loaiXe << ","
                    << dsCho[i].trangThai << ","
                    << dsCho[i].bienSo << endl;
        }
        outFile.close();
    } catch (exception& e) {
        cout << "Loi luu file: " << e.what() << endl;
    }
}

void DocFileBangGia(BangGia* dsBangGia, int& demBangGia, const string& file) {
    try {
        ifstream inFile(file);
        if (!inFile.is_open()) {
            throw runtime_error("Khong the mo file bang gia");
        }
        demBangGia = 0;
        string line;
        getline(inFile, line); // Skip header
        while (getline(inFile, line) && demBangGia < 10) {
            string parts[4] = {"", "", "", ""};
            int pos = 0;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    pos++;
                    if (pos >= 4) break;
                } else {
                    parts[pos] += line[i];
                }
            }
            dsBangGia[demBangGia].loaiXe = parts[0];
            dsBangGia[demBangGia].giaGio1 = StrToFloat(parts[1]);
            dsBangGia[demBangGia].giaGioTiep = StrToFloat(parts[2]);
            dsBangGia[demBangGia].giaQuaDem = StrToFloat(parts[3]);
            demBangGia++;
        }
        inFile.close();
        cout << "Doc bang gia thanh cong" << endl;
    } catch (exception& e) {
        cout << "Loi doc file: " << e.what() << endl;
    }
}

// ========== HIEN THI ==========

void HienThiChoDoXe(ChoDoXe* dsCho, int demCho) {
    cout << "\n===== DANH SACH CHO DO XE =====" << endl;
    cout << "So Cho\tLoai Xe\t\tTrang Thai\tBien So" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (int i = 0; i < demCho; i++) {
        cout << dsCho[i].soCho << "\t"
             << dsCho[i].loaiXe << "\t\t"
             << dsCho[i].trangThai << "\t\t"
             << dsCho[i].bienSo << endl;
    }
    cout << endl;
}

void HienThiChoTrong(ChoDoXe* dsCho, int demCho, const string& loaiXe) {
    cout << "\n===== CHO TRONG - " << loaiXe << " =====" << endl;
    bool coChoTrong = false;
    for (int i = 0; i < demCho; i++) {
        if (dsCho[i].trangThai == "Trong" && dsCho[i].loaiXe == loaiXe) {
            cout << "Cho so: " << dsCho[i].soCho << endl;
            coChoTrong = true;
        }
    }
    if (!coChoTrong) {
        cout << "Het cho!" << endl;
    }
    cout << endl;
}

void HienThiBangGia(BangGia* dsBangGia, int demBangGia) {
    cout << "\n===== BANG GIA GUI XE =====" << endl;
    cout << "Loai Xe\t\tGio 1\t\tGio Tiep\tQua Dem" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (int i = 0; i < demBangGia; i++) {
        cout << dsBangGia[i].loaiXe << "\t\t"
             << dsBangGia[i].giaGio1 << "\t\t"
             << dsBangGia[i].giaGioTiep << "\t\t"
             << dsBangGia[i].giaQuaDem << endl;
    }
    cout << endl;
}

// ========== TIM KIEM ==========

int TimChoTrongTheoLoai(ChoDoXe* dsCho, int demCho, const string& loaiXe) {
    for (int i = 0; i < demCho; i++) {
        if (dsCho[i].trangThai == "Trong" && dsCho[i].loaiXe == loaiXe) {
            return i;
        }
    }
    return -1;
}

int TimChoTheoBienSo(ChoDoXe* dsCho, int demCho, const string& bienSo) {
    for (int i = 0; i < demCho; i++) {
        if (dsCho[i].bienSo == bienSo && dsCho[i].trangThai == "DangSuDung") {
            return i;
        }
    }
    return -1;
}

int TimBangGiaTheoLoai(BangGia* dsBangGia, int demBangGia, const string& loaiXe) {
    for (int i = 0; i < demBangGia; i++) {
        if (dsBangGia[i].loaiXe == loaiXe) {
            return i;
        }
    }
    return -1;
}

// ========== TINH TIEN ==========

int TinhSoGio(const string& gioVao, const string& gioRa) {
    // Don gian hoa: gio hien tai - gio vao
    // Trong thuc te can parse chinh xac

    int gioV, phutV, gioR, phutR;

    // Parse gio vao (hh:mm)
    string gioStr = "", phutStr = "";
    bool coHai = false;
    for (int i = 0; i < gioVao.length(); i++) {
        if (gioVao[i] == ':') {
            coHai = true;
        } else {
            if (!coHai) {
                gioStr += gioVao[i];
            } else {
                phutStr += gioVao[i];
            }
        }
    }
    gioV = StrToInt(gioStr);
    phutV = StrToInt(phutStr);

    // Parse gio ra
    gioStr = "";
    phutStr = "";
    coHai = false;
    for (int i = 0; i < gioRa.length(); i++) {
        if (gioRa[i] == ':') {
            coHai = true;
        } else {
            if (!coHai) {
                gioStr += gioRa[i];
            } else {
                phutStr += gioRa[i];
            }
        }
    }
    gioR = StrToInt(gioStr);
    phutR = StrToInt(phutStr);

    // Tinh so gio (lam tron len)
    int tongPhutVao = gioV * 60 + phutV;
    int tongPhutRa = gioR * 60 + phutR;

    int soPhut = tongPhutRa - tongPhutVao;
    if (soPhut < 0) soPhut += 24 * 60; // Qua ngay

    int soGio = soPhut / 60;
    if (soPhut % 60 > 0) soGio++; // Lam tron len

    return soGio;
}

float TinhTienGui(int soGio, BangGia bangGia, int gioVao) {
    if (soGio <= 0) return 0.0;

    float tongTien = 0.0;

    // Gio dau tien
    tongTien = bangGia.giaGio1;

    // Cac gio tiep theo
    if (soGio > 1) {
        tongTien += (soGio - 1) * bangGia.giaGioTiep;
    }

    // Qua dem (22h-6h): tinh them
    if (gioVao >= 22 || gioVao < 6) {
        tongTien += bangGia.giaQuaDem;
    }

    return tongTien;
}

// ========== VAO BAI ==========

void VaoBai(ChoDoXe* dsCho, int demCho, int& soVe) {
    try {
        cout << "\n===== VAO BAI DO XE =====" << endl;

        string loaiXe;
        cout << "Loai xe (XeMay/OTo): ";
        cin >> loaiXe;

        // Tim cho trong
        int viTri = TimChoTrongTheoLoai(dsCho, demCho, loaiXe);
        if (viTri == -1) {
            cout << "Het cho do " << loaiXe << "!" << endl;
            return;
        }

        string bienSo;
        cout << "Nhap bien so: ";
        cin >> bienSo;

        // Tao ve
        VeGuiXe ve;
        soVe++;
        ve.maVe = "V" + IntToStr(soVe);
        ve.bienSo = bienSo;
        ve.loaiXe = loaiXe;
        ve.soCho = dsCho[viTri].soCho;
        ve.gioVao = GetCurrentDateTime();

        // Cap nhat cho do
        dsCho[viTri].trangThai = "DangSuDung";
        dsCho[viTri].bienSo = bienSo;

        // In ve
        cout << "\n========================================" << endl;
        cout << "       VE GUI XE" << endl;
        cout << "       BAI DO XE ABC" << endl;
        cout << "========================================" << endl;
        cout << "Ma ve: " << ve.maVe << endl;
        cout << "Bien so: " << ve.bienSo << endl;
        cout << "Loai xe: " << ve.loaiXe << endl;
        cout << "So cho: " << ve.soCho << endl;
        cout << "Gio vao: " << ve.gioVao << endl;
        cout << "========================================" << endl;
        cout << "Vui long giu ve de lay xe!" << endl;
        cout << "========================================" << endl;

        // Luu ve
        try {
            ofstream outFile("VeGuiXe.txt", ios::app);
            if (outFile.is_open()) {
                outFile << ve.maVe << ","
                        << ve.bienSo << ","
                        << ve.loaiXe << ","
                        << ve.soCho << ","
                        << ve.gioVao << ","
                        << "ChuaRa" << ","
                        << "0" << ","
                        << "0" << endl;
                outFile.close();
            }
        } catch (exception& e) {
            cout << "Loi luu ve: " << e.what() << endl;
        }

        // Luu file cho do
        LuuFileChoDoXe(dsCho, demCho, "DanhSachChoDoXe.txt");

        cout << "\nVao bai thanh cong!" << endl;

    } catch (exception& e) {
        cout << "Loi: " << e.what() << endl;
    }
}

// ========== RA BAI ==========

void RaBai(ChoDoXe* dsCho, int demCho, BangGia* dsBangGia, int demBangGia) {
    try {
        cout << "\n===== RA BAI DO XE =====" << endl;

        string bienSo;
        cout << "Nhap bien so: ";
        cin >> bienSo;

        // Tim cho do
        int viTri = TimChoTheoBienSo(dsCho, demCho, bienSo);
        if (viTri == -1) {
            cout << "Khong tim thay xe!" << endl;
            return;
        }

        // Tim bang gia
        int viTriGia = TimBangGiaTheoLoai(dsBangGia, demBangGia, dsCho[viTri].loaiXe);

        // Lay gio vao (can doc tu file VeGuiXe.txt)
        string gioVao = "08:00"; // Gia su
        string gioRa = GetCurrentDateTime();

        // Tinh tien
        int gioVaoInt, phutVaoInt;
        GetCurrentTime(gioVaoInt, phutVaoInt);

        int soGio = TinhSoGio(gioVao, gioRa);
        float tienGui = TinhTienGui(soGio, dsBangGia[viTriGia], gioVaoInt);

        // In hoa don
        cout << "\n========================================" << endl;
        cout << "       HOA DON GUI XE" << endl;
        cout << "       BAI DO XE ABC" << endl;
        cout << "========================================" << endl;
        cout << "Bien so: " << bienSo << endl;
        cout << "Loai xe: " << dsCho[viTri].loaiXe << endl;
        cout << "So cho: " << dsCho[viTri].soCho << endl;
        cout << "----------------------------------------" << endl;
        cout << "Gio vao: " << gioVao << endl;
        cout << "Gio ra: " << gioRa << endl;
        cout << "So gio: " << soGio << " gio" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Tien gui: " << tienGui << " VND" << endl;
        cout << "========================================" << endl;
        cout << "   CAM ON QUY KHACH!" << endl;
        cout << "   HEN GAP LAI!" << endl;
        cout << "========================================" << endl;

        // Cap nhat cho do
        dsCho[viTri].trangThai = "Trong";
        dsCho[viTri].bienSo = "";

        // Luu file
        LuuFileChoDoXe(dsCho, demCho, "DanhSachChoDoXe.txt");

        cout << "\nRa bai thanh cong!" << endl;

    } catch (exception& e) {
        cout << "Loi: " << e.what() << endl;
    }
}

// ========== THONG KE ==========

void ThongKe(ChoDoXe* dsCho, int demCho) {
    cout << "\n===== THONG KE =====" << endl;

    int tongXeMay = 0, tongOTo = 0;
    int xeMayDang = 0, oToDang = 0;
    int xeMayTrong = 0, oToTrong = 0;

    for (int i = 0; i < demCho; i++) {
        if (dsCho[i].loaiXe == "XeMay") {
            tongXeMay++;
            if (dsCho[i].trangThai == "DangSuDung") {
                xeMayDang++;
            } else {
                xeMayTrong++;
            }
        } else if (dsCho[i].loaiXe == "OTo") {
            tongOTo++;
            if (dsCho[i].trangThai == "DangSuDung") {
                oToDang++;
            } else {
                oToTrong++;
            }
        }
    }

    cout << "XE MAY:" << endl;
    cout << "  Tong: " << tongXeMay << endl;
    cout << "  Dang su dung: " << xeMayDang << endl;
    cout << "  Trong: " << xeMayTrong << endl;

    cout << "\nO TO:" << endl;
    cout << "  Tong: " << tongOTo << endl;
    cout << "  Dang su dung: " << oToDang << endl;
    cout << "  Trong: " << oToTrong << endl;

    float tyLeLapDay = (float)(xeMayDang + oToDang) / (tongXeMay + tongOTo) * 100;
    cout << "\nTy le lap day: " << tyLeLapDay << "%" << endl;
}

// ========== MAIN ==========

int main() {
    cout << "=== HE THONG QUAN LY BAI DO XE ===" << endl;

    const int MAX_CHO = 200;
    const int MAX_BANGGIA = 10;

    ChoDoXe* dsCho = new ChoDoXe[MAX_CHO];
    BangGia* dsBangGia = new BangGia[MAX_BANGGIA];

    int demCho = 0;
    int demBangGia = 0;
    int soVe = 0;

    // Doc du lieu
    DocFileChoDoXe(dsCho, demCho, "DanhSachChoDoXe.txt");
    DocFileBangGia(dsBangGia, demBangGia, "BangGia.txt");

    if (demCho == 0) {
        cout << "Canh bao: Chua co cho do xe!" << endl;
    }

    // Menu
    int luaChon;
    do {
        cout << "\n========== MENU ==========" << endl;
        cout << "1. Hien thi danh sach cho do" << endl;
        cout << "2. Hien thi bang gia" << endl;
        cout << "3. Vao bai" << endl;
        cout << "4. Ra bai" << endl;
        cout << "5. Thong ke" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                HienThiChoDoXe(dsCho, demCho);
                break;
            case 2:
                HienThiBangGia(dsBangGia, demBangGia);
                break;
            case 3:
                VaoBai(dsCho, demCho, soVe);
                break;
            case 4:
                RaBai(dsCho, demCho, dsBangGia, demBangGia);
                break;
            case 5:
                ThongKe(dsCho, demCho);
                break;
            case 0:
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }

    } while (luaChon != 0);

    // Giai phong
    delete[] dsCho;
    delete[] dsBangGia;

    return 0;
}
