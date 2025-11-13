# BÀI 139: QUAN LY SHOP THUOC BAC

## 📚 Mô tả
Hệ thống quản lý bài 139.

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
g++ Bai139_QuanLyShopThuocBac.cpp -o Bai139
./Bai139
```
