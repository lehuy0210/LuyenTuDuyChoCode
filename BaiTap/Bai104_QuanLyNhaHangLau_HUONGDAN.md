# BÀI 104: QUAN LY NHA HANG LAU

## 📚 Mô tả
Hệ thống quản lý bài 104.

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
g++ Bai104_QuanLyNhaHangLau.cpp -o Bai104
./Bai104
```

## 💡 Kiến thức
- Business management
- Invoice generation
- Inventory tracking
