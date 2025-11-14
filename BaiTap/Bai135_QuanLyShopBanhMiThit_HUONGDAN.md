# BÀI 135: QUAN LY SHOP BANH MI THIT

## 📚 Mô tả
Hệ thống quản lý bài 135.

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
g++ Bai135_QuanLyShopBanhMiThit.cpp -o Bai135
./Bai135
```
