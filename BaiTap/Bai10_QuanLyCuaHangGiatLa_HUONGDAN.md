# BÀI 10: HỆ THỐNG QUẢN LÝ GIẶT LÀ

## 📋 TỔNG QUAN

Hệ thống quản lý cửa hàng giặt là toàn diện:
- **Quản lý khách hàng**: Tên, SĐT, địa chỉ
- **Dịch vụ**: Giặt thường, giặt khô, ủi, giặt+ủi
- **Đơn giặt**: Nhiều dịch vụ, tính theo kg hoặc cái
- **Trạng thái**: Nhận → Đang giặt → Đang sấy → Hoàn thành → Đã giao
- **Phụ phí**: Giao nhận (+30k), dịch vụ gấp (+50%)
- **Thống kê**: Doanh thu, đơn chưa hoàn thành

---

## 🎯 CÁC KHÁI NIỆM QUAN TRỌNG

### 1. **Đơn giặt với nhiều dịch vụ**

```cpp
struct ChiTietDon {
    string maDV;          // Mã dịch vụ
    float soLuong;        // Số kg hoặc số cái
    float thanhTien;      // = soLuong × donGia
};

struct DonGiat {
    string maDon;
    string maKH;
    int soLuongDV;        // Số dịch vụ
    ChiTietDon* dsDichVu; // Mảng động
    bool giaoNhan;        // Giao nhận tại nhà?
    bool dichVuGap;       // Dịch vụ gấp (+50%)?
    float phiGiaoNhan;    // 30000
    float tongTien;
    string trangThai;
};
```

**Công thức tính tiền**:
```
Tổng tiền dịch vụ = Σ(soLuong × donGia)
Nếu có giao nhận: + 30,000 VND
Nếu dịch vụ gấp: × 1.5 (+ 50%)

Tổng cuối = (Tổng DV + Phí giao) × (1 + % dịch vụ gấp)
```

---

### 2. **Quy trình tạo đơn giặt**

```
1. NHẬP SĐT KHÁCH HÀNG
   ├─→ Tìm thấy: Hiển thị thông tin
   └─→ Không tìm thấy: Tạo khách hàng mới

2. NHẬP THÔNG TIN ĐỜN
   - Ngày nhận, giờ nhận
   - Ngày hẹn trả, giờ hẹn trả

3. CHỌN DỊCH VỤ (có thể nhiều dịch vụ)
   For i = 1 to soLuongDV:
     - Chọn dịch vụ (1-6)
     - Nhập số lượng (kg hoặc cái)
     - Tính thành tiền

4. CHỌN PHỤ PHÍ
   - Giao nhận? (+30k)
   - Dịch vụ gấp? (+50%)

5. TÍNH TỔNG TIỀN & IN HÓA ĐƠN
```

---

### 3. **Tìm hoặc tạo khách hàng tự động**

```cpp
void TaoDonGiat() {
    // Nhập SĐT
    cout << "Nhap so dien thoai khach hang: ";
    string sdtTimKiem;
    cin >> sdtTimKiem;

    // Tìm khách hàng
    KhachHang* khachHang = NULL;
    for (int i = 0; i < soLuongKH; i++) {
        if (dsKhachHang[i].sdt == sdtTimKiem) {
            khachHang = &dsKhachHang[i];
            cout << "Tim thay: " << khachHang->hoTen << "\n";
            break;
        }
    }

    // Nếu không tìm thấy → Tạo mới
    if (khachHang == NULL) {
        cout << "Khach hang moi. Nhap thong tin:\n";

        KhachHang khMoi;
        khMoi.maKH = TaoMaKHMoi();
        khMoi.sdt = sdtTimKiem;

        cout << "Nhap ho ten: ";
        getline(cin, khMoi.hoTen);

        cout << "Nhap dia chi: ";
        getline(cin, khMoi.diaChi);

        // Thêm vào danh sách
        // ...
    }
}
```

**Pattern quan trọng**:
- ✅ Tìm trước, không có thì tạo mới
- ✅ Tránh trùng lặp khách hàng
- ✅ UX tốt: Không cần đăng ký trước

---

### 4. **Trạng thái đơn giặt**

```
Nhận → Đang giặt → Đang sấy → Hoàn thành → Đã giao
```

```cpp
void CapNhatTrangThaiDon() {
    cout << "Nhap ma don: ";
    string maDon;
    cin >> maDon;

    for (int i = 0; i < soLuongDon; i++) {
        if (dsDonGiat[i].maDon == maDon) {
            cout << "Trang thai hien tai: " << dsDonGiat[i].trangThai << "\n";
            cout << "Chon trang thai moi:\n";
            cout << "  1. Nhan\n";
            cout << "  2. DangGiat\n";
            cout << "  3. DangSay\n";
            cout << "  4. HoanThanh\n";
            cout << "  5. DaGiao\n";

            int chon;
            cin >> chon;

            if (chon == 1) dsDonGiat[i].trangThai = "Nhan";
            else if (chon == 2) dsDonGiat[i].trangThai = "DangGiat";
            else if (chon == 3) dsDonGiat[i].trangThai = "DangSay";
            else if (chon == 4) dsDonGiat[i].trangThai = "HoanThanh";
            else if (chon == 5) dsDonGiat[i].trangThai = "DaGiao";

            break;
        }
    }
}
```

