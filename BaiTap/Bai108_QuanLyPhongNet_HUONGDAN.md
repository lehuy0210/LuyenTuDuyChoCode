# BÀI 108: QUAN LY PHONG NET

## 📚 Mô tả
Hệ thống quản lý bài 108.

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
g++ Bai108_QuanLyPhongNet.cpp -o Bai108
./Bai108
```

## 💡 Kiến thức
- Business management
- Invoice generation
- Inventory tracking
