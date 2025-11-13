# BÀI 109: QUAN LY SHOP PHU KIEN DIEN THOAI

## 📚 Mô tả
Hệ thống quản lý bài 109.

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
g++ Bai109_QuanLyShopPhuKien.cpp -o Bai109
./Bai109
```

## 💡 Kiến thức
- Business management
- Invoice generation
- Inventory tracking
