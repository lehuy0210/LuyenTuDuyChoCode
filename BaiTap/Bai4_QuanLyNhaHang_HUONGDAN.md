# BÀI 4: QUẢN LÝ NHÀ HÀNG

## 📋 Mô Tả Bài Toán
Xây dựng hệ thống quản lý nhà hàng bao gồm:
- Quản lý thực đơn (menu)
- Quản lý bàn ăn
- Tạo order (gọi món)
- Tính tiền với phí phục vụ, thuế, tip
- Xuất hóa đơn
- Ghi chú món ăn

## 🎯 Khái Niệm Áp Dụng
- ✅ Restaurant management system
- ✅ Order processing (xử lý đơn hàng)
- ✅ Table management (quản lý bàn)
- ✅ Menu system (hệ thống thực đơn)
- ✅ Service charge calculation (tính phí phục vụ)
- ✅ Multi-level pricing (giá nhiều tầng)

---

## 🏗️ PHÂN TÍCH THIẾT KẾ

### 1. Xác Định Thực Thể (Entities)

#### 🍽️ Món Ăn (Food Item)
```cpp
struct MonAn {
    string maMonAn;     // Mã món
    string tenMonAn;    // Tên món
    string loai;        // Khai vị, Món chính, Tráng miệng, Nước uống
    float donGia;       // Đơn giá
    bool conMon;        // Còn món không
};
```

#### 🪑 Bàn Ăn (Table)
```cpp
struct BanAn {
    int soBan;          // Số bàn
    int soChoNgoi;      // Sức chứa
    string trangThai;   // Trống, ĐangPhucVu, ĐaDat
};
```

#### 📝 Chi Tiết Order
```cpp
struct ChiTietOrder {
    string maMonAn;     // Mã món
    string tenMonAn;    // Tên món
    float donGia;       // Đơn giá
    int soLuong;        // Số lượng
    string ghiChu;      // "Không hành", "Ít cay"...
    float thanhTien;    // Thành tiền
};
```

#### 🧾 Order (Đơn Hàng)
```cpp
struct Order {
    string maOrder;             // Mã order
    int soBan;                  // Số bàn
    string ngayGio;             // Thời gian
    ChiTietOrder* dsChiTiet;    // Danh sách món
    int soLuongChiTiet;         // Số lượng món
    float tongTien;             // Tổng tiền món
    float phiPhucVu;            // Phí phục vụ 10%
    float thue;                 // Thuế 8% VAT
    float tienTip;              // Tiền tip
    float tongThanhToan;        // Tổng cộng
    string trangThai;           // ĐangPhucVu, ĐaThanhToan
};
```

### 2. Thiết Kế Mối Quan Hệ

```
BanAn (1) -----> (1) Order (đang phục vụ)
Order (1) -----> (N) ChiTietOrder
ChiTietOrder (N) -----> (1) MonAn
```

- Một bàn chỉ có một order đang phục vụ
- Một order có nhiều chi tiết (nhiều món)
- Một chi tiết tham chiếu đến một món ăn

---

## 💰 TÍNH TOÁN HÓA ĐƠN NHÀ HÀNG

### Công Thức
```
Thành tiền món = Đơn giá × Số lượng
Tổng tiền = Σ Thành tiền món

Phí phục vụ = Tổng tiền × 10%
Sau phí phục vụ = Tổng tiền + Phí phục vụ

Thuế (VAT) = Sau phí phục vụ × 8%
Tổng thanh toán = Sau phí phục vụ + Thuế + Tip
```

### Ví Dụ Cụ Thể
```
Món 1: Cơm gà     55,000 × 2 = 110,000
Món 2: Phở        50,000 × 1 =  50,000
Món 3: Trà đá     10,000 × 2 =  20,000
----------------------------------------------
Tổng tiền:                      180,000 VND
Phí phục vụ (10%):               18,000 VND
----------------------------------------------
Sau phí phục vụ:                198,000 VND
Thuế VAT (8%):                   15,840 VND
Tip:                             20,000 VND
==============================================
TỔNG THANH TOÁN:                233,840 VND
```

---

## 🔄 QUY TRÌNH TẠO ORDER

