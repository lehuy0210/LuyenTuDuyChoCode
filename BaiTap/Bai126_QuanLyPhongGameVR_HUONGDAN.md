# BÀI 126: QUAN LY PHONG GAME VR

## 📚 Mô tả
Hệ thống quản lý bài 126.

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
g++ Bai126_QuanLyPhongGameVR.cpp -o Bai126
./Bai126
```

## 💡 Kiến thức
- Product management
- Billing system
- Inventory tracking
