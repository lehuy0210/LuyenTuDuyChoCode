# BÀI 115: QUAN LY PHONG XAM HINH

## 📚 Mô tả
Hệ thống quản lý bài 115.

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
g++ Bai115_QuanLyPhongXamHinh.cpp -o Bai115
./Bai115
```

## 💡 Kiến thức
- Order management
- Customer information
- Sales tracking
