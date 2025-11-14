# BÀI 101: QUẢN LÝ TRUNG TÂM TIẾNG ANH

## 📚 Mô tả
Hệ thống quản lý trung tâm tiếng Anh với các khóa học: Giao tiếp, TOEIC, IELTS, Trẻ em.

## 🎯 Tính năng
- Quản lý khóa học (4 loại khóa)
- Đăng ký học viên mới
- Đóng học phí
- Giảm giá theo số tháng đăng ký (6 tháng: -10%, 12 tháng: -15%)
- Thống kê học viên và doanh thu

## 📊 Struct

### HocVien
```cpp
struct HocVien {
    string ma;          // "HV1001", "HV1002"...
    string hoTen;
    string sdt;
    string email;
    string khoaHoc;     // "Tieng Anh Giao Tiep", "TOEIC", "IELTS", "Tre Em"
    int soThang;        // Số tháng đăng ký
    float hocPhi;       // Tổng học phí
    bool daDongTien;
};
```

### KhoaHoc
```cpp
struct KhoaHoc {
    string ten;
    float giaThanh;     // VND/tháng
    int soTiet;         // Số tiết/tháng
};
```

## 💰 Bảng giá

| Khóa học | Giá/tháng | Số tiết/tháng |
|----------|-----------|---------------|
| Tiếng Anh Giao Tiếp | 2,000,000 VND | 24 tiết |
| TOEIC | 2,500,000 VND | 28 tiết |
| IELTS | 3,500,000 VND | 32 tiết |
| Trẻ Em | 1,800,000 VND | 20 tiết |

## 🎁 Chính sách giảm giá

- **6-11 tháng**: Giảm 10%
- **12+ tháng**: Giảm 15%

## 🔧 Hàm chính

### 1. KhoiTaoKhoaHoc()
Khởi tạo 4 khóa học mặc định.

### 2. DangKyHocVien()
- Tự động sinh mã HV1001++
- Chọn khóa học
- Nhập số tháng đăng ký
- Tính học phí với giảm giá

### 3. DongHocPhi()
- Tìm học viên theo mã
- Hiển thị thông tin học phí
- Xác nhận đóng tiền

### 4. ThongKe()
Hiển thị tổng học viên, đã đóng, chưa đóng, doanh thu.

## 📝 Ví dụ

### Input:
```
Đăng ký: Nguyen Van A
Khóa: IELTS
Số tháng: 12
```

### Tính toán:
```
Học phí gốc = 3,500,000 × 12 = 42,000,000 VND
Giảm 15% = 42,000,000 × 0.85 = 35,700,000 VND
```

### Output:
```
Đăng ký thành công! Học phí: 35,700,000 VND
```

## 🚀 Cách chạy

```bash
g++ Bai101_QuanLyTrungTamTiengAnh.cpp -o Bai101
./Bai101
```

## 💡 Kiến thức áp dụng
- Struct lồng nhau
- Giảm giá theo số lượng
- Quản lý trạng thái thanh toán
- Thống kê doanh thu
- String manipulation
