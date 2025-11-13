# BÀI 6: QUẢN LÝ KHÁCH SẠN

## 📋 Mô Tả Bài Toán
Xây dựng hệ thống quản lý khách sạn bao gồm:
- Quản lý phòng theo loại
- Đặt phòng với tiền cọc
- Check-in/Check-out
- Tính tiền phòng theo số ngày
- Xuất hóa đơn thanh toán

## 🎯 Khái Niệm Áp Dụng
- ✅ Hotel management system
- ✅ Room booking (đặt phòng)
- ✅ Check-in/Check-out process
- ✅ Deposit handling (xử lý tiền cọc)
- ✅ Stay duration calculation (tính số ngày ở)

---

## 🏗️ PHÂN TÍCH THIẾT KẾ

### 1. Xác Định Thực Thể

#### 🛏️ Phòng (Room)
```cpp
struct Phong {
    string maPhong;     // 101, 102, 201...
    string loaiPhong;   // Standard, Deluxe, Suite
    int soGiuong;       // 1, 2, 3 giường
    float giaPhong;     // Giá/đêm
    string trangThai;   // Trong, DaDat, DangO
    string moTa;        // PhongDon-ViewThanhPho
};
```

#### 👤 Khách Hàng (Customer)
```cpp
struct KhachHang {
    string maCMND;      // CMND hoặc Passport
    string hoTen;
    string soDienThoai;
    string quocTich;    // VietNam, USA...
};
```

#### 📝 Đặt Phòng (Booking)
```cpp
struct DatPhong {
    string maDatPhong;  // DP1, DP2...
    string maPhong;
    string maCMND;
    string tenKH;
    string ngayNhan;    // dd/mm/yyyy
    string ngayTra;     // dd/mm/yyyy
    int soNgay;
    int soNguoi;
    float tienCoc;      // 30% tổng tiền
    string trangThai;   // DaDat, DaCheckIn, DaCheckOut, DaHuy
};
```

#### 🧾 Hóa Đơn (Invoice)
```cpp
struct HoaDon {
    string maHoaDon;
    string maDatPhong;
    string maPhong;
    string tenKH;
    string ngayCheckIn;
    string ngayCheckOut;
    int soNgay;
    float tienPhong;     // Giá phòng × số ngày
    float tienDichVu;    // Giặt là, mini bar...
    float tienCoc;       // Tiền cọc đã đặt
    float tongTien;
    float conLai;        // Còn phải trả
};
```

### 2. Phân Loại Phòng

| Loại Phòng | Giường | Giá/Đêm | Mô Tả |
|------------|--------|---------|--------|
| Standard | 1-2 | 500,000 | Phòng tiêu chuẩn |
| Deluxe | 2 | 1,000,000 | Phòng VIP |
| Suite | 3+ | 1,500,000 | Phòng hạng sang |

### 3. Trạng Thái Phòng

| Trạng Thái | Ý Nghĩa | Có thể đặt? |
|------------|---------|------------|
| Trống | Phòng đang trống | ✅ Có |
| ĐaDat | Đã có người đặt | ❌ Không |
| ĐangO | Đang có khách ở | ❌ Không |

---

## 🔄 QUY TRÌNH ĐẶT PHÒNG

### Sơ Đồ Luồng
```
Bắt đầu
   ↓
Hiển thị danh sách phòng trống
   ↓
Chọn phòng
   ↓
Kiểm tra phòng trống?
   ↓ Có
Nhập thông tin khách hàng:
   - CMND/Passport
   - Họ tên
   - Số điện thoại
   - Quốc tịch
   ↓
Nhập thông tin đặt phòng:
   - Ngày nhận phòng
   - Ngày trả phòng
   - Số người ở
   ↓
Tính số ngày ở
   ↓
Tính tổng tiền dự kiến
   ↓
Tính tiền cọc (30%)
   ↓
In phiếu đặt phòng
   ↓
Cập nhật trạng thái phòng = "DaDat"
   ↓
Lưu file
   ↓
Kết thúc
```

### Công Thức Tính Toán

```
Số ngày = Ngày trả - Ngày nhận
Tổng tiền dự kiến = Giá phòng × Số ngày
Tiền cọc = Tổng tiền dự kiến × 30%
```

### Ví Dụ Cụ Thể
```
Phòng: 101 - Standard
Giá: 500,000 VND/đêm
Ngày nhận: 15/11/2025
Ngày trả: 18/11/2025
Số ngày: 3 đêm
------------------------
Tổng tiền: 1,500,000 VND
Tiền cọc (30%): 450,000 VND
```

---

## 🚪 QUY TRÌNH CHECK-IN

### Các Bước
1. Nhập mã đặt phòng
2. Xác minh thông tin khách hàng
3. Kiểm tra CMND/Passport
4. Giao chìa khóa phòng
5. Cập nhật trạng thái phòng = "ĐangO"
6. Ghi log check-in

