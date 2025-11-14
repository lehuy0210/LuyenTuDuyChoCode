# BÀI 118: QUAN LY NHA TRO SINH VIEN

## 📚 Mô tả
Hệ thống quản lý bài 118.

## 🎯 Tính năng
- Quản lý sản phẩm/dịch vụ
- Tạo order/đơn hàng
- Tính tổng tiền
- Hiển thị danh sách đơn hàng

## 📊 Struct
```cpp
struct Item {
    string ma;
    string ten;
    float gia;
    int soLuong;
};

struct Order {
    string maOrder;
    string tenKH;
    string sdtKH;
    float tongTien;
};
```

## 🚀 Cách chạy
```bash
g++ Bai118_QuanLyNhaTroSinhVien.cpp -o Bai118
./Bai118
```

## 💡 Kiến thức
- Order management
- Customer information
- Sales tracking
