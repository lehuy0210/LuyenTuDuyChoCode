# BÀI 127: QUAN LY SHOP GOM SU THU CONG

## 📚 Mô tả
Hệ thống quản lý bài 127.

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
g++ Bai127_QuanLyShopGomSu.cpp -o Bai127
./Bai127
```

## 💡 Kiến thức
- Product management
- Billing system
- Inventory tracking
