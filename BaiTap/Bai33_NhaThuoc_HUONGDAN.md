# BÀI 33: NHÀ THUỐC

## 🎯 MỤC TIÊU
Quản lý nhà thuốc với phân loại thuốc kê đơn và cảnh báo hết hạn.

## 📋 TÍNH NĂNG

### 1. Quản lý thuốc
- Tên, loại (kê đơn/không kê đơn)
- Đơn vị (viên, hộp, chai, tuýp)
- Giá, tồn kho
- Hạn sử dụng

### 2. Bán thuốc
- Chọn nhiều thuốc
- **Kiểm tra kê đơn**: Thuốc kê đơn cần đơn bác sĩ
- Tự động giảm tồn kho

### 3. Cảnh báo
- Thuốc sắp hết (tồn < 50)
- Thuốc hết hạn/sắp hết hạn

### 4. Thống kê
- Doanh thu theo từng loại thuốc
- Số lượng bán theo đơn vị

## 💡 PATTERN

### Prescription validation
```cpp
if (loai == "KeoDon") {
    if (!coDon) {
        // Không bán được
    }
}
```

### Expiry warning
```cpp
if (hanDung <= "01/2025") {
    // Cảnh báo hết hạn
}
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Quầy thuốc bệnh viện
- Cửa hàng thực phẩm chức năng
- Kho y tế
- Phòng khám tư nhân

**Mở rộng:**
- Quản lý nhà cung cấp
- Tư vấn thuốc tự động
- Lịch sử mua thuốc
- Nhắc nhở uống thuốc