### Sơ Đồ Luồng
```
Bắt đầu
   ↓
Hiển thị danh sách bàn
   ↓
Chọn bàn → Kiểm tra bàn trống?
   ↓ Có
Đặt trạng thái bàn = "ĐangPhucVu"
   ↓
Tạo order mới (sinh mã tự động)
   ↓
┌─────────────────────────────────┐
│  Vòng lặp gọi món:              │
│  1. Hiển thị menu theo loại     │
│  2. Nhập mã món                 │
│  3. Kiểm tra còn món?           │
│  4. Nhập số lượng               │
│  5. Nhập ghi chú (tùy chọn)     │
│  6. Thêm vào order              │
│  7. Hỏi tiếp tục?               │
└─────────────────────────────────┘
   ↓
Tính phí phục vụ (10%)
   ↓
Tính thuế VAT (8%)
   ↓
Tính tổng thanh toán
   ↓
In order ra màn hình
   ↓
Lưu order vào file
   ↓
Kết thúc
```

### Code Minh Họa
```cpp
void TaoOrder(MonAn* dsMenu, int demMenu,
              BanAn* dsBan, int demBan,
              int& soOrder) {
    // 1. Chọn bàn
    int soBan;
    cin >> soBan;

    // 2. Kiểm tra bàn
    int viTriBan = TimBanTheoSo(dsBan, demBan, soBan);
    if (dsBan[viTriBan].trangThai != "Trong") {
        cout << "Ban dang duoc su dung!" << endl;
        return;
    }

    // 3. Tạo order
    Order order;
    soOrder++;
    order.maOrder = "ORD" + IntToStr(soOrder);
    order.soBan = soBan;
    order.dsChiTiet = new ChiTietOrder[50];

    // 4. Đặt bàn
    dsBan[viTriBan].trangThai = "DangPhucVu";

    // 5. Gọi món
    char tiepTuc = 'y';
    do {
        // Nhập món...
        // Thêm vào order...

        cout << "Tiep tuc? (y/n): ";
        cin >> tiepTuc;
    } while (tiepTuc == 'y');

    // 6. Tính toán
    order.phiPhucVu = order.tongTien * 0.10;
    order.thue = (order.tongTien + order.phiPhucVu) * 0.08;
    order.tongThanhToan = order.tongTien + order.phiPhucVu + order.thue;

    // 7. In order
    // ...

    // 8. Lưu file
    // ...
}
```

---

## 🍽️ QUẢN LÝ MENU

### Cấu Trúc Menu Theo Loại

**1. Khai Vị (Appetizer)**
- Gỏi cuốn
- Nem rán
- Salata trộn

**2. Món Chính (Main Course)**
- Cơm (gà, sườn, cá)
- Phở
- Bún (bò, riêu)
- Mì xào

**3. Tráng Miệng (Dessert)**
- Chè (chuối, đậu đỏ)
- Yaourt
- Rau câu

**4. Nước Uống (Beverage)**
- Trà đá
- Cà phê
- Nước ép
- Sinh tố

### Hiển Thị Menu Theo Loại
```cpp
void HienThiMenu(MonAn* dsMenu, int demMenu) {
    string loais[] = {"KhaiVi", "MonChinh", "TrangMieng", "NuocUong"};
    string tenLoais[] = {"KHAI VI", "MON CHINH", "TRANG MIENG", "NUOC UONG"};

    for (int l = 0; l < 4; l++) {
        cout << "\n--- " << tenLoais[l] << " ---" << endl;

        for (int i = 0; i < demMenu; i++) {
            if (dsMenu[i].loai == loais[l]) {
                cout << dsMenu[i].maMonAn << "\t"
                     << dsMenu[i].tenMonAn << "\t"
                     << dsMenu[i].donGia << "\t"
                     << (dsMenu[i].conMon ? "Con mon" : "Het mon") << endl;
            }
        }
    }
}
```

---

## 🪑 QUẢN LÝ BÀN ĂN

### Trạng Thái Bàn

| Trạng thái | Ý nghĩa | Có thể gọi món? |
|------------|---------|----------------|
| Trống | Bàn đang trống | ✅ Có |
| ĐangPhucVu | Khách đang ngồi | ❌ Không |
| ĐaDat | Đã đặt trước | ❌ Không |

