# BÀI 32: CỬA HÀNG ĐIỆN MÁY

## 🎯 MỤC TIÊU
Quản lý cửa hàng điện máy với bán hàng trả góp và bảo hành.

## 📋 TÍNH NĂNG

### 1. Quản lý sản phẩm
- Tên, hãng, model
- Giá, tồn kho
- Thời hạn bảo hành
- Số lượng đã bán

### 2. Bán hàng
- **Trả tiền mặt**: Giảm 3%
- **Trả góp 0%**: Chọn 6/12/24 tháng
- Ghi serial/IMEI
- Tự động giảm tồn kho

### 3. Kiểm tra bảo hành
- Tra cứu bằng serial/IMEI
- Hiển thị thông tin mua hàng
- Thời hạn bảo hành

### 4. Thống kê
- Top sản phẩm bán chạy
- Sắp xếp theo số lượng bán

## 💡 PATTERN

### Payment options
```cpp
if (tienMat)
    tongTien *= 0.97;  // -3% discount
else
    tienHangThang = tongTien / kyTraGop;  // 0% installment
```

### Warranty tracking
```cpp
struct HoaDonBan {
    string serial;  // Unique identifier
    string ngayMua;
};
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Cửa hàng laptop
- Cửa hàng đồ điện tử
- Showroom ô tô
- Cửa hàng nội thất

**Mở rộng:**
- So sánh sản phẩm
- Đánh giá khách hàng
- Lịch sử sửa chữa
- Trade-in cũ lấy mới
