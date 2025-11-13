/*
BÀI 20: BẢO HIỂM
- Mua bảo hiểm (tên, loại BH, gói, phí hàng năm)
- Gia hạn bảo hiểm
- Yêu cầu bồi thường
- Kiểm tra tình trạng
*/

#include <iostream>
#include <string>
using namespace std;

int StrToInt(const string& s) { int r = 0; for (char c : s) if (c >= '0' && c <= '9') r = r * 10 + (c - '0'); return r; }

struct BaoHiem { string ma, hoTen, loai, ngayMua, ngayHetHan; float phiNam, soTienBH; string tt; };
BaoHiem* dsBH = NULL;
int soBH = 0;

void MuaBaoHiem() {
    BaoHiem bh;
    bh.ma = "BH" + to_string(soBH + 1);
    cout << "\nHo ten: "; cin.ignore(); getline(cin, bh.hoTen);
    cout << "Loai BH:\n1. Suc khoe\n2. Xe may\n3. Nha cua\nChon: "; int loai; cin >> loai;
    if (loai == 1) { bh.loai = "SucKhoe"; bh.phiNam = 2000000; bh.soTienBH = 50000000; }
    else if (loai == 2) { bh.loai = "XeMay"; bh.phiNam = 500000; bh.soTienBH = 20000000; }
    else { bh.loai = "NhaCua"; bh.phiNam = 3000000; bh.soTienBH = 500000000; }
    cout << "Ngay mua (dd/mm/yyyy): "; cin >> bh.ngayMua;
    cout << "Ngay het han (dd/mm/yyyy): "; cin >> bh.ngayHetHan;
    bh.tt = "HoatDong";

    BaoHiem* tmp = new BaoHiem[soBH + 1];
    for (int i = 0; i < soBH; i++) tmp[i] = dsBH[i];
    tmp[soBH] = bh;
    delete[] dsBH; dsBH = tmp; soBH++;

    cout << "\n[OK] Ma BH: " << bh.ma << "\nPhi nam: " << bh.phiNam << " VND\nSo tien BH: " << bh.soTienBH << " VND\n";
}

int main() {
    while (true) {
        cout << "\n1. Mua bao hiem\n0. Thoat\nChon: ";
        int c; cin >> c;
        if (c == 1) MuaBaoHiem();
        else if (c == 0) break;
    }
    delete[] dsBH;
    return 0;
}