### Code Minh Họa
```cpp
void CheckIn(Phong* dsPhong, int demPhong) {
    string maDatPhong, maPhong;

    // Nhập thông tin
    cout << "Nhap ma dat phong: ";
    cin >> maDatPhong;

    cout << "Nhap ma phong: ";
    cin >> maPhong;

    // Tìm phòng
    int viTri = TimPhongTheoMa(dsPhong, demPhong, maPhong);

    // Kiểm tra trạng thái
    if (dsPhong[viTri].trangThai != "DaDat") {
        cout << "Phong chua duoc dat!" << endl;
        return;
    }

    // Cập nhật
    dsPhong[viTri].trangThai = "DangO";
    LuuFilePhong(dsPhong, demPhong, "DanhSachPhong.txt");

    cout << "Check in thanh cong!" << endl;
}
```

---

## 🚶 QUY TRÌNH CHECK-OUT

### Sơ Đồ Luồng
```
Bắt đầu
   ↓
Nhập mã phòng
   ↓
Kiểm tra phòng đang có người ở?
   ↓ Có
Nhập thông tin:
   - Tên khách
   - Ngày check-in
   - Số ngày ở
   ↓
Tính tiền phòng = Giá × Số ngày
   ↓
Nhập tiền dịch vụ (nếu có)
   ↓
Nhập tiền cọc đã trả
   ↓
Tính:
   Tổng tiền = Tiền phòng + Tiền dịch vụ
   Còn lại = Tổng tiền - Tiền cọc
   ↓
In hóa đơn thanh toán
   ↓
Cập nhật trạng thái phòng = "Trong"
   ↓
Lưu hóa đơn
   ↓
Kết thúc
```

### Các Loại Dịch Vụ Thêm

| Dịch Vụ | Giá |
|---------|-----|
| Giặt là | 50,000 VND |
| Mini bar | 100,000 VND |
| Room service | 200,000 VND |
| Spa | 300,000 VND |
| Ăn sáng | 150,000 VND/người |

---

## 🧾 HÓA ĐƠN THANH TOÁN

### Định Dạng
```
========================================
       KHACH SAN ABC
       123 Nguyen Hue, Quan 1
       Tel: 0123456789
========================================
       HOA DON THANH TOAN
========================================
Ma hoa don: HD1
Phong: 101 - Standard
Khach hang: Nguyen Van A
----------------------------------------
Check in: 15/11/2025
Check out: 18/11/2025
So ngay o: 3 dem
----------------------------------------
Tien phong:         1,500,000 VND
Tien dich vu:         200,000 VND
Tong tien:          1,700,000 VND
Tien coc:             450,000 VND
========================================
CON LAI:            1,250,000 VND
========================================

   CAM ON QUY KHACH!
   HEN GAP LAI!
```

---

## 📊 QUẢN LÝ PHÒNG

### Hiển Thị Phòng Theo Trạng Thái
```cpp
void HienThiPhongTrong(Phong* dsPhong, int demPhong) {
    cout << "===== PHONG TRONG =====" << endl;

    bool coPhongTrong = false;
    for (int i = 0; i < demPhong; i++) {
        if (dsPhong[i].trangThai == "Trong") {
            cout << dsPhong[i].maPhong << " - "
                 << dsPhong[i].loaiPhong << " - "
                 << dsPhong[i].giaPhong << " VND/dem" << endl;
            coPhongTrong = true;
        }
    }

    if (!coPhongTrong) {
        cout << "Het phong!" << endl;
    }
}
```

### Tìm Phòng Theo Tiêu Chí
```cpp
void TimPhongTheoGia(Phong* dsPhong, int demPhong,
                     float giaMin, float giaMax) {
    for (int i = 0; i < demPhong; i++) {
        if (dsPhong[i].trangThai == "Trong" &&
            dsPhong[i].giaPhong >= giaMin &&
            dsPhong[i].giaPhong <= giaMax) {
            // Hiển thị phòng
        }
    }
}
```

---

## 💰 CHÍNH SÁCH TIỀN CỌC

### Quy Định
- **Tiền cọc:** 30% tổng tiền phòng
- **Hoàn cọc:** Nếu hủy trước 3 ngày
- **Không hoàn:** Nếu hủy trong vòng 3 ngày
- **Khấu trừ:** Nếu làm hỏng đồ đạc

### Code Xử Lý
```cpp
float TinhTienCoc(float tongTien) {
    return tongTien * 0.30;
}

bool KiemTraHoanCoc(string ngayHuy, string ngayNhan) {
    int soNgay = TinhSoNgay(ngayHuy, ngayNhan);
    return soNgay >= 3;
}
```

---

## 📅 TÍNH SỐ NGÀY Ở

### Phương Pháp Đơn Giản
```cpp
int TinhSoNgay(const string& ngayBD, const string& ngayKT) {
    // Version đơn giản - trong thực tế cần tính chính xác hơn

    int ngay1, thang1, nam1;
    int ngay2, thang2, nam2;

    TachNgayThangNam(ngayBD, ngay1, thang1, nam1);
    TachNgayThangNam(ngayKT, ngay2, thang2, nam2);

    // Tính số ngày (cần thuật toán phức tạp hơn)
    // Đây chỉ là ví dụ đơn giản

    return 3; // Giả sử 3 ngày
}
```

