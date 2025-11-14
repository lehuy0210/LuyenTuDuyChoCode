/*
BÀI 43: TRUNG TÂM NGOẠI NGỮ
- Đăng ký khóa học (Anh, Hàn, Nhật, Trung...)
- Lớp theo trình độ (Beginner, Intermediate, Advanced)
- Học phí (theo khóa/tháng)
- Kiểm tra đầu vào
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
struct KhoaHoc {
    string maKH, tenKH, ngoaiNgu;  // "TiengAnh", "TiengHan", "TiengNhat"
    string trinhDo;  // "Beginner", "Intermediate", "Advanced"
    int soThang;
    float hocPhiThang;
    string lichHoc;  // VD: "T2,T4,T6 18h-20h"
    int soHocVienToiDa;
    int soHocVienHienTai;
};

struct HocVien {
    string maHV, hoTen, sdt, email;
    string maKH;  // Khóa học đang theo
    float daDong, conNo;
};

// === DỮ LIỆU ===
KhoaHoc dsKH[20] = {
    {"KH01", "Tieng Anh Giao Tiep", "TiengAnh", "Beginner", 3, 2000000, "T2,T4,T6 18h-20h", 15, 8},
    {"KH02", "Tieng Anh IELTS", "TiengAnh", "Intermediate", 6, 3500000, "T3,T5,T7 19h-21h", 12, 10},
    {"KH03", "Tieng Han Sơ Cap", "TiengHan", "Beginner", 4, 2500000, "T2,T4 18h-20h", 15, 5},
    {"KH04", "Tieng Nhat N5", "TiengNhat", "Beginner", 5, 2800000, "T3,T5,T7 18h-20h", 12, 7},
    {"KH05", "Tieng Trung HSK3", "TiengTrung", "Intermediate", 6, 3000000, "T2,T4,T6 19h-21h", 10, 6}
};
int soKH = 5;

HocVien* dsHV = NULL;
int soHV = 0;

// === CHỨC NĂNG ===
void DanhSachKhoaHoc() {
    cout << "\n=== DANH SACH KHOA HOC ===\n";
    for (int i = 0; i < soKH; i++) {
        cout << (i+1) << ". " << dsKH[i].tenKH << " (" << dsKH[i].trinhDo << ")\n";
        cout << "   Thoi luong: " << dsKH[i].soThang << " thang | Hoc phi: "
             << FloatToStr(dsKH[i].hocPhiThang) << " VND/thang\n";
        cout << "   Lich hoc: " << dsKH[i].lichHoc << "\n";
        cout << "   So hoc vien: " << dsKH[i].soHocVienHienTai << "/"
             << dsKH[i].soHocVienToiDa << "\n\n";
    }
}

void DangKyHoc() {
    cout << "\n=== DANG KY HOC ===\n";
    DanhSachKhoaHoc();

    cout << "Chon khoa hoc: "; int c; cin >> c; c--;
    if (c < 0 || c >= soKH) {
        cout << "Khong hop le!\n";
        return;
    }

    if (dsKH[c].soHocVienHienTai >= dsKH[c].soHocVienToiDa) {
        cout << "Lop da day!\n";
        return;
    }

    HocVien hv;
    hv.maHV = "HV" + IntToStr(soHV + 1);
    hv.maKH = dsKH[c].maKH;

    cout << "\nHo ten: "; cin.ignore(); getline(cin, hv.hoTen);
    cout << "SDT: "; getline(cin, hv.sdt);
    cout << "Email: "; getline(cin, hv.email);

    float tongHocPhi = dsKH[c].soThang * dsKH[c].hocPhiThang;

    cout << "\n--- THONG TIN KHOA HOC ---\n";
    cout << "Khoa: " << dsKH[c].tenKH << "\n";
    cout << "Thoi luong: " << dsKH[c].soThang << " thang\n";
    cout << "Tong hoc phi: " << FloatToStr(tongHocPhi) << " VND\n";

    cout << "\nDong hoc phi:\n";
    cout << "1. Dong day du (giam 5%)\n";
    cout << "2. Dong tung thang\n";
    cout << "Chon: "; int loai; cin >> loai;

    if (loai == 1) {
        tongHocPhi *= 0.95;  // Giảm 5%
        hv.daDong = tongHocPhi;
        hv.conNo = 0;
        cout << "\n>>> GIAM 5% khi dong day du!\n";
        cout << "Tong dong: " << FloatToStr(tongHocPhi) << " VND\n";
    } else {
        cout << "Dong truoc (thang): "; float dongTruoc; cin >> dongTruoc;
        hv.daDong = dongTruoc;
        hv.conNo = tongHocPhi - dongTruoc;
        cout << "Con no: " << FloatToStr(hv.conNo) << " VND\n";
    }

    dsKH[c].soHocVienHienTai++;

    cout << "\n[OK] Ma hoc vien: " << hv.maHV << "\n";

    HocVien* tmp = new HocVien[soHV + 1];
    for (int i = 0; i < soHV; i++) tmp[i] = dsHV[i];
    tmp[soHV] = hv;
    delete[] dsHV;
    dsHV = tmp;
    soHV++;
}

void DanhSachHocVien() {
    cout << "\n=== DANH SACH HOC VIEN ===\n";
    for (int i = 0; i < soHV; i++) {
        // Tìm tên khóa học
        string tenKH = "";
        for (int j = 0; j < soKH; j++) {
            if (dsKH[j].maKH == dsHV[i].maKH) {
                tenKH = dsKH[j].tenKH;
                break;
            }
        }

        cout << dsHV[i].maHV << " | " << dsHV[i].hoTen << " | "
             << tenKH << " | Da dong: " << FloatToStr(dsHV[i].daDong)
             << " VND | Con no: " << FloatToStr(dsHV[i].conNo) << " VND\n";
    }
}

// === MAIN ===
int main() {
    while (true) {
        cout << "\n===== TRUNG TAM NGOAI NGU =====\n";
        cout << "1. Danh sach khoa hoc\n";
        cout << "2. Dang ky hoc\n";
        cout << "3. Danh sach hoc vien\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int c; cin >> c;

        if (c == 1) DanhSachKhoaHoc();
        else if (c == 2) DangKyHoc();
        else if (c == 3) DanhSachHocVien();
        else if (c == 0) break;
    }

    delete[] dsHV;
    return 0;
}
