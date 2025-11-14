# BÀI 36: CO-WORKING SPACE

## 🎯 MỤC TIÊU
Quản lý không gian làm việc chung với thuê linh hoạt và thẻ thành viên.

## 📋 TÍNH NĂNG

### 1. Loại vị trí
- Bàn đơn (1 người)
- Phòng họp (8-12 người)
- Phòng riêng (4 người)

### 2. Thuê linh hoạt
- Theo giờ
- Theo ngày
- Theo tháng

### 3. Dịch vụ thêm
- In ấn (10k/trang)
- Cà phê (30k/ly)
- Đỗ xe (20k/ngày)

### 4. Thẻ thành viên
- Basic: Giảm 10%
- Premium: Giảm 20%

## 💡 PATTERN

### Flexible pricing tiers
```cpp
giaGio, giaNgay, giaThang;
// Customer chooses billing period
```

### Membership discount
```cpp
if (isThanhVien)
    tongTien *= (1 - giamGia);
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Meeting room rental
- Event venue
- Storage units
- Equipment rental

**Mở rộng:**
- Đặt chỗ trước online
- Hot desk vs fixed desk
- Community events
- Networking features
