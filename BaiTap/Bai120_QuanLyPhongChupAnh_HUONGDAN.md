# BÀI 120: QUAN LY PHONG CHUP ANH

## 📚 Mô tả
Hệ thống quản lý bài 120.

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
g++ Bai120_QuanLyPhongChupAnh.cpp -o Bai120
./Bai120
```

## 💡 Kiến thức
- Order management
- Customer information
- Sales tracking
