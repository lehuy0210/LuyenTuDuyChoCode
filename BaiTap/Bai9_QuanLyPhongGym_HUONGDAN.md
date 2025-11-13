# BÀI 9: HỆ THỐNG QUẢN LÝ PHÒNG TẬP GYM

## 📋 TỔNG QUAN

Hệ thống quản lý phòng tập gym toàn diện bao gồm:
- **Quản lý hội viên**: Đăng ký, gia hạn, theo dõi trạng thái
- **Gói thành viên**: 1 tháng, 3 tháng, 6 tháng, 1 năm, VIP
- **Lớp học nhóm**: Yoga, Zumba, Boxing, Spinning...
- **Personal Trainer (PT)**: Đặt lịch tập riêng
- **Điểm danh**: Check-in/Check-out hàng ngày
- **Thuê thiết bị**: Tủ đồ, khăn
- **Thống kê**: Doanh thu, lớp học phổ biến, giờ cao điểm

---

## 🎯 CÁC KHÁI NIỆM QUAN TRỌNG

### 1. **Quản lý Gói Thành viên & Tính Ngày hết hạn**

#### Cấu trúc gói tập
```cpp
struct GoiTap {
    string maGoi;         // G001, G002...
    string tenGoi;        // "1 Thang", "3 Thang", "VIP"
    int soThang;          // 1, 3, 6, 12...
    float giaGoi;         // 500000, 1200000, 8000000
    string moTa;          // Mô tả quyền lợi
};
```

#### Bảng giá gói tập mẫu

| Mã gói | Tên gói | Thời hạn | Giá (VND) | Quyền lợi |
|--------|---------|----------|-----------|-----------|
| G001 | 1 Tháng | 1 tháng | 500,000 | Tập gym + Yoga cơ bản |
| G002 | 3 Tháng | 3 tháng | 1,200,000 | Tập gym + Yoga + 2 buổi PT |
| G003 | 6 Tháng | 6 tháng | 2,000,000 | Tập gym + Yoga + Zumba + 5 buổi PT |
| G004 | 1 Năm | 12 tháng | 3,500,000 | Tất cả lớp học + 10 buổi PT + Thuê đồ miễn phí |
| G005 | VIP | 12 tháng | 8,000,000 | Unlimited + PT không giới hạn + Thuê đồ + Nước miễn phí |

**Chiến lược giá**:
- Giá 3 tháng: ~20% rẻ hơn mua 3 tháng riêng lẻ
- Giá 1 năm: ~30% rẻ hơn mua 12 tháng riêng lẻ
- Gói VIP: Premium với dịch vụ cao cấp

---

### 2. **Tính Ngày hết hạn Tự động**

#### Thuật toán cơ bản

```cpp
string TinhNgayHetHan(const string& ngayDangKy, int soThang) {
    // 1. Parse ngày đăng ký (dd/mm/yyyy)
    string fields[3];
    int count;

    string temp = ngayDangKy;
    // Chuyển "/" thành "," để dùng ParseCSV
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '/') temp[i] = ',';
    }
    ParseCSV(temp, fields, count);

    int ngay = StrToInt(fields[0]);     // 15
    int thang = StrToInt(fields[1]);    // 01
    int nam = StrToInt(fields[2]);      // 2025

    // 2. Cộng thêm số tháng
    thang += soThang;

    // 3. Xử lý tràn tháng
    while (thang > 12) {
        thang -= 12;
        nam++;
    }

    // 4. Format lại thành chuỗi
    string result = "";
    if (ngay < 10) result += "0";
    result += IntToStr(ngay) + "/";
    if (thang < 10) result += "0";
    result += IntToStr(thang) + "/";
    result += IntToStr(nam);

    return result;
}
```

**Ví dụ**:
```
Ngày đăng ký: 15/01/2025
Gói tập: 3 tháng

Tính toán:
- thang = 1 + 3 = 4
- Kết quả: 15/04/2025

Ngày đăng ký: 15/11/2025
Gói tập: 6 tháng

Tính toán:
- thang = 11 + 6 = 17
- 17 > 12 → thang = 17 - 12 = 5, nam = 2026
- Kết quả: 15/05/2026
```

#### Thuật toán nâng cao (xử lý ngày không tồn tại)

```cpp
string TinhNgayHetHanChinhXac(const string& ngayDangKy, int soThang) {
    string fields[3];
    int count;
    string temp = ngayDangKy;
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '/') temp[i] = ',';
    }
    ParseCSV(temp, fields, count);

    int ngay = StrToInt(fields[0]);
    int thang = StrToInt(fields[1]);
    int nam = StrToInt(fields[2]);

    thang += soThang;

    while (thang > 12) {
        thang -= 12;
        nam++;
    }

    // Xử lý số ngày trong tháng
    int soNgayTrongThang = 31;

    if (thang == 2) {
        // Năm nhuận
        bool laNamNhuan = (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
        soNgayTrongThang = laNamNhuan ? 29 : 28;
    } else if (thang == 4 || thang == 6 || thang == 9 || thang == 11) {
        soNgayTrongThang = 30;
    }

    // Nếu ngày vượt quá số ngày trong tháng, lấy ngày cuối tháng
    if (ngay > soNgayTrongThang) {
        ngay = soNgayTrongThang;
    }

    string result = "";
    if (ngay < 10) result += "0";
    result += IntToStr(ngay) + "/";
    if (thang < 10) result += "0";
    result += IntToStr(thang) + "/";
    result += IntToStr(nam);

    return result;
}
```

