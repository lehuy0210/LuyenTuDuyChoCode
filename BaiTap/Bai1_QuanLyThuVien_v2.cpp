#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <ctime>
using namespace std;

// ========== HAM TU VIET - KHONG DUNG BUILT-IN ==========

// Ham chuyen string sang int (thay the stoi)
int ChuyenStringSangInt(const string& str) {
    int ketqua = 0;
    bool amDuong = false;
    int batdau = 0;

    // Kiem tra dau am
    if (str.length() > 0 && str[0] == '-') {
        amDuong = true;
        batdau = 1;
    }

    // Duyet tung ky tu
    for (int i = batdau; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            ketqua = ketqua * 10 + (str[i] - '0');
        } else {
            // Neu gap ky tu khong phai so thi dung lai
            break;
        }
    }

    return amDuong ? -ketqua : ketqua;
}

// Ham chuyen int sang string (thay the to_string)
string ChuyenIntSangString(int so) {
    if (so == 0) return "0";

    string ketqua = "";
    bool amDuong = false;

    if (so < 0) {
        amDuong = true;
        so = -so;
    }

    while (so > 0) {
        int chuSo = so % 10;
        ketqua = char('0' + chuSo) + ketqua;
        so = so / 10;
    }

    if (amDuong) {
        ketqua = '-' + ketqua;
    }

    return ketqua;
}

// Forward declaration
void GhiLog(const string& noidung);

// ========== CAU TRUC DU LIEU ==========

struct Sach {
    string ISBN;
    string tenSach;
    string tacGia;
    int soLuong;
};

struct DocGia {
    string maDocGia;
    string hoTen;
    string soDienThoai;
};

struct PhieuMuon {
    string maPhieu;
    string maDocGia;
    string ISBN;
    int soLuongMuon;
    string ngayMuon;    // dd/mm/yyyy
    string ngayTra;     // dd/mm/yyyy
    bool daTra;
};

// ========== HAM XU LY NGAY THANG ==========

void LayThoiGianHienTai(int& ngay, int& thang, int& nam) {
    time_t thoiGian = time(0);
    tm* tg = localtime(&thoiGian);
    ngay = tg->tm_mday;
    thang = tg->tm_mon + 1;
    nam = tg->tm_year + 1900;
}

// Tach ngay thang nam tu string dd/mm/yyyy
void TachNgayThangNam(const string& ngayStr, int& ngay, int& thang, int& nam) {
    string ngayS = "", thangS = "", namS = "";
    int phan = 0;

    for (int i = 0; i < ngayStr.length(); i++) {
        if (ngayStr[i] == '/' || ngayStr[i] == '-') {
            phan++;
        } else {
            if (phan == 0) {
                ngayS = ngayS + ngayStr[i];
            } else if (phan == 1) {
                thangS = thangS + ngayStr[i];
            } else if (phan == 2) {
                namS = namS + ngayStr[i];
            }
        }
    }

    ngay = ChuyenStringSangInt(ngayS);
    thang = ChuyenStringSangInt(thangS);
    nam = ChuyenStringSangInt(namS);
}

// So sanh 2 ngay: return -1 neu ngay1 < ngay2, 0 neu bang, 1 neu ngay1 > ngay2
int SoSanhNgay(int ngay1, int thang1, int nam1, int ngay2, int thang2, int nam2) {
    if (nam1 < nam2) return -1;
    if (nam1 > nam2) return 1;

    if (thang1 < thang2) return -1;
    if (thang1 > thang2) return 1;

    if (ngay1 < ngay2) return -1;
    if (ngay1 > ngay2) return 1;

    return 0;
}

// Kiem tra qua han
bool KiemTraQuaHan(const string& ngayTra) {
    int ngayT, thangT, namT;
    TachNgayThangNam(ngayTra, ngayT, thangT, namT);

    int ngayHT, thangHT, namHT;
    LayThoiGianHienTai(ngayHT, thangHT, namHT);

    // Neu ngay tra < ngay hien tai thi qua han
    return SoSanhNgay(ngayT, thangT, namT, ngayHT, thangHT, namHT) < 0;
}

// ========== HAM GHI LOG ==========

