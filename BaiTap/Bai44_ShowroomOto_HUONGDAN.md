# BÀI 44: SHOWROOM Ô TÔ

## 🎯 MỤC TIÊU
Quản lý showroom ô tô với trả góp và test drive.

## 📋 TÍNH NĂNG

### 1. Quản lý xe
- Hãng, model, năm sản xuất
- Màu, giá
- Trạng thái còn hàng

### 2. Đặt xe
- Đặt cọc 30%
- **Tiền mặt**: Giảm 2%
- **Trả góp**: 36/48/60 tháng (lãi suất 8%/năm)

### 3. Test drive
- Đặt lịch lái thử
- Chọn xe, ngày giờ

## 💡 PATTERN

### Installment calculation
```cpp
laiSuatThang = laiSuatNam / 12;
tienHangThang = soTienVay * formula...
```

### Deposit system
```cpp
datCoc = gia * 0.30;  // 30% upfront
conLai = tongTien - datCoc;
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Xe máy showroom
- Real estate
- Machinery sales
- High-value products

**Mở rộng:**
- Trade-in valuation
- Insurance packages
- Maintenance plans
- Delivery tracking
