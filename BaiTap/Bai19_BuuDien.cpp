/*
BÀI 19: BƯU ĐIỆN
- Gửi thư/bưu kiện (khối lượng, loại, điểm đến)
- Tính cước phí (nội thành/ngoại thành, nhanh/thường)
- Tra cứu đơn hàng
- Thống kê
*/

#include <iostream>
#include <string>
using namespace std;

int StrToInt(const string& s) { int r = 0; for (char c : s) if (c >= '0' && c <= '9') r = r * 10 + (c - '0'); return r; }

struct BuuPham { string ma, nguoiGui, nguoiNhan, diaChi, loai; float khoiLuong, cuocPhi; };
BuuPham* dsBP = NULL;
int soBP = 0;

float TinhCuocPhi(const string& loai, float kl, const string& kv) {
    float gia = 0;
    if (loai == "Thu") gia = 5000;
    else if (loai == "HangHoa") gia = kl * 15000;  // 15k/kg
    if (kv == "NgoaiThanh") gia *= 1.5;  // +50%
    return gia;
}

void GuiBuuPham() {
    BuuPham bp;
    bp.ma = "BP" + to_string(soBP + 1);
    cout << "\nNguoi gui: "; cin.ignore(); getline(cin, bp.nguoiGui);
    cout << "Nguoi nhan: "; getline(cin, bp.nguoiNhan);
    cout << "Dia chi: "; getline(cin, bp.diaChi);
    cout << "Loai (Thu/HangHoa): "; getline(cin, bp.loai);
    if (bp.loai == "HangHoa") { cout << "Khoi luong (kg): "; cin >> bp.khoiLuong; }
    else bp.khoiLuong = 0;
    cout << "Khu vuc (NoiThanh/NgoaiThanh): "; string kv; cin >> kv;
    bp.cuocPhi = TinhCuocPhi(bp.loai, bp.khoiLuong, kv);

    BuuPham* tmp = new BuuPham[soBP + 1];
    for (int i = 0; i < soBP; i++) tmp[i] = dsBP[i];
    tmp[soBP] = bp;
    delete[] dsBP; dsBP = tmp; soBP++;

    cout << "\n[OK] Ma: " << bp.ma << "\nCuoc phi: " << bp.cuocPhi << " VND\n";
}

int main() {
    while (true) {
        cout << "\n1. Gui buu pham\n0. Thoat\nChon: ";
        int c; cin >> c;
        if (c == 1) GuiBuuPham();
        else if (c == 0) break;
    }
    delete[] dsBP;
    return 0;
}
