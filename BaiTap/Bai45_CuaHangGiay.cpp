/*
BÀI 45: CỬA HÀNG GIÀY DÉP
- Quản lý giày (thể thao, tây, sandal...)
- Size chart (EU, US, UK, CM)
- Bán hàng (mua 2 giảm 15%)
- Đổi size trong 3 ngày
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
struct Giay {
    string ma, ten, hang, loai;  // "TheThao", "Tay", "Sandal"
    float gia;
    int sizeEU[15];  // VD: 36, 37, 38... 50
    int tonKho[15];
    int soSize;
};

struct HoaDon {
    string maHD, hoTenKH, sdt, ngayMua;
    string maGiay[10];
    int sizeEU[10];
    int soLuong[10];
    int soMon;
    float tongTien;
    bool daDoi;
};

// === DỮ LIỆU ===
Giay dsGiay[20] = {
    {"G01", "Nike Air Max", "Nike", "TheThao", 2500000,
     {38, 39, 40, 41, 42, 43}, {5, 10, 8, 6, 4, 3}, 6},
    {"G02", "Adidas Ultraboost", "Adidas", "TheThao", 4200000,
     {39, 40, 41, 42, 43}, {3, 5, 7, 4, 2}, 5},
    {"G03", "Giay da nam cong so", "Pierre Cardin", "Tay", 1800000,
     {39, 40, 41, 42, 43, 44}, {8, 10, 12, 9, 6, 4}, 6},
    {"G04", "Sandal Adilette", "Adidas", "Sandal", 850000,
     {36, 37, 38, 39, 40, 41, 42}, {10, 12, 15, 10, 8, 6, 5}, 7}
};
int soGiay = 4;

HoaDon* dsHD = NULL;
int soHD = 0;

// === CHỨC NĂNG ===
void DanhSachGiay() {
    cout << "\n=== DANH SACH GIAY ===\n";
    for (int i = 0; i < soGiay; i++) {
        cout << (i+1) << ". " << dsGiay[i].ten << " (" << dsGiay[i].hang << ")\n";
        cout << "   Loai: " << dsGiay[i].loai << " | Gia: "
             << FloatToStr(dsGiay[i].gia) << " VND\n";
        cout << "   Size co san: ";
        for (int j = 0; j < dsGiay[i].soSize; j++) {
            cout << dsGiay[i].sizeEU[j];
            if (j < dsGiay[i].soSize - 1) cout << ", ";
        }
        cout << "\n\n";
    }
}

void BanHang() {
    cout << "\n=== BAN HANG ===\n";

    HoaDon hd;
    hd.maHD = "HD" + IntToStr(soHD + 1);
    cout << "Ho ten: "; cin.ignore(); getline(cin, hd.hoTenKH);
    cout << "SDT: "; getline(cin, hd.sdt);
    cout << "Ngay mua (dd/mm/yyyy): "; cin >> hd.ngayMua;

    hd.soMon = 0;
    hd.tongTien = 0;
    hd.daDoi = false;

    while (true) {
        DanhSachGiay();
        cout << "\nChon giay (0 = ket thuc): "; int c; cin >> c;
        if (c == 0) break;
        c--;

        if (c < 0 || c >= soGiay) {
            cout << "Khong hop le!\n";
            continue;
        }

        cout << "Size (EU): "; int size; cin >> size;

        // Kiểm tra size có sẵn không
        int idxSize = -1;
        for (int i = 0; i < dsGiay[c].soSize; i++) {
            if (dsGiay[c].sizeEU[i] == size) {
                idxSize = i;
                break;
            }
        }

        if (idxSize == -1 || dsGiay[c].tonKho[idxSize] == 0) {
            cout << "Size khong co san hoac het hang!\n";
            continue;
        }

        cout << "So luong: "; int sl; cin >> sl;
        if (sl > dsGiay[c].tonKho[idxSize]) {
            cout << "Khong du hang!\n";
            continue;
        }

        hd.maGiay[hd.soMon] = dsGiay[c].ma;
        hd.sizeEU[hd.soMon] = size;
        hd.soLuong[hd.soMon] = sl;
        hd.soMon++;

        dsGiay[c].tonKho[idxSize] -= sl;
        hd.tongTien += dsGiay[c].gia * sl;

        cout << "[OK] Da them vao gio hang!\n";
    }

    if (hd.soMon == 0) {
        cout << "Khong co san pham nao!\n";
        return;
    }

    // Khuyến mãi mua 2 đôi giảm 15%
    if (hd.soMon >= 2) {
        hd.tongTien *= 0.85;
        cout << "\n>>> MUA 2 DOI GIAM 15%!\n";
    }

    cout << "\n[OK] Tong tien: " << FloatToStr(hd.tongTien) << " VND\n";
    cout << "Ma hoa don: " << hd.maHD << " (luu de doi size trong 3 ngay)\n";

    HoaDon* tmp = new HoaDon[soHD + 1];
    for (int i = 0; i < soHD; i++) tmp[i] = dsHD[i];
    tmp[soHD] = hd;
    delete[] dsHD;
    dsHD = tmp;
    soHD++;
}

void DoiSize() {
    cout << "\n=== DOI SIZE (trong 3 ngay) ===\n";
    cout << "Ma hoa don: "; string maHD; cin >> maHD;

    for (int i = 0; i < soHD; i++) {
        if (dsHD[i].maHD == maHD) {
            if (dsHD[i].daDoi) {
                cout << "Hoa don nay da doi roi!\n";
                return;
            }

            cout << "\n--- THONG TIN HOA DON ---\n";
            cout << "Khach: " << dsHD[i].hoTenKH << " | Ngay mua: " << dsHD[i].ngayMua << "\n";

            cout << "\nXac nhan doi size? (1=Co, 0=Khong): "; int cf; cin >> cf;
            if (cf == 1) {
                dsHD[i].daDoi = true;
                cout << "[OK] Da ghi nhan doi size. Vui long mang giay den cua hang.\n";
            }
            return;
        }
    }

    cout << "Khong tim thay hoa don!\n";
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== CUA HANG GIAY DEP =====\n";
        cout << "1. Danh sach giay\n";
        cout << "2. Ban hang\n";
        cout << "3. Doi size\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachGiay();
        else if (c == 2) BanHang();
        else if (c == 3) DoiSize();
        else if (c == 0) break;
    }

    delete[] dsHD;
    return 0;
}
