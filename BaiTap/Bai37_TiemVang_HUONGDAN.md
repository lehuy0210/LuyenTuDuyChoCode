# BÀI 37: TIỆM VÀNG

## 🎯 MỤC TIÊU
Quản lý tiệm vàng với giá vàng theo ngày và thu mua vàng cũ.

## 📋 TÍNH NĂNG

### 1. Giá vàng
- Giá mua vào (thu mua)
- Giá bán ra (bán sản phẩm)
- Cập nhật theo ngày

### 2. Sản phẩm
- Loại (nhẫn, vòng, dây chuyền...)
- Trọng lượng (chỉ, 1 chỉ = 3.75g)
- Tiền công (craftsmanship)

### 3. Bán sản phẩm
- Giá = Tiền vàng + Tiền công
- Tính theo giá bán ra

### 4. Thu mua vàng cũ
- Tính theo giá mua vào
- Không có tiền công

## 💡 PATTERN

### Commodity pricing
```cpp
giaBan = (trongLuong * giaVang) + tienCong;
giaMua = trongLuong * giaMuaVao;  // No labor cost
```

### Daily price updates
```cpp
struct GiaVang {
    string ngay;
    float giaMuaVao, giaBanRa;
};
```

## 🔄 ÁP DỤNG CHO DỰ ÁN KHÁC

**Pattern này dùng được cho:**
- Silver jewelry
- Diamond shop
- Gemstone trading
- Precious metal exchange

**Mở rộng:**
- Lịch sử giá vàng
- Custom design order
- Trade-in program
- Certificate tracking
