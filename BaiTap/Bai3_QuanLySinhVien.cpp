#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

// ========== HAM TU VIET - KHONG DUNG BUILT-IN ==========

// Ham chuyen string sang int
int StrToInt(const string& str) {
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
float StrToFloat(const string& str) {
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

    for (int i = 0; i < viTriThapPhan; i++) {
        phanThapPhan = phanThapPhan / 10.0;
    }

    ketqua = ketqua + phanThapPhan;
    return amDuong ? -ketqua : ketqua;
}

// Ham chuyen int sang string
string IntToStr(int so) {
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

// Ham chuyen float sang string
string FloatToStr(float so) {
    int phanNguyen = (int)so;
    string ketqua = IntToStr(phanNguyen);

    float phanThapPhan = so - phanNguyen;
    if (phanThapPhan < 0) phanThapPhan = -phanThapPhan;

    int thapPhan = (int)((phanThapPhan * 10) + 0.5);

    ketqua = ketqua + ".";
    ketqua = ketqua + IntToStr(thapPhan);

    return ketqua;
}

// Ham chuyen chu thuong thanh chu hoa
string ToUpper(const string& str) {
    string ketqua = "";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            ketqua = ketqua + char(str[i] - 32);
        } else {
            ketqua = ketqua + str[i];
        }
    }
    return ketqua;
}

// Ham kiem tra chuoi co chua chuoi con khong (tim kiem)
bool Contains(const string& str, const string& subStr) {
    if (subStr.length() > str.length()) return false;

    for (int i = 0; i <= str.length() - subStr.length(); i++) {
        bool found = true;
        for (int j = 0; j < subStr.length(); j++) {
            if (str[i + j] != subStr[j]) {
                found = false;
                break;
            }
        }
        if (found) return true;
    }
    return false;
}

// ========== CAU TRUC DU LIEU ==========

struct SinhVien {
    string maSV;
    string hoTen;
    string lop;
    float diemTB;
};

// ========== HAM VALIDATE DU LIEU ==========

bool ValidateMaSV(const string& maSV) {
    // Ma sinh vien phai co it nhat 3 ky tu
    if (maSV.length() < 3) {
        cout << "Ma sinh vien phai co it nhat 3 ky tu!" << endl;
        return false;
    }

    // Khong duoc chua khoang trang
    for (int i = 0; i < maSV.length(); i++) {
        if (maSV[i] == ' ') {
            cout << "Ma sinh vien khong duoc chua khoang trang!" << endl;
            return false;
        }
    }

    return true;
}

bool ValidateHoTen(const string& hoTen) {
    if (hoTen.length() < 2) {
        cout << "Ho ten phai co it nhat 2 ky tu!" << endl;
        return false;
    }

    // Kiem tra co ky tu chu cai
    bool coKyTuChuCai = false;
    for (int i = 0; i < hoTen.length(); i++) {
        if ((hoTen[i] >= 'A' && hoTen[i] <= 'Z') ||
            (hoTen[i] >= 'a' && hoTen[i] <= 'z')) {
            coKyTuChuCai = true;
            break;
        }
    }

    if (!coKyTuChuCai) {
        cout << "Ho ten phai co ky tu chu cai!" << endl;
        return false;
    }

    return true;
}

bool ValidateDiem(float diem) {
    if (diem < 0.0 || diem > 10.0) {
        cout << "Diem phai nam trong khoang 0.0 - 10.0!" << endl;
        return false;
    }
    return true;
}

bool ValidateLop(const string& lop) {
    if (lop.length() < 2) {
        cout << "Ten lop phai co it nhat 2 ky tu!" << endl;
        return false;
    }
    return true;
}

// ========== HAM XU LY FILE ==========

void DocFileSinhVien(SinhVien* dsSV, int& demSV, const string& tenFile) {
    try {
        ifstream inFile(tenFile);
        if (!inFile.is_open()) {
            throw runtime_error("Khong the mo file " + tenFile);
        }

        demSV = 0;
        string line;

        // Bo qua dong tieu de
        getline(inFile, line);

        while (getline(inFile, line) && demSV < 200) {
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

            // Validate truoc khi them
            if (ValidateMaSV(phan[0]) && ValidateHoTen(phan[1]) &&
                ValidateLop(phan[2])) {

                dsSV[demSV].maSV = phan[0];
                dsSV[demSV].hoTen = phan[1];
                dsSV[demSV].lop = phan[2];
                dsSV[demSV].diemTB = StrToFloat(phan[3]);

                if (ValidateDiem(dsSV[demSV].diemTB)) {
                    demSV++;
                }
            }
        }

        inFile.close();
        cout << "Doc file thanh cong. So luong sinh vien: " << demSV << endl;

    } catch (exception& e) {
        cout << "Loi doc file: " << e.what() << endl;
    }
}

