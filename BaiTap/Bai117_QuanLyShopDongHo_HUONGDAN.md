# BÀI 117: QUAN LY SHOP DONG HO

## 📚 Mô tả
Hệ thống quản lý bài 117.

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
g++ Bai117_QuanLyShopDongHo.cpp -o Bai117
./Bai117
```

## 💡 Kiến thức
- Order management
- Customer information
- Sales tracking
