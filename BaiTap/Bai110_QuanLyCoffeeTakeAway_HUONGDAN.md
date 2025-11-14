# BÀI 110: QUAN LY COFFEE TAKE AWAY

## 📚 Mô tả
Hệ thống quản lý bài 110.

## 🎯 Tính năng
- Quản lý sản phẩm/dịch vụ
- Tạo hóa đơn
- Tính tổng tiền

## 📊 Struct
```cpp
struct SanPham {
    string ma;
    string ten;
    float gia;
    int soLuong;
};

struct HoaDon {
    string maHD;
    string maSP;
    int soLuong;
    float tongTien;
};
```

## 🚀 Cách chạy

```bash
g++ Bai110_QuanLyCoffeeTakeAway.cpp -o Bai110
./Bai110
```

## 💡 Kiến thức
- Business management
- Invoice generation
- Inventory tracking