---

### 5. **Dịch vụ gấp (+50%)**

```cpp
// Ví dụ tính tiền với dịch vụ gấp
float tongTienDV = 200000;      // Giặt + ủi
float phiGiaoNhan = 30000;      // Giao nhận

// Trường hợp 1: Không dịch vụ gấp
tongTien = 200000 + 30000 = 230,000 VND

// Trường hợp 2: Có dịch vụ gấp
tongTien = (200000 + 30000) × 1.5 = 345,000 VND
```

```cpp
donMoi.tongTien = tongTienDV + donMoi.phiGiaoNhan;

if (donMoi.dichVuGap) {
    donMoi.tongTien = donMoi.tongTien * 1.5;  // +50%
}
```

---

## 📊 DỮ LIỆU MẪU

### File: DichVu.txt
```
MaDV,TenDV,DonVi,DonGia,MoTa
DV001,Giat Thuong,kg,20000,Giat thuong voi nuoc va bot giat
DV002,Giat Kho,cai,50000,Giat kho cho do cao cap
DV003,Ui,cai,15000,Ui phang do
DV004,Giat + Ui,kg,30000,Gom ca giat va ui
DV005,Giat Rem Man,cai,100000,Giat rem cua man nuoc
DV006,Giat Chan Ga Goi,bo,80000,Giat bo chan ga goi nem
```

### File: DanhSachKhachHang.txt
```
MaKH,HoTen,SDT,DiaChi
KH001,Nguyen Van A,0912345678,123 Nguyen Trai Q.1
KH002,Tran Thi B,0923456789,456 Le Loi Q.3
```

---

## 🎓 ỨNG DỤNG THỰC TẾ

### 1. Hệ thống sửa chữa điện thoại
- Dịch vụ: Thay màn hình, thay pin, sửa main
- Trạng thái: Nhận máy → Đang kiểm tra → Đang sửa → Hoàn thành
- Tính giá: Linh kiện + công

### 2. Hệ thống sửa xe
- Dịch vụ: Thay dầu, vá lốp, sửa phanh
- Nhiều dịch vụ trong 1 đơn
- Phụ tùng + công

### 3. Hệ thống in ấn
- Dịch vụ: In màu, in đen trắng, photocopy, đóng sách
- Tính theo tờ hoặc quyển
- Dịch vụ gấp: In ngay (+50%)

---

## 💡 BÀI TẬP MỞ RỘNG

### Cấp độ 1
1. **Tìm kiếm đơn giặt**
   - Tìm theo mã đơn
   - Tìm theo SĐT khách hàng
   - Tìm đơn theo trạng thái

2. **In nhãn đơn giặt**
   - Mã đơn + tên khách hàng
   - Ngày nhận, ngày hẹn trả
   - QR code để quét

### Cấp độ 2
3. **Chương trình khách hàng thân thiết**
   ```cpp
   struct KhachHang {
       // ...
       int diemTichLuy;      // 100 điểm
       string loaiTV;        // "Thuong", "Vang", "BacKim"
   };

   // Tích điểm: 10,000 VND = 1 điểm
   // Đổi điểm: 100 điểm = 50,000 VND giảm giá
   ```

4. **Thông báo SMS khi hoàn thành**
   ```cpp
   void GuiThongBao(const string& sdt, const string& maDon) {
       cout << "[SMS] Gui den " << sdt << ":\n";
       cout << "Don " << maDon << " da hoan thanh. Vui long den nhan.\n";
   }
   ```

### Cấp độ 3
5. **Quản lý máy giặt/máy sấy**
   ```cpp
   struct MayGiat {
       int soMay;            // 1, 2, 3
       string trangThai;     // "Trong", "DangChay"
       string maDonDangGiat; // DG001
       string gioKetThuc;    // "14:30"
   };
   ```

6. **Dự tính thời gian hoàn thành**
   - Giặt thường: 2 ngày
   - Giặt khô: 3 ngày
   - Dịch vụ gấp: 1 ngày
   - Tự động tính ngày hẹn trả

---

## 🎯 KẾT LUẬN

Bài 10 rèn luyện:
- ✅ **Đơn hàng phức tạp**: Nhiều dịch vụ, nhiều phụ phí
- ✅ **Tìm hoặc tạo**: Pattern quan trọng trong UX
- ✅ **Quản lý trạng thái**: Workflow xử lý đơn
- ✅ **Tính giá linh hoạt**: Nhiều điều kiện

**Pattern áp dụng**:
1. Đơn hàng với nhiều chi tiết → POS, e-commerce
2. Trạng thái workflow → Đơn hàng, tickets, orders
3. Phụ phí động → Giao hàng, dịch vụ cao cấp

Chúc bạn thành công! 🎉
