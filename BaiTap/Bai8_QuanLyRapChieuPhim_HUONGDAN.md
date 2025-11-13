# BÀI 8: HỆ THỐNG QUẢN LÝ RẠP CHIẾU PHIM

## 📋 TỔNG QUAN

Hệ thống quản lý rạp chiếu phim toàn diện bao gồm:
- **Quản lý phim**: Thông tin phim (tên, thể loại, thời lượng, đánh giá)
- **Quản lý phòng chiếu**: Cấu hình phòng và sơ đồ ghế ngồi
- **Lịch chiếu**: Lập lịch chiếu phim theo phòng, ngày, giờ
- **Đặt vé**: Chọn ghế, loại vé (Thường/VIP/Học sinh)
- **Bán combo**: Bắp nước, đồ ăn nhẹ
- **Thống kê doanh thu**: Báo cáo tổng hợp

---

## 🎯 CÁC KHÁI NIỆM QUAN TRỌNG

### 1. **Quản lý Ma trận Ghế Ngồi**

#### Cấu trúc dữ liệu
```cpp
struct PhongChieu {
    int soPhong;          // Số phòng (1, 2, 3...)
    int soHangGhe;        // Số hàng ghế (10 hàng: A-J)
    int soGheMoiHang;     // Số ghế mỗi hàng (12 ghế)
    string* trangThaiGhe; // Mảng trạng thái ghế
};
```

#### Mảng 1 chiều mô phỏng ma trận 2 chiều
- **Tổng số ghế** = `soHangGhe × soGheMoiHang`
- **Công thức chuyển đổi**:
  - Từ (hàng, ghế) → index: `index = hàng × soGheMoiHang + ghế`
  - Từ index → (hàng, ghế): `hàng = index / soGheMoiHang`, `ghế = index % soGheMoiHang`

**Ví dụ**: Phòng 10 hàng × 12 ghế = 120 ghế
- Ghế A5 (hàng 0, ghế 4): index = 0 × 12 + 4 = **4**
- Ghế C8 (hàng 2, ghế 7): index = 2 × 12 + 7 = **31**
- Index 50: hàng = 50/12 = 4 (E), ghế = 50%12 = 2 → **E3**

#### Code chuyển đổi vị trí ghế

```cpp
// Chuyển từ ký hiệu (A5, B10) sang số index
int ChuyenHangGheThanhSo(const string& viTri, int soGheMoiHang) {
    if (viTri.length() < 2) return -1;

    char hang = viTri[0];
    if (hang < 'A' || hang > 'Z') return -1;

    int hangNum = hang - 'A';              // A=0, B=1, C=2...
    int gheNum = StrToInt(viTri.substr(1)) - 1;  // "5" -> 4 (index)

    return hangNum * soGheMoiHang + gheNum;
}

// Chuyển từ số index sang ký hiệu (A5, B10)
string ChuyenSoThanhHangGhe(int soGhe, int soGheMoiHang) {
    int hang = soGhe / soGheMoiHang;      // Hàng
    int ghe = soGhe % soGheMoiHang + 1;   // Ghế (1-based)

    char hangChar = 'A' + hang;           // 0->A, 1->B...
    return string(1, hangChar) + IntToStr(ghe);
}
```

**Ứng dụng**:
- ✅ Kiểm tra ghế có trống không
- ✅ Đặt/hủy ghế
- ✅ Hiển thị sơ đồ ghế
- ✅ Tính tỷ lệ lấp đầy

---

### 2. **Hiển thị Sơ đồ Ghế Động**

#### Thuật toán
```cpp
void HienThiSoDoGhe(int soPhong, const string& maLich) {
    // 1. Tìm phòng chiếu
    PhongChieu* phong = NULL;
    for (int i = 0; i < soLuongPhong; i++) {
        if (dsPhongChieu[i].soPhong == soPhong) {
            phong = &dsPhongChieu[i];
            break;
        }
    }

    // 2. Hiển thị màn hình
    cout << "                MAN HINH\n";
    cout << "=====================================\n\n";

    // 3. Vẽ sơ đồ ghế
    for (int hang = 0; hang < phong->soHangGhe; hang++) {
        cout << char('A' + hang) << "  ";  // Tên hàng

        for (int ghe = 0; ghe < phong->soGheMoiHang; ghe++) {
            int index = hang * phong->soGheMoiHang + ghe;

            if (phong->trangThaiGhe[index] == "Trong") {
                cout << "[_] ";  // Ghế trống
            } else {
                cout << "[X] ";  // Ghế đã đặt
            }
        }
        cout << "\n";
    }

    // 4. Hiển thị số ghế
    cout << "\n   ";
    for (int i = 1; i <= phong->soGheMoiHang; i++) {
        if (i < 10) cout << " " << i << "  ";
        else cout << i << "  ";
    }

    // 5. Chú thích
    cout << "\n\n[_] = Trong    [X] = Da dat\n";
}
```

**Output mẫu**:
```
                MAN HINH
=====================================

A  [_] [_] [X] [_] [_] [_] [_] [_] [_] [_] [_] [_]
B  [_] [_] [_] [_] [X] [X] [_] [_] [_] [_] [_] [_]
C  [X] [X] [X] [X] [X] [X] [X] [X] [_] [_] [_] [_]
...

    1   2   3   4   5   6   7   8   9  10  11  12

[_] = Trong    [X] = Da dat
```

**Ứng dụng**:
- 🎬 Rạp chiếu phim
- ✈️ Đặt chỗ máy bay
- 🚌 Đặt ghế xe bus
- 🏟️ Đặt vé sân vận động

