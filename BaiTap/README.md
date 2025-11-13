# 🎓 BÀI TẬP LẬP TRÌNH C++ - KHÔNG DÙNG BUILT-IN FUNCTIONS

> **Made with ❤️ for students | Phù hợp sinh viên trung bình - khá**

---

## 📚 TỔNG QUAN

Bộ bài tập bao gồm **7 bài** về các hệ thống quản lý thực tế, **KHÔNG sử dụng** `stoi()`, `to_string()`, `stringstream` mà tự viết tất cả các hàm chuyển đổi.

---

## 📋 DANH SÁCH BÀI TẬP

### ✅ Bài 1: Quản Lý Thư Viện Sách
**File:** `Bai1_QuanLyThuVien_v2.cpp` + `Bai1_QuanLyThuVien_HUONGDAN.md`

**Tính năng:**
- Mượn/trả sách với kiểm tra tồn kho
- Quản lý độc giả
- Thống kê sách quá hạn (so sánh ngày)
- Logging với timestamp
- Exception handling

**Khái niệm:** Logging, Exception handling, Date/Time processing

---

### ✅ Bài 2: Quản Lý Bán Hàng POS
**File:** `Bai2_QuanLyBanHang.cpp` + `Bai2_QuanLyBanHang_HUONGDAN.md`

**Tính năng:**
- Quản lý sản phẩm
- Tạo hóa đơn bán hàng
- **4 loại giảm giá:**
  - Phần trăm (%)
  - Cố định (VND)
  - Bậc thang (theo tổng tiền)
  - Combo (theo số lượng)
- Tính VAT (10%)
- Xuất hóa đơn ra file

**Khái niệm:** Business logic, Receipt generation, Discount calculation

---

### ✅ Bài 3: Quản Lý Sinh Viên
**File:** `Bai3_QuanLySinhVien.cpp` + `Bai3_QuanLySinhVien_HUONGDAN.md`

**Tính năng:**
- **CRUD đầy đủ:** Thêm, Xóa, Sửa, Hiển thị
- **Tìm kiếm đa tiêu chí:**
  - Theo mã sinh viên
  - Theo họ tên (substring search)
  - Theo lớp
  - Theo khoảng điểm
- **Sắp xếp:**
  - Theo điểm (Selection Sort)
  - Theo tên (Bubble Sort)
- **Thống kê:**
  - Điểm trung bình chung
  - Điểm cao/thấp nhất
  - Phân loại học lực (Xuất sắc, Giỏi, Khá...)

**Khái niệm:** File I/O, Data validation, Error handling, Sorting, Searching

---

### ✅ Bài 4: Quản Lý Nhà Hàng
**File:** `Bai4_QuanLyNhaHang.cpp` + `Bai4_QuanLyNhaHang_HUONGDAN.md`

**Tính năng:**
- Menu theo 4 loại: Khai vị, Món chính, Tráng miệng, Nước uống
- Quản lý bàn ăn (Trống, ĐangPhucVụ, ĐaDat)
- Tạo order với nhiều món
- **Ghi chú món ăn:** "Không hành", "Ít cay"...
- Tính phí phục vụ (10%)
- Thuế VAT (8%)
- Xuất hóa đơn chi tiết

**Khái niệm:** Order processing, Table management, Multi-level pricing

---

### ✅ Bài 5: Quản Lý Phòng Khám
**File:** `Bai5_QuanLyPhongKham.cpp` + `Bai5_QuanLyPhongKham_HUONGDAN.md`

**Tính năng:**
- Đăng ký bệnh nhân mới (tự động sinh mã BN1001++)
- Quản lý bác sĩ theo chuyên khoa
- Đặt lịch hẹn khám
- Tạo phiếu khám bệnh với chẩn đoán
- Quản lý dịch vụ y tế (Xét nghiệm, Siêu âm, X-quang...)
- Tính tổng tiền = Dịch vụ + Khám + Thuốc
- Lưu hồ sơ bệnh án

**Khái niệm:** Healthcare management, Appointment scheduling, Medical records

---

### ✅ Bài 6: Quản Lý Khách Sạn
**File:** `Bai6_QuanLyKhachSan.cpp` + `Bai6_QuanLyKhachSan_HUONGDAN.md`

**Tính năng:**
- Quản lý phòng (Standard, Deluxe, Suite)
- Giá phòng: 500k, 1tr, 1.5tr/đêm
- Đặt phòng với thông tin khách (CMND, quốc tịch...)
- Tính tiền cọc 30% tự động
- Check-in: Cập nhật trạng thái "Đang ở"
- Check-out:
  - Tính tiền phòng × số ngày
  - Thêm tiền dịch vụ
  - Trừ tiền cọc
  - Xuất hóa đơn

