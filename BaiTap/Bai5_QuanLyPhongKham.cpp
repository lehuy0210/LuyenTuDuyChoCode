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
                  + IntToStr(dt->tm_min);

    return result;
}

// ========== CAU TRUC DU LIEU ==========

struct BenhNhan {
    string maBN;
    string hoTen;
    int namSinh;
    string gioiTinh;
    string soDienThoai;
    string diaChi;
    string tienSuBenh;  // Benh man tinh, di ung...
};

struct BacSi {
    string maBS;
    string hoTen;
    string chuyenKhoa;
    string soPhongKham;
    string lichLamViec;  // "Sang: 8h-12h, Chieu: 14h-18h"
};

struct DichVuKham {
    string maDV;
    string tenDichVu;
    float donGia;
    string moTa;
};

struct LichHen {
    string maLichHen;
    string maBN;
    string tenBN;
    string maBS;
    string tenBS;
    string ngayHen;      // dd/mm/yyyy
    string gioHen;       // hh:mm
    string lyDoKham;
    string trangThai;    // DaDat, DaKham, HuyHen
};

struct PhieuKham {
    string maPhieuKham;
    string maBN;
    string tenBN;
    string maBS;
    string tenBS;
    string ngayKham;
    string chanDoan;
    string ghiChu;
    string* dsMaDV;      // Danh sach dich vu da su dung
    int soLuongDV;
    float tongTienDichVu;
    float tienKham;
    float tienThuoc;
    float tongTien;
};

// ========== FILE I/O ==========

void DocFileBenhNhan(BenhNhan* dsBN, int& demBN, const string& file) {
    try {
        ifstream inFile(file);
        if (!inFile.is_open()) {
            cout << "File benh nhan chua ton tai, tao moi..." << endl;
            return;
        }

        demBN = 0;
        string line;
        getline(inFile, line); // Skip header

        while (getline(inFile, line) && demBN < 500) {
            string parts[7] = {"", "", "", "", "", "", ""};
            int pos = 0;

            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    pos++;
                    if (pos >= 7) break;
                } else {
                    parts[pos] += line[i];
                }
            }

            dsBN[demBN].maBN = parts[0];
            dsBN[demBN].hoTen = parts[1];
            dsBN[demBN].namSinh = StrToInt(parts[2]);
            dsBN[demBN].gioiTinh = parts[3];
            dsBN[demBN].soDienThoai = parts[4];
            dsBN[demBN].diaChi = parts[5];
            dsBN[demBN].tienSuBenh = parts[6];

            demBN++;
        }

        inFile.close();
        cout << "Doc file benh nhan thanh cong: " << demBN << " benh nhan" << endl;

    } catch (exception& e) {
        cout << "Loi doc file: " << e.what() << endl;
    }
}

void LuuFileBenhNhan(BenhNhan* dsBN, int demBN, const string& file) {
    try {
        ofstream outFile(file);
        if (!outFile.is_open()) {
            throw runtime_error("Khong the luu file benh nhan");
        }

        outFile << "MaBN,HoTen,NamSinh,GioiTinh,SoDienThoai,DiaChi,TienSuBenh" << endl;

        for (int i = 0; i < demBN; i++) {
            outFile << dsBN[i].maBN << ","
                    << dsBN[i].hoTen << ","
                    << dsBN[i].namSinh << ","
                    << dsBN[i].gioiTinh << ","
                    << dsBN[i].soDienThoai << ","
                    << dsBN[i].diaChi << ","
                    << dsBN[i].tienSuBenh << endl;
        }

        outFile.close();

    } catch (exception& e) {
        cout << "Loi luu file: " << e.what() << endl;
    }
}

void DocFileBacSi(BacSi* dsBS, int& demBS, const string& file) {
    try {
        ifstream inFile(file);
        if (!inFile.is_open()) {
            throw runtime_error("Khong the mo file bac si");
        }

        demBS = 0;
        string line;
        getline(inFile, line); // Skip header

        while (getline(inFile, line) && demBS < 50) {
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

            dsBS[demBS].maBS = parts[0];
            dsBS[demBS].hoTen = parts[1];
            dsBS[demBS].chuyenKhoa = parts[2];
            dsBS[demBS].soPhongKham = parts[3];
            dsBS[demBS].lichLamViec = parts[4];

            demBS++;
        }

        inFile.close();
        cout << "Doc file bac si thanh cong: " << demBS << " bac si" << endl;

    } catch (exception& e) {
        cout << "Loi doc file: " << e.what() << endl;
    }
}

