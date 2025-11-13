# BÀI 30: QUẢN LÝ TAXI

## 🎯 MỤC TIÊU
Quản lý đội xe taxi với đặt xe, tính cước và thống kê theo xe/tài xế.

## 📋 TÍNH NĂNG

### 1. Quản lý xe
- Biển số, loại xe (4 chỗ, 7 chỗ)
- Tài xế và SĐT
- Trạng thái (rảnh/đang chạy)

### 2. Đặt xe
- Chọn xe rảnh
- Thông tin khách và điểm đón/đến
- Nhập số km
- Tính cước tự động

### 3. Tính cước
- 2 km đầu: 15,000 VND (giá mở cửa)
- Từ km thứ 3: 12,000 VND/km
- Phụ phí giờ cao điểm: +20%

### 4. Thống kê
- Doanh thu theo xe
- Số cuốc theo tài xế

## 💡 PATTERN

### Distance-based pricing
```cpp
if (soKm <= 2)
    cuoc = GIA_MO_CUA;
else
    cuoc = GIA_MO_CUA + (soKm - 2) * GIA_KM_SAU;
```

### Surge pricing
```cpp
if (gioCaoDiem) cuoc *= 1.20;  // +20% peak hours
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Grab/Uber clone
- Xe ôm công nghệ
- Dịch vụ giao hàng
- Thuê xe theo km

**Mở rộng:**
- GPS tracking
- Rating system
- Multiple pricing tiers
- Driver earnings report
