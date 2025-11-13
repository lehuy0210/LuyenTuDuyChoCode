# BÀI 43: TRUNG TÂM NGOẠI NGỮ

## 🎯 MỤC TIÊU
Quản lý trung tâm ngoại ngữ với đăng ký khóa học và học phí.

## 📋 TÍNH NĂNG

### 1. Khóa học
- Ngoại ngữ (Anh, Hán, Nhật, Trung...)
- Trình độ (Beginner, Intermediate, Advanced)
- Thời lượng (tháng)
- Học phí/tháng
- Lịch học

### 2. Đăng ký
- Chọn khóa học
- Kiểm tra số lượng học viên
- Thanh toán học phí

### 3. Học phí
- **Đóng đầy đủ**: Giảm 5%
- **Đóng từng tháng**: Không giảm

### 4. Quản lý
- Danh sách học viên
- Theo dõi công nợ

## 💡 PATTERN

### Capacity management
```cpp
if (soHocVienHienTai >= soHocVienToiDa) {
    // Class full
}
```

### Upfront payment discount
```cpp
if (dongDayDu)
    tongHocPhi *= 0.95;  // -5%
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Music school
- Driving school
- Coding bootcamp
- Fitness classes

**Mở rộng:**
- Online classes
- Placement test
- Progress tracking
- Certificate generation