void DocFileDichVu(DichVuKham* dsDV, int& demDV, const string& file) {
    try {
        ifstream inFile(file);
        if (!inFile.is_open()) {
            throw runtime_error("Khong the mo file dich vu");
        }

        demDV = 0;
        string line;
        getline(inFile, line); // Skip header

        while (getline(inFile, line) && demDV < 100) {
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

            dsDV[demDV].maDV = parts[0];
            dsDV[demDV].tenDichVu = parts[1];
            dsDV[demDV].donGia = StrToFloat(parts[2]);
            dsDV[demDV].moTa = parts[3];

            demDV++;
        }

        inFile.close();
        cout << "Doc file dich vu thanh cong: " << demDV << " dich vu" << endl;

    } catch (exception& e) {
        cout << "Loi doc file: " << e.what() << endl;
    }
}

// ========== HIEN THI ==========

void HienThiBenhNhan(BenhNhan* dsBN, int demBN) {
    if (demBN == 0) {
        cout << "Danh sach rong!" << endl;
        return;
    }

    cout << "\n===== DANH SACH BENH NHAN =====" << endl;
    cout << "Ma BN\tHo Ten\t\t\tNam Sinh\tGioi Tinh\tSDT" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (int i = 0; i < demBN; i++) {
        cout << dsBN[i].maBN << "\t"
             << dsBN[i].hoTen << "\t\t"
             << dsBN[i].namSinh << "\t\t"
             << dsBN[i].gioiTinh << "\t\t"
             << dsBN[i].soDienThoai << endl;
    }
    cout << endl;
}

void HienThiBacSi(BacSi* dsBS, int demBS) {
    cout << "\n===== DANH SACH BAC SI =====" << endl;
    cout << "Ma BS\tHo Ten\t\t\tChuyen Khoa\t\tPhong" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (int i = 0; i < demBS; i++) {
        cout << dsBS[i].maBS << "\t"
             << dsBS[i].hoTen << "\t\t"
             << dsBS[i].chuyenKhoa << "\t\t"
             << dsBS[i].soPhongKham << endl;
    }
    cout << endl;
}

void HienThiDichVu(DichVuKham* dsDV, int demDV) {
    cout << "\n===== DANH SACH DICH VU KHAM =====" << endl;
    cout << "Ma DV\tTen Dich Vu\t\t\tDon Gia" << endl;
    cout << "--------------------------------------------------------" << endl;

    for (int i = 0; i < demDV; i++) {
        cout << dsDV[i].maDV << "\t"
             << dsDV[i].tenDichVu << "\t\t\t"
             << dsDV[i].donGia << endl;
    }
    cout << endl;
}

// ========== TIM KIEM ==========

int TimBenhNhanTheoMa(BenhNhan* dsBN, int demBN, const string& ma) {
    for (int i = 0; i < demBN; i++) {
        if (dsBN[i].maBN == ma) {
            return i;
        }
    }
    return -1;
}

int TimBacSiTheoMa(BacSi* dsBS, int demBS, const string& ma) {
    for (int i = 0; i < demBS; i++) {
        if (dsBS[i].maBS == ma) {
            return i;
        }
    }
    return -1;
}

int TimDichVuTheoMa(DichVuKham* dsDV, int demDV, const string& ma) {
    for (int i = 0; i < demDV; i++) {
        if (dsDV[i].maDV == ma) {
            return i;
        }
    }
    return -1;
}

// ========== DANG KY BENH NHAN MOI ==========

void DangKyBenhNhanMoi(BenhNhan* dsBN, int& demBN, int maxBN) {
    if (demBN >= maxBN) {
        cout << "Danh sach day!" << endl;
        return;
    }

    cout << "\n===== DANG KY BENH NHAN MOI =====" << endl;

    BenhNhan bn;

    // Sinh ma benh nhan tu dong
    bn.maBN = "BN" + IntToStr(demBN + 1001);

    cout << "Ma benh nhan (tu dong): " << bn.maBN << endl;

    cout << "Nhap ho ten: ";
    cin.ignore();
    getline(cin, bn.hoTen);

    cout << "Nhap nam sinh: ";
    cin >> bn.namSinh;

    cout << "Nhap gioi tinh (Nam/Nu): ";
    cin >> bn.gioiTinh;

    cout << "Nhap so dien thoai: ";
    cin >> bn.soDienThoai;

    cout << "Nhap dia chi: ";
    cin.ignore();
    getline(cin, bn.diaChi);

    cout << "Nhap tien su benh (Enter de bo qua): ";
    getline(cin, bn.tienSuBenh);

    dsBN[demBN] = bn;
    demBN++;

    LuuFileBenhNhan(dsBN, demBN, "DanhSachBenhNhan.txt");

    cout << "Dang ky thanh cong! Ma benh nhan: " << bn.maBN << endl;
}