### Code Quản Lý Trạng Thái
```cpp
// Khi tạo order → set trạng thái
dsBan[viTriBan].trangThai = "DangPhucVu";

// Khi thanh toán xong → set lại
dsBan[viTriBan].trangThai = "Trong";

// Lưu lại file
LuuFileBanAn(dsBan, demBan, "DanhSachBanAn.txt");
```

---

## 📝 GHI CHÚ MÓN ĂN

### Các Loại Ghi Chú Thường Gặp

**Độ cay:**
- "Ít cay"
- "Vừa cay"
- "Nhiều cay"
- "Không cay"

**Nguyên liệu:**
- "Không hành"
- "Không rau mùi"
- "Thêm ớt"
- "Bỏ đường"

**Yêu cầu đặc biệt:**
- "Ăn chay"
- "Không mỡ"
- "Nhiều rau"

### Code Xử Lý Ghi Chú
```cpp
// Nhập ghi chú
string ghiChu;
cout << "Ghi chu (Enter de bo qua): ";
cin.ignore();
getline(cin, ghiChu);

// Lưu vào chi tiết
ct.ghiChu = ghiChu;

// Hiển thị trên hóa đơn
if (order.dsChiTiet[i].ghiChu.length() > 0) {
    cout << "\t* Ghi chu: " << order.dsChiTiet[i].ghiChu << endl;
}
```

---

## 🧾 ĐỊNH DẠNG HÓA ĐƠN

### Mẫu Hóa Đơn Chuẩn
```
========================================
       NHA HANG XYZ
       123 Nguyen Hue, Quan 1
       Tel: 0123456789
========================================
Ma Order: ORD1
Ban so: 5
Ngay gio: 13/11/2025 12:30:45
Nhan vien: Nguyen Van A
----------------------------------------
STT  Ma    Ten Mon      SL  Don Gia    Thanh Tien
----------------------------------------
1    MC001 Com Ga       2   55000      110000
              * Ghi chu: Khong hanh
2    NU001 Tra Da       2   10000       20000
----------------------------------------
Tong tien:                      130000 VND
Phi phuc vu (10%):               13000 VND
Thue VAT (8%):                   11440 VND
Tip:                             10000 VND
========================================
TONG THANH TOAN:                164440 VND
========================================

   CAM ON QUY KHACH!
   HEN GAP LAI!
```

---

## 💡 TÍNH NĂNG NÂNG CAO (TÙY CHỌN)

### 1. Quản Lý Nhân Viên
```cpp
struct NhanVien {
    string maNV;
    string hoTen;
    string viTri;  // PhucVu, ThuNgan, BepTruong
};

// Thêm vào Order
struct Order {
    // ...
    string maNhanVien;  // Nhân viên phục vụ
};
```

### 2. Đặt Bàn Trước
```cpp
void DatBan(BanAn* dsBan, int demBan) {
    int soBan;
    string tenKhach, soDT, thoiGian;

    // Nhập thông tin...

    // Đổi trạng thái
    dsBan[viTri].trangThai = "DaDat";

    // Lưu thông tin đặt bàn
    LuuThongTinDatBan(soBan, tenKhach, soDT, thoiGian);
}
```

### 3. Combo Set Menu
```cpp
struct ComboSet {
    string maCombo;
    string tenCombo;
    string* dsMaMon;      // Danh sách món trong combo
    int soLuongMon;
    float giaCombo;       // Rẻ hơn mua lẻ
};
```

### 4. Chương Trình Khuyến Mãi
```cpp
float TinhGiamGia(Order& order) {
    // Happy hour: 14h-16h giảm 20%
    // Sinh nhật: free tráng miệng
    // Khách VIP: giảm 10%
    // ...
}
```

### 5. Tách Hóa Đơn
```cpp
void TachHoaDon(Order& order, int soNguoi) {
    float tienMoiNguoi = order.tongThanhToan / soNguoi;

    for (int i = 0; i < soNguoi; i++) {
        // Tạo hóa đơn con cho mỗi người
    }
}
```

