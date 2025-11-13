/*
BÀI 26: QUẢN LÝ BỆNH VIỆN
- Đăng ký khám (bệnh nhân, khoa khám, bác sĩ)
- Phân phòng bệnh (nội trú)
- Kê đơn thuốc (tên, liều lượng, giá)
- Xuất viện và thanh toán (tiền khám + thuốc + phòng)
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// === HÀM TỰ VIẾT ===
int StrToInt(const string& str) {
    int result = 0, sign = 1, i = 0;
    if (str[0] == '-') { sign = -1; i = 1; }
    for (; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') result = result * 10 + (str[i] - '0');
    }
    return result * sign;
}

string IntToStr(int num) {
    if (num == 0) return "0";
    string result = "";
    bool neg = num < 0;
    if (neg) num = -num;
    while (num > 0) {
        result = char('0' + num % 10) + result;
        num /= 10;
    }
    return neg ? "-" + result : result;
}

float StrToFloat(const string& str) {
    float result = 0, sign = 1;
    int i = 0;
    if (str[0] == '-') { sign = -1; i = 1; }
    bool afterDot = false;
    float divisor = 1;
    for (; i < str.length(); i++) {
        if (str[i] == '.') afterDot = true;
        else if (str[i] >= '0' && str[i] <= '9') {
            if (afterDot) {
                divisor *= 10;
                result += (str[i] - '0') / divisor;
            } else {
                result = result * 10 + (str[i] - '0');
            }
        }
    }
    return result * sign;
}

string FloatToStr(float num) {
    int intPart = (int)num;
    int decPart = (int)((num - intPart) * 100);
    if (decPart < 0) decPart = -decPart;
    return IntToStr(intPart) + "." + (decPart < 10 ? "0" : "") + IntToStr(decPart);
}

// === CẤU TRÚC ===
struct BenhNhan {
    string ma, hoTen, sdt, ngaySinh, diaChi;
    string khoa, bacSi, ngayKham;
    float tienKham;
    bool noiTru;
    string soPhong;
    int soNgayNamVien;
};

struct DonThuoc {
    string maBN, tenThuoc;
    int soLuong;
    float donGia;
};

struct Phong {
    string soPhong;
    string loai;  // "Thuong", "VIP"
    float giaTheoNgay;
    bool daDung;
    string maBN;
};

// === DỮ LIỆU ===
BenhNhan* dsBN = NULL;
int soBN = 0;

DonThuoc* dsDT = NULL;
int soDT = 0;

Phong dsPhong[20] = {
    {"P101", "Thuong", 200000, false, ""},
    {"P102", "Thuong", 200000, false, ""},
    {"P103", "Thuong", 200000, false, ""},
    {"P201", "VIP", 500000, false, ""},
    {"P202", "VIP", 500000, false, ""}
};
int soPhong = 5;

// === CHỨC NĂNG ===
void DangKyKham() {
    BenhNhan bn;
    bn.ma = "BN" + IntToStr(soBN + 1);

    cout << "\n=== DANG KY KHAM ===\n";
    cout << "Ho ten: "; cin.ignore(); getline(cin, bn.hoTen);
    cout << "SDT: "; getline(cin, bn.sdt);
    cout << "Ngay sinh (dd/mm/yyyy): "; cin >> bn.ngaySinh;
    cout << "Dia chi: "; cin.ignore(); getline(cin, bn.diaChi);
    cout << "Khoa kham (Noi, Ngoai, San, Nhi, Mat...): "; getline(cin, bn.khoa);
    cout << "Bac si: "; getline(cin, bn.bacSi);
    cout << "Ngay kham: "; cin >> bn.ngayKham;
    cout << "Tien kham: "; cin >> bn.tienKham;

    cout << "Noi tru? (1=Co, 0=Khong): "; int nt; cin >> nt;
    bn.noiTru = (nt == 1);
    bn.soNgayNamVien = 0;
    bn.soPhong = "";

    if (bn.noiTru) {
        cout << "\n--- Danh sach phong trong ---\n";
        bool coPhong = false;
        for (int i = 0; i < soPhong; i++) {
            if (!dsPhong[i].daDung) {
                cout << dsPhong[i].soPhong << " (" << dsPhong[i].loai << ") - "
                     << FloatToStr(dsPhong[i].giaTheoNgay) << " VND/ngay\n";
                coPhong = true;
            }
        }

        if (coPhong) {
            cout << "Chon phong: "; string sp; cin >> sp;
            for (int i = 0; i < soPhong; i++) {
                if (dsPhong[i].soPhong == sp && !dsPhong[i].daDung) {
                    dsPhong[i].daDung = true;
                    dsPhong[i].maBN = bn.ma;
                    bn.soPhong = sp;
                    cout << "So ngay nam vien du kien: "; cin >> bn.soNgayNamVien;
                    break;
                }
            }
        } else {
            cout << "Het phong!\n";
            bn.noiTru = false;
        }
    }

    BenhNhan* tmp = new BenhNhan[soBN + 1];
    for (int i = 0; i < soBN; i++) tmp[i] = dsBN[i];
    tmp[soBN] = bn;
    delete[] dsBN;
    dsBN = tmp;
    soBN++;

    cout << "\n[OK] Ma benh nhan: " << bn.ma << "\n";
}

void KeDonThuoc() {
    cout << "\n=== KE DON THUOC ===\n";
    cout << "Ma benh nhan: "; string ma; cin >> ma;

    bool found = false;
    for (int i = 0; i < soBN; i++) {
        if (dsBN[i].ma == ma) {
            found = true;
            cout << "Benh nhan: " << dsBN[i].hoTen << "\n\n";

            cout << "So loai thuoc: "; int n; cin >> n;
            for (int j = 0; j < n; j++) {
                DonThuoc dt;
                dt.maBN = ma;
                cout << "\nThuoc " << (j+1) << ":\n";
                cout << "  Ten thuoc: "; cin.ignore(); getline(cin, dt.tenThuoc);
                cout << "  So luong: "; cin >> dt.soLuong;
                cout << "  Don gia: "; cin >> dt.donGia;

                DonThuoc* tmp = new DonThuoc[soDT + 1];
                for (int k = 0; k < soDT; k++) tmp[k] = dsDT[k];
                tmp[soDT] = dt;
                delete[] dsDT;
                dsDT = tmp;
                soDT++;
            }

            cout << "\n[OK] Da ke don thuoc!\n";
            break;
        }
    }

    if (!found) cout << "Khong tim thay benh nhan!\n";
}

void XuatVien() {
    cout << "\n=== XUAT VIEN ===\n";
    cout << "Ma benh nhan: "; string ma; cin >> ma;

    for (int i = 0; i < soBN; i++) {
        if (dsBN[i].ma == ma) {
            cout << "\n--- HOA DON XUAT VIEN ---\n";
            cout << "Benh nhan: " << dsBN[i].hoTen << "\n";
            cout << "Khoa: " << dsBN[i].khoa << " | Bac si: " << dsBN[i].bacSi << "\n";

            float tongTien = dsBN[i].tienKham;
            cout << "\n1. Tien kham: " << FloatToStr(dsBN[i].tienKham) << " VND\n";

            // Tính tiền thuốc
            float tienThuoc = 0;
            cout << "\n2. Thuoc:\n";
            for (int j = 0; j < soDT; j++) {
                if (dsDT[j].maBN == ma) {
                    float tt = dsDT[j].soLuong * dsDT[j].donGia;
                    cout << "   - " << dsDT[j].tenThuoc << " x" << dsDT[j].soLuong
                         << " = " << FloatToStr(tt) << " VND\n";
                    tienThuoc += tt;
                }
            }
            cout << "   Tong tien thuoc: " << FloatToStr(tienThuoc) << " VND\n";
            tongTien += tienThuoc;

            // Tính tiền phòng
            if (dsBN[i].noiTru) {
                float tienPhong = 0;
                for (int j = 0; j < soPhong; j++) {
                    if (dsPhong[j].soPhong == dsBN[i].soPhong) {
                        tienPhong = dsPhong[j].giaTheoNgay * dsBN[i].soNgayNamVien;
                        cout << "\n3. Phong " << dsBN[i].soPhong << " (" << dsPhong[j].loai << "):\n";
                        cout << "   " << dsBN[i].soNgayNamVien << " ngay x "
                             << FloatToStr(dsPhong[j].giaTheoNgay) << " = "
                             << FloatToStr(tienPhong) << " VND\n";

                        // Trả phòng
                        dsPhong[j].daDung = false;
                        dsPhong[j].maBN = "";
                        break;
                    }
                }
                tongTien += tienPhong;
            }

            cout << "\n" << string(40, '=') << "\n";
            cout << "TONG CONG: " << FloatToStr(tongTien) << " VND\n";
            cout << string(40, '=') << "\n";

            cout << "\n[OK] Xuat vien thanh cong!\n";
            return;
        }
    }

    cout << "Khong tim thay benh nhan!\n";
}

void DanhSachPhong() {
    cout << "\n=== DANH SACH PHONG ===\n";
    for (int i = 0; i < soPhong; i++) {
        cout << dsPhong[i].soPhong << " | " << dsPhong[i].loai << " | "
             << FloatToStr(dsPhong[i].giaTheoNgay) << " VND/ngay | ";
        if (dsPhong[i].daDung) {
            cout << "DANG SU DUNG (BN: " << dsPhong[i].maBN << ")\n";
        } else {
            cout << "TRONG\n";
        }
    }
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== BENH VIEN =====\n";
        cout << "1. Dang ky kham\n";
        cout << "2. Ke don thuoc\n";
        cout << "3. Xuat vien\n";
        cout << "4. Danh sach phong\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DangKyKham();
        else if (c == 2) KeDonThuoc();
        else if (c == 3) XuatVien();
        else if (c == 4) DanhSachPhong();
        else if (c == 0) break;
    }

    delete[] dsBN;
    delete[] dsDT;

    return 0;
}