// ========== DAT LICH HEN ==========

void DatLichHen(BenhNhan* dsBN, int demBN, BacSi* dsBS, int demBS, int& soLichHen) {
    try {
        cout << "\n===== DAT LICH HEN KHAM =====" << endl;

        LichHen lichHen;

        // Chon benh nhan
        cout << "1. Benh nhan cu" << endl;
        cout << "2. Benh nhan moi" << endl;
        cout << "Chon: ";

        int luaChon;
        cin >> luaChon;

        if (luaChon == 2) {
            DangKyBenhNhanMoi(dsBN, demBN, 500);
        }

        HienThiBenhNhan(dsBN, demBN);

        string maBN;
        cout << "Nhap ma benh nhan: ";
        cin >> maBN;

        int viTriBN = TimBenhNhanTheoMa(dsBN, demBN, maBN);
        if (viTriBN == -1) {
            cout << "Khong tim thay benh nhan!" << endl;
            return;
        }

        lichHen.maBN = dsBN[viTriBN].maBN;
        lichHen.tenBN = dsBN[viTriBN].hoTen;

        // Chon bac si
        HienThiBacSi(dsBS, demBS);

        string maBS;
        cout << "Nhap ma bac si: ";
        cin >> maBS;

        int viTriBS = TimBacSiTheoMa(dsBS, demBS, maBS);
        if (viTriBS == -1) {
            cout << "Khong tim thay bac si!" << endl;
            return;
        }

        lichHen.maBS = dsBS[viTriBS].maBS;
        lichHen.tenBS = dsBS[viTriBS].hoTen;

        // Nhap ngay gio hen
        cout << "Nhap ngay hen (dd/mm/yyyy): ";
        cin >> lichHen.ngayHen;

        cout << "Nhap gio hen (hh:mm): ";
        cin >> lichHen.gioHen;

        cout << "Nhap ly do kham: ";
        cin.ignore();
        getline(cin, lichHen.lyDoKham);

        // Tao ma lich hen
        soLichHen++;
        lichHen.maLichHen = "LH" + IntToStr(soLichHen);
        lichHen.trangThai = "DaDat";

        // Luu lich hen
        try {
            ofstream outFile("LichHen.txt", ios::app);
            if (outFile.is_open()) {
                outFile << lichHen.maLichHen << ","
                        << lichHen.maBN << ","
                        << lichHen.tenBN << ","
                        << lichHen.maBS << ","
                        << lichHen.tenBS << ","
                        << lichHen.ngayHen << ","
                        << lichHen.gioHen << ","
                        << lichHen.lyDoKham << ","
                        << lichHen.trangThai << endl;
                outFile.close();
            }
        } catch (exception& e) {
            cout << "Loi luu lich hen: " << e.what() << endl;
        }

        // In phieu hen
        cout << "\n========================================" << endl;
        cout << "       PHIEU HEN KHAM" << endl;
        cout << "========================================" << endl;
        cout << "Ma lich hen: " << lichHen.maLichHen << endl;
        cout << "Benh nhan: " << lichHen.tenBN << " (" << lichHen.maBN << ")" << endl;
        cout << "Bac si: " << lichHen.tenBS << " (" << lichHen.maBS << ")" << endl;
        cout << "Chuyen khoa: " << dsBS[viTriBS].chuyenKhoa << endl;
        cout << "Phong kham: " << dsBS[viTriBS].soPhongKham << endl;
        cout << "Ngay hen: " << lichHen.ngayHen << endl;
        cout << "Gio hen: " << lichHen.gioHen << endl;
        cout << "Ly do: " << lichHen.lyDoKham << endl;
        cout << "========================================" << endl;
        cout << "Vui long den truoc gio hen 15 phut!" << endl;
        cout << "========================================" << endl;

        cout << "\nDat lich hen thanh cong!" << endl;

    } catch (exception& e) {
        cout << "Loi: " << e.what() << endl;
    }
}