---

### 3. **Hệ thống Giá vé Phân tầng**

#### Cấu trúc giá
```cpp
struct Ve {
    string maVe;       // DH001_V1, DH001_V2...
    string maLich;     // Mã lịch chiếu
    string viTriGhe;   // A5, B10...
    string loaiVe;     // "Thuong", "VIP", "HocSinh"
    float giaVe;       // Giá theo loại vé
};
```

#### Bảng giá
| Loại vé | Giá (VND) | Đối tượng | Vị trí |
|---------|-----------|-----------|---------|
| **Thường** | 70,000 | Người lớn | Hàng D-J |
| **VIP** | 120,000 | Premium | Hàng A-C (gần màn hình) |
| **Học sinh** | 50,000 | Sinh viên/HS | Tất cả |

#### Code xử lý giá vé
```cpp
cout << "Chon loai ve:\n";
cout << "  1. Ve thuong (70000 VND)\n";
cout << "  2. Ve VIP (120000 VND)\n";
cout << "  3. Ve hoc sinh (50000 VND)\n";

int loaiVe = StrToInt(input);

if (loaiVe == 1) {
    veMoi.loaiVe = "Thuong";
    veMoi.giaVe = 70000;
} else if (loaiVe == 2) {
    veMoi.loaiVe = "VIP";
    veMoi.giaVe = 120000;
} else if (loaiVe == 3) {
    veMoi.loaiVe = "HocSinh";
    veMoi.giaVe = 50000;
}
```

**Mở rộng**: Giá vé có thể thay đổi theo:
- ⏰ Khung giờ (sáng, chiều, tối, đêm)
- 📅 Ngày trong tuần (cuối tuần đắt hơn)
- 🎬 Phim mới/phim cũ
- 🪑 Vị trí ghế (hàng giữa đắt hơn)

---

### 4. **Quản lý Đơn hàng Kết hợp**

#### Cấu trúc đơn hàng
```cpp
struct DonHang {
    string maDon;              // DH001, DH002...
    string ngayDat;            // "15/01/2025"
    string gioData;            // "10:30"
    string hoTenKhach;         // Tên khách
    string sdt;                // Số điện thoại
    int soVe;                  // Số lượng vé
    Ve* danhSachVe;            // Mảng động chứa vé
    int soCombo;               // Số lượng combo
    Combo* danhSachCombo;      // Mảng động chứa combo
    float tongTien;            // Tổng tiền thanh toán
};
```

#### Quy trình đặt vé

```
┌─────────────────────────────────────────────────┐
│ 1. CHỌN LỊCH CHIẾU                              │
│    - Hiển thị danh sách lịch chiếu             │
│    - Khách chọn mã lịch (LC001, LC002...)      │
└─────────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────────┐
│ 2. XEM SƠ ĐỒ GHẾ                               │
│    - Hiển thị ghế trống/đã đặt                 │
│    - [_] = trống, [X] = đã đặt                 │
└─────────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────────┐
│ 3. NHẬP THÔNG TIN KHÁCH HÀNG                    │
│    - Họ tên                                     │
│    - Số điện thoại                              │
│    - Số lượng vé                                │
└─────────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────────┐
│ 4. CHỌN GHẾ VÀ LOẠI VÉ (lặp theo số vé)        │
│    For i = 1 to soVe:                           │
│      - Nhập vị trí ghế (VD: A5, B10)           │
│      - Kiểm tra ghế có trống không             │
│      - Chọn loại vé (Thường/VIP/Học sinh)      │
│      - Cập nhật trạng thái ghế = "DaDat"       │
│      - Tính tiền vé                             │
└─────────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────────┐
│ 5. CHỌN COMBO ĐỒ ĂN (tùy chọn)                 │
│    - Hiển thị danh sách combo                   │
│    - Khách chọn combo (có thể nhiều)           │
│    - Tính tiền combo                            │
└─────────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────────┐
│ 6. TÍNH TỔNG TIỀN & IN HÓA ĐƠN                 │
│    tongTien = tongTienVe + tongTienCombo        │
│    - In hóa đơn chi tiết                        │
│    - Lưu đơn hàng vào hệ thống                 │
└─────────────────────────────────────────────────┘
```

#### Code đặt vé (phần chính)

