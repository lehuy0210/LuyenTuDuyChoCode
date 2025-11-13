# BÀI 34: SHOP HOA

## 🎯 MỤC TIÊU
Quản lý shop hoa với giảm giá theo độ tươi và bó hoa tùy chọn.

## 📋 TÍNH NĂNG

### 1. Quản lý hoa
- Tên, màu, giá/cây
- Tồn kho
- Số ngày từ lúc nhập

### 2. Bó hoa tự chọn
- Chọn nhiều loại hoa
- Mỗi loại chọn số cây
- Tùy chọn giao hàng

### 3. Giảm giá theo ngày
- Ngày 1: Giá gốc
- Ngày 2: Giảm 15%
- Ngày 3+: Giảm 30%

### 4. Phí giao hàng
- Trong thành phố: 30,000
- Ngoại thành: 50,000
- Tự đến lấy: 0

## 💡 PATTERN

### Time-based discount (perishable goods)
```cpp
if (soNgayNhap >= 3)
    gia *= 0.70;  // -30%
else if (soNgayNhap == 2)
    gia *= 0.85;  // -15%
```

### Custom bundle builder
```cpp
// Customer picks multiple items
while (true) {
    select flower + quantity
}
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Cửa hàng bánh tươi
- Cửa hàng rau củ
- Hải sản tươi sống
- Sản phẩm có hạn sử dụng ngắn

**Mở rộng:**
- Đặt hoa theo dịp (sinh nhật, cưới...)
- Gợi ý bó hoa theo giá
- Hoa khô/giả
- Subscription service
