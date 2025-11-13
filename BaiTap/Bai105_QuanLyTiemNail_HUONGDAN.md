# BÀI 105: QUAN LY TIEM NAIL

## 📚 Mô tả
Hệ thống quản lý bài 105.

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
g++ Bai105_QuanLyTiemNail.cpp -o Bai105
./Bai105
```

## 💡 Kiến thức
- Business management
- Invoice generation
- Inventory tracking
