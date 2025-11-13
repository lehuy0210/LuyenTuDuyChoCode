# BÀI 41: CỬA HÀNG MỸ PHẨM

## 🎯 MỤC TIÊU
Quản lý cửa hàng mỹ phẩm với combo set và tích điểm.

## 📋 TÍNH NĂNG

### 1. Quản lý sản phẩm
- Loại (son, phấn, sữa rửa mặt, kem dưỡng...)
- Hãng (3CE, Laneige, Cetaphil...)
- Hạn sử dụng

### 2. Combo set
- Nhóm nhiều sản phẩm
- Giá combo rẻ hơn mua lẻ
- Ví dụ: Combo trang điểm cơ bản

### 3. Tích điểm thành viên
- 100 VND = 1 điểm
- Điểm tích lũy

### 4. Mua hàng
- Mua lẻ hoặc combo
- Tự động tích điểm nếu là thành viên

## 💡 PATTERN

### Bundle discount
```cpp
giaCombo < tongGiaLe;  // Incentive to buy bundle
```

### Loyalty points
```cpp
diemThem = tongTien / 100;
diemTichLuy += diemThem;
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Skincare shop
- Perfume store
- Fashion boutique
- Supplement store

**Mở rộng:**
- Đổi điểm lấy quà
- Flash sale
- Beauty tips blog
- Virtual try-on
