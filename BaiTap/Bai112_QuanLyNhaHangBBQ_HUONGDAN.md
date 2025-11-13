# BÀI 112: QUAN LY NHA HANG BBQ

## 📚 Mô tả
Hệ thống quản lý bài 112.

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
g++ Bai112_QuanLyNhaHangBBQ.cpp -o Bai112
./Bai112
```

## 💡 Kiến thức
- Order management
- Customer information
- Sales tracking