**Ví dụ xử lý trường hợp đặc biệt**:
```
Ngày đăng ký: 31/01/2025
Gói tập: 1 tháng

Tính toán:
- thang = 1 + 1 = 2 (Tháng 2)
- Tháng 2/2025 có 28 ngày (không nhuận)
- ngay = 31 > 28 → ngay = 28
- Kết quả: 28/02/2025

Ngày đăng ký: 31/01/2024
Gói tập: 1 tháng

Tính toán:
- thang = 2 (Tháng 2)
- 2024 là năm nhuận → Tháng 2 có 29 ngày
- ngay = 31 > 29 → ngay = 29
- Kết quả: 29/02/2024
```

**Ứng dụng**:
- ✅ Tính ngày hết hạn thẻ thành viên
- ✅ Tính ngày hết hạn bảo hành
- ✅ Tính ngày đến hạn thanh toán
- ✅ Tính ngày kết thúc hợp đồng

---

### 3. **So sánh Ngày & Kiểm tra Hết hạn**

#### Thuật toán so sánh ngày

```cpp
// Trả về: -1 nếu ngay1 < ngay2, 0 nếu bằng, 1 nếu ngay1 > ngay2
int SoSanhNgay(const string& ngay1, const string& ngay2) {
    int soNgay = TinhSoNgay(ngay1, ngay2);

    if (soNgay < 0) return 1;   // ngay1 > ngay2
    if (soNgay > 0) return -1;  // ngay1 < ngay2
    return 0;                    // ngay1 == ngay2
}

// Tính số ngày giữa 2 ngày (đơn giản hóa)
int TinhSoNgay(const string& ngayBatDau, const string& ngayKetThuc) {
    // Parse ngày 1
    string fields1[3];
    int count;
    string temp = ngayBatDau;
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '/') temp[i] = ',';
    }
    ParseCSV(temp, fields1, count);

    int ngay1 = StrToInt(fields1[0]);
    int thang1 = StrToInt(fields1[1]);
    int nam1 = StrToInt(fields1[2]);

    // Parse ngày 2
    string fields2[3];
    temp = ngayKetThuc;
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '/') temp[i] = ',';
    }
    ParseCSV(temp, fields2, count);

    int ngay2 = StrToInt(fields2[0]);
    int thang2 = StrToInt(fields2[1]);
    int nam2 = StrToInt(fields2[2]);

    // Chuyển thành tổng số ngày (đơn giản: 1 năm = 365 ngày, 1 tháng = 30 ngày)
    int tongNgay1 = nam1 * 365 + thang1 * 30 + ngay1;
    int tongNgay2 = nam2 * 365 + thang2 * 30 + ngay2;

    return tongNgay2 - tongNgay1;
}
```

**Lưu ý**: Thuật toán trên là phiên bản đơn giản hóa. Trong thực tế, cần tính chính xác số ngày từng tháng và năm nhuận.

#### Kiểm tra hội viên hết hạn

```cpp
void CapNhatTrangThaiHoiVien(const string& ngayHienTai) {
    for (int i = 0; i < soLuongHV; i++) {
        // So sánh ngày hiện tại với ngày hết hạn
        if (SoSanhNgay(dsHoiVien[i].ngayHetHan, ngayHienTai) < 0) {
            // ngayHetHan < ngayHienTai → đã hết hạn
            dsHoiVien[i].trangThai = "HetHan";
        } else {
            dsHoiVien[i].trangThai = "HoatDong";
        }
    }

    GhiHoiVien();  // Lưu thay đổi
}

// Kiểm tra trước khi cho phép hoạt động
bool KiemTraHoiVienHopLe(const string& maHV, const string& ngayHienTai) {
    for (int i = 0; i < soLuongHV; i++) {
        if (dsHoiVien[i].maHV == maHV) {
            if (dsHoiVien[i].trangThai != "HoatDong") {
                cout << "[LOI] Hoi vien da het han! Vui long gia han.\n";
                cout << "Ngay het han: " << dsHoiVien[i].ngayHetHan << "\n";
                return false;
            }

            if (SoSanhNgay(dsHoiVien[i].ngayHetHan, ngayHienTai) < 0) {
                cout << "[LOI] The thanh vien da het han!\n";
                dsHoiVien[i].trangThai = "HetHan";
                GhiHoiVien();
                return false;
            }

            return true;
        }
    }

    cout << "[LOI] Khong tim thay hoi vien!\n";
    return false;
}
```

**Ứng dụng**:
- 🔒 Chặn hội viên hết hạn vào phòng gym
- 📧 Gửi thông báo nhắc gia hạn (trước 7 ngày)
- 📊 Thống kê hội viên sắp hết hạn
- 🎁 Khuyến mãi gia hạn sớm

---

### 4. **Quản lý Lớp học & Đăng ký**

#### Cấu trúc lớp học

