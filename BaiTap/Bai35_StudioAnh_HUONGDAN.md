# BÀI 35: STUDIO ẢNH

## 🎯 MỤC TIÊU
Quản lý studio ảnh với đặt lịch, gói dịch vụ và thanh toán cọc.

## 📋 TÍNH NĂNG

### 1. Gói chụp
- Số ảnh
- Phục trang (có/không)
- Trang điểm (có/không)
- Giá gói

### 2. Đặt lịch
- Chọn gói chụp
- Chọn ngày giờ
- Đặt cọc 30%

### 3. Thanh toán
- Hiển thị số tiền còn lại
- Thanh toán đủ
- Cập nhật trạng thái

### 4. Quản lý lịch
- Danh sách lịch đã đặt
- Trạng thái: Đã cọc/Đã chụp/Hoàn thành

## 💡 PATTERN

### Deposit system
```cpp
datCoc = tongTien * 0.30;
conLai = tongTien - datCoc;
```

### Package tiers
```cpp
struct GoiChup {
    int soAnh;
    bool coPhucTrang, coTrangDiem;
    float gia;
};
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Studio makeup
- Video production
- Event photography
- Venue booking

**Mở rộng:**
- Quản lý album ảnh
- In ảnh, làm photobook
- Chỉnh sửa ảnh
- Đánh giá dịch vụ