**Khái niệm:** Hotel management, Room booking, Check-in/Check-out process

---

### ✅ Bài 7: Quản Lý Bãi Đỗ Xe
**File:** `Bai7_QuanLyBaiDoXe.cpp`

**Tính năng:**
- Quản lý chỗ đỗ (Xe máy, Ô tô)
- **Vào bãi:** Tạo vé gửi xe tự động
- **Ra bãi:** Tính tiền theo số giờ
- **Bảng giá:**
  - Giờ đầu tiên
  - Giờ tiếp theo
  - Qua đêm (22h-6h)
- Thống kê tỷ lệ lấp đầy
- In vé và hóa đơn

**Khái niệm:** Parking management, Hourly billing, Time calculation

---

## 🔧 HÀM TỰ VIẾT CHUNG

Tất cả các bài đều sử dụng các hàm sau (KHÔNG dùng built-in):

### 1. Chuyển Đổi String ↔ Int
```cpp
int StrToInt(const string& str);      // Thay thế stoi()
string IntToStr(int num);              // Thay thế to_string()
```

### 2. Chuyển Đổi String ↔ Float
```cpp
float StrToFloat(const string& str);   // Parse float từ string
string FloatToStr(float num);          // Float → String (2 chữ số)
```

### 3. Xử Lý Ngày Tháng
```cpp
void TachNgayThangNam(const string& ngayStr, int& ngay, int& thang, int& nam);
int SoSanhNgay(int ngay1, int thang1, int nam1, int ngay2, int thang2, int nam2);
```

### 4. Xử Lý Chuỗi
```cpp
string ToUpper(const string& str);     // Chữ thường → Chữ hoa
bool Contains(const string& str, const string& subStr);  // Tìm chuỗi con
```

---

## 📂 CẤU TRÚC THƯ MỤC

```
BaiTap/
├── Bai1_QuanLyThuVien_v2.cpp
├── Bai1_QuanLyThuVien_HUONGDAN.md
├── Bai2_QuanLyBanHang.cpp
├── Bai2_QuanLyBanHang_HUONGDAN.md
├── Bai3_QuanLySinhVien.cpp
├── Bai3_QuanLySinhVien_HUONGDAN.md
├── Bai4_QuanLyNhaHang.cpp
├── Bai4_QuanLyNhaHang_HUONGDAN.md
├── Bai5_QuanLyPhongKham.cpp
├── Bai5_QuanLyPhongKham_HUONGDAN.md
├── Bai6_QuanLyKhachSan.cpp
├── Bai6_QuanLyKhachSan_HUONGDAN.md
├── Bai7_QuanLyBaiDoXe.cpp
├── DanhSachSach.txt
├── DanhSachDocGia.txt
├── DanhSachSanPham.txt
├── DanhSachSinhVien.txt
├── Menu.txt
├── DanhSachBanAn.txt
├── DanhSachBacSi.txt
├── DanhSachDichVu.txt
├── DanhSachPhong.txt
├── DanhSachChoDoXe.txt
├── BangGia.txt
└── README.md
```

---

## 🚀 CÁCH SỬ DỤNG

### Biên Dịch
```bash
# Linux/Mac
g++ Bai1_QuanLyThuVien_v2.cpp -o Bai1
g++ Bai2_QuanLyBanHang.cpp -o Bai2
g++ Bai3_QuanLySinhVien.cpp -o Bai3
g++ Bai4_QuanLyNhaHang.cpp -o Bai4
g++ Bai5_QuanLyPhongKham.cpp -o Bai5
g++ Bai6_QuanLyKhachSan.cpp -o Bai6
g++ Bai7_QuanLyBaiDoXe.cpp -o Bai7

# Windows (MinGW)
g++ Bai1_QuanLyThuVien_v2.cpp -o Bai1.exe
```

### Chạy
```bash
./Bai1
./Bai2
./Bai3
# ...
```

---

## 📊 THỐNG KÊ

| Tiêu chí | Số lượng |
|----------|----------|
| Tổng số bài | 7 bài |
| Tổng dòng code C++ | ~5500 dòng |
| File hướng dẫn .md | 6 files (~3000 dòng) |
| File dữ liệu mẫu | 11 files |
| Hàm tự viết | 25+ hàm |
| Struct định nghĩa | 30+ structs |