### Phương Pháp Chính Xác
```cpp
int SoNgayTrongThang(int thang, int nam) {
    if (thang == 2) {
        // Năm nhuận
        if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0)) {
            return 29;
        }
        return 28;
    }

    if (thang == 4 || thang == 6 || thang == 9 || thang == 11) {
        return 30;
    }

    return 31;
}
```

---

## 💡 TÍNH NĂNG NÂNG CAO (TÙY CHỌN)

### 1. Đặt Phòng Theo Nhóm
```cpp
struct DatPhongNhom {
    string maNhom;
    int soPhong;
    string* dsMaPhong;
    float giamGia;  // Giảm giá cho đoàn
};
```

### 2. Khách Hàng Thân Thiết
```cpp
struct KhachThiet {
    string maCMND;
    int soLanO;
    float giamGia;  // VIP: 10%, Gold: 5%
};
```

### 3. Chương Trình Khuyến Mãi
```cpp
float TinhGiamGia(string ngayDat) {
    // Thứ 2-5: Giảm 20%
    // Cuối tuần: Giá gốc
    // Ngày lễ: Tăng 30%
}
```

### 4. Quản Lý Đặt Phòng Online
```cpp
struct DatPhongOnline {
    string maDat;
    string email;
    string maXacNhan;
    bool daXacNhan;
};
```

### 5. Thống Kê Doanh Thu
```cpp
void ThongKeTheoThang(int thang, int nam) {
    // Tổng số phòng đã đặt
    // Doanh thu
    // Tỷ lệ lấp đầy
    // Phòng được ưa chuộng nhất
}
```

### 6. Đánh Giá & Review
```cpp
struct DanhGia {
    string maCMND;
    string maPhong;
    int soSao;      // 1-5 sao
    string nhanXet;
    string ngayDanhGia;
};
```

---

## 📂 CẤU TRÚC FILE

### DanhSachPhong.txt
```
MaPhong,LoaiPhong,SoGiuong,GiaPhong,TrangThai,MoTa
101,Standard,1,500000,Trong,PhongDon-ViewThanhPho
102,Standard,2,700000,Trong,PhongDoi-ViewThanhPho
201,Deluxe,2,1000000,DaDat,PhongVIP-ViewBien
301,Suite,3,1500000,DangO,PhongHangSang-ViewBien
```

### DatPhong.txt
```
MaDatPhong,MaPhong,MaCMND,TenKH,NgayNhan,NgayTra,SoNgay,SoNguoi,TienCoc,TrangThai
DP1,101,123456789,NguyenVanA,15/11/2025,18/11/2025,3,2,450000,DaDat
```

### HoaDon_HD1.txt
```
========================================
       HOA DON THANH TOAN
========================================
Ma: HD1
Phong: 101 - Standard
Khach: Nguyen Van A
Tong tien: 1,700,000 VND
Con lai: 1,250,000 VND
```

---

## 🎯 ÁP DỤNG VÀO DỰ ÁN KHÁC

### 1. Homestay
**Tương tự:**
- Phòng → Nhà
- Check-in → Nhận chìa
- Dịch vụ → Tour du lịch

### 2. Resort
**Tương tự:**
- Thêm: Bể bơi, Nhà hàng
- Gói combo: Phòng + Ăn + Spa

### 3. Nhà Nghỉ
**Tương tự:**
- Đơn giản hóa
- Giá theo giờ
- Không đặt trước

### 4. Coworking Space
**Tương tự:**
- Phòng → Bàn làm việc
- Ngày → Giờ
- Check-in/out → Swipe card

---

## ✅ CHECKLIST HOÀN THÀNH

- [ ] Định nghĩa struct Phong, KhachHang, DatPhong, HoaDon
- [ ] Phân loại phòng (Standard, Deluxe, Suite)
- [ ] Hiển thị phòng trống
- [ ] Đặt phòng với thông tin đầy đủ
- [ ] Tính tiền cọc 30%
- [ ] Check-in: Cập nhật trạng thái
- [ ] Check-out: Tạo hóa đơn
- [ ] Tính tiền phòng + dịch vụ - cọc
- [ ] In hóa đơn đẹp
- [ ] Lưu file đầy đủ
- [ ] Test với dữ liệu mẫu

---

## 💭 CÂU HỎI THẢO LUẬN

1. **Nếu khách muốn ở thêm?**
   - Kiểm tra phòng có đặt tiếp không
   - Gia hạn và tính thêm tiền

2. **Nếu khách check-out sớm?**
   - Tính tiền theo số ngày thực tế
   - Hoàn lại tiền cọc thừa

3. **Nếu phòng bị hỏng?**
   - Tính tiền bồi thường
   - Khấu trừ từ tiền cọc

4. **Booking engine?**
   - Tích hợp Agoda, Booking.com
   - API đồng bộ tồn kho

5. **Quản lý nhiều chi nhánh?**
   - Thêm trường `maChinh Hanh`
   - Quản lý tập trung

---

**Made with ❤️ for students | Hotel Management System**
