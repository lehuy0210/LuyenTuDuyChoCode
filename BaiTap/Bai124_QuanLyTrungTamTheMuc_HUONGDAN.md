# BÀI 124: QUAN LY TRUNG TAM THE MUC

## 📚 Mô tả
Hệ thống quản lý bài 124.

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
g++ Bai124_QuanLyTrungTamTheMuc.cpp -o Bai124
./Bai124
```

## 💡 Kiến thức
- Product management
- Billing system
- Inventory tracking
