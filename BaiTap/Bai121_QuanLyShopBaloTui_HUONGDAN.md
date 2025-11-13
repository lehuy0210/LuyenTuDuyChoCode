# BÀI 121: QUAN LY SHOP BALO TUI XACH

## 📚 Mô tả
Hệ thống quản lý bài 121.

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
g++ Bai121_QuanLyShopBaloTui.cpp -o Bai121
./Bai121
```

## 💡 Kiến thức
- Product management
- Billing system
- Inventory tracking