```cpp
void DatVe() {
    // 1. Chọn lịch chiếu
    HienThiLichChieu();
    cout << "\nNhap ma lich chieu: ";
    string maLich;
    cin >> maLich;

    // Tìm lịch chiếu
    LichChieu* lich = NULL;
    for (int i = 0; i < soLuongLich; i++) {
        if (dsLichChieu[i].maLich == maLich) {
            lich = &dsLichChieu[i];
            break;
        }
    }

    if (lich == NULL) {
        cout << "[LOI] Khong tim thay lich chieu!\n";
        return;
    }

    // 2. Hiển thị sơ đồ ghế
    HienThiSoDoGhe(lich->soPhong, maLich);

    // 3. Tạo đơn hàng mới
    DonHang donMoi;
    donMoi.maDon = TaoMaDonMoi();
    donMoi.ngayDat = lich->ngayChieu;
    donMoi.gioData = lich->gioChieu;

    // 4. Nhập thông tin khách
    cout << "\nNhap ho ten khach hang: ";
    cin.ignore();
    getline(cin, donMoi.hoTenKhach);

    cout << "Nhap so dien thoai: ";
    getline(cin, donMoi.sdt);

    cout << "Nhap so luong ve: ";
    string input;
    getline(cin, input);
    donMoi.soVe = StrToInt(input);

    // 5. Cấp phát mảng động cho vé
    donMoi.danhSachVe = new Ve[donMoi.soVe];

    float tongTienVe = 0;

    // 6. Đặt từng vé
    for (int i = 0; i < donMoi.soVe; i++) {
        cout << "\n--- Ve " << (i + 1) << " ---\n";

        Ve veMoi;
        veMoi.maVe = donMoi.maDon + "_V" + IntToStr(i + 1);
        veMoi.maLich = maLich;

        // Nhập vị trí ghế
        cout << "Nhap vi tri ghe (VD: A5, B10): ";
        getline(cin, veMoi.viTriGhe);

        // Chuyển sang index
        int indexGhe = ChuyenHangGheThanhSo(veMoi.viTriGhe, phong->soGheMoiHang);

        // Kiểm tra hợp lệ
        if (indexGhe < 0 || indexGhe >= phong->soHangGhe * phong->soGheMoiHang) {
            cout << "[LOI] Vi tri ghe khong hop le!\n";
            i--;
            continue;
        }

        // Kiểm tra đã đặt chưa
        if (phong->trangThaiGhe[indexGhe] == "DaDat") {
            cout << "[LOI] Ghe da duoc dat!\n";
            i--;
            continue;
        }

        // Chọn loại vé
        cout << "Chon loai ve:\n";
        cout << "  1. Ve thuong (70000 VND)\n";
        cout << "  2. Ve VIP (120000 VND)\n";
        cout << "  3. Ve hoc sinh (50000 VND)\n";
        cout << "Lua chon: ";
        getline(cin, input);
        int loaiVe = StrToInt(input);

        if (loaiVe == 1) {
            veMoi.loaiVe = "Thuong";
            veMoi.giaVe = 70000;
        } else if (loaiVe == 2) {
            veMoi.loaiVe = "VIP";
            veMoi.giaVe = 120000;
        } else if (loaiVe == 3) {
            veMoi.loaiVe = "HocSinh";
            veMoi.giaVe = 50000;
        }

        // Cập nhật trạng thái ghế
        phong->trangThaiGhe[indexGhe] = "DaDat";

        // Lưu vé
        donMoi.danhSachVe[i] = veMoi;
        tongTienVe += veMoi.giaVe;

        cout << "[OK] Dat ghe " << veMoi.viTriGhe << " thanh cong!\n";
    }

    // 7. Chọn combo đồ ăn
    cout << "\n========== BAN COMBO ==========\n";
    cout << "Danh sach combo:\n";
    for (int i = 0; i < soLuongCombo; i++) {
        cout << "  " << (i + 1) << ". " << dsCombo[i].tenCombo
             << " - " << FloatToStr(dsCombo[i].giaCombo, 0) << " VND\n";
    }

    cout << "\nNhap so luong combo (0 neu khong): ";
    getline(cin, input);
    donMoi.soCombo = StrToInt(input);

    float tongTienCombo = 0;

    if (donMoi.soCombo > 0) {
        donMoi.danhSachCombo = new Combo[donMoi.soCombo];

        for (int i = 0; i < donMoi.soCombo; i++) {
            cout << "Chon combo thu " << (i + 1) << " (1-" << soLuongCombo << "): ";
            getline(cin, input);
            int chon = StrToInt(input) - 1;

            donMoi.danhSachCombo[i] = dsCombo[chon];
            tongTienCombo += dsCombo[chon].giaCombo;
        }
    } else {
        donMoi.danhSachCombo = NULL;
    }

    // 8. Tính tổng tiền
    donMoi.tongTien = tongTienVe + tongTienCombo;

    // 9. In hóa đơn
    cout << "\n========== HOA DON ==========\n";
    cout << "Ma don: " << donMoi.maDon << "\n";
    cout << "Khach hang: " << donMoi.hoTenKhach << "\n";
    cout << "SDT: " << donMoi.sdt << "\n";
    cout << "----------------------------\n";
    cout << "Tong tien ve: " << FloatToStr(tongTienVe, 0) << " VND\n";
    cout << "Tong tien combo: " << FloatToStr(tongTienCombo, 0) << " VND\n";
    cout << "----------------------------\n";
    cout << "TONG CONG: " << FloatToStr(donMoi.tongTien, 0) << " VND\n";
    cout << "============================\n";

    // 10. Lưu đơn hàng
    DonHang* temp = new DonHang[soLuongDon + 1];
    for (int i = 0; i < soLuongDon; i++) {
        temp[i] = dsDonHang[i];
    }
    temp[soLuongDon] = donMoi;

    delete[] dsDonHang;
    dsDonHang = temp;
    soLuongDon++;

    cout << "\n[THANH CONG] Dat ve thanh cong!\n";
}
```

---

### 5. **Quản lý Bộ nhớ Động cho Mảng lồng nhau**

#### Vấn đề
```cpp
struct DonHang {
    Ve* danhSachVe;           // Con trỏ động 1
    Combo* danhSachCombo;     // Con trỏ động 2
};

DonHang* dsDonHang = NULL;    // Mảng động chứa DonHang
```

Có **3 cấp độ cấp phát**:
1. Mảng `dsDonHang`
2. Mảng `danhSachVe` trong mỗi `DonHang`
3. Mảng `danhSachCombo` trong mỗi `DonHang`

#### Cấp phát bộ nhớ