void LuuFileSinhVien(SinhVien* dsSV, int demSV, const string& tenFile) {
    try {
        ofstream outFile(tenFile);
        if (!outFile.is_open()) {
            throw runtime_error("Khong the mo file " + tenFile);
        }

        outFile << "MaSV,HoTen,Lop,DiemTB" << endl;

        for (int i = 0; i < demSV; i++) {
            outFile << dsSV[i].maSV << ","
                    << dsSV[i].hoTen << ","
                    << dsSV[i].lop << ","
                    << dsSV[i].diemTB << endl;
        }

        outFile.close();
        cout << "Luu file thanh cong!" << endl;

    } catch (exception& e) {
        cout << "Loi luu file: " << e.what() << endl;
    }
}

// ========== HAM NGHIEP VU ==========

void HienThiDanhSachSinhVien(SinhVien* dsSV, int demSV) {
    if (demSV == 0) {
        cout << "Danh sach rong!" << endl;
        return;
    }

    cout << "\n===== DANH SACH SINH VIEN =====" << endl;
    cout << "Ma SV\t\tHo Ten\t\t\tLop\t\tDiem TB" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (int i = 0; i < demSV; i++) {
        cout << dsSV[i].maSV << "\t\t"
             << dsSV[i].hoTen << "\t\t"
             << dsSV[i].lop << "\t\t"
             << dsSV[i].diemTB << endl;
    }
    cout << endl;
}

int TimSinhVienTheoMa(SinhVien* dsSV, int demSV, const string& maSV) {
    for (int i = 0; i < demSV; i++) {
        if (dsSV[i].maSV == maSV) {
            return i;
        }
    }
    return -1;
}

void ThemSinhVien(SinhVien* dsSV, int& demSV, int maxSV) {
    if (demSV >= maxSV) {
        cout << "Danh sach da day!" << endl;
        return;
    }

    cout << "\n===== THEM SINH VIEN MOI =====" << endl;

    SinhVien sv;

    // Nhap ma sinh vien
    do {
        cout << "Nhap ma sinh vien: ";
        cin >> sv.maSV;

        if (!ValidateMaSV(sv.maSV)) {
            continue;
        }

        // Kiem tra trung ma
        if (TimSinhVienTheoMa(dsSV, demSV, sv.maSV) != -1) {
            cout << "Ma sinh vien da ton tai!" << endl;
            continue;
        }

        break;
    } while (true);

    // Nhap ho ten
    do {
        cout << "Nhap ho ten: ";
        cin.ignore();
        getline(cin, sv.hoTen);

        if (ValidateHoTen(sv.hoTen)) {
            break;
        }
    } while (true);

    // Nhap lop
    do {
        cout << "Nhap lop: ";
        getline(cin, sv.lop);

        if (ValidateLop(sv.lop)) {
            break;
        }
    } while (true);

    // Nhap diem
    do {
        cout << "Nhap diem trung binh: ";
        cin >> sv.diemTB;

        if (ValidateDiem(sv.diemTB)) {
            break;
        }
    } while (true);

    dsSV[demSV] = sv;
    demSV++;

    cout << "Them sinh vien thanh cong!" << endl;
}

void XoaSinhVien(SinhVien* dsSV, int& demSV) {
    if (demSV == 0) {
        cout << "Danh sach rong!" << endl;
        return;
    }

    cout << "\n===== XOA SINH VIEN =====" << endl;

    string maSV;
    cout << "Nhap ma sinh vien can xoa: ";
    cin >> maSV;

    int viTri = TimSinhVienTheoMa(dsSV, demSV, maSV);

    if (viTri == -1) {
        cout << "Khong tim thay sinh vien!" << endl;
        return;
    }

    // Hien thi thong tin sinh vien can xoa
    cout << "Sinh vien can xoa:" << endl;
    cout << "Ma SV: " << dsSV[viTri].maSV << endl;
    cout << "Ho Ten: " << dsSV[viTri].hoTen << endl;
    cout << "Lop: " << dsSV[viTri].lop << endl;
    cout << "Diem TB: " << dsSV[viTri].diemTB << endl;

    char xacNhan;
    cout << "Ban co chac chan muon xoa? (y/n): ";
    cin >> xacNhan;

    if (xacNhan != 'y' && xacNhan != 'Y') {
        cout << "Huy xoa!" << endl;
        return;
    }

    // Dich chuyen mang
    for (int i = viTri; i < demSV - 1; i++) {
        dsSV[i] = dsSV[i + 1];
    }

    demSV--;

    cout << "Xoa sinh vien thanh cong!" << endl;
}

