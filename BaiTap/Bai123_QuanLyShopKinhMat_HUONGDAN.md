# BÀI 123: QUAN LY SHOP KINH MAT

## 📚 Mô tả
Hệ thống quản lý bài 123.

## 🎯 Tính năng
- Quản lý sản phẩm
- Tạo hóa đơn
- Tính tổng tiền

## 📊 Struct
```cpp
struct Product {
    string id;
    string name;
    float price;
    int stock;
};

struct Bill {
    string billId;
    string customerName;
    float total;
};
```

## 🚀 Cách chạy
```bash
g++ Bai123_QuanLyShopKinhMat.cpp -o Bai123
./Bai123
```

## 💡 Kiến thức
- Product management
- Billing system
- Inventory tracking
