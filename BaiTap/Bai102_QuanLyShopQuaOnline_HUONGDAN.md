# BÀI 102: QUẢN LÝ SHOP QUÀ TẶNG ONLINE

## 📚 Mô tả
Hệ thống shop quà tặng online (hoa, chocolate, gấu bông) với giao hàng tận nơi.

## 🎯 Tính năng
- Quản lý sản phẩm quà tặng
- Đặt hàng online
- Gửi lời chúc kèm theo
- Tính phí ship (30k, miễn phí nếu > 500k)
- Tra cứu đơn hàng

## 📊 Struct

### QuaTang
```cpp
struct QuaTang {
    string ma;
    string ten;
    string loai;     // "Hoa", "Chocolate", "Gau bong", "Hop qua"
    float gia;
    bool conHang;
};
```

### DonHang
```cpp
struct DonHang {
    string maDH;
    string nguoiGui;
    string nguoiNhan;
    string sdtNhan;
    string diaChiNhan;
    string loiChuc;
    string maSP;
    int soLuong;
    float phiShip;
    float tongTien;
    string trangThai;
};
```

## 💰 Chính sách ship

- Đơn hàng < 500k: Phí ship 30,000 VND
- Đơn hàng >= 500k: **MIỄN PHÍ SHIP**

## 📝 Ví dụ

### Input:
```
Đặt: Bó hoa hồng (350k)
Số lượng: 2
```

### Tính toán:
```
Tiền hàng = 350,000 × 2 = 700,000 VND
Phí ship = 0 (miễn phí vì > 500k)
Tổng = 700,000 VND
```

## 🚀 Cách chạy

```bash
g++ Bai102_QuanLyShopQuaOnline.cpp -o Bai102
./Bai102
```

## 💡 Kiến thức
- E-commerce system
- Shipping fee calculation
- Order tracking
- Free shipping threshold
