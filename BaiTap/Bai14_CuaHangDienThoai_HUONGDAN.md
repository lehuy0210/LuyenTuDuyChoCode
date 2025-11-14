# BÀI 14: CỬA HÀNG ĐIỆN THOẠI

## Pattern quan trọng
- **IMEI tracking**: Mỗi máy có mã IMEI duy nhất
- **Bảo hành**: Lưu ngày hết hạn, kiểm tra theo IMEI
- **Tồn kho điện tử**: Mỗi máy bán = giảm 1 tồn kho

## Code mẫu
```cpp
struct DonBan {
    string IMEI;         // Mã máy duy nhất
    string ngayBan;      // 15/01/2025
    string ngayHetBH;    // 15/01/2026 (+12 tháng)
};

void KiemTraBaoHanh() {
    // Tìm theo IMEI
    // Hiển thị thông tin bảo hành
}
```

Ứng dụng: Cửa hàng laptop, tablet, đồ điện tử
