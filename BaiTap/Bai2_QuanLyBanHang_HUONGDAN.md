# BÀI 2: QUẢN LÝ BÁN HÀNG CỬA HÀNG NHỎ

## 📋 Mô Tả Bài Toán
Phát triển hệ thống POS (Point of Sale) đơn giản bao gồm:
- Quản lý sản phẩm
- Tạo hóa đơn bán hàng
- Tính tổng tiền và áp dụng chiết khấu
- Xuất hóa đơn ra file
- Kiểm tra tồn kho

## 🎯 Khái Niệm Áp Dụng
- ✅ Business logic (logic nghiệp vụ)
- ✅ Receipt generation (tạo hóa đơn)
- ✅ Discount calculation (tính chiết khấu)
- ✅ Inventory management (quản lý tồn kho)
- ✅ VAT calculation (tính thuế VAT)

---

## 🏗️ PHÂN TÍCH THIẾT KẾ

### 1. Xác Định Thực Thể (Entities)

#### 📦 Sản Phẩm (Product)
```cpp
struct SanPham {
    string maSP;        // Mã sản phẩm duy nhất
    string tenSP;       // Tên sản phẩm
    float donGia;       // Đơn giá
    int tonKho;         // Tồn kho
};
```

#### 📝 Chi Tiết Hóa Đơn (Invoice Detail)
```cpp
struct ChiTietHoaDon {
    string maSP;        // Mã sản phẩm
    string tenSP;       // Tên sản phẩm
    float donGia;       // Đơn giá
    int soLuong;        // Số lượng
    float thanhTien;    // Thành tiền = đơn giá × số lượng
};
```

#### 🧾 Hóa Đơn (Invoice)
```cpp
struct HoaDon {
    string maHD;                    // Mã hóa đơn
    string ngayLap;                 // Ngày lập
    ChiTietHoaDon* dsChiTiet;      // Danh sách chi tiết
    int soLuongChiTiet;            // Số lượng chi tiết
    float tongTien;                 // Tổng tiền
    float giamGia;                  // Giảm giá
    float VAT;                      // Thuế VAT
    float tongThanhToan;            // Tổng thanh toán
};
```

### 2. Thiết Kế Mối Quan Hệ

```
HoaDon (1) -----> (N) ChiTietHoaDon
ChiTietHoaDon (N) -----> (1) SanPham
```

- Một hóa đơn có nhiều chi tiết hóa đơn
- Một chi tiết hóa đơn tham chiếu đến một sản phẩm
- Khi bán hàng → giảm tồn kho

---

## 🔧 CÁC HÀM QUAN TRỌNG KHÔNG DÙNG BUILT-IN

### 1. Chuyển String Sang Float
```cpp
float StringToFloat(const string& str) {
    float ketqua = 0.0;
    float phanThapPhan = 0.0;
    int viTriThapPhan = 0;
    bool coThapPhan = false;
    bool amDuong = false;
    int batdau = 0;

    if (str.length() > 0 && str[0] == '-') {
        amDuong = true;
        batdau = 1;
    }

    for (int i = batdau; i < str.length(); i++) {
        if (str[i] == '.' || str[i] == ',') {
            coThapPhan = true;
            continue;
        }

        if (str[i] >= '0' && str[i] <= '9') {
            if (!coThapPhan) {
                ketqua = ketqua * 10 + (str[i] - '0');
            } else {
                viTriThapPhan++;
                phanThapPhan = phanThapPhan * 10 + (str[i] - '0');
            }
        }
    }

    // Chuyển phần thập phân
    for (int i = 0; i < viTriThapPhan; i++) {
        phanThapPhan = phanThapPhan / 10.0;
    }

    ketqua = ketqua + phanThapPhan;
    return amDuong ? -ketqua : ketqua;
}
```

**Giải thích:**
- Tách phần nguyên và phần thập phân
- Duyệt từng ký tự, gặp '.' hoặc ',' thì chuyển sang phần thập phân
- Phần nguyên: tích lũy như chuyển int
- Phần thập phân: chia cho 10 cho mỗi chữ số

