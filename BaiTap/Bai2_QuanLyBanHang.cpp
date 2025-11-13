#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <ctime>
using namespace std;

// ========== HAM TU VIET - KHONG DUNG BUILT-IN ==========

// Ham chuyen string sang int
int StringToInt(const string& str) {
    int ketqua = 0;
    bool amDuong = false;
    int batdau = 0;

    if (str.length() > 0 && str[0] == '-') {
        amDuong = true;
        batdau = 1;
    }

    for (int i = batdau; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            ketqua = ketqua * 10 + (str[i] - '0');
        } else {
            break;
        }
    }

    return amDuong ? -ketqua : ketqua;
}

// Ham chuyen string sang float
float StringToFloat(const string& str) {
    float ketqua = 0.0;
    float phanThapPhan = 0.0;
    int viTriThapPhan = 0;
    bool coThapPhan = false;
    bool amDuong = false;
    int batdau = 0;

    if (str.length() > 0 && str[0] == '-') {
        amDuong = true;
        batdau = 1;
    }

    for (int i = batdau; i < str.length(); i++) {
        if (str[i] == '.' || str[i] == ',') {
            coThapPhan = true;
            continue;
        }

        if (str[i] >= '0' && str[i] <= '9') {
            if (!coThapPhan) {
                ketqua = ketqua * 10 + (str[i] - '0');
            } else {
                viTriThapPhan++;
                phanThapPhan = phanThapPhan * 10 + (str[i] - '0');
            }
        }
    }

    // Chuyen phan thap phan
    for (int i = 0; i < viTriThapPhan; i++) {
        phanThapPhan = phanThapPhan / 10.0;
    }

    ketqua = ketqua + phanThapPhan;
    return amDuong ? -ketqua : ketqua;
}

// Ham chuyen int sang string
string IntToString(int so) {
    if (so == 0) return "0";

    string ketqua = "";
    bool amDuong = false;

    if (so < 0) {
        amDuong = true;
        so = -so;
    }

    while (so > 0) {
        ketqua = char('0' + (so % 10)) + ketqua;
        so = so / 10;
    }

    if (amDuong) {
        ketqua = '-' + ketqua;
    }

    return ketqua;
}

// Ham chuyen float sang string (2 chu so thap phan)
string FloatToString(float so) {
    // Phan nguyen
    int phanNguyen = (int)so;
    string ketqua = IntToString(phanNguyen);

    // Phan thap phan (2 chu so)
    float phanThapPhan = so - phanNguyen;
    if (phanThapPhan < 0) phanThapPhan = -phanThapPhan;

    int thapPhan = (int)((phanThapPhan * 100) + 0.5); // Lam tron

    ketqua = ketqua + ".";

    if (thapPhan < 10) {
        ketqua = ketqua + "0";
    }
    ketqua = ketqua + IntToString(thapPhan);

    return ketqua;
}

// ========== CAU TRUC DU LIEU ==========

struct SanPham {
    string maSP;
    string tenSP;
    float donGia;
    int tonKho;
};

struct ChiTietHoaDon {
    string maSP;
    string tenSP;
    float donGia;
    int soLuong;
    float thanhTien;
};

struct HoaDon {
    string maHD;
    string ngayLap;
    ChiTietHoaDon* dsChiTiet;
    int soLuongChiTiet;
    float tongTien;
    float giamGia;
    float VAT;
    float tongThanhToan;
};

// ========== HAM XU LY NGAY GIO ==========

string LayNgayGioHienTai() {
    time_t thoiGian = time(0);
    tm* tg = localtime(&thoiGian);

    string ketqua = "";
    ketqua = IntToString(tg->tm_mday) + "/"
           + IntToString(tg->tm_mon + 1) + "/"
           + IntToString(tg->tm_year + 1900) + " "
           + IntToString(tg->tm_hour) + ":"
           + IntToString(tg->tm_min) + ":"
           + IntToString(tg->tm_sec);

    return ketqua;
}

// ========== HAM XU LY FILE ==========

void DocFileSanPham(SanPham* dsSP, int& demSP, const string& tenFile) {
    try {
        ifstream inFile(tenFile);
        if (!inFile.is_open()) {
            throw runtime_error("Khong the mo file " + tenFile);
        }

        demSP = 0;
        string line;

        // Bo qua dong tieu de
        getline(inFile, line);

        while (getline(inFile, line) && demSP < 100) {
            string phan[4] = {"", "", "", ""};
            int viTri = 0;

            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    viTri++;
                    if (viTri >= 4) break;
                } else {
                    phan[viTri] = phan[viTri] + line[i];
                }
            }

            dsSP[demSP].maSP = phan[0];
            dsSP[demSP].tenSP = phan[1];
            dsSP[demSP].donGia = StringToFloat(phan[2]);
            dsSP[demSP].tonKho = StringToInt(phan[3]);

            demSP++;
        }

        inFile.close();
        cout << "Doc file san pham thanh cong. So luong: " << demSP << endl;

    } catch (exception& e) {
        cout << "Loi doc file: " << e.what() << endl;
    }
}

