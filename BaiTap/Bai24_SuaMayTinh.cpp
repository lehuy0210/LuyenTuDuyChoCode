/*
BÀI 24: DỊCH VỤ SỬA MÁY TÍNH
- Nhận máy (tên KH, SĐT, triệu chứng)
- Báo giá (linh kiện + công sửa)
- Trạng thái (Đang kiểm tra, Đang sửa, Hoàn thành)
- Giao máy (thanh toán)
*/

#include <iostream>
#include <string>
using namespace std;

struct PhieuSua { string ma, hoTen, sdt, trieuChung, ngayNhan; float giaLK, giaCong, tongTien; string tt; };
PhieuSua* dsPS = NULL;
int soPS = 0;

void NhanMay() {
    PhieuSua ps;
    ps.ma = "PS" + to_string(soPS + 1);
    cout << "Ho ten: "; cin.ignore(); getline(cin, ps.hoTen);
    cout << "SDT: "; getline(cin, ps.sdt);
    cout << "Trieu chung: "; getline(cin, ps.trieuChung);
    cout << "Ngay nhan: "; cin >> ps.ngayNhan;
    ps.tt = "DangKiemTra";
    ps.giaLK = 0; ps.giaCong = 0; ps.tongTien = 0;

    PhieuSua* tmp = new PhieuSua[soPS + 1];
    for (int i = 0; i < soPS; i++) tmp[i] = dsPS[i];
    tmp[soPS] = ps;
    delete[] dsPS; dsPS = tmp; soPS++;

    cout << "[OK] Ma phieu: " << ps.ma << "\n";
}

void BaoGia() {
    cout << "Ma phieu: "; string ma; cin >> ma;
    for (int i = 0; i < soPS; i++) {
        if (dsPS[i].ma == ma) {
            cout << "Gia linh kien: "; cin >> dsPS[i].giaLK;
            cout << "Tien cong: "; cin >> dsPS[i].giaCong;
            dsPS[i].tongTien = dsPS[i].giaLK + dsPS[i].giaCong;
            dsPS[i].tt = "DaBaoGia";
            cout << "[OK] Tong: " << dsPS[i].tongTien << " VND\n";
            return;
        }
    }
    cout << "Khong tim thay!\n";
}

int main() {
    while (true) {
        cout << "\n1. Nhan may\n2. Bao gia\n0. Thoat\nChon: ";
        int c; cin >> c;
        if (c == 1) NhanMay();
        else if (c == 2) BaoGia();
        else if (c == 0) break;
    }
    delete[] dsPS;
    return 0;
}
