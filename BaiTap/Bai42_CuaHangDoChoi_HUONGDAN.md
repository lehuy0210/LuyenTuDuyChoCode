# BÀI 42: CỬA HÀNG ĐỒ CHƠI

## 🎯 MỤC TIÊU
Quản lý cửa hàng đồ chơi với phân loại độ tuổi và gói quà.

## 📋 TÍNH NĂNG

### 1. Phân loại đồ chơi
- **Theo loại**: Giáo dục, Vận động, Sáng tạo
- **Theo độ tuổi**: 0-3, 3-6, 6-12, 12+

### 2. Tìm kiếm
- Lọc theo độ tuổi phù hợp

### 3. Mua hàng
- Chọn nhiều món
- Gói quà (3 mức):
  - Không gói: 0đ
  - Đơn giản: 20k
  - Cao cấp: 50k

### 4. Khuyến mãi
- **Sinh nhật**: Giảm 10% khi mua quà sinh nhật

## 💡 PATTERN

### Age-based filtering
```cpp
if (doTuoi == "3-6") {
    // Show suitable toys
}
```

### Gift wrapping service
```cpp
tongTien = tienHang + phiGoiQua;
```

### Occasion-based discount
```cpp
if (laSinhNhat)
    tongTien *= 0.90;  // -10%
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Bookstore (age groups)
- Kids clothing
- Educational tools
- Baby products

**Mở rộng:**
- Toy rental service
- Educational content
- Safety certifications
- Wish list feature