void LuuFileSanPham(SanPham* dsSP, int demSP, const string& tenFile) {
    try {
        ofstream outFile(tenFile);
        if (!outFile.is_open()) {
            throw runtime_error("Khong the mo file " + tenFile);
        }

        outFile << "MaSP,TenSP,DonGia,TonKho" << endl;

        for (int i = 0; i < demSP; i++) {
            outFile << dsSP[i].maSP << ","
                    << dsSP[i].tenSP << ","
                    << dsSP[i].donGia << ","
                    << dsSP[i].tonKho << endl;
        }

        outFile.close();

    } catch (exception& e) {
        cout << "Loi luu file: " << e.what() << endl;
    }
}

// ========== HAM NGHIEP VU ==========

void HienThiDanhSachSanPham(SanPham* dsSP, int demSP) {
    cout << "\n===== DANH SACH SAN PHAM =====" << endl;
    cout << "Ma SP\tTen San Pham\t\tDon Gia\t\tTon Kho" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (int i = 0; i < demSP; i++) {
        cout << dsSP[i].maSP << "\t"
             << dsSP[i].tenSP << "\t\t"
             << dsSP[i].donGia << "\t\t"
             << dsSP[i].tonKho << endl;
    }
    cout << endl;
}

int TimSanPhamTheoMa(SanPham* dsSP, int demSP, const string& maSP) {
    for (int i = 0; i < demSP; i++) {
        if (dsSP[i].maSP == maSP) {
            return i;
        }
    }
    return -1;
}

// ========== HAM TINH GIAM GIA ==========

// Loai 1: Giam gia theo phan tram (%)
float GiamGiaPhanTram(float tongTien, float phanTram) {
    return tongTien * phanTram / 100.0;
}

// Loai 2: Giam gia co dinh (VND)
float GiamGiaCoDinh(float soTienGiam) {
    return soTienGiam;
}

// Loai 3: Giam gia theo tong tien (bac thang)
float GiamGiaBacThang(float tongTien) {
    if (tongTien >= 1000000) {
        return tongTien * 10.0 / 100.0;  // Giam 10%
    } else if (tongTien >= 500000) {
        return tongTien * 5.0 / 100.0;   // Giam 5%
    } else if (tongTien >= 200000) {
        return tongTien * 2.0 / 100.0;   // Giam 2%
    }
    return 0.0;
}

// Loai 4: Giam gia combo (mua nhieu san pham)
float GiamGiaCombo(int soLuongSanPham, float tongTien) {
    if (soLuongSanPham >= 5) {
        return tongTien * 15.0 / 100.0;  // Giam 15%
    } else if (soLuongSanPham >= 3) {
        return tongTien * 10.0 / 100.0;  // Giam 10%
    }
    return 0.0;
}

// ========== TAO HOA DON ==========