```cpp
struct LopHoc {
    string maLop;         // L001, L002...
    string tenLop;        // "Yoga", "Zumba", "Boxing"
    string giangVien;     // "Tran Thi B"
    string ngayHoc;       // "16/01/2025"
    string gioHoc;        // "06:00", "18:30"
    int soChoToiDa;       // 20, 30...
    int soChoDaDangKy;    // Số người đã đăng ký
    float phiThamGia;     // 50000, 100000 (0 nếu miễn phí)
};

struct DangKyLop {
    string maDK;          // DKL001
    string maHV;          // HV001
    string maLop;         // L001
    string ngayDangKy;    // "15/01/2025"
    bool daThamGia;       // true/false (đã check-in chưa)
};
```

#### Quy trình đăng ký lớp học

```
┌─────────────────────────────────────────────────┐
│ 1. KIỂM TRA HỘI VIÊN                            │
│    - Nhập mã hội viên                           │
│    - Kiểm tra hội viên tồn tại                 │
│    - Kiểm tra trạng thái: HoatDong/HetHan      │
│    - Nếu hết hạn → Yêu cầu gia hạn             │
└─────────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────────┐
│ 2. HIỂN THỊ LỊCH LỚP HỌC                        │
│    - Danh sách tất cả lớp học                   │
│    - Thông tin: Tên, GV, Ngày, Giờ             │
│    - Số chỗ: X/Y (đã đăng ký/tối đa)           │
│    - Phí tham gia (nếu có)                      │
└─────────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────────┐
│ 3. CHỌN LỚP HỌC                                 │
│    - Nhập số thứ tự lớp học                     │
│    - Kiểm tra lớp còn chỗ không               │
│    - Kiểm tra đã đăng ký lớp này chưa         │
└─────────────────────────────────────────────────┘
              ↓
┌─────────────────────────────────────────────────┐
│ 4. XÁC NHẬN VÀ LƯU ĐĂNG KÝ                      │
│    - Tạo mã đăng ký (DKL001, DKL002...)        │
│    - Tăng soChoDaDangKy của lớp                 │
│    - Lưu thông tin đăng ký                      │
│    - In thông tin xác nhận                      │
└─────────────────────────────────────────────────┘
```

#### Code đăng ký lớp học

```cpp
void DangKyLopHoc() {
    cout << "\n========== DANG KY LOP HOC ==========\n";

    // Bước 1: Kiểm tra hội viên
    cout << "Nhap ma hoi vien: ";
    string maHV;
    cin >> maHV;

    bool timThayHV = false;
    for (int i = 0; i < soLuongHV; i++) {
        if (dsHoiVien[i].maHV == maHV) {
            // Kiểm tra trạng thái
            if (dsHoiVien[i].trangThai != "HoatDong") {
                cout << "[LOI] Hoi vien da het han! Vui long gia han goi tap.\n";
                return;
            }
            timThayHV = true;
            break;
        }
    }

    if (!timThayHV) {
        cout << "[LOI] Khong tim thay hoi vien!\n";
        return;
    }

    // Bước 2: Hiển thị lịch lớp học
    HienThiLopHoc();

    // Bước 3: Chọn lớp học
    cout << "Chon lop hoc (1-" << soLuongLop << "): ";
    string input;
    cin >> input;
    int chon = StrToInt(input) - 1;

    if (chon < 0 || chon >= soLuongLop) {
        cout << "[LOI] Lua chon khong hop le!\n";
        return;
    }

    // Kiểm tra còn chỗ
    if (dsLopHoc[chon].soChoDaDangKy >= dsLopHoc[chon].soChoToiDa) {
        cout << "[LOI] Lop hoc da day!\n";
        return;
    }

    // Kiểm tra đã đăng ký chưa
    for (int i = 0; i < soLuongDKLop; i++) {
        if (dsDangKyLop[i].maHV == maHV &&
            dsDangKyLop[i].maLop == dsLopHoc[chon].maLop) {
            cout << "[LOI] Ban da dang ky lop hoc nay roi!\n";
            return;
        }
    }

    // Bước 4: Xác nhận và lưu
    DangKyLop dkMoi;
    dkMoi.maDK = TaoMaDKLopMoi();
    dkMoi.maHV = maHV;
    dkMoi.maLop = dsLopHoc[chon].maLop;
    dkMoi.ngayDangKy = dsLopHoc[chon].ngayHoc;
    dkMoi.daThamGia = false;

    // Thêm vào danh sách
    DangKyLop* temp = new DangKyLop[soLuongDKLop + 1];
    for (int i = 0; i < soLuongDKLop; i++) {
        temp[i] = dsDangKyLop[i];
    }
    temp[soLuongDKLop] = dkMoi;

    delete[] dsDangKyLop;
    dsDangKyLop = temp;
    soLuongDKLop++;

    // Cập nhật số chỗ đã đăng ký
    dsLopHoc[chon].soChoDaDangKy++;
    GhiLopHoc();

    cout << "[THANH CONG] Dang ky lop hoc thanh cong!\n";
    cout << "Lop: " << dsLopHoc[chon].tenLop << "\n";
    cout << "Ngay: " << dsLopHoc[chon].ngayHoc << " - Gio: " << dsLopHoc[chon].gioHoc << "\n";
}
```

---

### 5. **Đặt lịch Personal Trainer (PT)**

#### Cấu trúc lịch PT

```cpp
struct LichPT {
    string maLichPT;      // PT001, PT002...
    string maHV;          // HV001
    string tenPT;         // "Nguyen Van C" (tên PT)
    string ngayTap;       // "16/01/2025"
    string gioTap;        // "07:00"
    int soPhut;           // 60, 90, 120
    float phiPT;          // 300000/buổi
};
```