```cpp
// Cấp phát cho 1 đơn hàng mới
DonHang donMoi;

// Cấp phát cho vé
donMoi.soVe = 3;
donMoi.danhSachVe = new Ve[donMoi.soVe];

// Cấp phát cho combo (có thể NULL nếu không mua)
if (donMoi.soCombo > 0) {
    donMoi.danhSachCombo = new Combo[donMoi.soCombo];
} else {
    donMoi.danhSachCombo = NULL;
}

// Thêm vào mảng dsDonHang
DonHang* temp = new DonHang[soLuongDon + 1];
for (int i = 0; i < soLuongDon; i++) {
    temp[i] = dsDonHang[i];  // Copy dữ liệu (bao gồm con trỏ)
}
temp[soLuongDon] = donMoi;

delete[] dsDonHang;  // Xóa mảng cũ (chỉ xóa mảng, không xóa dữ liệu con trỏ)
dsDonHang = temp;
soLuongDon++;
```

#### Giải phóng bộ nhớ (QUAN TRỌNG!)

```cpp
// Giải phóng theo thứ tự ngược lại
for (int i = 0; i < soLuongDon; i++) {
    // 1. Giải phóng mảng vé
    delete[] dsDonHang[i].danhSachVe;

    // 2. Giải phóng mảng combo (nếu có)
    if (dsDonHang[i].danhSachCombo != NULL) {
        delete[] dsDonHang[i].danhSachCombo;
    }
}

// 3. Giải phóng mảng đơn hàng
delete[] dsDonHang;
```

**Nguyên tắc**: Giải phóng từ trong ra ngoài (cấp thấp → cấp cao)

**Lỗi thường gặp**:
- ❌ Giải phóng `dsDonHang` trước → **Memory leak** (không giải phóng được `danhSachVe`, `danhSachCombo`)
- ❌ Quên kiểm tra `NULL` → **Segmentation fault**
- ❌ Giải phóng 2 lần → **Double free**

---

### 6. **Tự động Sinh Mã ID Phân cấp**

#### Các loại mã trong hệ thống

| Loại | Format | Ví dụ | Quy tắc |
|------|--------|-------|---------|
| Mã phim | P + 3 số | P001, P002, P010 | Bắt đầu từ P001 |
| Mã lịch chiếu | LC + 3 số | LC001, LC025 | LC = Lịch Chiếu |
| Mã đơn hàng | DH + 3 số | DH001, DH150 | DH = Đơn Hàng |
| Mã vé | {MaDon}_V{STT} | DH001_V1, DH001_V2 | Gắn với đơn hàng |

#### Thuật toán sinh mã tự động

```cpp
string TaoMaDonMoi() {
    // 1. Tìm số lớn nhất hiện có
    int maxNum = 0;
    for (int i = 0; i < soLuongDon; i++) {
        // DH001 -> lấy "001" -> chuyển thành 1
        if (dsDonHang[i].maDon.length() >= 4 &&
            dsDonHang[i].maDon[0] == 'D') {

            string numStr = dsDonHang[i].maDon.substr(2); // "001"
            int num = StrToInt(numStr);                   // 1

            if (num > maxNum) maxNum = num;
        }
    }

    // 2. Tạo mã mới = maxNum + 1
    string ma = "DH";
    int newNum = maxNum + 1;

    // 3. Thêm số 0 đứng trước để đủ 3 chữ số
    if (newNum < 10) ma += "00";        // DH001, DH002...
    else if (newNum < 100) ma += "0";   // DH010, DH099
    // newNum >= 100: không thêm số 0   // DH100, DH999

    ma += IntToStr(newNum);

    return ma;  // DH001, DH002, DH003...
}
```

**Ví dụ cụ thể**:
```
Hiện có: DH001, DH002, DH005, DH010
maxNum = 10
newNum = 10 + 1 = 11
ma = "DH" + "0" + "11" = "DH011"
```

#### Tạo mã vé gắn với đơn hàng

```cpp
// Mỗi vé có mã riêng, gắn với mã đơn hàng
for (int i = 0; i < donMoi.soVe; i++) {
    Ve veMoi;
    // DH001_V1, DH001_V2, DH001_V3...
    veMoi.maVe = donMoi.maDon + "_V" + IntToStr(i + 1);

    donMoi.danhSachVe[i] = veMoi;
}
```

**Lợi ích**:
- ✅ Dễ truy vết: Biết vé thuộc đơn hàng nào
- ✅ Tránh trùng mã: Mỗi vé có mã duy nhất
- ✅ Dễ tìm kiếm: Tìm tất cả vé của đơn hàng

---

### 7. **Validation Ghế ngồi**

#### Các trường hợp cần kiểm tra

```cpp
// 1. Định dạng vị trí (A5, B10, C1...)
bool KiemTraDinhDangGhe(const string& viTri) {
    if (viTri.length() < 2) return false;        // Quá ngắn

    char hang = viTri[0];
    if (hang < 'A' || hang > 'Z') return false;  // Không phải chữ cái

    string soGhe = viTri.substr(1);
    for (int i = 0; i < soGhe.length(); i++) {
        if (soGhe[i] < '0' || soGhe[i] > '9') {
            return false;  // Phần số không hợp lệ
        }
    }

    return true;
}

// 2. Nằm trong giới hạn phòng
bool KiemTraGioiHan(const string& viTri, PhongChieu* phong) {
    int index = ChuyenHangGheThanhSo(viTri, phong->soGheMoiHang);

    if (index < 0) return false;  // Chuyển đổi thất bại

    int tongGhe = phong->soHangGhe * phong->soGheMoiHang;
    if (index >= tongGhe) return false;  // Vượt quá số ghế

    return true;
}

// 3. Ghế chưa được đặt
bool KiemTraGheTrong(const string& viTri, PhongChieu* phong) {
    int index = ChuyenHangGheThanhSo(viTri, phong->soGheMoiHang);

    return phong->trangThaiGhe[index] == "Trong";
}
```