void SuaSinhVien(SinhVien* dsSV, int demSV) {
    if (demSV == 0) {
        cout << "Danh sach rong!" << endl;
        return;
    }

    cout << "\n===== SUA THONG TIN SINH VIEN =====" << endl;

    string maSV;
    cout << "Nhap ma sinh vien can sua: ";
    cin >> maSV;

    int viTri = TimSinhVienTheoMa(dsSV, demSV, maSV);

    if (viTri == -1) {
        cout << "Khong tim thay sinh vien!" << endl;
        return;
    }

    // Hien thi thong tin hien tai
    cout << "Thong tin hien tai:" << endl;
    cout << "Ma SV: " << dsSV[viTri].maSV << endl;
    cout << "Ho Ten: " << dsSV[viTri].hoTen << endl;
    cout << "Lop: " << dsSV[viTri].lop << endl;
    cout << "Diem TB: " << dsSV[viTri].diemTB << endl;

    cout << "\nNhap thong tin moi (Enter de giu nguyen):" << endl;

    // Sua ho ten
    cout << "Ho ten moi: ";
    cin.ignore();
    string hoTenMoi;
    getline(cin, hoTenMoi);
    if (hoTenMoi.length() > 0 && ValidateHoTen(hoTenMoi)) {
        dsSV[viTri].hoTen = hoTenMoi;
    }

    // Sua lop
    cout << "Lop moi: ";
    string lopMoi;
    getline(cin, lopMoi);
    if (lopMoi.length() > 0 && ValidateLop(lopMoi)) {
        dsSV[viTri].lop = lopMoi;
    }

    // Sua diem
    cout << "Diem TB moi (nhap -1 de giu nguyen): ";
    float diemMoi;
    cin >> diemMoi;
    if (diemMoi >= 0 && ValidateDiem(diemMoi)) {
        dsSV[viTri].diemTB = diemMoi;
    }

    cout << "Sua thong tin thanh cong!" << endl;
}

void TimKiemSinhVien(SinhVien* dsSV, int demSV) {
    if (demSV == 0) {
        cout << "Danh sach rong!" << endl;
        return;
    }

    cout << "\n===== TIM KIEM SINH VIEN =====" << endl;
    cout << "1. Tim theo ma sinh vien" << endl;
    cout << "2. Tim theo ho ten" << endl;
    cout << "3. Tim theo lop" << endl;
    cout << "4. Tim theo diem (khoang)" << endl;
    cout << "Chon: ";

    int luaChon;
    cin >> luaChon;

    bool timThay = false;

    switch (luaChon) {
        case 1: {
            string maSV;
            cout << "Nhap ma sinh vien: ";
            cin >> maSV;

            int viTri = TimSinhVienTheoMa(dsSV, demSV, maSV);
            if (viTri != -1) {
                cout << "\nKet qua tim kiem:" << endl;
                cout << "Ma SV: " << dsSV[viTri].maSV << endl;
                cout << "Ho Ten: " << dsSV[viTri].hoTen << endl;
                cout << "Lop: " << dsSV[viTri].lop << endl;
                cout << "Diem TB: " << dsSV[viTri].diemTB << endl;
                timThay = true;
            }
            break;
        }
        case 2: {
            string hoTen;
            cout << "Nhap ho ten (co the nhap mot phan): ";
            cin.ignore();
            getline(cin, hoTen);

            // Chuyen thanh chu hoa de tim kiem khong phan biet hoa thuong
            string hoTenUpper = ToUpper(hoTen);

            cout << "\nKet qua tim kiem:" << endl;
            for (int i = 0; i < demSV; i++) {
                string hoTenSVUpper = ToUpper(dsSV[i].hoTen);
                if (Contains(hoTenSVUpper, hoTenUpper)) {
                    cout << "Ma SV: " << dsSV[i].maSV << " - "
                         << "Ho Ten: " << dsSV[i].hoTen << " - "
                         << "Lop: " << dsSV[i].lop << " - "
                         << "Diem: " << dsSV[i].diemTB << endl;
                    timThay = true;
                }
            }
            break;
        }
        case 3: {
            string lop;
            cout << "Nhap lop: ";
            cin >> lop;

            string lopUpper = ToUpper(lop);

            cout << "\nKet qua tim kiem:" << endl;
            for (int i = 0; i < demSV; i++) {
                string lopSVUpper = ToUpper(dsSV[i].lop);
                if (lopSVUpper == lopUpper) {
                    cout << "Ma SV: " << dsSV[i].maSV << " - "
                         << "Ho Ten: " << dsSV[i].hoTen << " - "
                         << "Diem: " << dsSV[i].diemTB << endl;
                    timThay = true;
                }
            }
            break;
        }
        case 4: {
            float diemMin, diemMax;
            cout << "Nhap diem min: ";
            cin >> diemMin;
            cout << "Nhap diem max: ";
            cin >> diemMax;

            cout << "\nKet qua tim kiem:" << endl;
            for (int i = 0; i < demSV; i++) {
                if (dsSV[i].diemTB >= diemMin && dsSV[i].diemTB <= diemMax) {
                    cout << "Ma SV: " << dsSV[i].maSV << " - "
                         << "Ho Ten: " << dsSV[i].hoTen << " - "
                         << "Lop: " << dsSV[i].lop << " - "
                         << "Diem: " << dsSV[i].diemTB << endl;
                    timThay = true;
                }
            }
            break;
        }
        default:
            cout << "Lua chon khong hop le!" << endl;
            return;
    }

    if (!timThay) {
        cout << "Khong tim thay sinh vien nao!" << endl;
    }
}