#### Bảng giá PT

| Thời lượng | Giá (VND) | Ghi chú |
|------------|-----------|---------|
| 60 phút | 300,000 | Cơ bản |
| 90 phút | 400,000 | Khuyến nghị |
| 120 phút | 500,000 | Chuyên sâu |

**Công thức tính giá**:
```cpp
// Giá: 5000 VND/phút
float phiPT = soPhut * 5000;

// Ví dụ:
// 60 phút: 60 × 5000 = 300,000 VND
// 90 phút: 90 × 5000 = 450,000 VND
// 120 phút: 120 × 5000 = 600,000 VND
```

#### Code đặt lịch PT

```cpp
void DatLichPT() {
    cout << "\n========== DAT LICH PERSONAL TRAINER ==========\n";

    // 1. Kiểm tra hội viên
    cout << "Nhap ma hoi vien: ";
    string maHV;
    cin >> maHV;

    bool timThayHV = false;
    for (int i = 0; i < soLuongHV; i++) {
        if (dsHoiVien[i].maHV == maHV) {
            if (dsHoiVien[i].trangThai != "HoatDong") {
                cout << "[LOI] Hoi vien da het han!\n";
                return;
            }
            timThayHV = true;
            break;
        }
    }

    if (!timThayHV) {
        cout << "[LOI] Khong tim thay hoi vien!\n";
        return;
    }

    // 2. Nhập thông tin lịch PT
    LichPT ptMoi;
    ptMoi.maLichPT = TaoMaPTMoi();
    ptMoi.maHV = maHV;

    cout << "Nhap ten PT: ";
    cin.ignore();
    getline(cin, ptMoi.tenPT);

    cout << "Nhap ngay tap (dd/mm/yyyy): ";
    getline(cin, ptMoi.ngayTap);

    cout << "Nhap gio tap (HH:MM): ";
    getline(cin, ptMoi.gioTap);

    cout << "Nhap so phut (60, 90, 120): ";
    string input;
    getline(cin, input);
    ptMoi.soPhut = StrToInt(input);

    // 3. Tính phí PT
    ptMoi.phiPT = ptMoi.soPhut * 5000;

    // 4. Hiển thị thông tin
    cout << "\n========== THONG TIN DAT LICH PT ==========\n";
    cout << "Ma lich: " << ptMoi.maLichPT << "\n";
    cout << "PT: " << ptMoi.tenPT << "\n";
    cout << "Ngay: " << ptMoi.ngayTap << " - Gio: " << ptMoi.gioTap << "\n";
    cout << "Thoi luong: " << ptMoi.soPhut << " phut\n";
    cout << "Phi: " << FloatToStr(ptMoi.phiPT, 0) << " VND\n";
    cout << "==========================================\n";

    // 5. Lưu lịch PT
    LichPT* temp = new LichPT[soLuongPT + 1];
    for (int i = 0; i < soLuongPT; i++) {
        temp[i] = dsLichPT[i];
    }
    temp[soLuongPT] = ptMoi;

    delete[] dsLichPT;
    dsLichPT = temp;
    soLuongPT++;

    cout << "[THANH CONG] Dat lich PT thanh cong!\n";
}
```

**Mở rộng**: Kiểm tra xung đột lịch PT
```cpp
bool KiemTraXungDotLichPT(const string& tenPT, const string& ngayTap, const string& gioTap) {
    for (int i = 0; i < soLuongPT; i++) {
        if (dsLichPT[i].tenPT == tenPT &&
            dsLichPT[i].ngayTap == ngayTap &&
            dsLichPT[i].gioTap == gioTap) {
            return true;  // Có xung đột
        }
    }
    return false;  // Không xung đột
}
```

---

### 6. **Điểm danh (Check-in/Check-out)**

#### Cấu trúc điểm danh

```cpp
struct DiemDanh {
    string maDD;          // DD001
    string maHV;          // HV001
    string ngay;          // "15/01/2025"
    string gioVao;        // "06:30"
    string gioRa;         // "08:00" (có thể trống nếu chưa check-out)
};
```

#### Quy trình check-in

```cpp
void CheckIn(const string& maHV, const string& ngayHienTai, const string& gioHienTai) {
    // 1. Kiểm tra hội viên hợp lệ
    bool hoiVienHopLe = false;
    for (int i = 0; i < soLuongHV; i++) {
        if (dsHoiVien[i].maHV == maHV) {
            if (dsHoiVien[i].trangThai != "HoatDong") {
                cout << "[LOI] Hoi vien da het han!\n";
                cout << "Ngay het han: " << dsHoiVien[i].ngayHetHan << "\n";
                return;
            }
            hoiVienHopLe = true;
            break;
        }
    }

    if (!hoiVienHopLe) {
        cout << "[LOI] Hoi vien khong hop le!\n";
        return;
    }

    // 2. Kiểm tra đã check-in chưa
    for (int i = 0; i < soLuongDD; i++) {
        if (dsDiemDanh[i].maHV == maHV &&
            dsDiemDanh[i].ngay == ngayHienTai &&
            dsDiemDanh[i].gioRa == "") {  // Chưa check-out
            cout << "[LOI] Ban da check-in roi luc " << dsDiemDanh[i].gioVao << "!\n";
            return;
        }
    }

    // 3. Tạo bản ghi điểm danh
    DiemDanh ddMoi;
    ddMoi.maDD = TaoMaDDMoi();
    ddMoi.maHV = maHV;
    ddMoi.ngay = ngayHienTai;
    ddMoi.gioVao = gioHienTai;
    ddMoi.gioRa = "";  // Chưa check-out

    // 4. Lưu vào danh sách
    DiemDanh* temp = new DiemDanh[soLuongDD + 1];
    for (int i = 0; i < soLuongDD; i++) {
        temp[i] = dsDiemDanh[i];
    }
    temp[soLuongDD] = ddMoi;

    delete[] dsDiemDanh;
    dsDiemDanh = temp;
    soLuongDD++;

    cout << "[THANH CONG] Check-in thanh cong!\n";
    cout << "Gio vao: " << gioHienTai << "\n";
}
```

