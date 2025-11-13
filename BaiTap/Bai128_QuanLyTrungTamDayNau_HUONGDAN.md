# BÀI 128: QUAN LY TRUNG TAM DAY NAU AN

## 📚 Mô tả
Hệ thống quản lý bài 128.

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
g++ Bai128_QuanLyTrungTamDayNau.cpp -o Bai128
./Bai128
```

## 💡 Kiến thức
- Product management
- Billing system
- Inventory tracking