// ========== HAM SAP XEP ==========

void SapXepTheoDiem(SinhVien* dsSV, int demSV, bool tangDan) {
    // Selection sort
    for (int i = 0; i < demSV - 1; i++) {
        int viTriChon = i;

        for (int j = i + 1; j < demSV; j++) {
            if (tangDan) {
                if (dsSV[j].diemTB < dsSV[viTriChon].diemTB) {
                    viTriChon = j;
                }
            } else {
                if (dsSV[j].diemTB > dsSV[viTriChon].diemTB) {
                    viTriChon = j;
                }
            }
        }

        // Hoan doi
        if (viTriChon != i) {
            SinhVien temp = dsSV[i];
            dsSV[i] = dsSV[viTriChon];
            dsSV[viTriChon] = temp;
        }
    }
}

void SapXepTheoTen(SinhVien* dsSV, int demSV) {
    // Bubble sort theo ten (chu cuoi cung cua ho ten)
    for (int i = 0; i < demSV - 1; i++) {
        for (int j = 0; j < demSV - i - 1; j++) {
            // Lay ten (chu cuoi cung)
            string ten1 = "", ten2 = "";

            // Tim tu cuoi cua ho ten
            int viTriCachTen1 = -1, viTriCachTen2 = -1;

            for (int k = dsSV[j].hoTen.length() - 1; k >= 0; k--) {
                if (dsSV[j].hoTen[k] == ' ') {
                    viTriCachTen1 = k;
                    break;
                }
            }

            for (int k = dsSV[j + 1].hoTen.length() - 1; k >= 0; k--) {
                if (dsSV[j + 1].hoTen[k] == ' ') {
                    viTriCachTen2 = k;
                    break;
                }
            }

            if (viTriCachTen1 != -1) {
                for (int k = viTriCachTen1 + 1; k < dsSV[j].hoTen.length(); k++) {
                    ten1 = ten1 + dsSV[j].hoTen[k];
                }
            } else {
                ten1 = dsSV[j].hoTen;
            }

            if (viTriCachTen2 != -1) {
                for (int k = viTriCachTen2 + 1; k < dsSV[j + 1].hoTen.length(); k++) {
                    ten2 = ten2 + dsSV[j + 1].hoTen[k];
                }
            } else {
                ten2 = dsSV[j + 1].hoTen;
            }

            // So sanh ten
            string ten1Upper = ToUpper(ten1);
            string ten2Upper = ToUpper(ten2);

            if (ten1Upper > ten2Upper) {
                SinhVien temp = dsSV[j];
                dsSV[j] = dsSV[j + 1];
                dsSV[j + 1] = temp;
            }
        }
    }
}

void SapXepSinhVien(SinhVien* dsSV, int demSV) {
    if (demSV == 0) {
        cout << "Danh sach rong!" << endl;
        return;
    }

    cout << "\n===== SAP XEP SINH VIEN =====" << endl;
    cout << "1. Sap xep theo diem tang dan" << endl;
    cout << "2. Sap xep theo diem giam dan" << endl;
    cout << "3. Sap xep theo ten" << endl;
    cout << "Chon: ";

    int luaChon;
    cin >> luaChon;

    switch (luaChon) {
        case 1:
            SapXepTheoDiem(dsSV, demSV, true);
            cout << "Sap xep thanh cong!" << endl;
            HienThiDanhSachSinhVien(dsSV, demSV);
            break;
        case 2:
            SapXepTheoDiem(dsSV, demSV, false);
            cout << "Sap xep thanh cong!" << endl;
            HienThiDanhSachSinhVien(dsSV, demSV);
            break;
        case 3:
            SapXepTheoTen(dsSV, demSV);
            cout << "Sap xep thanh cong!" << endl;
            HienThiDanhSachSinhVien(dsSV, demSV);
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
    }
}

