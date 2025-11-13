# BÀI 26: QUẢN LÝ BỆNH VIỆN

## 🎯 MỤC TIÊU
Xây dựng hệ thống quản lý bệnh viện với các chức năng: đăng ký khám, phân phòng bệnh, kê đơn thuốc, thanh toán xuất viện.

## 📋 TÍNH NĂNG

### 1. Đăng ký khám
- Thông tin bệnh nhân (họ tên, SĐT, ngày sinh, địa chỉ)
- Chọn khoa khám (Nội, Ngoại, Sản, Nhi, Mắt...)
- Chọn bác sĩ
- Phí khám

### 2. Phân phòng (nội trú)
- Danh sách phòng trống
- 2 loại: Thường (200k/ngày), VIP (500k/ngày)
- Cập nhật trạng thái phòng

### 3. Kê đơn thuốc
- Nhập tên thuốc, số lượng, đơn giá
- Liên kết với bệnh nhân

### 4. Xuất viện
- Tính tổng tiền:
  - Tiền khám
  - Tiền thuốc
  - Tiền phòng (nếu nội trú)
- Trả phòng

## 💡 PATTERN

### Workflow bệnh viện
```
Đăng ký → Khám bệnh → (Nội trú?) → Kê đơn → Xuất viện → Thanh toán
```

### Công thức tính tiền
```cpp
tongTien = tienKham + tienThuoc + (soNgay * giaPhong)
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Phòng khám tư
- Trung tâm y tế
- Nha khoa
- Thú y

**Mở rộng:**
- Quản lý lịch hẹn khám
- Lưu bệnh án điện tử
- Báo cáo doanh thu theo khoa
- Quản lý nhân viên y tế
