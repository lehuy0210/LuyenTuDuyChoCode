#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Hàm chuyển đổi int -> string (không dùng to_string)
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

// Hàm chuyển đổi string -> int (không dùng stoi)
int StrToInt(const string& str) {
    int result = 0;
    int sign = 1;
    int i = 0;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    for (; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result * sign;
}

// Hàm chuyển đổi float -> string
string FloatToStr(float num) {
    int intPart = (int)num;
    float decimalPart = num - intPart;
    if (decimalPart < 0) decimalPart = -decimalPart;
    int dec = (int)(decimalPart * 100 + 0.5);
    return IntToStr(intPart) + "." + (dec < 10 ? "0" : "") + IntToStr(dec);
}

struct HocVien {
    string ma;
    string hoTen;
    string sdt;
    string email;
    string khoaHoc;  // "Tieng Anh Giao Tiep", "TOEIC", "IELTS", "Tre Em"
    int soThang;
    float hocPhi;
    bool daDongTien;
};

struct KhoaHoc {
    string ten;
    float giaThanh;  // VND/tháng
    int soTiet;      // số tiết/tháng
};

const int MAX_HV = 100;
const int MAX_KH = 10;
HocVien dsHV[MAX_HV];
KhoaHoc dsKH[MAX_KH];
int soHV = 0;
int soKH = 0;

void KhoiTaoKhoaHoc() {
    dsKH[soKH++] = {"Tieng Anh Giao Tiep", 2000000, 24};
    dsKH[soKH++] = {"TOEIC", 2500000, 28};
    dsKH[soKH++] = {"IELTS", 3500000, 32};
    dsKH[soKH++] = {"Tre Em", 1800000, 20};
}

void HienThiKhoaHoc() {
    cout << "\n===== DANH SACH KHOA HOC =====\n";
    for (int i = 0; i < soKH; i++) {
        cout << (i+1) << ". " << dsKH[i].ten
             << " - " << FloatToStr(dsKH[i].giaThanh) << " VND/thang"
             << " - " << dsKH[i].soTiet << " tiet/thang\n";
    }
}

void DangKyHocVien() {
    if (soHV >= MAX_HV) {
        cout << "Da dat gioi han hoc vien!\n";
        return;
    }

    HocVien hv;
    hv.ma = "HV" + IntToStr(1001 + soHV);

    cout << "\n===== DANG KY HOC VIEN MOI =====\n";
    cout << "Ma hoc vien: " << hv.ma << "\n";
    cout << "Ho ten: "; cin.ignore(); getline(cin, hv.hoTen);
    cout << "So dien thoai: "; getline(cin, hv.sdt);
    cout << "Email: "; getline(cin, hv.email);

    HienThiKhoaHoc();
    int chon;
    cout << "Chon khoa hoc (1-" << soKH << "): "; cin >> chon;
    if (chon < 1 || chon > soKH) {
        cout << "Khoa hoc khong hop le!\n";
        return;
    }
    hv.khoaHoc = dsKH[chon-1].ten;

    cout << "So thang dang ky: "; cin >> hv.soThang;
    hv.hocPhi = dsKH[chon-1].giaThanh * hv.soThang;

    // Giảm giá theo số tháng
    if (hv.soThang >= 12) {
        hv.hocPhi *= 0.85;  // -15%
        cout << "Giam gia 15% cho dang ky 12 thang!\n";
    } else if (hv.soThang >= 6) {
        hv.hocPhi *= 0.90;  // -10%
        cout << "Giam gia 10% cho dang ky 6 thang!\n";
    }

    hv.daDongTien = false;

    dsHV[soHV++] = hv;

    cout << "\n>>> Dang ky thanh cong! Hoc phi: " << FloatToStr(hv.hocPhi) << " VND\n";
    cout << ">>> Vui long dong hoc phi de bat dau hoc!\n";
}

void DongHocPhi() {
    string ma;
    cout << "\n===== DONG HOC PHI =====\n";
    cout << "Ma hoc vien: "; cin >> ma;

    for (int i = 0; i < soHV; i++) {
        if (dsHV[i].ma == ma) {
            if (dsHV[i].daDongTien) {
                cout << "Hoc vien da dong hoc phi!\n";
                return;
            }

            cout << "\n----- THONG TIN HOC VIEN -----\n";
            cout << "Ho ten: " << dsHV[i].hoTen << "\n";
            cout << "Khoa hoc: " << dsHV[i].khoaHoc << "\n";
            cout << "So thang: " << dsHV[i].soThang << "\n";
            cout << "Hoc phi: " << FloatToStr(dsHV[i].hocPhi) << " VND\n";

            char xacNhan;
            cout << "\nXac nhan dong tien (Y/N)? "; cin >> xacNhan;
            if (xacNhan == 'Y' || xacNhan == 'y') {
                dsHV[i].daDongTien = true;
                cout << "\n>>> Dong hoc phi thanh cong!\n";
                cout << ">>> Chuc hoc vien hoc tot!\n";
            }
            return;
        }
    }
    cout << "Khong tim thay hoc vien!\n";
}

void HienThiHocVien() {
    cout << "\n===== DANH SACH HOC VIEN =====\n";
    for (int i = 0; i < soHV; i++) {
        cout << "\n" << (i+1) << ". " << dsHV[i].ma << " - " << dsHV[i].hoTen << "\n";
        cout << "   Khoa hoc: " << dsHV[i].khoaHoc << " (" << dsHV[i].soThang << " thang)\n";
        cout << "   Hoc phi: " << FloatToStr(dsHV[i].hocPhi) << " VND\n";
        cout << "   Trang thai: " << (dsHV[i].daDongTien ? "Da dong tien" : "Chua dong tien") << "\n";
    }
}

void ThongKe() {
    int tongHV = soHV;
    int hvDaDong = 0;
    float tongDoanhThu = 0;

    for (int i = 0; i < soHV; i++) {
        if (dsHV[i].daDongTien) {
            hvDaDong++;
            tongDoanhThu += dsHV[i].hocPhi;
        }
    }

    cout << "\n===== THONG KE =====\n";
    cout << "Tong hoc vien: " << tongHV << "\n";
    cout << "Da dong tien: " << hvDaDong << "\n";
    cout << "Chua dong tien: " << (tongHV - hvDaDong) << "\n";
    cout << "Tong doanh thu: " << FloatToStr(tongDoanhThu) << " VND\n";
}

int main() {
    KhoiTaoKhoaHoc();

    int chon;
    do {
        cout << "\n===== QUAN LY TRUNG TAM TIENG ANH =====\n";
        cout << "1. Hien thi khoa hoc\n";
        cout << "2. Dang ky hoc vien moi\n";
        cout << "3. Dong hoc phi\n";
        cout << "4. Hien thi danh sach hoc vien\n";
        cout << "5. Thong ke\n";
        cout << "0. Thoat\n";
        cout << "Chon: "; cin >> chon;

        switch(chon) {
            case 1: HienThiKhoaHoc(); break;
            case 2: DangKyHocVien(); break;
            case 3: DongHocPhi(); break;
            case 4: HienThiHocVien(); break;
            case 5: ThongKe(); break;
        }
    } while (chon != 0);

    return 0;
}