void TaoHoaDon(SanPham* dsSP, int demSP, int& soHoaDon) {
    try {
        cout << "\n===== TAO HOA DON MOI =====" << endl;

        HoaDon hoaDon;
        soHoaDon++;
        hoaDon.maHD = "HD" + IntToString(soHoaDon);
        hoaDon.ngayLap = LayNgayGioHienTai();

        // Cap phat bo nho cho chi tiet hoa don
        hoaDon.dsChiTiet = new ChiTietHoaDon[50];
        hoaDon.soLuongChiTiet = 0;
        hoaDon.tongTien = 0.0;

        // Nhap san pham vao hoa don
        char tiepTuc = 'y';
        do {
            HienThiDanhSachSanPham(dsSP, demSP);

            string maSP;
            cout << "Nhap ma san pham: ";
            cin >> maSP;

            int viTri = TimSanPhamTheoMa(dsSP, demSP, maSP);

            if (viTri == -1) {
                cout << "Khong tim thay san pham!" << endl;
                continue;
            }

            if (dsSP[viTri].tonKho <= 0) {
                cout << "San pham het hang!" << endl;
                continue;
            }

            int soLuong;
            cout << "Nhap so luong (con lai: " << dsSP[viTri].tonKho << "): ";
            cin >> soLuong;

            if (soLuong <= 0 || soLuong > dsSP[viTri].tonKho) {
                cout << "So luong khong hop le!" << endl;
                continue;
            }

            // Them vao chi tiet hoa don
            ChiTietHoaDon ct;
            ct.maSP = dsSP[viTri].maSP;
            ct.tenSP = dsSP[viTri].tenSP;
            ct.donGia = dsSP[viTri].donGia;
            ct.soLuong = soLuong;
            ct.thanhTien = ct.donGia * soLuong;

            hoaDon.dsChiTiet[hoaDon.soLuongChiTiet] = ct;
            hoaDon.soLuongChiTiet++;
            hoaDon.tongTien += ct.thanhTien;

            // Giam ton kho
            dsSP[viTri].tonKho -= soLuong;

            cout << "Da them san pham vao hoa don!" << endl;

            cout << "Tiep tuc them san pham? (y/n): ";
            cin >> tiepTuc;

        } while (tiepTuc == 'y' || tiepTuc == 'Y');

        if (hoaDon.soLuongChiTiet == 0) {
            cout << "Hoa don rong, huy tao hoa don!" << endl;
            delete[] hoaDon.dsChiTiet;
            return;
        }

        // Chon loai giam gia
        cout << "\n===== CHON LOAI GIAM GIA =====" << endl;
        cout << "1. Giam gia phan tram (%)" << endl;
        cout << "2. Giam gia co dinh (VND)" << endl;
        cout << "3. Giam gia bac thang (tu dong)" << endl;
        cout << "4. Giam gia combo (tu dong)" << endl;
        cout << "0. Khong giam gia" << endl;
        cout << "Chon: ";

        int loaiGiamGia;
        cin >> loaiGiamGia;

        hoaDon.giamGia = 0.0;

        switch (loaiGiamGia) {
            case 1: {
                float phanTram;
                cout << "Nhap phan tram giam gia: ";
                cin >> phanTram;
                hoaDon.giamGia = GiamGiaPhanTram(hoaDon.tongTien, phanTram);
                break;
            }
            case 2: {
                float soTien;
                cout << "Nhap so tien giam: ";
                cin >> soTien;
                hoaDon.giamGia = GiamGiaCoDinh(soTien);
                break;
            }
            case 3:
                hoaDon.giamGia = GiamGiaBacThang(hoaDon.tongTien);
                cout << "Giam gia bac thang: " << hoaDon.giamGia << " VND" << endl;
                break;
            case 4:
                hoaDon.giamGia = GiamGiaCombo(hoaDon.soLuongChiTiet, hoaDon.tongTien);
                cout << "Giam gia combo: " << hoaDon.giamGia << " VND" << endl;
                break;
            default:
                hoaDon.giamGia = 0.0;
        }

        // Tinh VAT (10%)
        hoaDon.VAT = (hoaDon.tongTien - hoaDon.giamGia) * 0.10;

        // Tinh tong thanh toan
        hoaDon.tongThanhToan = hoaDon.tongTien - hoaDon.giamGia + hoaDon.VAT;

        // In hoa don ra man hinh
        cout << "\n========================================" << endl;
        cout << "       HOA DON BAN HANG" << endl;
        cout << "========================================" << endl;
        cout << "Ma hoa don: " << hoaDon.maHD << endl;
        cout << "Ngay lap: " << hoaDon.ngayLap << endl;
        cout << "----------------------------------------" << endl;
        cout << "STT\tMa SP\tTen SP\t\tSL\tDon Gia\t\tThanh Tien" << endl;
        cout << "----------------------------------------" << endl;

        for (int i = 0; i < hoaDon.soLuongChiTiet; i++) {
            cout << (i + 1) << "\t"
                 << hoaDon.dsChiTiet[i].maSP << "\t"
                 << hoaDon.dsChiTiet[i].tenSP << "\t"
                 << hoaDon.dsChiTiet[i].soLuong << "\t"
                 << hoaDon.dsChiTiet[i].donGia << "\t\t"
                 << hoaDon.dsChiTiet[i].thanhTien << endl;
        }

        cout << "----------------------------------------" << endl;
        cout << "Tong tien:\t\t\t\t" << hoaDon.tongTien << " VND" << endl;
        cout << "Giam gia:\t\t\t\t" << hoaDon.giamGia << " VND" << endl;
        cout << "VAT (10%):\t\t\t\t" << hoaDon.VAT << " VND" << endl;
        cout << "========================================" << endl;
        cout << "TONG THANH TOAN:\t\t\t" << hoaDon.tongThanhToan << " VND" << endl;
        cout << "========================================" << endl;

        // Luu hoa don ra file
        try {
            ofstream outFile("HoaDon_" + hoaDon.maHD + ".txt");
            if (!outFile.is_open()) {
                throw runtime_error("Khong the tao file hoa don");
            }

            outFile << "========================================" << endl;
            outFile << "       HOA DON BAN HANG" << endl;
            outFile << "========================================" << endl;
            outFile << "Ma hoa don: " << hoaDon.maHD << endl;
            outFile << "Ngay lap: " << hoaDon.ngayLap << endl;
            outFile << "----------------------------------------" << endl;
            outFile << "STT\tMa SP\tTen SP\t\tSL\tDon Gia\t\tThanh Tien" << endl;
            outFile << "----------------------------------------" << endl;

            for (int i = 0; i < hoaDon.soLuongChiTiet; i++) {
                outFile << (i + 1) << "\t"
                       << hoaDon.dsChiTiet[i].maSP << "\t"
                       << hoaDon.dsChiTiet[i].tenSP << "\t"
                       << hoaDon.dsChiTiet[i].soLuong << "\t"
                       << hoaDon.dsChiTiet[i].donGia << "\t\t"
                       << hoaDon.dsChiTiet[i].thanhTien << endl;
            }

            outFile << "----------------------------------------" << endl;
            outFile << "Tong tien:\t\t\t\t" << hoaDon.tongTien << " VND" << endl;
            outFile << "Giam gia:\t\t\t\t" << hoaDon.giamGia << " VND" << endl;
            outFile << "VAT (10%):\t\t\t\t" << hoaDon.VAT << " VND" << endl;
            outFile << "========================================" << endl;
            outFile << "TONG THANH TOAN:\t\t\t" << hoaDon.tongThanhToan << " VND" << endl;
            outFile << "========================================" << endl;
            outFile << "\n   CAM ON QUY KHACH!" << endl;

            outFile.close();
            cout << "\nDa luu hoa don vao file: HoaDon_" << hoaDon.maHD << ".txt" << endl;

        } catch (exception& e) {
            cout << "Loi luu file hoa don: " << e.what() << endl;
        }

        // Cap nhat file san pham
        LuuFileSanPham(dsSP, demSP, "DanhSachSanPham.txt");

        // Giai phong bo nho
        delete[] hoaDon.dsChiTiet;

    } catch (exception& e) {
        cout << "Loi: " << e.what() << endl;
    }
}