#### Quy trình validation đầy đủ

```cpp
cout << "Nhap vi tri ghe (VD: A5, B10): ";
getline(cin, veMoi.viTriGhe);

// Bước 1: Kiểm tra định dạng
if (!KiemTraDinhDangGhe(veMoi.viTriGhe)) {
    cout << "[LOI] Dinh dang ghe khong hop le! (VD: A5, B10)\n";
    i--;
    continue;
}

// Bước 2: Chuyển sang index
int indexGhe = ChuyenHangGheThanhSo(veMoi.viTriGhe, phong->soGheMoiHang);

// Bước 3: Kiểm tra giới hạn
if (indexGhe < 0 || indexGhe >= phong->soHangGhe * phong->soGheMoiHang) {
    cout << "[LOI] Vi tri ghe khong ton tai!\n";
    cout << "Phong co " << phong->soHangGhe << " hang (A-"
         << char('A' + phong->soHangGhe - 1) << "), "
         << phong->soGheMoiHang << " ghe/hang\n";
    i--;
    continue;
}

// Bước 4: Kiểm tra đã đặt
if (phong->trangThaiGhe[indexGhe] == "DaDat") {
    cout << "[LOI] Ghe " << veMoi.viTriGhe << " da duoc dat!\n";
    i--;
    continue;
}

// Bước 5: Đặt ghế
phong->trangThaiGhe[indexGhe] = "DaDat";
cout << "[OK] Dat ghe " << veMoi.viTriGhe << " thanh cong!\n";
```

**Thông báo lỗi chi tiết giúp người dùng**:
- ❌ "Dinh dang ghe khong hop le!" → Cho biết format đúng
- ❌ "Vi tri ghe khong ton tai!" → Cho biết giới hạn phòng
- ❌ "Ghe da duoc dat!" → Yêu cầu chọn ghế khác

---

### 8. **Thống kê Doanh thu**

#### Các chỉ số quan trọng

```cpp
void ThongKeDoanhThu() {
    cout << "\n========== THONG KE DOANH THU ==========\n";

    if (soLuongDon == 0) {
        cout << "Chua co don hang nao!\n";
        return;
    }

    // 1. Tính tổng doanh thu và tổng vé
    float tongDoanhThu = 0;
    int tongVe = 0;

    for (int i = 0; i < soLuongDon; i++) {
        tongDoanhThu += dsDonHang[i].tongTien;
        tongVe += dsDonHang[i].soVe;
    }

    // 2. Hiển thị thống kê
    cout << "Tong so don hang: " << soLuongDon << "\n";
    cout << "Tong so ve ban: " << tongVe << "\n";
    cout << "Tong doanh thu: " << FloatToStr(tongDoanhThu, 0) << " VND\n";
    cout << "Doanh thu trung binh/don: "
         << FloatToStr(tongDoanhThu / soLuongDon, 0) << " VND\n";
}
```

#### Thống kê nâng cao (có thể mở rộng)

```cpp
// Thống kê theo phim
void ThongKeTheoPhim() {
    for (int i = 0; i < soLuongPhim; i++) {
        int soVe = 0;
        float doanhThu = 0;

        // Đếm vé của phim này
        for (int j = 0; j < soLuongDon; j++) {
            for (int k = 0; k < dsDonHang[j].soVe; k++) {
                string maLich = dsDonHang[j].danhSachVe[k].maLich;

                // Tìm mã phim từ mã lịch
                for (int l = 0; l < soLuongLich; l++) {
                    if (dsLichChieu[l].maLich == maLich &&
                        dsLichChieu[l].maPhim == dsPhim[i].maPhim) {

                        soVe++;
                        doanhThu += dsDonHang[j].danhSachVe[k].giaVe;
                        break;
                    }
                }
            }
        }

        cout << dsPhim[i].tenPhim << ": " << soVe << " ve, "
             << FloatToStr(doanhThu, 0) << " VND\n";
    }
}

// Thống kê theo phòng
void ThongKeTheoPhong() {
    for (int i = 0; i < soLuongPhong; i++) {
        int soLanChieu = 0;
        float doanhThu = 0;

        // Đếm lịch chiếu của phòng này
        for (int j = 0; j < soLuongLich; j++) {
            if (dsLichChieu[j].soPhong == dsPhongChieu[i].soPhong) {
                soLanChieu++;

                // Tính doanh thu lịch chiếu này
                for (int k = 0; k < soLuongDon; k++) {
                    for (int l = 0; l < dsDonHang[k].soVe; l++) {
                        if (dsDonHang[k].danhSachVe[l].maLich ==
                            dsLichChieu[j].maLich) {
                            doanhThu += dsDonHang[k].danhSachVe[l].giaVe;
                        }
                    }
                }
            }
        }

        cout << "Phong " << dsPhongChieu[i].soPhong << ": "
             << soLanChieu << " suat, "
             << FloatToStr(doanhThu, 0) << " VND\n";
    }
}

// Tỷ lệ lấp đầy (Occupancy Rate)
float TinhTyLeLapDay(const string& maLich) {
    // Tìm lịch chiếu
    int soPhong = 0;
    for (int i = 0; i < soLuongLich; i++) {
        if (dsLichChieu[i].maLich == maLich) {
            soPhong = dsLichChieu[i].soPhong;
            break;
        }
    }

    // Tìm phòng chiếu
    PhongChieu* phong = NULL;
    for (int i = 0; i < soLuongPhong; i++) {
        if (dsPhongChieu[i].soPhong == soPhong) {
            phong = &dsPhongChieu[i];
            break;
        }
    }

    if (phong == NULL) return 0.0;

    // Đếm ghế đã đặt
    int tongGhe = phong->soHangGhe * phong->soGheMoiHang;
    int gheDaDat = 0;

    for (int i = 0; i < tongGhe; i++) {
        if (phong->trangThaiGhe[i] == "DaDat") {
            gheDaDat++;
        }
    }

    return (float)gheDaDat / tongGhe * 100;  // Phần trăm
}
```