void GhiLog(const string& noidung) {
    try {
        ofstream logFile("log.txt", ios::app);
        if (!logFile.is_open()) {
            throw runtime_error("Khong the mo file log.txt");
        }

        int ngay, thang, nam;
        LayThoiGianHienTai(ngay, thang, nam);
        time_t thoiGian = time(0);
        tm* tg = localtime(&thoiGian);

        logFile << "[" << ChuyenIntSangString(ngay) << "/"
                << ChuyenIntSangString(thang) << "/"
                << ChuyenIntSangString(nam) << " "
                << ChuyenIntSangString(tg->tm_hour) << ":"
                << ChuyenIntSangString(tg->tm_min) << ":"
                << ChuyenIntSangString(tg->tm_sec) << "] "
                << noidung << endl;
        logFile.close();
    } catch (exception& e) {
        cout << "Loi ghi log: " << e.what() << endl;
    }
}

// ========== HAM XU LY FILE ==========

void DocFileSach(Sach* dsSach, int& demSach, const string& tenFile) {
    try {
        ifstream inFile(tenFile);
        if (!inFile.is_open()) {
            throw runtime_error("Khong the mo file " + tenFile);
        }

        demSach = 0;
        string line;

        // Bo qua dong tieu de (neu co)
        getline(inFile, line);

        while (getline(inFile, line) && demSach < 100) {
            string phan[4] = {"", "", "", ""};
            int viTri = 0;

            // Tach dong theo dau phay
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    viTri++;
                    if (viTri >= 4) break;
                } else {
                    phan[viTri] = phan[viTri] + line[i];
                }
            }

            dsSach[demSach].ISBN = phan[0];
            dsSach[demSach].tenSach = phan[1];
            dsSach[demSach].tacGia = phan[2];
            dsSach[demSach].soLuong = ChuyenStringSangInt(phan[3]);

            demSach++;
        }

        inFile.close();
        GhiLog("Doc file sach thanh cong. So luong: " + ChuyenIntSangString(demSach));

    } catch (exception& e) {
        cout << "Loi doc file: " << e.what() << endl;
        GhiLog("Loi doc file sach: " + string(e.what()));
    }
}

void DocFileDocGia(DocGia* dsDocGia, int& demDocGia, const string& tenFile) {
    try {
        ifstream inFile(tenFile);
        if (!inFile.is_open()) {
            throw runtime_error("Khong the mo file " + tenFile);
        }

        demDocGia = 0;
        string line;

        // Bo qua dong tieu de
        getline(inFile, line);

        while (getline(inFile, line) && demDocGia < 100) {
            string phan[3] = {"", "", ""};
            int viTri = 0;

            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    viTri++;
                    if (viTri >= 3) break;
                } else {
                    phan[viTri] = phan[viTri] + line[i];
                }
            }

            dsDocGia[demDocGia].maDocGia = phan[0];
            dsDocGia[demDocGia].hoTen = phan[1];
            dsDocGia[demDocGia].soDienThoai = phan[2];

            demDocGia++;
        }

        inFile.close();
        GhiLog("Doc file doc gia thanh cong. So luong: " + ChuyenIntSangString(demDocGia));

    } catch (exception& e) {
        cout << "Loi doc file: " << e.what() << endl;
        GhiLog("Loi doc file doc gia: " + string(e.what()));
    }
}

void LuuFileSach(Sach* dsSach, int demSach, const string& tenFile) {
    try {
        ofstream outFile(tenFile);
        if (!outFile.is_open()) {
            throw runtime_error("Khong the mo file " + tenFile);
        }

        outFile << "ISBN,TenSach,TacGia,SoLuong" << endl;

        for (int i = 0; i < demSach; i++) {
            outFile << dsSach[i].ISBN << ","
                    << dsSach[i].tenSach << ","
                    << dsSach[i].tacGia << ","
                    << dsSach[i].soLuong << endl;
        }

        outFile.close();
        GhiLog("Luu file sach thanh cong");

    } catch (exception& e) {
        cout << "Loi luu file: " << e.what() << endl;
        GhiLog("Loi luu file sach: " + string(e.what()));
    }
}

void GhiPhieuMuon(const PhieuMuon& phieu) {
    try {
        ofstream outFile("PhieuMuon.txt", ios::app);
        if (!outFile.is_open()) {
            throw runtime_error("Khong the mo file PhieuMuon.txt");
        }

        outFile << phieu.maPhieu << ","
                << phieu.maDocGia << ","
                << phieu.ISBN << ","
                << phieu.soLuongMuon << ","
                << phieu.ngayMuon << ","
                << phieu.ngayTra << ","
                << (phieu.daTra ? "1" : "0") << endl;

        outFile.close();
        GhiLog("Ghi phieu muon thanh cong: " + phieu.maPhieu);

    } catch (exception& e) {
        cout << "Loi ghi phieu muon: " << e.what() << endl;
        GhiLog("Loi ghi phieu muon: " + string(e.what()));
    }
}

