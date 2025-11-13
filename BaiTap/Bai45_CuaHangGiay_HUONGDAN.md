# BÀI 45: CỬA HÀNG GIÀY DÉP

## 🎯 MỤC TIÊU
Quản lý cửa hàng giày với size chart và đổi trả.

## 📋 TÍNH NĂNG

### 1. Quản lý giày
- Loại (thể thao, tây, sandal...)
- Hãng (Nike, Adidas...)
- Size chart (EU standard)
- Tồn kho theo từng size

### 2. Bán hàng
- Chọn size cụ thể
- Kiểm tra tồn kho theo size
- **Khuyến mãi**: Mua ≥ 2 đôi giảm 15%

### 3. Đổi size
- Trong 3 ngày kể từ ngày mua
- Tra cứu theo mã hóa đơn

## 💡 PATTERN

### Size-based inventory
```cpp
struct Giay {
    int sizeEU[15];
    int tonKho[15];  // Stock per size
};
```

### Quantity discount
```cpp
if (soDoi >= 2)
    tongTien *= 0.85;  // -15%
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Clothing store (S/M/L/XL)
- Ring shop (size-based)
- Any size-specific products

**Mở rộng:**
- Virtual try-on AR
- Size recommendation
- Shoe care products
- VIP membership