---

## 🔧 CÁC KỸ THUẬT LẬP TRÌNH

### 1. **Parse CSV với dấu phẩy trong dữ liệu**

```cpp
void ParseCSV(const string& line, string fields[], int& count) {
    count = 0;
    string currentField = "";
    bool inQuotes = false;  // Đang trong dấu nháy kép

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '"') {
            inQuotes = !inQuotes;  // Toggle trạng thái
        } else if (line[i] == ',' && !inQuotes) {
            // Dấu phẩy ngoài dấu nháy -> phân tách field
            fields[count++] = Trim(currentField);
            currentField = "";
        } else {
            currentField += line[i];
        }
    }

    // Field cuối cùng
    if (currentField.length() > 0) {
        fields[count++] = Trim(currentField);
    }
}
```

**Ví dụ**:
```
"Avengers: Endgame",Hanh dong,181,8.5
"The Dark Knight, Part II",Hanh dong,152,9.0
```

Field 1: `Avengers: Endgame` (bỏ dấu nháy)
Field 2: `The Dark Knight, Part II` (giữ dấu phẩy vì trong nháy kép)

---

### 2. **Copy Deep vs Shallow**

#### Shallow Copy (Copy nông)
```cpp
DonHang don1;
don1.danhSachVe = new Ve[3];
// ... điền dữ liệu

DonHang don2 = don1;  // Shallow copy

// Vấn đề: don2.danhSachVe = don1.danhSachVe (cùng địa chỉ)
// Xóa don1 -> don2 bị lỗi (dangling pointer)
```

#### Deep Copy (Copy sâu)
```cpp
DonHang CopyDonHang(const DonHang& nguon) {
    DonHang moi;

    // Copy dữ liệu thông thường
    moi.maDon = nguon.maDon;
    moi.ngayDat = nguon.ngayDat;
    moi.hoTenKhach = nguon.hoTenKhach;
    moi.soVe = nguon.soVe;

    // Cấp phát mảng mới và copy dữ liệu
    if (nguon.soVe > 0) {
        moi.danhSachVe = new Ve[nguon.soVe];
        for (int i = 0; i < nguon.soVe; i++) {
            moi.danhSachVe[i] = nguon.danhSachVe[i];
        }
    }

    if (nguon.soCombo > 0) {
        moi.danhSachCombo = new Combo[nguon.soCombo];
        for (int i = 0; i < nguon.soCombo; i++) {
            moi.danhSachCombo[i] = nguon.danhSachCombo[i];
        }
    } else {
        moi.danhSachCombo = NULL;
    }

    return moi;
}
```

**Khi nào cần Deep Copy**:
- ✅ Struct/Class có con trỏ động
- ✅ Khi thêm vào mảng động
- ✅ Khi cần clone object hoàn toàn độc lập

---

### 3. **Kiểm tra Con trỏ NULL trước khi sử dụng**

```cpp
// ❌ SAI: Không kiểm tra NULL
for (int i = 0; i < soLuongDon; i++) {
    delete[] dsDonHang[i].danhSachCombo;  // Crash nếu NULL!
}

// ✅ ĐÚNG: Kiểm tra trước
for (int i = 0; i < soLuongDon; i++) {
    if (dsDonHang[i].danhSachVe != NULL) {
        delete[] dsDonHang[i].danhSachVe;
    }

    if (dsDonHang[i].danhSachCombo != NULL) {
        delete[] dsDonHang[i].danhSachCombo;
    }
}
```

**Nguyên tắc**:
- Luôn khởi tạo con trỏ = `NULL` nếu chưa cấp phát
- Kiểm tra `!= NULL` trước khi dereference
- Set = `NULL` sau khi `delete`

---

## 📊 DỮ LIỆU MẪU

### File: DanhSachPhim.txt
```
MaPhim,TenPhim,TheLoai,ThoiLuong,DanhGia
P001,Avengers: Endgame,Hanh dong,181,8.5
P002,Doraemon: Nobita va Mat Trang,Hoat hinh,111,7.8
P003,Mat Biec,Tinh cam,117,7.2
P004,Parasite,Tam ly,132,8.9
P005,The Batman,Hanh dong,176,8.3
```

### File: DanhSachPhongChieu.txt
```
SoPhong,SoHangGhe,SoGheMoiHang
1,10,12
2,8,10
3,12,15
```

Phòng 1: 10 hàng × 12 ghế = **120 ghế**
Phòng 2: 8 hàng × 10 ghế = **80 ghế**
Phòng 3: 12 hàng × 15 ghế = **180 ghế**