// ========== HAM NGHIEP VU ==========

void HienThiDanhSachSach(Sach* dsSach, int demSach) {
    cout << "\n===== DANH SACH SACH =====" << endl;
    cout << "ISBN\t\tTen Sach\t\tTac Gia\t\tSo Luong" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (int i = 0; i < demSach; i++) {
        cout << dsSach[i].ISBN << "\t"
             << dsSach[i].tenSach << "\t\t"
             << dsSach[i].tacGia << "\t"
             << dsSach[i].soLuong << endl;
    }
    cout << endl;
}

void HienThiDanhSachDocGia(DocGia* dsDocGia, int demDocGia) {
    cout << "\n===== DANH SACH DOC GIA =====" << endl;
    cout << "Ma DG\tHo Ten\t\t\tSo Dien Thoai" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (int i = 0; i < demDocGia; i++) {
        cout << dsDocGia[i].maDocGia << "\t"
             << dsDocGia[i].hoTen << "\t\t"
             << dsDocGia[i].soDienThoai << endl;
    }
    cout << endl;
}

int TimSachTheoISBN(Sach* dsSach, int demSach, const string& ISBN) {
    for (int i = 0; i < demSach; i++) {
        if (dsSach[i].ISBN == ISBN) {
            return i;
        }
    }
    return -1;
}

int TimDocGiaTheoMa(DocGia* dsDocGia, int demDocGia, const string& maDocGia) {
    for (int i = 0; i < demDocGia; i++) {
        if (dsDocGia[i].maDocGia == maDocGia) {
            return i;
        }
    }
    return -1;
}

void MuonSach(Sach* dsSach, int demSach, DocGia* dsDocGia, int demDocGia, int& soPhieuMuon) {
    try {
        cout << "\n===== MUON SACH =====" << endl;

        // Hien thi danh sach doc gia
        HienThiDanhSachDocGia(dsDocGia, demDocGia);

        string maDocGia;
        cout << "Nhap ma doc gia: ";
        cin >> maDocGia;

        int viTriDocGia = TimDocGiaTheoMa(dsDocGia, demDocGia, maDocGia);
        if (viTriDocGia == -1) {
            cout << "Khong tim thay doc gia!" << endl;
            GhiLog("Loi: Khong tim thay doc gia " + maDocGia);
            return;
        }

        // Hien thi danh sach sach
        HienThiDanhSachSach(dsSach, demSach);

        string ISBN;
        cout << "Nhap ISBN sach muon muon: ";
        cin >> ISBN;

        int viTriSach = TimSachTheoISBN(dsSach, demSach, ISBN);
        if (viTriSach == -1) {
            cout << "Khong tim thay sach!" << endl;
            GhiLog("Loi: Khong tim thay sach ISBN " + ISBN);
            return;
        }

        if (dsSach[viTriSach].soLuong <= 0) {
            cout << "Sach da het!" << endl;
            GhiLog("Loi: Sach het - ISBN " + ISBN);
            return;
        }

        int soLuongMuon;
        cout << "Nhap so luong muon muon (con lai: " << dsSach[viTriSach].soLuong << "): ";
        cin >> soLuongMuon;

        if (soLuongMuon <= 0 || soLuongMuon > dsSach[viTriSach].soLuong) {
            cout << "So luong khong hop le!" << endl;
            GhiLog("Loi: So luong muon khong hop le");
            return;
        }

        string ngayMuon, ngayTra;
        cout << "Nhap ngay muon (dd/mm/yyyy): ";
        cin >> ngayMuon;
        cout << "Nhap ngay tra du kien (dd/mm/yyyy): ";
        cin >> ngayTra;

        // Tao phieu muon
        PhieuMuon phieu;
        soPhieuMuon++;
        phieu.maPhieu = "PM" + ChuyenIntSangString(soPhieuMuon);
        phieu.maDocGia = maDocGia;
        phieu.ISBN = ISBN;
        phieu.soLuongMuon = soLuongMuon;
        phieu.ngayMuon = ngayMuon;
        phieu.ngayTra = ngayTra;
        phieu.daTra = false;

        // Giam so luong sach
        dsSach[viTriSach].soLuong -= soLuongMuon;

        // Luu phieu muon
        GhiPhieuMuon(phieu);

        // Cap nhat file sach
        LuuFileSach(dsSach, demSach, "DanhSachSach.txt");

        cout << "\nMuon sach thanh cong!" << endl;
        cout << "Ma phieu muon: " << phieu.maPhieu << endl;

        // Kiem tra qua han
        if (KiemTraQuaHan(ngayTra)) {
            cout << "CANH BAO: Ngay tra da qua han!" << endl;
            GhiLog("CANH BAO: Phieu " + phieu.maPhieu + " qua han");
        }

        GhiLog("Muon sach thanh cong - " + phieu.maPhieu + " - " + dsDocGia[viTriDocGia].hoTen);

    } catch (exception& e) {
        cout << "Loi: " << e.what() << endl;
        GhiLog("Loi muon sach: " + string(e.what()));
    }
}