### 2. Chuyển Float Sang String
```cpp
string FloatToString(float so) {
    // Phần nguyên
    int phanNguyen = (int)so;
    string ketqua = IntToString(phanNguyen);

    // Phần thập phân (2 chữ số)
    float phanThapPhan = so - phanNguyen;
    if (phanThapPhan < 0) phanThapPhan = -phanThapPhan;

    int thapPhan = (int)((phanThapPhan * 100) + 0.5); // Làm tròn

    ketqua = ketqua + ".";

    if (thapPhan < 10) {
        ketqua = ketqua + "0";  // Thêm số 0 đằng trước
    }
    ketqua = ketqua + IntToString(thapPhan);

    return ketqua;
}
```

**Giải thích:**
- Tách phần nguyên: ép kiểu `(int)`
- Phần thập phân: lấy phần lẻ × 100 để có 2 chữ số
- Làm tròn: + 0.5 trước khi ép kiểu
- Ghép lại với dấu chấm

---

## 💰 CÁC LOẠI GIẢM GIÁ

### 1. Giảm Giá Theo Phần Trăm (%)
```cpp
float GiamGiaPhanTram(float tongTien, float phanTram) {
    return tongTien * phanTram / 100.0;
}
```

**Ví dụ:**
- Tổng tiền: 1,000,000 VND
- Giảm 10% → 100,000 VND

### 2. Giảm Giá Cố Định (VND)
```cpp
float GiamGiaCoDinh(float soTienGiam) {
    return soTienGiam;
}
```

**Ví dụ:**
- Giảm 50,000 VND trực tiếp

### 3. Giảm Giá Bậc Thang
```cpp
float GiamGiaBacThang(float tongTien) {
    if (tongTien >= 1000000) {
        return tongTien * 10.0 / 100.0;  // Giảm 10%
    } else if (tongTien >= 500000) {
        return tongTien * 5.0 / 100.0;   // Giảm 5%
    } else if (tongTien >= 200000) {
        return tongTien * 2.0 / 100.0;   // Giảm 2%
    }
    return 0.0;
}
```

**Bảng giảm giá:**
| Tổng tiền | Giảm giá |
|-----------|----------|
| ≥ 1,000,000 | 10% |
| ≥ 500,000 | 5% |
| ≥ 200,000 | 2% |
| < 200,000 | 0% |

### 4. Giảm Giá Combo
```cpp
float GiamGiaCombo(int soLuongSanPham, float tongTien) {
    if (soLuongSanPham >= 5) {
        return tongTien * 15.0 / 100.0;  // Giảm 15%
    } else if (soLuongSanPham >= 3) {
        return tongTien * 10.0 / 100.0;  // Giảm 10%
    }
    return 0.0;
}
```

**Áp dụng:**
- Mua từ 5 sản phẩm → giảm 15%
- Mua từ 3 sản phẩm → giảm 10%

---

## 📊 TÍNH TOÁN HÓA ĐƠN

### Công Thức Tính
```
Thành tiền = Đơn giá × Số lượng
Tổng tiền = Σ Thành tiền

Sau giảm giá = Tổng tiền - Giảm giá
VAT = Sau giảm giá × 10%
TỔNG THANH TOÁN = Sau giảm giá + VAT
```

### Ví Dụ Cụ Thể
```
Sản phẩm 1: 50,000 × 2 = 100,000
Sản phẩm 2: 30,000 × 3 = 90,000
--------------------------------------
Tổng tiền:              190,000 VND
Giảm giá (5%):           -9,500 VND
--------------------------------------
Sau giảm giá:           180,500 VND
VAT (10%):               18,050 VND
======================================
TỔNG THANH TOÁN:        198,550 VND
```

---

## 📄 TẠO HÓA ĐƠN

### 1. Quy Trình Tạo Hóa Đơn

```
Bắt đầu
   ↓
Tạo hóa đơn mới (sinh mã tự động)
   ↓
Hiển thị danh sách sản phẩm
   ↓
Nhập mã sản phẩm
   ↓
Kiểm tra tồn kho → Không đủ? → Báo lỗi
   ↓ Đủ
Nhập số lượng
   ↓
Thêm vào chi tiết hóa đơn
   ↓
Giảm tồn kho
   ↓
Có thêm sản phẩm? → Có → Quay lại
   ↓ Không
Chọn loại giảm giá
   ↓
Tính VAT (10%)
   ↓
Tính tổng thanh toán
   ↓
In hóa đơn ra màn hình
   ↓
Xuất hóa đơn ra file
   ↓
Cập nhật file sản phẩm
   ↓
Kết thúc
```

