# BÀI 134: QUAN LY TRUNG TAM GUI XE

## 📚 Mô tả
Hệ thống quản lý bài 134.

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
g++ Bai134_QuanLyTrungTamGuiXe.cpp -o Bai134
./Bai134
```
