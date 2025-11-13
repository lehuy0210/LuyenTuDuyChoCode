# BÀI 40: QUÁN TRÀ SỮA

## 🎯 MỤC TIÊU
Quản lý quán trà sữa với menu linh hoạt và khuyến mãi.

## 📋 TÍNH NĂNG

### 1. Menu đa dạng
- Trà sữa
- Trái cây
- Sữa chua
- Matcha

### 2. Tùy chọn
- Size: M, L, XL (giá khác nhau)
- Topping: Trân châu, thạch, pudding, kem cheese
- Tối đa 5 loại topping/món

### 3. Khuyến mãi
- **Mua 2 tặng 1**: Tặng món rẻ nhất khi mua ≥ 3 món

### 4. Đặt món
- Chọn nhiều món
- Mỗi món có size + topping riêng

## 💡 PATTERN

### Size-based pricing
```cpp
if (size == "M") gia = giaM;
else if (size == "L") gia = giaL;
else gia = giaXL;
```

### Add-ons pricing
```cpp
tongGia = giaMonChinh + giaTopping;
```

### Buy-2-Get-1 promo
```cpp
if (soMon >= 3)
    tongTien -= minGia;  // Free cheapest item
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Coffee shop
- Smoothie bar
- Fast food
- Ice cream shop

**Mở rộng:**
- Loyalty card
- Pre-order online
- Seasonal drinks
- Custom sweetness level
