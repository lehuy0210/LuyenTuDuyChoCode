# BÀI 38: QUẢN LÝ SÂN BOWLING

## 🎯 MỤC TIÊU
Quản lý sân bowling với thuê làn theo giờ và dịch vụ thêm.

## 📋 TÍNH NĂNG

### 1. Quản lý làn
- 12 làn bowling
- Trạng thái (trống/đang dùng)
- Ghi giờ vào

### 2. Đặt làn
- Chọn số giờ chơi
- Số người chơi
- Thuê giày bowling
- Gọi đồ ăn/nước

### 3. Tính tiền
- Tiền làn: 150k/giờ
- Tiền giày: 30k/đôi
- Đồ ăn/nước

### 4. Trả làn
- Cập nhật trạng thái trống

## 💡 PATTERN

### Lane management
```cpp
struct Lan {
    bool dangDung;
    int gioVao, phutVao;
};
```

### Bundle pricing
```cpp
tongTien = tienLan + tienGiay + tienDoAn;
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Billiards hall
- Ice skating rink
- Arcade games
- Mini golf

**Mở rộng:**
- Scoring system
- Tournament mode
- Loyalty program
- Online booking
