# BÀI 106: QUAN LY SHOP GIAY DEP

## 📚 Mô tả
Hệ thống quản lý bài 106.

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
g++ Bai106_QuanLyShopGiayDep.cpp -o Bai106
./Bai106
```

## 💡 Kiến thức
- Business management
- Invoice generation
- Inventory tracking
