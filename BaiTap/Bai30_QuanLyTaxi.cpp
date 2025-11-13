/*
BÀI 30: QUẢN LÝ TAXI
- Quản lý xe (biển số, loại xe, tài xế)
- Đặt xe (điểm đón, điểm đến)
- Tính cước (km đầu, km sau, phụ phí)
- Thống kê doanh thu theo xe/tài xế
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
struct Xe {
    string bienSo, loai, taiXe, sdt;
    bool dangRanh;
};

struct CuocXe {
    string maCuoc, bienSo;
    string hoTenKH, sdtKH;
    string diemDon, diemDen;
    float soKm;
    float cuoc;
    string ngay;
};

// === DỮ LIỆU ===
Xe dsXe[10] = {
    {"29A-12345", "4 cho", "Nguyen Van A", "0901234567", true},
    {"29B-67890", "4 cho", "Tran Thi B", "0907654321", true},
    {"30C-11111", "7 cho", "Le Van C", "0912345678", true},
    {"30D-22222", "7 cho", "Pham Thi D", "0909876543", true}
};
int soXe = 4;

CuocXe* dsCuoc = NULL;
int soCuoc = 0;

// Bảng giá
const float GIA_MO_CUA = 15000;  // 2 km đầu
const float GIA_KM_SAU = 12000;  // Từ km thứ 3

// === CHỨC NĂNG ===
void DanhSachXe() {
    cout << "\n=== DANH SACH XE ===\n";
    for (int i = 0; i < soXe; i++) {
        cout << (i+1) << ". " << dsXe[i].bienSo << " | " << dsXe[i].loai
             << " | TX: " << dsXe[i].taiXe << " | "
             << (dsXe[i].dangRanh ? "RANH" : "DANG CHAY") << "\n";
    }
}

void DatXe() {
    cout << "\n=== DAT XE ===\n";

    // Chọn xe rảnh
    cout << "Danh sach xe ranh:\n";
    bool coXeRanh = false;
    for (int i = 0; i < soXe; i++) {
        if (dsXe[i].dangRanh) {
            cout << (i+1) << ". " << dsXe[i].bienSo << " (" << dsXe[i].loai
                 << ") - TX: " << dsXe[i].taiXe << "\n";
            coXeRanh = true;
        }
    }

    if (!coXeRanh) {
        cout << "Hien tai khong co xe ranh!\n";
        return;
    }

    cout << "\nChon xe: "; int c; cin >> c; c--;
    if (c < 0 || c >= soXe || !dsXe[c].dangRanh) {
        cout << "Khong hop le!\n";
        return;
    }

    CuocXe cuoc;
    cuoc.maCuoc = "CX" + IntToStr(soCuoc + 1);
    cuoc.bienSo = dsXe[c].bienSo;

    cout << "Ho ten khach: "; cin.ignore(); getline(cin, cuoc.hoTenKH);
    cout << "SDT: "; getline(cin, cuoc.sdtKH);
    cout << "Diem don: "; getline(cin, cuoc.diemDon);
    cout << "Diem den: "; getline(cin, cuoc.diemDen);
    cout << "So km: "; cin >> cuoc.soKm;
    cout << "Ngay (dd/mm/yyyy): "; cin >> cuoc.ngay;

    // Tính cước
    if (cuoc.soKm <= 2) {
        cuoc.cuoc = GIA_MO_CUA;
    } else {
        cuoc.cuoc = GIA_MO_CUA + (cuoc.soKm - 2) * GIA_KM_SAU;
    }

    // Phụ phí giờ cao điểm (20%)
    cout << "Gio cao diem? (1=Co, 0=Khong): "; int caoDiem; cin >> caoDiem;
    if (caoDiem == 1) {
        cuoc.cuoc *= 1.20;
        cout << ">>> Phu phi gio cao diem +20%\n";
    }

    dsXe[c].dangRanh = false;

    cout << "\n[OK] Dat xe thanh cong!\n";
    cout << "Ma cuoc: " << cuoc.maCuoc << "\n";
    cout << "Xe: " << dsXe[c].bienSo << " - TX: " << dsXe[c].taiXe << "\n";
    cout << "Cuoc: " << FloatToStr(cuoc.cuoc) << " VND\n";

    CuocXe* tmp = new CuocXe[soCuoc + 1];
    for (int i = 0; i < soCuoc; i++) tmp[i] = dsCuoc[i];
    tmp[soCuoc] = cuoc;
    delete[] dsCuoc;
    dsCuoc = tmp;
    soCuoc++;
}

void KetThucCuoc() {
    cout << "\n=== KET THUC CUOC ===\n";
    cout << "Bien so xe: "; string bs; cin.ignore(); getline(cin, bs);

    for (int i = 0; i < soXe; i++) {
        if (dsXe[i].bienSo == bs) {
            dsXe[i].dangRanh = true;
            cout << "[OK] Xe " << bs << " da ve trang thai ranh\n";
            return;
        }
    }

    cout << "Khong tim thay xe!\n";
}

void ThongKe() {
    cout << "\n=== THONG KE DOANH THU ===\n";

    for (int i = 0; i < soXe; i++) {
        float tongCuoc = 0;
        int soCuocXe = 0;

        for (int j = 0; j < soCuoc; j++) {
            if (dsCuoc[j].bienSo == dsXe[i].bienSo) {
                tongCuoc += dsCuoc[j].cuoc;
                soCuocXe++;
            }
        }

        if (soCuocXe > 0) {
            cout << dsXe[i].bienSo << " (TX: " << dsXe[i].taiXe << "):\n";
            cout << "  So cuoc: " << soCuocXe << "\n";
            cout << "  Doanh thu: " << FloatToStr(tongCuoc) << " VND\n\n";
        }
    }
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== QUAN LY TAXI =====\n";
        cout << "1. Danh sach xe\n";
        cout << "2. Dat xe\n";
        cout << "3. Ket thuc cuoc\n";
        cout << "4. Thong ke doanh thu\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachXe();
        else if (c == 2) DatXe();
        else if (c == 3) KetThucCuoc();
        else if (c == 4) ThongKe();
        else if (c == 0) break;
    }

    delete[] dsCuoc;
    return 0;
}
