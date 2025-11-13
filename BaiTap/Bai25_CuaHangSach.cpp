/*
BÀI 25: CỬA HÀNG SÁCH
- Quản lý sách (tên, tác giả, thể loại, giá, tồn kho)
- Tìm kiếm (theo tên, tác giả, thể loại)
- Bán sách (giảm giá mua nhiều: >5 cuốn -10%, >10 cuốn -15%)
- Thống kê sách bán chạy
*/

#include <iostream>
#include <string>
using namespace std;

struct Sach { string ma, ten, tacGia, theLoai; float gia; int tonKho, daBan; };
struct DonBan { string ma; int soSach; float tongTien; };

Sach dsSach[50] = {
    {"S01", "Nha Gia Kim", "Paulo Coelho", "Tieu thuyet", 95000, 100, 0},
    {"S02", "Tuoi Tre Dang Gia Bao Nhieu", "Rosie Nguyen", "Self-help", 79000, 80, 0},
    {"S03", "Sapiens", "Yuval Noah Harari", "Lich su", 189000, 50, 0}
};
int soSach = 3;
DonBan* dsDB = NULL;
int soDB = 0;

void BanSach() {
    cout << "\n=== BAN SACH ===\n";
    for (int i = 0; i < soSach; i++) cout << (i+1) << ". " << dsSach[i].ten << " - " << dsSach[i].gia << " VND (Con: " << dsSach[i].tonKho << ")\n";
    cout << "Chon sach: "; int c; cin >> c; c--;
    cout << "So luong: "; int sl; cin >> sl;
    if (sl > dsSach[c].tonKho) { cout << "Khong du!\n"; return; }

    float tong = dsSach[c].gia * sl;
    if (sl >= 10) tong *= 0.85;  // -15%
    else if (sl >= 5) tong *= 0.9;  // -10%

    dsSach[c].tonKho -= sl;
    dsSach[c].daBan += sl;

    cout << "[OK] Tong: " << tong << " VND\n";
}

int main() {
    while (true) {
        cout << "\n1. Ban sach\n0. Thoat\nChon: ";
        int c; cin >> c;
        if (c == 1) BanSach();
        else if (c == 0) break;
    }
    delete[] dsDB;
    return 0;
}