### 6. Thống Kê Doanh Thu
```cpp
void ThongKeTheoNgay(const string& ngay) {
    // Đọc tất cả order trong ngày
    // Tính tổng doanh thu
    // Món bán chạy nhất
    // Bàn sử dụng nhiều nhất
}
```

---

## 📂 CẤU TRÚC FILE

### Menu.txt
```
MaMonAn,TenMonAn,Loai,DonGia,ConMon
KV001,GoiCuon,KhaiVi,35000,1
MC001,ComGa,MonChinh,55000,1
TM001,CheChuoi,TrangMieng,25000,1
NU001,TraDa,NuocUong,10000,1
```

### DanhSachBanAn.txt
```
SoBan,SoChoNgoi,TrangThai
1,2,Trong
2,4,DangPhucVu
3,6,DaDat
```

### Order_ORD1.txt
```
========================================
       NHA HANG XYZ
========================================
Ma Order: ORD1
Ban so: 5
Ngay gio: 13/11/2025 12:30:45
... (hóa đơn chi tiết)
```

---

## 🎯 ÁP DỤNG VÀO DỰ ÁN KHÁC

### 1. Quán Cà Phê
**Tương tự:**
- Món ăn → Đồ uống
- Bàn ăn → Bàn café
- Order → Bill

**Thêm:**
- Topping (trân châu, thạch...)
- Size (S, M, L)
- Nhiệt độ (Nóng, Lạnh, Đá)

### 2. Đặt Phòng Khách Sạn
**Tương tự:**
- Món ăn → Loại phòng
- Bàn → Phòng
- Order → Booking

**Thêm:**
- Ngày nhận/trả phòng
- Số người
- Dịch vụ thêm

### 3. Spa/Salon
**Tương tự:**
- Món ăn → Dịch vụ
- Bàn → Giường/Ghế
- Order → Appointment

**Thêm:**
- Thời gian dịch vụ
- Nhân viên thực hiện
- Combo gói

### 4. Rạp Chiếu Phim
**Tương tự:**
- Món ăn → Combo bắp nước
- Bàn → Ghế ngồi
- Order → Vé

**Thêm:**
- Suất chiếu
- Phòng chiếu
- Loại ghế (VIP, thường)

---

## 📊 THỐNG KÊ QUAN TRỌNG

### 1. Doanh Thu
```cpp
float TinhDoanhThuNgay(const string& ngay) {
    // Đọc tất cả order trong ngày
    // Tính tổng
}

float TinhDoanhThuThang(int thang, int nam) {
    // Duyệt từng ngày trong tháng
}
```

### 2. Món Bán Chạy
```cpp
void ThongKeMonBanChay() {
    // Đếm số lần xuất hiện của mỗi món
    // Sắp xếp giảm dần
    // Top 10
}
```

### 3. Giờ Cao Điểm
```cpp
void PhanTichGioCaoDiem() {
    // Thống kê số order theo giờ
    // Xác định giờ đông khách
}
```

---

## ✅ CHECKLIST HOÀN THÀNH

- [ ] Định nghĩa struct MonAn, BanAn, Order, ChiTietOrder
- [ ] Đọc/ghi file Menu và Bàn ăn
- [ ] Hiển thị menu theo loại (4 loại)
- [ ] Chọn bàn và kiểm tra trạng thái
- [ ] Tạo order với nhiều món
- [ ] Nhập ghi chú cho món
- [ ] Tính phí phục vụ (10%)
- [ ] Tính thuế VAT (8%)
- [ ] Xuất hóa đơn ra file
- [ ] Cập nhật trạng thái bàn
- [ ] Test với dữ liệu mẫu

---

## 💭 CÂU HỎI THẢO LUẬN

1. **Nếu khách muốn thêm món giữa chừng?**
   - Cần chức năng "Thêm món vào order đang mở"

2. **Nếu khách đổi ý không muốn món nào đó?**
   - Cần chức năng "Xóa món khỏi order"

3. **Nếu nhà hàng có nhiều tầng?**
   - Thêm trường `tang` vào struct BanAn

4. **Xử lý khi hết món?**
   - Set `conMon = false`
   - Không cho phép gọi món đó

5. **Quản lý bếp?**
   - Tạo struct `PhieuBep` gửi cho bếp

---

**Made with ❤️ for students | Restaurant Management System**
