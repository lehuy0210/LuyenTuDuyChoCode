# BÀI 12: HỆ THỐNG QUẢN LÝ NGÂN HÀNG

## 📋 TỔNG QUAN

Hệ thống ngân hàng cơ bản với:
- **Mở tài khoản**: STK 10 số tự động, số dư tối thiểu 50k
- **Gửi tiền**: Nạp tiền vào tài khoản
- **Rút tiền**: Rút tiền (giữ tối thiểu 50k)
- **Chuyển khoản**: Chuyển tiền giữa tài khoản (phí 0.1%)
- **Lịch sử**: Theo dõi giao dịch
- **Thống kê**: Tổng tiền gửi, tài khoản lớn nhất

---

## 🎯 CÁC KHÁI NIỆM QUAN TRỌNG

### 1. **Tạo STK 10 số tự động**

```cpp
string TaoSoTKMoi() {
    int maxNum = 1000000000;  // Bắt đầu từ 1 tỷ
    for (int i = 0; i < soLuongTK; i++) {
        int num = StrToInt(dsTaiKhoan[i].soTK);
        if (num >= maxNum) maxNum = num + 1;
    }
    return IntToStr(maxNum);
}
```

**Kết quả**: 1000000001, 1000000002, 1000000003...

---

### 2. **Chuyển khoản với phí**

```cpp
float soTien = 1000000;
float phiChuyen = soTien * 0.001;  // 0.1%
if (phiChuyen < 1000) phiChuyen = 1000;  // Tối thiểu 1k

float tongTru = soTien + phiChuyen;

tkNguon->soDu -= tongTru;  // Trừ cả phí
tkNhan->soDu += soTien;    // Nhận không phí
```

**Ví dụ**:
- Chuyển 1 triệu: Phí = 1,000 VND
- Chuyển 10 triệu: Phí = 10,000 VND
- Chuyển 100 triệu: Phí = 100,000 VND

---

### 3. **Validation tài khoản**

```cpp
// Kiểm tra tồn tại
if (tk == NULL) {
    cout << "[LOI] Khong tim thay tai khoan!\n";
    return;
}

// Kiểm tra trạng thái
if (tk->trangThai != "HoatDong") {
    cout << "[LOI] Tai khoan da bi khoa!\n";
    return;
}

// Kiểm tra số dư tối thiểu
if (tk->soDu - soTien < 50000) {
    cout << "[LOI] So du toi thieu 50,000 VND!\n";
    return;
}
```

---

### 4. **Lưu lịch sử giao dịch**

```cpp
struct GiaoDich {
    string maGD;
    string soTK;
    string loaiGD;        // "GuiTien", "RutTien", "ChuyenKhoan"
    float soTien;
    string soTKNhan;      // Nếu chuyển khoản
    string ngayGD;
    string gioGD;
    string moTa;
};

void LuuGiaoDich(const GiaoDich& gd) {
    // Thêm vào mảng dynamic
    // ...
}
```

---

## 📊 DỮ LIỆU MẪU

### File: DanhSachTaiKhoan.txt
```
SoTK,HoTen,CMND,SDT,SoDu,NgayMo,TrangThai
1000000001,Nguyen Van A,123456789,0912345678,5000000,01/01/2025,HoatDong
1000000002,Tran Thi B,987654321,0923456789,15000000,05/01/2025,HoatDong
```

---

## 🎓 ỨNG DỤNG

1. **ATM**: Rút tiền, chuyển khoản, kiểm tra số dư
2. **E-wallet**: Ví điện tử (Momo, Zalo Pay)
3. **Fintech**: Ứng dụng tài chính

---

## 💡 MỞ RỘNG

1. **Lãi suất**: Tính lãi 0.5%/tháng cho số dư > 10 triệu
2. **Thẻ tín dụng**: Hạn mức, nợ, thanh toán
3. **Tiết kiệm**: Gửi có kỳ hạn 6-12 tháng
4. **Vay tiền**: Lãi suất, trả góp hàng tháng
5. **SMS/Email**: Thông báo giao dịch

Chúc thành công! 💰
