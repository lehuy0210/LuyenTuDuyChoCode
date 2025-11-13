# BÀI 138: QUAN LY TRUNG TAM KY NANG MEM

## 📚 Mô tả
Hệ thống quản lý bài 138.

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
g++ Bai138_QuanLyTrungTamSkills.cpp -o Bai138
./Bai138
```