#### Quy trình check-out

```cpp
void CheckOut(const string& maHV, const string& ngayHienTai, const string& gioHienTai) {
    // Tìm bản ghi check-in hôm nay chưa check-out
    for (int i = 0; i < soLuongDD; i++) {
        if (dsDiemDanh[i].maHV == maHV &&
            dsDiemDanh[i].ngay == ngayHienTai &&
            dsDiemDanh[i].gioRa == "") {

            // Cập nhật giờ ra
            dsDiemDanh[i].gioRa = gioHienTai;

            cout << "[THANH CONG] Check-out thanh cong!\n";
            cout << "Gio vao: " << dsDiemDanh[i].gioVao << "\n";
            cout << "Gio ra: " << gioHienTai << "\n";

            // Tính thời gian tập
            int phutTap = TinhPhutTap(dsDiemDanh[i].gioVao, gioHienTai);
            cout << "Thoi gian tap: " << phutTap << " phut\n";

            return;
        }
    }

    cout << "[LOI] Khong tim thay ban ghi check-in!\n";
}

// Tính số phút giữa 2 thời gian
int TinhPhutTap(const string& gioVao, const string& gioRa) {
    // Parse giờ vào (HH:MM)
    string fields1[2];
    int count;
    string temp = gioVao;
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == ':') temp[i] = ',';
    }
    ParseCSV(temp, fields1, count);

    int gioVaoH = StrToInt(fields1[0]);
    int gioVaoM = StrToInt(fields1[1]);

    // Parse giờ ra (HH:MM)
    string fields2[2];
    temp = gioRa;
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == ':') temp[i] = ',';
    }
    ParseCSV(temp, fields2, count);

    int gioRaH = StrToInt(fields2[0]);
    int gioRaM = StrToInt(fields2[1]);

    // Chuyển sang phút
    int tongPhutVao = gioVaoH * 60 + gioVaoM;
    int tongPhutRa = gioRaH * 60 + gioRaM;

    return tongPhutRa - tongPhutVao;
}
```

**Ứng dụng thống kê**:
- 📊 Số lượt tập/ngày, /tháng
- ⏰ Giờ cao điểm (nhiều người check-in nhất)
- 👤 Hội viên tích cực nhất (số lần tập nhiều nhất)
- 📈 Thời gian tập trung bình

---

### 7. **Thống kê Doanh thu Chi tiết**

#### Các nguồn doanh thu

```cpp
void ThongKeDoanhThu() {
    cout << "\n========== THONG KE DOANH THU ==========\n";

    // 1. Doanh thu từ gói tập
    float tongDoanhThuGoiTap = 0;
    for (int i = 0; i < soLuongHV; i++) {
        for (int j = 0; j < soLuongGoi; j++) {
            if (dsHoiVien[i].maGoi == dsGoiTap[j].maGoi) {
                tongDoanhThuGoiTap += dsGoiTap[j].giaGoi;
                break;
            }
        }
    }

    // 2. Doanh thu từ lớp học (có phí)
    float tongDoanhThuLop = 0;
    for (int i = 0; i < soLuongDKLop; i++) {
        for (int j = 0; j < soLuongLop; j++) {
            if (dsDangKyLop[i].maLop == dsLopHoc[j].maLop) {
                tongDoanhThuLop += dsLopHoc[j].phiThamGia;
                break;
            }
        }
    }

    // 3. Doanh thu từ PT
    float tongDoanhThuPT = 0;
    for (int i = 0; i < soLuongPT; i++) {
        tongDoanhThuPT += dsLichPT[i].phiPT;
    }

    // 4. Doanh thu từ thuê thiết bị (nếu có)
    float tongDoanhThuThue = 0;
    for (int i = 0; i < soLuongThue; i++) {
        tongDoanhThuThue += dsThueThietBi[i].phiThue;
    }

    // 5. Tổng hợp
    float tongDoanhThu = tongDoanhThuGoiTap + tongDoanhThuLop + tongDoanhThuPT + tongDoanhThuThue;

    // 6. Hiển thị
    cout << "Tong so hoi vien: " << soLuongHV << "\n";
    cout << "---------------------------------------\n";
    cout << "Doanh thu goi tap: " << FloatToStr(tongDoanhThuGoiTap, 0) << " VND\n";
    cout << "Doanh thu lop hoc: " << FloatToStr(tongDoanhThuLop, 0) << " VND\n";
    cout << "Doanh thu PT: " << FloatToStr(tongDoanhThuPT, 0) << " VND\n";
    cout << "Doanh thu thue TB: " << FloatToStr(tongDoanhThuThue, 0) << " VND\n";
    cout << "---------------------------------------\n";
    cout << "TONG DOANH THU: " << FloatToStr(tongDoanhThu, 0) << " VND\n";
}
```

