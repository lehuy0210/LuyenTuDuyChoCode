# BÀI 31: QUẢN LÝ CHUNG CƯ

## 🎯 MỤC TIÊU
Quản lý chung cư với tính phí hàng tháng và thanh toán.

## 📋 TÍNH NĂNG

### 1. Quản lý căn hộ
- Mã căn hộ (tòa + tầng + số)
- Diện tích (m²)
- Chủ hộ và số người ở
- Số xe (máy + ô tô)
- Trạng thái thanh toán

### 2. Tính phí tháng
- Phí quản lý: 15,000 VND/m²
- Phí xe máy: 70,000 VND/xe
- Phí ô tô: 1,200,000 VND/xe
- Phí dịch vụ (điện, nước...)

### 3. Thanh toán
- Tìm hóa đơn theo mã
- Cập nhật trạng thái đã thanh toán

### 4. Danh sách nợ
- Liệt kê căn hộ chưa thanh toán
- Hiển thị thông tin liên lạc

## 💡 PATTERN

### Multi-component billing
```cpp
tongPhi = phiQuanLy + phiXe + phiDichVu
phiQuanLy = dienTich * GIA_M2
phiXe = soXeMay * GIA_XM + soOto * GIA_OT
```

### Payment tracking
```cpp
struct CanHo {
    bool daThanhToan;
};
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Khu đô thị
- Khu biệt thự
- Tòa văn phòng
- Khu nghỉ dưỡng

**Mở rộng:**
- Quản lý tiện ích (gym, pool)
- Đặt lịch sử dụng tiện ích
- Báo cáo sự cố
- Thông báo BQL