// ========== THONG KE ==========

void ThongKeSinhVien(SinhVien* dsSV, int demSV) {
    if (demSV == 0) {
        cout << "Danh sach rong!" << endl;
        return;
    }

    cout << "\n===== THONG KE =====" << endl;

    // Tinh diem trung binh
    float tongDiem = 0.0;
    for (int i = 0; i < demSV; i++) {
        tongDiem += dsSV[i].diemTB;
    }
    float diemTB = tongDiem / demSV;

    // Tim diem cao nhat va thap nhat
    float diemCaoNhat = dsSV[0].diemTB;
    float diemThapNhat = dsSV[0].diemTB;

    for (int i = 1; i < demSV; i++) {
        if (dsSV[i].diemTB > diemCaoNhat) {
            diemCaoNhat = dsSV[i].diemTB;
        }
        if (dsSV[i].diemTB < diemThapNhat) {
            diemThapNhat = dsSV[i].diemTB;
        }
    }

    // Phan loai sinh vien
    int xuatSac = 0, gioi = 0, kha = 0, trungBinh = 0, yeu = 0;

    for (int i = 0; i < demSV; i++) {
        if (dsSV[i].diemTB >= 9.0) {
            xuatSac++;
        } else if (dsSV[i].diemTB >= 8.0) {
            gioi++;
        } else if (dsSV[i].diemTB >= 6.5) {
            kha++;
        } else if (dsSV[i].diemTB >= 5.0) {
            trungBinh++;
        } else {
            yeu++;
        }
    }

    cout << "Tong so sinh vien: " << demSV << endl;
    cout << "Diem trung binh chung: " << diemTB << endl;
    cout << "Diem cao nhat: " << diemCaoNhat << endl;
    cout << "Diem thap nhat: " << diemThapNhat << endl;
    cout << "\nPhan loai:" << endl;
    cout << "Xuat sac (>= 9.0): " << xuatSac << " sinh vien" << endl;
    cout << "Gioi (>= 8.0): " << gioi << " sinh vien" << endl;
    cout << "Kha (>= 6.5): " << kha << " sinh vien" << endl;
    cout << "Trung binh (>= 5.0): " << trungBinh << " sinh vien" << endl;
    cout << "Yeu (< 5.0): " << yeu << " sinh vien" << endl;
}

// ========== HAM MAIN ==========

int main() {
    cout << "=== HE THONG QUAN LY SINH VIEN ===" << endl;

    const int MAX = 200;
    SinhVien* dsSV = new SinhVien[MAX];
    int demSV = 0;

    // Doc du lieu tu file
    DocFileSinhVien(dsSV, demSV, "DanhSachSinhVien.txt");

    // Menu chuong trinh
    int luaChon;
    do {
        cout << "\n========== MENU ==========" << endl;
        cout << "1. Hien thi danh sach sinh vien" << endl;
        cout << "2. Them sinh vien moi" << endl;
        cout << "3. Xoa sinh vien" << endl;
        cout << "4. Sua thong tin sinh vien" << endl;
        cout << "5. Tim kiem sinh vien" << endl;
        cout << "6. Sap xep sinh vien" << endl;
        cout << "7. Thong ke" << endl;
        cout << "8. Luu file" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon chuc nang: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                HienThiDanhSachSinhVien(dsSV, demSV);
                break;
            case 2:
                ThemSinhVien(dsSV, demSV, MAX);
                break;
            case 3:
                XoaSinhVien(dsSV, demSV);
                break;
            case 4:
                SuaSinhVien(dsSV, demSV);
                break;
            case 5:
                TimKiemSinhVien(dsSV, demSV);
                break;
            case 6:
                SapXepSinhVien(dsSV, demSV);
                break;
            case 7:
                ThongKeSinhVien(dsSV, demSV);
                break;
            case 8:
                LuuFileSinhVien(dsSV, demSV, "DanhSachSinhVien.txt");
                break;
            case 0:
                // Luu truoc khi thoat
                char xacNhan;
                cout << "Ban co muon luu truoc khi thoat? (y/n): ";
                cin >> xacNhan;
                if (xacNhan == 'y' || xacNhan == 'Y') {
                    LuuFileSinhVien(dsSV, demSV, "DanhSachSinhVien.txt");
                }
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }

    } while (luaChon != 0);

    // Giai phong bo nho
    delete[] dsSV;

    return 0;
}