#### Thống kê nâng cao

```cpp
// Top 5 lớp học phổ biến nhất
void ThongKeLopHocPhoBien() {
    cout << "\n========== TOP 5 LOP HOC PHO BIEN ==========\n";

    // Sắp xếp lớp học theo số người đăng ký (giảm dần)
    for (int i = 0; i < soLuongLop - 1; i++) {
        for (int j = i + 1; j < soLuongLop; j++) {
            if (dsLopHoc[j].soChoDaDangKy > dsLopHoc[i].soChoDaDangKy) {
                LopHoc temp = dsLopHoc[i];
                dsLopHoc[i] = dsLopHoc[j];
                dsLopHoc[j] = temp;
            }
        }
    }

    int soLopHien = soLuongLop < 5 ? soLuongLop : 5;

    for (int i = 0; i < soLopHien; i++) {
        cout << (i + 1) << ". " << dsLopHoc[i].tenLop << " - "
             << dsLopHoc[i].soChoDaDangKy << " nguoi\n";
    }
}

// Giờ cao điểm
void ThongKeGioCaoDiem() {
    cout << "\n========== GIO CAO DIEM ==========\n";

    // Đếm số lượt check-in theo từng khung giờ
    int khungGio[24] = {0};  // 0-23h

    for (int i = 0; i < soLuongDD; i++) {
        // Parse giờ từ gioVao (HH:MM)
        string fields[2];
        int count;
        string temp = dsDiemDanh[i].gioVao;
        for (int j = 0; j < temp.length(); j++) {
            if (temp[j] == ':') temp[j] = ',';
        }
        ParseCSV(temp, fields, count);

        int gio = StrToInt(fields[0]);
        khungGio[gio]++;
    }

    // Tìm giờ có nhiều người nhất
    int maxLuot = 0;
    int gioCaoDiem = 0;

    for (int i = 0; i < 24; i++) {
        if (khungGio[i] > maxLuot) {
            maxLuot = khungGio[i];
            gioCaoDiem = i;
        }
    }

    cout << "Gio cao diem: " << gioCaoDiem << "h - " << (gioCaoDiem + 1) << "h\n";
    cout << "So luot check-in: " << maxLuot << "\n\n";

    // Hiển thị biểu đồ ASCII
    cout << "Bieu do theo gio:\n";
    for (int i = 0; i < 24; i++) {
        if (khungGio[i] > 0) {
            cout << i << "h: ";
            for (int j = 0; j < khungGio[i]; j++) {
                cout << "*";
            }
            cout << " (" << khungGio[i] << ")\n";
        }
    }
}

// Hội viên tích cực nhất
void ThongKeHoiVienTichCuc() {
    cout << "\n========== HOI VIEN TICH CUC NHAT ==========\n";

    // Đếm số lần tập của mỗi hội viên
    int* soLanTap = new int[soLuongHV];
    for (int i = 0; i < soLuongHV; i++) {
        soLanTap[i] = 0;
    }

    for (int i = 0; i < soLuongDD; i++) {
        for (int j = 0; j < soLuongHV; j++) {
            if (dsDiemDanh[i].maHV == dsHoiVien[j].maHV) {
                soLanTap[j]++;
                break;
            }
        }
    }

    // Tìm top 5
    for (int k = 0; k < 5 && k < soLuongHV; k++) {
        int maxLan = 0;
        int viTri = 0;

        for (int i = 0; i < soLuongHV; i++) {
            if (soLanTap[i] > maxLan) {
                maxLan = soLanTap[i];
                viTri = i;
            }
        }

        if (maxLan > 0) {
            cout << (k + 1) << ". " << dsHoiVien[viTri].hoTen << " - "
                 << maxLan << " lan\n";
            soLanTap[viTri] = 0;  // Đánh dấu đã in
        }
    }

    delete[] soLanTap;
}
```

---

## 🔧 CÁC KỸ THUẬT LẬP TRÌNH

### 1. **Parse Thời gian (HH:MM)**

```cpp
void ParseTime(const string& time, int& gio, int& phut) {
    string fields[2];
    int count;

    string temp = time;
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == ':') temp[i] = ',';
    }
    ParseCSV(temp, fields, count);

    gio = StrToInt(fields[0]);
    phut = StrToInt(fields[1]);
}

// Tính khoảng cách giữa 2 thời gian (phút)
int KhoangCachPhut(const string& time1, const string& time2) {
    int gio1, phut1, gio2, phut2;

    ParseTime(time1, gio1, phut1);
    ParseTime(time2, gio2, phut2);

    int tongPhut1 = gio1 * 60 + phut1;
    int tongPhut2 = gio2 * 60 + phut2;

    return tongPhut2 - tongPhut1;
}
```

### 2. **Kiểm tra Gói tập có quyền lợi**

