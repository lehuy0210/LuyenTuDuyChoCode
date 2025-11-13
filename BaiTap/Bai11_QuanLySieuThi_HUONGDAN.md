# BÀI 11: HỆ THỐNG QUẢN LÝ SIÊU THỊ

## 📋 TỔNG QUAN

Hệ thống quản lý siêu thị mini với:
- **Quản lý sản phẩm**: Mã vạch (barcode), tên, giá, tồn kho
- **Nhập hàng**: Cập nhật tồn kho, ghi nhận phiếu nhập
- **Bán hàng**: Quét mã vạch, giỏ hàng, thanh toán
- **Hóa đơn**: VAT 10%, thẻ thành viên giảm 5%
- **Cảnh báo**: Sản phẩm sắp hết hàng
- **Thống kê**: Doanh thu, sản phẩm bán chạy

---

## 🎯 CÁC KHÁI NIỆM QUAN TRỌNG

### 1. **Quản lý tồn kho với ngưỡng cảnh báo**

```cpp
struct SanPham {
    string maSP;          // SP001
    string maVach;        // 8934567890123
    string tenSP;         // "Sua tuoi Vinamilk"
    float giaBan;         // 12000
    int tonKho;           // 50
    int nguongCanhBao;    // 10 (cảnh báo khi < 10)
};

void KiemTraSapHetHang() {
    for (int i = 0; i < soLuongSP; i++) {
        if (dsSanPham[i].tonKho < dsSanPham[i].nguongCanhBao) {
            cout << "[CANH BAO] " << dsSanPham[i].tenSP
                 << " - Ton kho: " << dsSanPham[i].tonKho << "\n";
        }
    }
}
```

**Ứng dụng**: Tự động cảnh báo để nhập hàng kịp thời

---

### 2. **Quét mã vạch và giỏ hàng**

```cpp
void BanHang() {
    ChiTietHoaDon gioHang[100];
    int soMat = 0;

    while (true) {
        cout << "Quet ma vach (0 = ket thuc): ";
        string maVach;
        cin >> maVach;

        if (maVach == "0") break;

        SanPham* sp = TimSanPhamTheoMaVach(maVach);

        if (sp == NULL) {
            cout << "[LOI] Khong tim thay!\n";
            continue;
        }

        cout << "Nhap so luong: ";
        int soLuong;
        cin >> soLuong;

        if (soLuong > sp->tonKho) {
            cout << "[LOI] Khong du hang!\n";
            continue;
        }

        // Thêm vào giỏ hàng
        gioHang[soMat].maSP = sp->maSP;
        gioHang[soMat].soLuong = soLuong;
        gioHang[soMat].donGia = sp->giaBan;
        gioHang[soMat].thanhTien = soLuong * sp->giaBan;
        soMat++;

        // Giảm tồn kho
        sp->tonKho -= soLuong;
    }

    // Tính tiền...
}
```

---

### 3. **Tính tiền với VAT và giảm giá**

```
Tổng tiền hàng:     200,000 VND
+ VAT (10%):         20,000 VND
- Giảm giá TV (5%):  10,000 VND (nếu có thẻ)
= THANH TOÁN:       210,000 VND
```

```cpp
hdMoi.tongTien = 200000;
hdMoi.VAT = hdMoi.tongTien * 0.1;           // +10%
hdMoi.giamGiaTV = hdMoi.tongTien * 0.05;    // -5%
hdMoi.thanhToan = hdMoi.tongTien + hdMoi.VAT - hdMoi.giamGiaTV;
```

---

### 4. **Nhập hàng cập nhật tồn kho**

```cpp
void NhapHang() {
    PhieuNhap pnMoi;
    // ... nhập thông tin

    for (int i = 0; i < soMatHang; i++) {
        string maVach;
        cin >> maVach;

        SanPham* sp = TimSanPhamTheoMaVach(maVach);

        cout << "Ton kho hien tai: " << sp->tonKho << "\n";
        cout << "Nhap so luong nhap: ";
        int soLuong;
        cin >> soLuong;

        // Cập nhật tồn kho
        sp->tonKho += soLuong;

        cout << "[OK] Ton kho moi: " << sp->tonKho << "\n";
    }

    GhiSanPham();  // Lưu file
}
```

---

## 📊 DỮ LIỆU MẪU

### File: DanhSachSanPham.txt
```
MaSP,MaVach,TenSP,DanhMuc,GiaBan,TonKho,NguongCanhBao
SP001,8934567890123,Sua tuoi Vinamilk,Thuc pham,12000,50,10
SP002,8934567890124,Banh mi sandwich,Thuc pham,15000,30,10
SP003,8934567890125,Coca Cola 330ml,Do uong,10000,100,20
SP004,8934567890126,Nuoc suoi Lavie,Do uong,5000,200,30
```

---

## 🎓 ỨNG DỤNG

1. **Cửa hàng tạp hóa**: Quản lý hàng hóa, bán lẻ
2. **Kho hàng**: Nhập xuất tồn, kiểm kê
3. **Pharmacy**: Quản lý thuốc, cảnh báo hết hạn

---

## 💡 MỞ RỘNG

1. **Khuyến mãi mua X tặng Y**
2. **Lịch sử bán hàng theo ngày/tháng**
3. **Sản phẩm bán chạy nhất**
4. **In mã vạch cho sản phẩm mới**

Chúc thành công! 🛒
