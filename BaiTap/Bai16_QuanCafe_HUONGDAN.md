# BÀI 16: QUÁN CAFÉ

## Pattern
- **Quản lý bàn**: Trạng thái Trống/Đang sử dụng
- **Order tích lũy**: Cộng dồn tiền theo món
- **VAT**: Tính 10% khi thanh toán

```cpp
struct Ban {
    int so;
    string trangThai;  // "Trong", "DangSD"
    float tongTien;    // Cộng dồn khi order
};

// Order: Chọn món, số lượng → Cộng vào tongTien
ban.tongTien += gia * soLuong;

// Thanh toán: VAT 10% → Reset bàn về "Trong"
```

Ứng dụng: Nhà hàng, bar, karaoke
