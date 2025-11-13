/*
BÀI 21: ĐẶT VÉ MÁY BAY
- Quản lý chuyến bay (số hiệu, điểm đi/đến, giờ bay)
- Đặt vé (hạng Economy/Business, hành lý)
- Chọn ghế (sơ đồ A-F, 1-30)
- Check-in online
*/

#include <iostream>
#include <string>
using namespace std;

struct ChuyenBay { string ma, diemDi, diemDen, gioBay; float giaEco, giaBus; int ghe[30][6]; };  // 30 hàng x 6 cột
struct DatVe { string maDV, maCB, hoTen, viTriGhe; float giaVe; };

ChuyenBay dsCB[5] = { {"VN123", "HAN", "SGN", "06:00", 1500000, 5000000, {{0}}} };
int soCB = 1;
DatVe* dsDV = NULL;
int soDV = 0;

void DatVe() {
    cout << "\n=== DAT VE ===\n";
    cout << "1. " << dsCB[0].ma << " " << dsCB[0].diemDi << "-" << dsCB[0].diemDen << " " << dsCB[0].gioBay << "\n";
    DatVe dv;
    dv.maDV = "DV" + to_string(soDV + 1);
    dv.maCB = dsCB[0].ma;
    cout << "Ho ten: "; cin.ignore(); getline(cin, dv.hoTen);
    cout << "Hang ve (1.Economy/2.Business): "; int h; cin >> h;
    dv.giaVe = (h == 1) ? dsCB[0].giaEco : dsCB[0].giaBus;
    cout << "Vi tri ghe (VD: A5): "; cin >> dv.viTriGhe;

    DatVe* tmp = new DatVe[soDV + 1];
    for (int i = 0; i < soDV; i++) tmp[i] = dsDV[i];
    tmp[soDV] = dv;
    delete[] dsDV; dsDV = tmp; soDV++;

    cout << "[OK] Ma dat ve: " << dv.maDV << "\nGia: " << dv.giaVe << " VND\n";
}

int main() {
    while (true) {
        cout << "\n1. Dat ve\n0. Thoat\nChon: ";
        int c; cin >> c;
        if (c == 1) DatVe();
        else if (c == 0) break;
    }
    delete[] dsDV;
    return 0;
}
