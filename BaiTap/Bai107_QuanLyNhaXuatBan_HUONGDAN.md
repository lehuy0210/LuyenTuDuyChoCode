# BÀI 107: QUAN LY NHA XUAT BAN

## 📚 Mô tả
Hệ thống quản lý bài 107.

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
g++ Bai107_QuanLyNhaXuatBan.cpp -o Bai107
./Bai107
```

## 💡 Kiến thức
- Business management
- Invoice generation
- Inventory tracking