void ThongKeSachQuaHan() {
    try {
        ifstream inFile("PhieuMuon.txt");
        if (!inFile.is_open()) {
            cout << "Chua co phieu muon nao!" << endl;
            return;
        }

        cout << "\n===== THONG KE SACH QUA HAN =====" << endl;

        string line;
        int demQuaHan = 0;

        while (getline(inFile, line)) {
            string phan[7] = {"", "", "", "", "", "", ""};
            int viTri = 0;

            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    viTri++;
                    if (viTri >= 7) break;
                } else {
                    phan[viTri] = phan[viTri] + line[i];
                }
            }

            // Kiem tra da tra chua
            bool daTra = (phan[6] == "1");

            if (!daTra) {
                string ngayTra = phan[5];

                if (KiemTraQuaHan(ngayTra)) {
                    demQuaHan++;
                    cout << "Ma phieu: " << phan[0]
                         << " - Ma doc gia: " << phan[1]
                         << " - ISBN: " << phan[2]
                         << " - Ngay tra: " << ngayTra << endl;
                }
            }
        }

        inFile.close();

        if (demQuaHan == 0) {
            cout << "Khong co phieu muon nao qua han!" << endl;
        } else {
            cout << "\nTong so phieu qua han: " << demQuaHan << endl;
        }

        GhiLog("Thong ke qua han - So luong: " + ChuyenIntSangString(demQuaHan));

    } catch (exception& e) {
        cout << "Loi: " << e.what() << endl;
        GhiLog("Loi thong ke qua han: " + string(e.what()));
    }
}

// ========== HAM MAIN ==========

int main() {
    GhiLog("=== BAT DAU CHUONG TRINH QUAN LY THU VIEN ===");

    const int MAX = 100;
    Sach* dsSach = new Sach[MAX];
    DocGia* dsDocGia = new DocGia[MAX];
    int demSach = 0, demDocGia = 0, soPhieuMuon = 0;

    // Doc du lieu ban dau
    DocFileSach(dsSach, demSach, "DanhSachSach.txt");
    DocFileDocGia(dsDocGia, demDocGia, "DanhSachDocGia.txt");

    if (demSach == 0) {
        cout << "Canh bao: Khong co sach trong he thong!" << endl;
    }

    if (demDocGia == 0) {
        cout << "Canh bao: Khong co doc gia trong he thong!" << endl;
    }

    // Menu chuong trinh
    int luaChon;
    do {
        cout << "\n========== QUAN LY THU VIEN ==========" << endl;
        cout << "1. Hien thi danh sach sach" << endl;
        cout << "2. Hien thi danh sach doc gia" << endl;
        cout << "3. Muon sach" << endl;
        cout << "4. Thong ke sach qua han" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon chuc nang: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                HienThiDanhSachSach(dsSach, demSach);
                break;
            case 2:
                HienThiDanhSachDocGia(dsDocGia, demDocGia);
                break;
            case 3:
                MuonSach(dsSach, demSach, dsDocGia, demDocGia, soPhieuMuon);
                break;
            case 4:
                ThongKeSachQuaHan();
                break;
            case 0:
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }

    } while (luaChon != 0);

    // Giai phong bo nho
    delete[] dsSach;
    delete[] dsDocGia;

    GhiLog("=== KET THUC CHUONG TRINH ===");

    return 0;
}