```cpp
bool CoQuyenTapLop(const string& maHV, const string& maLop) {
    // Tìm gói tập của hội viên
    string maGoi = "";
    for (int i = 0; i < soLuongHV; i++) {
        if (dsHoiVien[i].maHV == maHV) {
            maGoi = dsHoiVien[i].maGoi;
            break;
        }
    }

    // Kiểm tra quyền lợi gói tập
    for (int i = 0; i < soLuongGoi; i++) {
        if (dsGoiTap[i].maGoi == maGoi) {
            // VIP: Tập tất cả
            if (dsGoiTap[i].tenGoi == "VIP") {
                return true;
            }

            // Gói 1 năm: Tập tất cả lớp học
            if (dsGoiTap[i].soThang >= 12) {
                return true;
            }

            // Gói khác: Kiểm tra lớp có phí không
            for (int j = 0; j < soLuongLop; j++) {
                if (dsLopHoc[j].maLop == maLop) {
                    return dsLopHoc[j].phiThamGia == 0;  // Chỉ lớp miễn phí
                }
            }
        }
    }

    return false;
}
```

### 3. **Gửi thông báo nhắc gia hạn**

```cpp
void KiemTraVaGuiThongBaoGiaHan(const string& ngayHienTai) {
    cout << "\n========== THONG BAO GIA HAN ==========\n";

    bool coHVSapHetHan = false;

    for (int i = 0; i < soLuongHV; i++) {
        int soNgayConLai = TinhSoNgay(ngayHienTai, dsHoiVien[i].ngayHetHan);

        // Nhắc trước 7 ngày
        if (soNgayConLai > 0 && soNgayConLai <= 7) {
            cout << "- " << dsHoiVien[i].hoTen << " (" << dsHoiVien[i].maHV << ")\n";
            cout << "  Het han: " << dsHoiVien[i].ngayHetHan << " (con " << soNgayConLai << " ngay)\n";
            cout << "  SDT: " << dsHoiVien[i].sdt << "\n\n";
            coHVSapHetHan = true;
        }
    }

    if (!coHVSapHetHan) {
        cout << "Khong co hoi vien nao sap het han.\n";
    }
}
```

---

## 📊 DỮ LIỆU MẪU

### File: GoiTap.txt
```
MaGoi,TenGoi,SoThang,GiaGoi,MoTa
G001,1 Thang,1,500000,Tap tap gym + Yoga co ban
G002,3 Thang,3,1200000,Tap tap gym + Yoga + 2 buoi PT
G003,6 Thang,6,2000000,Tap tap gym + Yoga + Zumba + 5 buoi PT
G004,1 Nam,12,3500000,Tap tat ca lop hoc + 10 buoi PT + Thu do mien phi
G005,VIP,12,8000000,Unlimited + PT khong gioi han + Thu do + Nuoc mien phi
```

### File: DanhSachHoiVien.txt
```
MaHV,HoTen,Tuoi,SDT,Email,MaGoi,NgayDangKy,NgayHetHan,TrangThai
HV001,Nguyen Van A,25,0912345678,a@example.com,G001,01/01/2025,01/02/2025,HoatDong
HV002,Tran Thi B,30,0923456789,b@example.com,G003,15/12/2024,15/06/2025,HoatDong
HV003,Le Van C,22,0934567890,c@example.com,G004,01/01/2025,01/01/2026,HoatDong
```

### File: LopHoc.txt
```
MaLop,TenLop,GiangVien,NgayHoc,GioHoc,SoChoToiDa,SoChoDaDangKy,PhiThamGia
L001,Yoga Morning,Tran Thi Hoa,16/01/2025,06:00,20,5,0
L002,Zumba Dance,Nguyen Van Nam,16/01/2025,18:30,30,12,50000
L003,Boxing Fitness,Le Thanh Tung,17/01/2025,19:00,15,8,100000
L004,Yoga Evening,Tran Thi Hoa,17/01/2025,20:00,20,10,0
L005,Spinning Class,Pham Van Duc,18/01/2025,07:00,25,15,50000
```

---

## 🎓 ỨNG DỤNG THỰC TẾ

### 1. **Hệ thống quản lý spa**
- Gói liệu trình: 5 buổi, 10 buổi, 20 buổi
- Đặt lịch spa, massage
- Điểm danh sử dụng dịch vụ
- Tính toán số buổi còn lại

### 2. **Hệ thống quản lý bể bơi**
- Gói tập: Tháng, quý, năm
- Lớp học bơi (trẻ em, người lớn)
- Thuê giờ (1 giờ, 2 giờ)
- Quản lý HLV dạy bơi

### 3. **Hệ thống quản lý câu lạc bộ**
- Thành viên câu lạc bộ
- Sự kiện, hoạt động
- Điểm danh tham gia
- Đóng góp, quỹ

### 4. **Hệ thống quản lý trung tâm yoga/pilates**
- Gói tập yoga
- Lớp học theo cấp độ (cơ bản, nâng cao)
- Lịch PT riêng
- Theo dõi tiến độ tập luyện

---

## 💡 BÀI TẬP MỞ RỘNG

### Cấp độ 1: Cơ bản
1. **Gia hạn gói tập**
   - Input: Mã hội viên, gói tập mới
   - Tính ngày hết hạn mới từ ngày hết hạn cũ
   - Cập nhật trạng thái

2. **Hủy đăng ký lớp học**
   - Giảm `soChoDaDangKy`
   - Xóa bản ghi đăng ký
   - Hoàn phí (nếu có)

3. **Tìm kiếm hội viên**
   - Tìm theo tên (substring)
   - Tìm theo SĐT
   - Tìm hội viên hết hạn

