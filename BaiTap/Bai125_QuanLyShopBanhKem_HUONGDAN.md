# BÀI 125: QUAN LY SHOP BANH KEM

## 📚 Mô tả
Hệ thống quản lý bài 125.

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
g++ Bai125_QuanLyShopBanhKem.cpp -o Bai125
./Bai125
```

## 💡 Kiến thức
- Product management
- Billing system
- Inventory tracking