// ========== TAO PHIEU KHAM ==========

void TaoPhieuKham(BenhNhan* dsBN, int demBN,
                  BacSi* dsBS, int demBS,
                  DichVuKham* dsDV, int demDV,
                  int& soPhieuKham) {
    try {
        cout << "\n===== TAO PHIEU KHAM BENH =====" << endl;

        PhieuKham phieu;

        // Chon benh nhan
        HienThiBenhNhan(dsBN, demBN);

        string maBN;
        cout << "Nhap ma benh nhan: ";
        cin >> maBN;

        int viTriBN = TimBenhNhanTheoMa(dsBN, demBN, maBN);
        if (viTriBN == -1) {
            cout << "Khong tim thay benh nhan!" << endl;
            return;
        }

        phieu.maBN = dsBN[viTriBN].maBN;
        phieu.tenBN = dsBN[viTriBN].hoTen;

        // Chon bac si
        HienThiBacSi(dsBS, demBS);

        string maBS;
        cout << "Nhap ma bac si: ";
        cin >> maBS;

        int viTriBS = TimBacSiTheoMa(dsBS, demBS, maBS);
        if (viTriBS == -1) {
            cout << "Khong tim thay bac si!" << endl;
            return;
        }

        phieu.maBS = dsBS[viTriBS].maBS;
        phieu.tenBS = dsBS[viTriBS].hoTen;
        phieu.ngayKham = GetCurrentDateTime();

        // Nhap chan doan
        cout << "Nhap chan doan: ";
        cin.ignore();
        getline(cin, phieu.chanDoan);

        cout << "Ghi chu: ";
        getline(cin, phieu.ghiChu);

        // Chon dich vu da su dung
        HienThiDichVu(dsDV, demDV);

        phieu.dsMaDV = new string[20];
        phieu.soLuongDV = 0;
        phieu.tongTienDichVu = 0.0;

        char tiepTuc = 'y';
        do {
            string maDV;
            cout << "Nhap ma dich vu: ";
            cin >> maDV;

            int viTriDV = TimDichVuTheoMa(dsDV, demDV, maDV);
            if (viTriDV == -1) {
                cout << "Khong tim thay dich vu!" << endl;
                continue;
            }

            phieu.dsMaDV[phieu.soLuongDV] = maDV;
            phieu.soLuongDV++;
            phieu.tongTienDichVu += dsDV[viTriDV].donGia;

            cout << "Da them dich vu: " << dsDV[viTriDV].tenDichVu << endl;

            cout << "Them dich vu? (y/n): ";
            cin >> tiepTuc;

        } while (tiepTuc == 'y' || tiepTuc == 'Y');

        // Nhap tien kham va tien thuoc
        cout << "Nhap tien kham: ";
        cin >> phieu.tienKham;

        cout << "Nhap tien thuoc: ";
        cin >> phieu.tienThuoc;

        // Tinh tong
        phieu.tongTien = phieu.tongTienDichVu + phieu.tienKham + phieu.tienThuoc;

        // Tao ma phieu
        soPhieuKham++;
        phieu.maPhieuKham = "PK" + IntToStr(soPhieuKham);

        // In phieu kham
        cout << "\n========================================" << endl;
        cout << "       PHONG KHAM ABC" << endl;
        cout << "       123 Le Loi, Q1" << endl;
        cout << "       Tel: 0123456789" << endl;
        cout << "========================================" << endl;
        cout << "       PHIEU KHAM BENH" << endl;
        cout << "========================================" << endl;
        cout << "Ma phieu: " << phieu.maPhieuKham << endl;
        cout << "Ngay kham: " << phieu.ngayKham << endl;
        cout << "----------------------------------------" << endl;
        cout << "Benh nhan: " << phieu.tenBN << " (" << phieu.maBN << ")" << endl;
        cout << "Nam sinh: " << dsBN[viTriBN].namSinh << endl;
        cout << "Gioi tinh: " << dsBN[viTriBN].gioiTinh << endl;
        cout << "Dia chi: " << dsBN[viTriBN].diaChi << endl;
        cout << "Tien su benh: " << dsBN[viTriBN].tienSuBenh << endl;
        cout << "----------------------------------------" << endl;
        cout << "Bac si kham: " << phieu.tenBS << " (" << phieu.maBS << ")" << endl;
        cout << "Chuyen khoa: " << dsBS[viTriBS].chuyenKhoa << endl;
        cout << "----------------------------------------" << endl;
        cout << "CHAN DOAN: " << phieu.chanDoan << endl;
        cout << "Ghi chu: " << phieu.ghiChu << endl;
        cout << "----------------------------------------" << endl;
        cout << "DICH VU DA SU DUNG:" << endl;

        for (int i = 0; i < phieu.soLuongDV; i++) {
            int viTri = TimDichVuTheoMa(dsDV, demDV, phieu.dsMaDV[i]);
            if (viTri != -1) {
                cout << "- " << dsDV[viTri].tenDichVu
                     << ": " << dsDV[viTri].donGia << " VND" << endl;
            }
        }

        cout << "----------------------------------------" << endl;
        cout << "Tien dich vu:\t\t" << phieu.tongTienDichVu << " VND" << endl;
        cout << "Tien kham:\t\t" << phieu.tienKham << " VND" << endl;
        cout << "Tien thuoc:\t\t" << phieu.tienThuoc << " VND" << endl;
        cout << "========================================" << endl;
        cout << "TONG TIEN:\t\t" << phieu.tongTien << " VND" << endl;
        cout << "========================================" << endl;
        cout << "\n   CAM ON QUY KHACH!" << endl;

        // Luu phieu kham
        try {
            ofstream outFile("PhieuKham_" + phieu.maPhieuKham + ".txt");
            if (outFile.is_open()) {
                outFile << "========================================" << endl;
                outFile << "       PHONG KHAM ABC" << endl;
                outFile << "========================================" << endl;
                outFile << "Ma phieu: " << phieu.maPhieuKham << endl;
                outFile << "Benh nhan: " << phieu.tenBN << endl;
                outFile << "Bac si: " << phieu.tenBS << endl;
                outFile << "Chan doan: " << phieu.chanDoan << endl;
                outFile << "Tong tien: " << phieu.tongTien << " VND" << endl;
                outFile.close();

                cout << "\nDa luu phieu: PhieuKham_" << phieu.maPhieuKham << ".txt" << endl;
            }
        } catch (exception& e) {
            cout << "Loi luu phieu: " << e.what() << endl;
        }

        // Giai phong
        delete[] phieu.dsMaDV;

    } catch (exception& e) {
        cout << "Loi: " << e.what() << endl;
    }
}