### File: LichChieu.txt
```
MaLich,MaPhim,SoPhong,NgayChieu,GioChieu
LC001,P001,1,15/01/2025,14:30
LC002,P001,1,15/01/2025,19:00
LC003,P002,2,15/01/2025,10:00
LC004,P003,3,16/01/2025,20:30
```

### File: DanhSachCombo.txt
```
MaCombo,TenCombo,GiaCombo
CB001,Bap Nuoc,50000
CB002,Bap Nuoc Lon,70000
CB003,Combo Doi,120000
CB004,Combo Gia Dinh,200000
```

---

## 🎓 ỨNG DỤNG THỰC TẾ

### 1. **Hệ thống đặt vé máy bay**
```cpp
struct ChuyenBay {
    string maChuyenBay;   // VN123
    string hangBay;       // Vietnam Airlines
    string tuyen;         // HAN-SGN
    string ngayBay;       // 15/01/2025
    string gioBay;        // 14:30
};

struct GheMayBay {
    string hang;          // "A", "B", "C"...
    string loaiGhe;       // "PhoThong", "ThuongGia"
    bool coSanCuaSo;      // true/false
    float giaGhe;         // 1500000
};

// Tương tự code rạp chiếu phim
// - Sơ đồ ghế A-Z, 1-6
// - Loại ghế: Phổ thông, Thương gia, Hạng nhất
// - Thêm: Hành lý, Suất ăn
```

### 2. **Hệ thống đặt chỗ nhà hàng**
```cpp
struct BanAn {
    int soBan;            // 1, 2, 3...
    int soGhe;            // 2, 4, 6, 8
    string viTri;         // "Trong nha", "Ngoai troi"
    string trangThai;     // "Trong", "DaDat", "DangSuDung"
};

struct DatBan {
    string maDat;         // DB001
    int soBan;            // 5
    string ngayDat;       // 15/01/2025
    string gioDat;        // 19:00
    string tenKhach;      // "Nguyen Van A"
    int soNguoi;          // 4
};

// Tương tự quản lý ghế rạp
// - Sơ đồ bàn ăn (ma trận)
// - Trạng thái bàn (Trống/Đã đặt/Đang sử dụng)
// - Đặt trước + Walk-in
```

### 3. **Hệ thống quản lý khách sạn - nâng cấp từ Bài 6**
```cpp
// Bài 6: Đặt phòng đơn giản
// Bài 8: Thêm chọn giường (Đơn/Đôi/Twin)

struct Phong {
    int soPhong;          // 101, 102...
    string loaiPhong;     // Standard, Deluxe, Suite
    string loaiGiuong;    // "Don", "Doi", "Twin"
    int soGiuong;         // 1, 2
    float giaPhong;       // 500000
};

// Cho phép khách chọn:
// - Loại phòng
// - Loại giường
// - Tầng
```

### 4. **Hệ thống đăng ký sự kiện/hội thảo**
```cpp
struct SuKien {
    string maSK;          // SK001
    string tenSK;         // "Hoi thao AI"
    string ngay;          // 20/01/2025
    string gio;           // 09:00
    int soChoToiDa;       // 200
    int soChoDaDat;       // 0
};

struct DangKySK {
    string maDK;          // DK001
    string maSK;          // SK001
    string hoTen;         // "Nguyen Van A"
    string email;         // "a@example.com"
    string loaiVe;        // "Standard", "VIP"
    float giaVe;          // 500000
};

// Tương tự đặt vé xem phim
// - Số chỗ giới hạn
// - Loại vé khác nhau
// - Check-in khi đến
```

---

## 💡 BÀI TẬP MỞ RỘNG

### Cấp độ 1: Cơ bản
1. **Tìm kiếm phim**
   - Tìm theo tên (substring)
   - Tìm theo thể loại
   - Tìm theo đánh giá (>= 8.0)

2. **Hiển thị lịch chiếu theo ngày**
   - Input: Ngày (dd/mm/yyyy)
   - Output: Tất cả lịch chiếu trong ngày

3. **Hủy vé**
   - Input: Mã đơn hàng
   - Cập nhật trạng thái ghế = "Trong"
   - Xóa đơn hàng

### Cấp độ 2: Trung bình
4. **Giá vé theo khung giờ**
   ```cpp
   float TinhGiaTheoGio(const string& gioChieu, const string& loaiVe) {
       int gio = StrToInt(gioChieu.substr(0, 2));

       float giaGoc = 70000;  // Giá thường
       if (loaiVe == "VIP") giaGoc = 120000;
       else if (loaiVe == "HocSinh") giaGoc = 50000;

       // Khung giờ vàng (18h-22h): +30%
       if (gio >= 18 && gio < 22) {
           return giaGoc * 1.3;
       }

       // Khung giờ sáng (6h-12h): -20%
       if (gio >= 6 && gio < 12) {
           return giaGoc * 0.8;
       }

       return giaGoc;
   }
   ```

5. **Giá vé theo ngày trong tuần**
   ```cpp
   float TinhGiaTheoNgay(const string& ngay, float giaCoBan) {
       // Tính thứ trong tuần (algorithm phức tạp)
       // Giả sử có hàm LayThuTrongTuan(ngay) -> 0-6

       int thu = LayThuTrongTuan(ngay);

       // Thứ 7, Chủ nhật: +50%
       if (thu == 6 || thu == 0) {
           return giaCoBan * 1.5;
       }

       return giaCoBan;
   }
   ```

