/*
BÀI 48: DỊCH VỤ GIAO HOA NHANH
- Đặt hoa online
- Giao hàng theo khung giờ
- Phí giao khẩn cấp (trong 2h)
- Ghi thiệp tặng kèm
*/

#include <iostream>
#include <string>
using namespace std;

string IntToStr(int num) {
    if (num == 0) return "0";
    string result = "";
    while (num > 0) { result = char('0' + num % 10) + result; num /= 10; }
    return result;
}

string FloatToStr(float num) {
    int intPart = (int)num;
    int decPart = (int)((num - intPart) * 100);
    if (decPart < 0) decPart = -decPart;
    return IntToStr(intPart) + "." + (decPart < 10 ? "0" : "") + IntToStr(decPart);
}

struct DonHang {
    string maDH, hoTenKH, hoTenNguoiNhan, diaChiGiao;
    string loaiHoa;  // "Hong", "Tulip", "Huong duong"...
    int soLuong;
    string loiThiep;
    bool khancap;  // Giao trong 2h
    float tienHoa, phiGiao, tongTien;
};

const float GIA_HOA_TU = 250000;
const float GIA_HOA_TO = 450000;
const float PHI_GIAO_BINH_THUONG = 30000;
const float PHI_GIAO_KHAN_CAP = 100000;

DonHang* dsDH = NULL;
int soDH = 0;

void DatHoa() {
    cout << "\n=== DAT HOA ONLINE ===\n";
    DonHang dh;
    dh.maDH = "DH" + IntToStr(soDH + 1);

    cout << "Ho ten khach: "; cin.ignore(); getline(cin, dh.hoTenKH);
    cout << "Nguoi nhan: "; getline(cin, dh.hoTenNguoiNhan);
    cout << "Dia chi giao: "; getline(cin, dh.diaChiGiao);
    cout << "Loai hoa (Hong/Tulip/Huongduong): "; getline(cin, dh.loaiHoa);

    cout << "Kich co (1=Bo tu, 2=Bo to): "; int kc; cin >> kc;
    dh.tienHoa = (kc == 1) ? GIA_HOA_TU : GIA_HOA_TO;

    cout << "Loi thiep (de trong neu khong): "; cin.ignore(); getline(cin, dh.loiThiep);

    cout << "Giao khan cap (<2h)? (1=Co, 0=Khong): "; int kc2; cin >> kc2;
    dh.khancap = (kc2 == 1);
    dh.phiGiao = dh.khancap ? PHI_GIAO_KHAN_CAP : PHI_GIAO_BINH_THUONG;

    dh.tongTien = dh.tienHoa + dh.phiGiao;

    cout << "\n[OK] Ma don: " << dh.maDH << " | Tong: " << FloatToStr(dh.tongTien) << " VND\n";

    DonHang* tmp = new DonHang[soDH + 1];
    for (int i = 0; i < soDH; i++) tmp[i] = dsDH[i];
    tmp[soDH] = dh;
    delete[] dsDH; dsDH = tmp; soDH++;
}

int main() {
    while (true) {
        cout << "\n1. Dat hoa | 0. Thoat\nChon: "; int c; cin >> c;
        if (c == 1) DatHoa();
        else break;
    }
    delete[] dsDH;
    return 0;
}