### Cấp độ 2: Trung bình
4. **Gói tập linh hoạt**
   ```cpp
   struct GoiLinhDong {
       string maGoi;
       int soLanTap;     // 10 lần, 20 lần
       float giaGoi;     // 800000, 1500000
       string hanSuDung; // "60 ngay", "90 ngay"
       int soLanDaSuDung; // Đã tập bao nhiêu lần
   };

   // Kiểm tra hội viên còn lần tập không
   bool ConLanTap(const string& maHV) {
       // ...
   }
   ```

5. **Đánh giá lớp học**
   ```cpp
   struct DanhGiaLop {
       string maDG;
       string maHV;
       string maLop;
       int diemSao;      // 1-5 sao
       string nhanXet;   // "Rat tot", "Tot"...
   };

   float TinhDiemTrungBinhLop(const string& maLop) {
       // ...
   }
   ```

6. **Theo dõi cân nặng/BMI**
   ```cpp
   struct TheoDoiCanNang {
       string maHV;
       string ngayDo;
       float canNang;    // kg
       float chieuCao;   // m
       float BMI;        // canNang / (chieuCao^2)
   };

   void TinhBMI(TheoDoiCanNang& tt) {
       tt.BMI = tt.canNang / (tt.chieuCao * tt.chieuCao);
   }
   ```

### Cấp độ 3: Nâng cao
7. **Gói PT trọn gói**
   ```cpp
   struct GoiPT {
       string maGoiPT;
       string maHV;
       int soBuoi;        // 10, 20, 30 buổi
       int soBuoiDaTap;   // Đã tập bao nhiêu buổi
       string tenPT;      // PT phụ trách
       float tongPhi;     // 5000000
       bool daThanhToan;  // true/false
   };
   ```

8. **Chương trình khuyến mãi**
   ```cpp
   float TinhGiaGoi(const string& maGoi, const string& maKM) {
       float giaGoc = LayGiaGoi(maGoi);

       if (maKM == "KM001") {  // Giảm 20%
           return giaGoc * 0.8;
       } else if (maKM == "KM002") {  // Tặng thêm 1 tháng
           // Logic tặng thêm
       }

       return giaGoc;
   }
   ```

9. **Phân tích xu hướng**
   - Tháng nào có nhiều người đăng ký nhất
   - Gói tập nào bán chạy nhất
   - Tỷ lệ gia hạn (retention rate)
   - Dự đoán doanh thu tháng tới

10. **Ứng dụng mobile - QR code check-in**
    ```cpp
    string TaoMaQR(const string& maHV) {
        // Mã hóa thông tin hội viên thành QR code
        return "QR_" + maHV + "_" + LayNgayHienTai();
    }

    bool QuetMaQR(const string& maQR) {
        // Giải mã QR code và check-in
        // ...
    }
    ```

---

## 🚀 TỐI ƯU HÓA

### 1. **Cache thông tin gói tập**
```cpp
// Thay vì tìm kiếm mỗi lần
struct HoiVien {
    // ...
    float giaGoiHienTai;  // Cache giá gói
    int soThangGoi;       // Cache số tháng
};
```

### 2. **Index hội viên theo mã**
```cpp
// Sử dụng map (nếu được phép) hoặc hash table
// Tìm kiếm O(1) thay vì O(n)
```

### 3. **Batch update trạng thái**
```cpp
void CapNhatTrangThaiTatCaHoiVien() {
    string ngayHienTai = LayNgayHienTai();

    for (int i = 0; i < soLuongHV; i++) {
        if (SoSanhNgay(dsHoiVien[i].ngayHetHan, ngayHienTai) < 0) {
            dsHoiVien[i].trangThai = "HetHan";
        }
    }

    GhiHoiVien();  // Ghi 1 lần duy nhất
}
```

---

## 📝 CHECKLIST HOÀN THÀNH

### Chức năng cốt lõi
- [x] Đăng ký hội viên
- [x] Tính ngày hết hạn tự động
- [x] Quản lý gói tập
- [x] Lớp học nhóm
- [x] Đặt lịch PT
- [x] Điểm danh (check-in/check-out)
- [x] Thống kê doanh thu

### Kỹ thuật lập trình
- [x] Parse ngày (dd/mm/yyyy)
- [x] So sánh ngày
- [x] Tính toán ngày hết hạn
- [x] Parse thời gian (HH:MM)
- [x] Kiểm tra trùng lặp đăng ký
- [x] Validation trạng thái hội viên

---

## 🎯 KẾT LUẬN

Bài 9 là bài tập **quan trọng** với các kỹ thuật:
- ✅ **Quản lý thời gian**: Tính ngày hết hạn, so sánh ngày
- ✅ **Xử lý trạng thái**: HoatDong/HetHan, Trong/DaDat
- ✅ **Quản lý gói dịch vụ**: Nhiều gói với quyền lợi khác nhau
- ✅ **Điểm danh**: Check-in/Check-out với thời gian
- ✅ **Thống kê phức tạp**: Nhiều nguồn doanh thu

**Pattern quan trọng**:
1. **Tính toán ngày tháng** → Áp dụng: Hệ thống đặt vé, khách sạn, hợp đồng
2. **Gói dịch vụ linh hoạt** → Áp dụng: Spa, bể bơi, câu lạc bộ
3. **Điểm danh theo thời gian** → Áp dụng: Công ty, trường học, sự kiện

Chúc bạn thành công! 💪🎉