// ========== THEM SAN PHAM MOI ==========

void ThemSanPham(SanPham* dsSP, int& demSP) {
    if (demSP >= 100) {
        cout << "Danh sach san pham da day!" << endl;
        return;
    }

    cout << "\n===== THEM SAN PHAM MOI =====" << endl;

    SanPham sp;
    cout << "Nhap ma san pham: ";
    cin >> sp.maSP;

    // Kiem tra trung ma
    if (TimSanPhamTheoMa(dsSP, demSP, sp.maSP) != -1) {
        cout << "Ma san pham da ton tai!" << endl;
        return;
    }

    cout << "Nhap ten san pham: ";
    cin.ignore();
    getline(cin, sp.tenSP);

    cout << "Nhap don gia: ";
    cin >> sp.donGia;

    cout << "Nhap ton kho: ";
    cin >> sp.tonKho;

    dsSP[demSP] = sp;
    demSP++;

    LuuFileSanPham(dsSP, demSP, "DanhSachSanPham.txt");

    cout << "Them san pham thanh cong!" << endl;
}

// ========== HAM MAIN ==========

int main() {
    cout << "=== HE THONG QUAN LY BAN HANG ===" << endl;

    const int MAX = 100;
    SanPham* dsSP = new SanPham[MAX];
    int demSP = 0;
    int soHoaDon = 0;

    // Doc du lieu san pham
    DocFileSanPham(dsSP, demSP, "DanhSachSanPham.txt");

    if (demSP == 0) {
        cout << "Canh bao: Khong co san pham trong he thong!" << endl;
    }

    // Menu chuong trinh
    int luaChon;
    do {
        cout << "\n========== MENU ==========" << endl;
        cout << "1. Hien thi danh sach san pham" << endl;
        cout << "2. Them san pham moi" << endl;
        cout << "3. Tao hoa don ban hang" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon chuc nang: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                HienThiDanhSachSanPham(dsSP, demSP);
                break;
            case 2:
                ThemSanPham(dsSP, demSP);
                break;
            case 3:
                TaoHoaDon(dsSP, demSP, soHoaDon);
                break;
            case 0:
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }

    } while (luaChon != 0);

    // Giai phong bo nho
    delete[] dsSP;

    return 0;
}