// ========== MAIN ==========

int main() {
    cout << "=== HE THONG QUAN LY PHONG KHAM ===" << endl;

    const int MAX_BN = 500;
    const int MAX_BS = 50;
    const int MAX_DV = 100;

    BenhNhan* dsBN = new BenhNhan[MAX_BN];
    BacSi* dsBS = new BacSi[MAX_BS];
    DichVuKham* dsDV = new DichVuKham[MAX_DV];

    int demBN = 0;
    int demBS = 0;
    int demDV = 0;
    int soLichHen = 0;
    int soPhieuKham = 0;

    // Doc du lieu
    DocFileBenhNhan(dsBN, demBN, "DanhSachBenhNhan.txt");
    DocFileBacSi(dsBS, demBS, "DanhSachBacSi.txt");
    DocFileDichVu(dsDV, demDV, "DanhSachDichVu.txt");

    // Menu
    int luaChon;
    do {
        cout << "\n========== MENU ==========" << endl;
        cout << "1. Dang ky benh nhan moi" << endl;
        cout << "2. Hien thi danh sach benh nhan" << endl;
        cout << "3. Hien thi danh sach bac si" << endl;
        cout << "4. Hien thi danh sach dich vu" << endl;
        cout << "5. Dat lich hen kham" << endl;
        cout << "6. Tao phieu kham benh" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                DangKyBenhNhanMoi(dsBN, demBN, MAX_BN);
                break;
            case 2:
                HienThiBenhNhan(dsBN, demBN);
                break;
            case 3:
                HienThiBacSi(dsBS, demBS);
                break;
            case 4:
                HienThiDichVu(dsDV, demDV);
                break;
            case 5:
                DatLichHen(dsBN, demBN, dsBS, demBS, soLichHen);
                break;
            case 6:
                TaoPhieuKham(dsBN, demBN, dsBS, demBS, dsDV, demDV, soPhieuKham);
                break;
            case 0:
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }

    } while (luaChon != 0);

    // Giai phong
    delete[] dsBN;
    delete[] dsBS;
    delete[] dsDV;

    return 0;
}