6. **Ghế ngồi ưu tiên (Best Seats)**
   - Hàng giữa (C-F): giá +20%
   - Cột giữa (5-8): giá +10%
   - Ghế góc (A1, A12, J1, J12): giá -10%

### Cấp độ 3: Nâng cao
7. **Đặt nhiều lịch chiếu trong 1 đơn**
   ```cpp
   struct DonHang {
       // ... các field cũ
       int soLichChieu;             // 2 (xem 2 phim)
       LichChieuVaDanhSachVe* dsLichVaVe;
   };

   struct LichChieuVaDanhSachVe {
       string maLich;      // LC001
       int soVe;           // 3
       Ve* danhSachVe;     // 3 vé
   };
   ```

8. **Membership & Loyalty Points**
   ```cpp
   struct KhachHang {
       string maKH;        // KH001
       string hoTen;       // "Nguyen Van A"
       string loaiTV;      // "Bac", "Vang", "Kim Cuong"
       int diemTichLuy;    // 1250 điểm
   };

   float TinhGiaSauGiamGia(float giaGoc, const KhachHang& kh) {
       if (kh.loaiTV == "Bac") return giaGoc * 0.95;      // -5%
       if (kh.loaiTV == "Vang") return giaGoc * 0.90;     // -10%
       if (kh.loaiTV == "KimCuong") return giaGoc * 0.85; // -15%
       return giaGoc;
   }

   void CongDiem(KhachHang& kh, float soTienThanhToan) {
       // 1000 VND = 1 điểm
       kh.diemTichLuy += (int)(soTienThanhToan / 1000);
   }
   ```

9. **Tối ưu hóa sắp xếp lịch chiếu**
   - Tránh xung đột phòng chiếu
   - Tính thời gian dọn phòng (30 phút)
   - Đề xuất lịch chiếu tối ưu

10. **Báo cáo doanh thu nâng cao**
    - Doanh thu theo tháng/quý/năm
    - Top 5 phim bán chạy
    - Phòng chiếu hiệu quả nhất
    - Khung giờ đông khách nhất
    - Biểu đồ ASCII

---

## 🚀 TỐI ƯU HÓA VÀ CẢI TIẾN

### 1. **Tối ưu tìm kiếm**
```cpp
// ❌ Tìm tuyến tính: O(n)
for (int i = 0; i < soLuongPhim; i++) {
    if (dsPhim[i].maPhim == ma) return &dsPhim[i];
}

// ✅ Sử dụng map/hash table (nếu được phép): O(1)
// hoặc sắp xếp + binary search: O(log n)
```

### 2. **Cache sơ đồ ghế**
```cpp
// Thay vì reset trạng thái ghế mỗi lịch chiếu
// → Lưu trạng thái riêng cho mỗi lịch chiếu

struct LichChieu {
    // ... các field cũ
    string* trangThaiGhe;  // Trạng thái riêng cho lịch này
};
```

### 3. **Lazy Loading**
```cpp
// Chỉ load dữ liệu khi cần
void DocDonHangTheoNgay(const string& ngay) {
    // Chỉ đọc đơn hàng của ngày cụ thể
    // Thay vì load tất cả đơn hàng
}
```

---

## 📝 CHECKLIST HOÀN THÀNH

### Chức năng cốt lõi
- [x] Quản lý phim (CRUD)
- [x] Quản lý phòng chiếu
- [x] Lập lịch chiếu
- [x] Hiển thị sơ đồ ghế động
- [x] Đặt vé với validation
- [x] Bán combo
- [x] In hóa đơn
- [x] Thống kê doanh thu

### Kỹ thuật lập trình
- [x] Không dùng built-in functions (stoi, to_string, stringstream)
- [x] Parse CSV thủ công
- [x] Quản lý bộ nhớ động (new/delete)
- [x] Mảng lồng nhau (3 cấp)
- [x] Validation đầy đủ
- [x] Sinh mã ID tự động
- [x] Chuyển đổi ma trận 1D ↔ 2D

### Code quality
- [x] Comment đầy đủ (tiếng Việt)
- [x] Tên biến có ý nghĩa
- [x] Xử lý lỗi (file không tồn tại, dữ liệu không hợp lệ)
- [x] Giải phóng bộ nhớ đúng cách
- [x] Không memory leak

---

## 🎯 KẾT LUẬN

Bài 8 là bài tập **nâng cao** kết hợp nhiều kỹ thuật:
- ✅ **Ma trận 2D**: Quản lý ghế ngồi
- ✅ **Validation phức tạp**: Ghế, định dạng, giới hạn
- ✅ **Đơn hàng phức tạp**: Vé + Combo (mảng lồng nhau)
- ✅ **Bộ nhớ động 3 cấp**: DonHang → Ve/Combo → data
- ✅ **UI tương tác**: Sơ đồ ghế trực quan

**Pattern quan trọng**:
1. **Ma trận 1D mô phỏng 2D** → Áp dụng cho: Bàn cờ, lưới, sơ đồ chỗ ngồi
2. **Quản lý trạng thái đối tượng** → Áp dụng cho: Phòng, bàn, ghế, sản phẩm
3. **Đơn hàng với nhiều mục** → Áp dụng cho: E-commerce, POS, đặt hàng

Bài tập này rèn luyện:
- 🧠 Tư duy logic phức tạp
- 🔧 Kỹ năng debug (con trỏ, bộ nhớ)
- 🎨 Thiết kế UI/UX (sơ đồ ghế)
- 📊 Quản lý dữ liệu phức tạp

Chúc bạn thành công! 🎉
