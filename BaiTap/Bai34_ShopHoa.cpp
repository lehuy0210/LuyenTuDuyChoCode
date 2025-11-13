/*
BÀI 34: SHOP HOA
- Quản lý hoa (loại, màu, giá)
- Bó hoa theo yêu cầu (custom bouquet)
- Đặt hoa online (giao hàng)
- Giảm giá theo ngày (hoa tươi giảm giá nếu lâu)
*/

#include <iostream>
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

string FloatToStr(float num) {
    int intPart = (int)num;
    int decPart = (int)((num - intPart) * 100);
    if (decPart < 0) decPart = -decPart;
    return IntToStr(intPart) + "." + (decPart < 10 ? "0" : "") + IntToStr(decPart);
}

// === CẤU TRÚC ===
struct Hoa {
    string ma, ten, mau;
    float giaCay;  // Giá 1 cây
    int tonKho;
    int soNgayNhap;  // Số ngày từ lúc nhập, để tính giảm giá
};

struct DonHang {
    string maDH, hoTenKH, sdt, diaChiGiao;
    string maHoa[20];
    int soLuong[20];
    int soLoai;
    float phiGiaoHang;
    float tongTien;
    string ngayDat;
};

// === DỮ LIỆU ===
Hoa dsHoa[30] = {
    {"H01", "Hong Do", "Do", 25000, 100, 1},
    {"H02", "Hong Trang", "Trang", 30000, 80, 1},
    {"H03", "Hong Vang", "Vang", 28000, 60, 1},
    {"H04", "Tuylip Do", "Do", 35000, 50, 2},
    {"H05", "Huong Duong", "Vang", 40000, 40, 1},
    {"H06", "Cuc Hoa Mi", "Trang", 15000, 200, 3},
    {"H07", "Lan Ho Diep", "Tim", 120000, 30, 1},
    {"H08", "Baby", "Trang", 80000, 50, 2}
};
int soHoa = 8;

DonHang* dsDH = NULL;
int soDH = 0;

// === CHỨC NĂNG ===
void DanhSachHoa() {
    cout << "\n=== DANH SACH HOA ===\n";
    for (int i = 0; i < soHoa; i++) {
        float giaHienTai = dsHoa[i].giaCay;

        // Giảm giá theo số ngày (hoa cũ giảm giá)
        if (dsHoa[i].soNgayNhap >= 3) {
            giaHienTai *= 0.70;  // Giảm 30%
            cout << (i+1) << ". " << dsHoa[i].ten << " (" << dsHoa[i].mau << ") - "
                 << FloatToStr(giaHienTai) << " VND/cay [GIAM 30%!] (Ton: "
                 << dsHoa[i].tonKho << ")\n";
        } else if (dsHoa[i].soNgayNhap == 2) {
            giaHienTai *= 0.85;  // Giảm 15%
            cout << (i+1) << ". " << dsHoa[i].ten << " (" << dsHoa[i].mau << ") - "
                 << FloatToStr(giaHienTai) << " VND/cay [GIAM 15%] (Ton: "
                 << dsHoa[i].tonKho << ")\n";
        } else {
            cout << (i+1) << ". " << dsHoa[i].ten << " (" << dsHoa[i].mau << ") - "
                 << FloatToStr(giaHienTai) << " VND/cay (Ton: "
                 << dsHoa[i].tonKho << ")\n";
        }
    }
}

void BoHoaTuChon() {
    cout << "\n=== BO HOA TU CHON ===\n";

    DonHang dh;
    dh.maDH = "DH" + IntToStr(soDH + 1);
    cout << "Ho ten khach: "; cin.ignore(); getline(cin, dh.hoTenKH);
    cout << "SDT: "; getline(cin, dh.sdt);
    cout << "Dia chi giao: "; getline(cin, dh.diaChiGiao);
    cout << "Ngay dat (dd/mm/yyyy): "; cin >> dh.ngayDat;

    dh.soLoai = 0;
    dh.tongTien = 0;

    cout << "\nChon hoa de bo:\n";

    while (true) {
        DanhSachHoa();
        cout << "\nChon loai hoa (0 de ket thuc): "; int c; cin >> c;
        if (c == 0) break;
        c--;

        if (c < 0 || c >= soHoa) {
            cout << "Khong hop le!\n";
            continue;
        }

        cout << "So cay: "; int sl; cin >> sl;

        if (sl > dsHoa[c].tonKho) {
            cout << "Khong du hang!\n";
            continue;
        }

        // Tính giá theo số ngày
        float gia = dsHoa[c].giaCay;
        if (dsHoa[c].soNgayNhap >= 3) gia *= 0.70;
        else if (dsHoa[c].soNgayNhap == 2) gia *= 0.85;

        dh.maHoa[dh.soLoai] = dsHoa[c].ma;
        dh.soLuong[dh.soLoai] = sl;
        dh.soLoai++;

        dsHoa[c].tonKho -= sl;
        dh.tongTien += gia * sl;

        cout << "[OK] Da them " << dsHoa[c].ten << "\n";
    }

    if (dh.soLoai == 0) {
        cout << "Khong co hoa nao!\n";
        return;
    }

    // Phí giao hàng
    cout << "\nPhi giao hang:\n";
    cout << "1. Giao trong thanh pho: 30,000 VND\n";
    cout << "2. Giao ngoai thanh: 50,000 VND\n";
    cout << "3. Tu den lay: 0 VND\n";
    cout << "Chon: "; int loaiGiao; cin >> loaiGiao;

    if (loaiGiao == 1) dh.phiGiaoHang = 30000;
    else if (loaiGiao == 2) dh.phiGiaoHang = 50000;
    else dh.phiGiaoHang = 0;

    dh.tongTien += dh.phiGiaoHang;

    cout << "\n[OK] Dat hang thanh cong!\n";
    cout << "Ma don hang: " << dh.maDH << "\n";
    cout << "Tong tien: " << FloatToStr(dh.tongTien) << " VND\n";

    DonHang* tmp = new DonHang[soDH + 1];
    for (int i = 0; i < soDH; i++) tmp[i] = dsDH[i];
    tmp[soDH] = dh;
    delete[] dsDH;
    dsDH = tmp;
    soDH++;
}

void CapNhatNgayNhap() {
    cout << "\n=== CAP NHAT NGAY NHAP (Tang ngay cho tat ca hoa) ===\n";
    for (int i = 0; i < soHoa; i++) {
        dsHoa[i].soNgayNhap++;
    }
    cout << "[OK] Da tang ngay nhap cho tat ca hoa!\n";
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== SHOP HOA =====\n";
        cout << "1. Danh sach hoa\n";
        cout << "2. Bo hoa tu chon\n";
        cout << "3. Cap nhat ngay nhap (+1 ngay)\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachHoa();
        else if (c == 2) BoHoaTuChon();
        else if (c == 3) CapNhatNgayNhap();
        else if (c == 0) break;
    }

    delete[] dsDH;
    return 0;
}
