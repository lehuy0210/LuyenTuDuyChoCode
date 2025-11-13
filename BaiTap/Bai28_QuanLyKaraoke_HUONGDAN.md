# BÀI 28: QUẢN LÝ KARAOKE

## 🎯 MỤC TIÊU
Quản lý karaoke với đặt phòng theo giờ, gọi món và thanh toán.

## 📋 TÍNH NĂNG

### 1. Quản lý phòng
- Loại phòng: Thường, VIP
- Số chỗ ngồi
- Giá theo giờ
- Trạng thái (trống/đang dùng)

### 2. Đặt phòng
- Chọn phòng trống
- Nhập thông tin khách
- Ghi giờ vào

### 3. Gọi món
- Menu đồ ăn/nước
- Gắn với số phòng
- Tính tổng tiền đồ

### 4. Thanh toán
- Nhập giờ ra
- Tính số giờ (làm tròn 0.5h)
- Tổng = Tiền phòng + Tiền đồ

## 💡 PATTERN

### Time-based billing + F&B
```cpp
tongTien = (soGio * giaPhong) + tienDoAn
```

### Rounding time
```cpp
if (tongPhut % 60 > 0) soGio += 0.5;  // Round up to 0.5h
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Billiards/Pool
- Bowling
- Game center
- VR entertainment

**Mở rộng:**
- Đặt phòng trước
- Khuyến mãi giờ vàng
- Thẻ thành viên giảm giá
- Quản lý thiết bị (mic, loa)