---

## 🎯 PATTERN ÁP DỤNG CHO DỰ ÁN KHÁC

### Từ Bài 1-3 (Cơ bản)
✅ Quản lý đơn giản với CRUD
✅ File I/O cơ bản
✅ Validation và Error handling

### Từ Bài 4 (Nhà hàng)
✅ Quán café, Bar, Food court
✅ Order system với nhiều items
✅ Ghi chú và customization

### Từ Bài 5 (Phòng khám)
✅ Spa/Salon, Nha khoa, Thú y
✅ Appointment scheduling
✅ Service-based billing

### Từ Bài 6 (Khách sạn)
✅ Homestay, Resort
✅ Booking với tiền cọc
✅ Check-in/Check-out workflow

### Từ Bài 7 (Bãi đỗ xe)
✅ Bãi xe thông minh
✅ Time-based billing
✅ Slot management

---

## 💡 KIẾN THỨC HỌC ĐƯỢC

### 1. Không Dùng Built-in
- ✅ Tự viết hàm chuyển đổi String ↔ Int/Float
- ✅ Parse ngày tháng thủ công
- ✅ Xử lý chuỗi không dùng `stringstream`

### 2. Cấu Trúc Dữ Liệu
- ✅ Struct với nhiều trường
- ✅ Mảng động (dynamic array)
- ✅ Con trỏ và quản lý bộ nhớ

### 3. File I/O
- ✅ Đọc/ghi file CSV
- ✅ Append mode (`ios::app`)
- ✅ Parse dòng theo delimiter

### 4. Business Logic
- ✅ Tính toán phức tạp (thuế, phí, giảm giá...)
- ✅ Workflow nhiều bước (booking, check-in, check-out...)
- ✅ State management (trạng thái phòng, bàn, chỗ đỗ...)

### 5. Thuật Toán
- ✅ Tìm kiếm tuyến tính
- ✅ Sắp xếp (Selection Sort, Bubble Sort)
- ✅ Tính toán thời gian (số giờ, số ngày...)

---

## ✅ ĐIỂM MẠNH CỦA BỘ BÀI TẬP

1. **100% tự viết** - Không phụ thuộc built-in functions
2. **Thực tế** - Các hệ thống thực sự được dùng trong đời sống
3. **Code sạch** - Dễ đọc, có comment, module hóa
4. **Đầy đủ** - Có cả code + file .md hướng dẫn chi tiết
5. **Dữ liệu mẫu** - Có sẵn để test ngay
6. **Pattern** - Dễ áp dụng cho dự án khác

---

## 📚 HỌC GÌ TỪ MỖI BÀI?

| Bài | Học được gì? |
|-----|-------------|
| Bài 1 | Logging, Exception, Date comparison |
| Bài 2 | Discount algorithms, VAT calculation |
| Bài 3 | CRUD, Search, Sort, Statistics |
| Bài 4 | Order management, Multi-level pricing |
| Bài 5 | Appointment system, Service billing |
| Bài 6 | Booking với deposit, Check-in/out |
| Bài 7 | Time-based billing, Slot management |

---

## 🎓 PHÙ HỢP CHO

- ✅ Sinh viên năm 1-2 ngành Công nghệ thông tin
- ✅ Học sinh giỏi THPT muốn học trước
- ✅ Người tự học lập trình C++
- ✅ Ôn thi học kỳ, thi cuối kỳ
- ✅ Làm đồ án môn học

---

## 🚀 PHÁT TRIỂN THÊM

Các ý tưởng nâng cao (tùy chọn):

1. **Thêm GUI** - Dùng thư viện SDL hoặc SFML
2. **Database** - Chuyển từ file txt sang SQLite
3. **Multi-threading** - Xử lý đồng thời nhiều order
4. **Network** - Client-Server architecture
5. **Security** - Mã hóa dữ liệu nhạy cảm
6. **API** - RESTful API cho mobile app

---

## 📞 HỖ TRỢ

Nếu gặp vấn đề:
1. Đọc kỹ file `*_HUONGDAN.md` của bài đó
2. Kiểm tra file dữ liệu mẫu đã đúng định dạng chưa
3. Compile với flag `-std=c++11` trở lên
4. Kiểm tra quyền đọc/ghi file

---

## 📝 LICENSE

Code này được chia sẻ miễn phí cho mục đích học tập.

---

**Made with ❤️ for students**
**Chúc bạn học tốt!** 🎓

---

*Last updated: 2025-11-13*
