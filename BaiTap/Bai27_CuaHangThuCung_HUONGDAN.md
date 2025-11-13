# BÀI 27: CỬA HÀNG THÚ CƯNG

## 🎯 MỤC TIÊU
Quản lý cửa hàng thú cưng với bán động vật và dịch vụ chăm sóc.

## 📋 TÍNH NĂNG

### 1. Quản lý thú cưng
- Loại (chó, mèo, cá, chim...)
- Giống, màu, tuổi
- Giá bán
- Trạng thái (đã bán/chưa)

### 2. Bán thú cưng
- Chọn thú cưng từ danh sách
- Nhập thông tin khách hàng
- Cập nhật trạng thái đã bán

### 3. Dịch vụ spa/grooming
- Tắm + sấy
- Cắt tỉa lông
- Nhuộm lông
- Khám sức khỏe
- Tiêm phòng

### 4. Thống kê
- Doanh thu bán thú cưng
- Doanh thu dịch vụ
- Tổng doanh thu

## 💡 PATTERN

### Dual revenue stream
```
Doanh thu = Bán thú cưng + Dịch vụ
```

### Status tracking
```cpp
struct ThuCung {
    bool daBan;  // Track sold status
};
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Cửa hàng cây cảnh
- Aquarium shop
- Cửa hàng chim cảnh
- Farm animals

**Mở rộng:**
- Quản lý thức ăn, phụ kiện
- Đặt lịch dịch vụ định kỳ
- Chăm sóc thú cưng lưu trú
- Thẻ thành viên
