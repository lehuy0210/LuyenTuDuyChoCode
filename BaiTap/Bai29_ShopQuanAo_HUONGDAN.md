# BÀI 29: SHOP QUẦN ÁO

## 🎯 MỤC TIÊU
Quản lý cửa hàng quần áo với bán hàng nhiều món, giảm giá và đổi trả.

## 📋 TÍNH NĂNG

### 1. Quản lý sản phẩm
- Loại (áo, quần, váy, đầm...)
- Size (S, M, L, XL hoặc số)
- Màu sắc
- Giá và tồn kho

### 2. Bán hàng
- Chọn nhiều sản phẩm
- Mỗi món có số lượng
- Giảm giá tự động:
  - Mua ≥ 3 món: -10%
  - Mua ≥ 5 món: -15%

### 3. Đổi trả hàng
- Tìm hóa đơn theo mã
- Hoàn tiền
- Cập nhật lại tồn kho

## 💡 PATTERN

### Quantity-based discount
```cpp
if (soMon >= 5) giamGia = 0.15;
else if (soMon >= 3) giamGia = 0.10;
tongTien *= (1 - giamGia);
```

### Return/refund management
```cpp
struct HoaDon {
    bool daDoiTra;
};
// Restore inventory on return
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Cửa hàng giày dép
- Shop phụ kiện
- Cửa hàng mỹ phẩm
- Cửa hàng đồ chơi

**Mở rộng:**
- Quản lý size chart
- Wishlist
- Flash sale
- Loyalty points
