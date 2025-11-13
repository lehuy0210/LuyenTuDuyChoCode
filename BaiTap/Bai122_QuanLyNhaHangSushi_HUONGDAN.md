# BÀI 122: QUAN LY NHA HANG SUSHI

## 📚 Mô tả
Hệ thống quản lý bài 122.

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
g++ Bai122_QuanLyNhaHangSushi.cpp -o Bai122
./Bai122
```

## 💡 Kiến thức
- Product management
- Billing system
- Inventory tracking
