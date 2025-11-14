# BÀI 39: CỬA HÀNG BÁNH

## 🎯 MỤC TIÊU
Quản lý cửa hàng bánh với bán sẵn và đặt custom.

## 📋 TÍNH NĂNG

### 1. Bán bánh sẵn
- Bánh sandwich, croissant, su kem...
- Giảm giá theo giờ:
  - 18h-20h: Giảm 30%
  - Sau 20h: Giảm 50%

### 2. Đặt bánh sinh nhật
- Chọn loại (Mousse, Tiramisu...)
- Chọn số tầng (1/2/3)
- Chọn vị kem phủ
- In chữ lên bánh (+50k)
- Giao hàng (+30k)

### 3. Giá bánh custom
- 1 tầng: 350k
- 2 tầng: 650k
- 3 tầng: 950k

## 💡 PATTERN

### Time-of-day pricing (perishables)
```cpp
if (gio >= 20) gia *= 0.50;      // -50%
else if (gio >= 18) gia *= 0.70; // -30%
```

### Custom product builder
```cpp
tongTien = giaBanh + phiInChu + phiGiao;
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Coffee shop
- Pizza shop
- Sandwich shop
- Any food with expiry

**Mở rộng:**
- Đặt bánh cưới
- Bánh kem hình thú
- Tư vấn dinh dưỡng
- Subscription service
