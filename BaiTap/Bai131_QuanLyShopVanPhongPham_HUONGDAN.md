# BÀI 131: QUAN LY SHOP VAN PHONG PHAM

## 📚 Mô tả
Hệ thống quản lý bài 131.

## 🎯 Tính năng
- Thêm items/sản phẩm
- Tạo transaction/giao dịch
- Tính tổng tiền

## 📊 Struct
```cpp
struct Item {
    string id;
    string name;
    float price;
};

struct Transaction {
    string txId;
    string itemId;
    int quantity;
    float amount;
};
```

## 🚀 Cách chạy
```bash
g++ Bai131_QuanLyShopVanPhongPham.cpp -o Bai131
./Bai131
```