### 2. Định Dạng Hóa Đơn

```
========================================
       HOA DON BAN HANG
========================================
Ma hoa don: HD1
Ngay lap: 13/11/2025 10:30:45
----------------------------------------
STT  Ma SP  Ten SP      SL  Don Gia    Thanh Tien
----------------------------------------
1    SP001  BanhMi      2   15000      30000
2    SP002  Sua         3   20000      60000
----------------------------------------
Tong tien:                      90000 VND
Giam gia:                        4500 VND
VAT (10%):                       8550 VND
========================================
TONG THANH TOAN:                94050 VND
========================================
```

---

## 🗄️ QUẢN LÝ TỒN KHO

### 1. Kiểm Tra Trước Khi Bán
```cpp
if (dsSP[viTri].tonKho <= 0) {
    cout << "San pham het hang!" << endl;
    return;
}

if (soLuong > dsSP[viTri].tonKho) {
    cout << "Khong du ton kho!" << endl;
    return;
}
```

### 2. Cập Nhật Tồn Kho
```cpp
// Giảm tồn kho khi bán
dsSP[viTri].tonKho -= soLuong;

// Lưu lại file ngay sau khi bán
LuuFileSanPham(dsSP, demSP, "DanhSachSanPham.txt");
```

### 3. Cảnh Báo Tồn Kho Thấp
```cpp
void KiemTraTonKhoThap(SanPham* dsSP, int demSP, int nguong) {
    cout << "San pham ton kho thap:" << endl;
    for (int i = 0; i < demSP; i++) {
        if (dsSP[i].tonKho < nguong) {
            cout << dsSP[i].maSP << " - "
                 << dsSP[i].tenSP << ": "
                 << dsSP[i].tonKho << endl;
        }
    }
}
```

---

## 📂 XỬ LÝ FILE

### 1. File Sản Phẩm (CSV)
```
MaSP,TenSP,DonGia,TonKho
SP001,BanhMi,15000,50
SP002,Sua,20000,30
```

### 2. Xuất Hóa Đơn Ra File
```cpp
void XuatHoaDon(const HoaDon& hoaDon) {
    ofstream outFile("HoaDon_" + hoaDon.maHD + ".txt");

    // Ghi tiêu đề
    outFile << "======================================" << endl;
    outFile << "       HOA DON BAN HANG" << endl;
    outFile << "======================================" << endl;

    // Ghi thông tin hóa đơn
    outFile << "Ma hoa don: " << hoaDon.maHD << endl;
    outFile << "Ngay lap: " << hoaDon.ngayLap << endl;

    // Ghi chi tiết
    // ...

    // Ghi tổng cộng
    outFile << "TONG THANH TOAN: " << hoaDon.tongThanhToan << " VND" << endl;

    outFile.close();
}
```

---

## 💡 MẸO LẬP TRÌNH

### 1. Tách Module
```cpp
// Module quản lý sản phẩm
void ThemSanPham();
void XoaSanPham();
void SuaSanPham();
void HienThiSanPham();

// Module hóa đơn
void TaoHoaDon();
void XemHoaDon();
void XuatHoaDon();

// Module giảm giá
float TinhGiamGia();
```

### 2. Validate Đầu Vào
```cpp
// Kiểm tra giá
if (donGia < 0) {
    cout << "Don gia khong hop le!" << endl;
    return;
}

// Kiểm tra số lượng
if (soLuong <= 0) {
    cout << "So luong phai lon hon 0!" << endl;
    return;
}

// Kiểm tra tồn kho
if (soLuong > tonKho) {
    cout << "Khong du ton kho!" << endl;
    return;
}
```

### 3. Sử Dụng Const
```cpp
const float VAT_RATE = 0.10;  // 10%
const int MAX_SANPHAM = 100;
const int MAX_CHITIET = 50;

// Tính VAT
float vat = tongTien * VAT_RATE;
```

---

## 🎯 ÁP DỤNG VÀO DỰ ÁN KHÁC

