# BÀI 47: NHÀ HÀNG BUFFET

## 🎯 MỤC TIÊU
Quản lý nhà hàng buffet với giá theo đầu người và giờ vàng.

## 📋 TÍNH NĂNG

### 1. Giá theo tuổi
- Trẻ em (<  12): 199k
- Người lớn (12-60): 399k
- Cao tuổi (> 60): 299k

### 2. Giờ vàng
- 11h-13h: +20%
- 17h-19h: +20%

### 3. Thời gian
- Giới hạn 90 phút

## 💡 PATTERN

### Age-based pricing
```cpp
tongTien = soTreEm * GIA_TE +
           soNguoiLon * GIA_NL +
           soCaoTuoi * GIA_CT;
```

### Peak hour surcharge
```cpp
if (gioVang)
    tongTien *= 1.20;
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Lẩu buffet
- BBQ buffet
- Theme parks (age-based tickets)
- Cinema (age-based seats)
