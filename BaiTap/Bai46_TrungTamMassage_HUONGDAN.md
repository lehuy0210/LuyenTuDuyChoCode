# BÀI 46: TRUNG TÂM MASSAGE

## 🎯 MỤC TIÊU
Quản lý trung tâm massage với đặt lịch và tip.

## 📋 TÍNH NĂNG

### 1. Gói dịch vụ
- Massage toàn thân (90 phút)
- Foot massage (45 phút)
- Body + foot (120 phút)
- Hot stone massage

### 2. Đặt lịch
- Chọn gói
- Chọn kỹ thuật viên (KTV)
- Đặt ngày giờ

### 3. Thanh toán
- Giá gói
- Tip (tự nguyện)

## 💡 PATTERN

### Staff selection
```cpp
struct KyThuatVien {
    bool dangRanh;
    int namKinhNghiem;
};
```

### Tipping system
```cpp
tongTien = giaGoi + tip;
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Nail salon
- Hair salon
- Spa services
- Beauty services

**Mở rộng:**
- Rating KTV
- Membership packages
- Add-on services
- Home service