### 1. Quản Lý Nhà Hàng
**Tương tự:**
- Sản phẩm → Món ăn
- Hóa đơn → Order
- Chi tiết hóa đơn → Chi tiết order
- Giảm giá → Giảm giá khách hàng thân thiết

**Thêm:**
- Bàn ăn (Table)
- Nhân viên phục vụ (Waiter)
- Tip (tiền boa)

### 2. Quản Lý Thuê Phòng Trọ
**Tương tự:**
- Sản phẩm → Phòng
- Hóa đơn → Hợp đồng thuê
- Giảm giá → Giảm giá thuê dài hạn

**Thêm:**
- Tiền điện, nước
- Tiền cọc
- Hạn thanh toán

### 3. Quản Lý Phòng Gym
**Tương tự:**
- Sản phẩm → Gói tập
- Hóa đơn → Hóa đơn đăng ký
- Giảm giá → Khuyến mãi

**Thêm:**
- Thời hạn gói tập
- PT (Personal Trainer)
- Lịch tập

### 4. Quản Lý Đặt Vé Xem Phim
**Tương tự:**
- Sản phẩm → Ghế ngồi
- Hóa đơn → Vé
- Giảm giá → Giảm giá sinh viên, người cao tuổi

**Thêm:**
- Phim (Movie)
- Suất chiếu (Showtime)
- Phòng chiếu (Room)
- Combo bắp nước

---

## 🧮 CÔNG THỨC TOÁN HỌC QUAN TRỌNG

### 1. Tính Phần Trăm
```
Giảm giá = Tổng tiền × (Phần trăm / 100)
```

### 2. Làm Tròn
```cpp
// Làm tròn đến 2 chữ số thập phân
float LamTron(float so) {
    return (int)(so * 100 + 0.5) / 100.0;
}
```

### 3. Tính Trung Bình
```cpp
float TinhTrungBinhDonGia(SanPham* dsSP, int demSP) {
    if (demSP == 0) return 0.0;

    float tong = 0.0;
    for (int i = 0; i < demSP; i++) {
        tong += dsSP[i].donGia;
    }

    return tong / demSP;
}
```

---

## ✅ CHECKLIST HOÀN THÀNH

- [ ] Định nghĩa struct SanPham, ChiTietHoaDon, HoaDon
- [ ] Viết hàm StringToFloat và FloatToString
- [ ] Implement 4 loại giảm giá
- [ ] Viết hàm tạo hóa đơn hoàn chỉnh
- [ ] Kiểm tra tồn kho trước khi bán
- [ ] Tính VAT 10%
- [ ] Xuất hóa đơn ra file
- [ ] Cập nhật tồn kho sau khi bán
- [ ] Định dạng hóa đơn đẹp
- [ ] Test với nhiều trường hợp

---

## 🚀 NÂNG CAO (TÙY CHỌN)

1. **Tìm kiếm sản phẩm theo tên** - Dùng thuật toán tìm kiếm chuỗi
2. **Thống kê doanh thu theo ngày** - Đọc tất cả hóa đơn và tính tổng
3. **Sản phẩm bán chạy nhất** - Đếm số lượng bán của từng sản phẩm
4. **In mã vạch** - Sinh mã vạch từ mã sản phẩm
5. **Lịch sử hóa đơn** - Lưu tất cả hóa đơn vào 1 file master
6. **Khách hàng thân thiết** - Tích điểm và giảm giá theo điểm

---

## 📚 KIẾN THỨC BỔ SUNG

### Xử Lý Số Thập Phân
- Luôn sử dụng `float` hoặc `double` cho tiền
- Làm tròn khi hiển thị: 2 chữ số thập phân
- Cẩn thận với phép so sánh float (dùng epsilon)

### Quản Lý Bộ Nhớ
```cpp
// Cấp phát động
HoaDon* hd = new HoaDon;
hd->dsChiTiet = new ChiTietHoaDon[50];

// Giải phóng
delete[] hd->dsChiTiet;
delete hd;
```

### Error Handling
- Kiểm tra file có mở được không
- Validate tất cả input từ người dùng
- Xử lý trường hợp chia cho 0
- Kiểm tra mảng không vượt quá giới hạn

---

**Made with ❤️ for students | Phù hợp sinh viên trung bình - khá**
