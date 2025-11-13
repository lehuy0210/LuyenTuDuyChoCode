# BÀI 7: QUẢN LÝ BÃI ĐỖ XE

## 📋 Mô Tả Bài Toán
Xây dựng hệ thống quản lý bãi đỗ xe bao gồm:
- Quản lý chỗ đỗ xe theo loại (xe máy, ô tô)
- Vào bãi: Tạo vé gửi xe
- Ra bãi: Tính tiền theo thời gian
- Bảng giá linh hoạt
- Thống kê tỷ lệ lấp đầy

## 🎯 Khái Niệm Áp Dụng
- ✅ Parking management system
- ✅ Time-based billing (tính tiền theo giờ)
- ✅ Slot allocation (phân bổ chỗ đỗ)
- ✅ Hourly rate calculation
- ✅ Overnight parking (qua đêm)

---

## 🏗️ PHÂN TÍCH THIẾT KẾ

### 1. Xác Định Thực Thể

#### 🚗 Chỗ Đỗ Xe (Parking Slot)
```cpp
struct ChoDoXe {
    int soCho;          // Số chỗ: 1, 2, 3...
    string loaiXe;      // XeMay, OTo
    string trangThai;   // Trong, DangSuDung
    string bienSo;      // Biển số xe đang đỗ
};
```

#### 💰 Bảng Giá (Pricing)
```cpp
struct BangGia {
    string loaiXe;      // XeMay, OTo
    float giaGio1;      // Giờ đầu tiên
    float giaGioTiep;   // Giờ tiếp theo
    float giaQuaDem;    // Qua đêm (22h-6h)
};
```

#### 🎫 Vé Gửi Xe (Parking Ticket)
```cpp
struct VeGuiXe {
    string maVe;        // V1, V2...
    string bienSo;
    string loaiXe;
    int soCho;
    string gioVao;      // dd/mm/yyyy hh:mm
    string gioRa;       // dd/mm/yyyy hh:mm
    int soGio;
    float tienGui;
};
```

### 2. Bảng Giá Mẫu

| Loại Xe | Giờ 1 | Giờ Tiếp | Qua Đêm |
|---------|-------|----------|---------|
| Xe máy | 5,000 | 3,000 | 10,000 |
| Ô tô | 10,000 | 5,000 | 20,000 |

---

## 🔄 QUY TRÌNH VÀO BÃI

### Sơ Đồ Luồng
```
Bắt đầu
   ↓
Nhập loại xe (XeMay/OTo)
   ↓
Tìm chỗ trống theo loại xe
   ↓
Còn chỗ?
   ↓ Có
Nhập biển số
   ↓
Tạo vé gửi xe:
   - Sinh mã tự động (V1, V2...)
   - Lưu biển số
   - Lưu loại xe
   - Lưu số chỗ
   - Lấy giờ vào hiện tại
   ↓
In vé gửi xe
   ↓
Cập nhật trạng thái chỗ = "DangSuDung"
   ↓
Lưu biển số vào chỗ đỗ
   ↓
Lưu file
   ↓
Kết thúc
```

### Code Minh Họa
```cpp
void VaoBai(ChoDoXe* dsCho, int demCho, int& soVe) {
    // Nhập loại xe
    string loaiXe;
    cout << "Loai xe (XeMay/OTo): ";
    cin >> loaiXe;

    // Tìm chỗ trống
    int viTri = TimChoTrongTheoLoai(dsCho, demCho, loaiXe);
    if (viTri == -1) {
        cout << "Het cho!" << endl;
        return;
    }

    // Nhập biển số
    string bienSo;
    cout << "Bien so: ";
    cin >> bienSo;

    // Tạo vé
    soVe++;
    string maVe = "V" + IntToStr(soVe);
    string gioVao = GetCurrentDateTime();

    // Cập nhật chỗ đỗ
    dsCho[viTri].trangThai = "DangSuDung";
    dsCho[viTri].bienSo = bienSo;

    // In vé...
}
```

---

## 🚪 QUY TRÌNH RA BÃI

### Sơ Đồ Luồng
```
Bắt đầu
   ↓
Nhập biển số
   ↓
Tìm xe trong bãi
   ↓
Tìm thấy?
   ↓ Có
Lấy giờ vào từ file
   ↓
Lấy giờ ra hiện tại
   ↓
Tính số giờ đỗ
   ↓
Tìm bảng giá theo loại xe
   ↓
Tính tiền:
   - Giờ 1: Giá giờ đầu
   - Giờ 2+: Giá giờ tiếp × (số giờ - 1)
   - Nếu qua đêm: + Phụ phí
   ↓
In hóa đơn
   ↓
Cập nhật trạng thái chỗ = "Trong"
   ↓
Xóa biển số khỏi chỗ đỗ
   ↓
Lưu file
   ↓
Kết thúc
```

---

## 💰 TÍNH TOÁN TIỀN GỬI

### Công Thức
```
Số giờ = (Giờ ra - Giờ vào)
         Làm tròn lên (31 phút = 1 giờ)

Tiền gửi = Giá giờ 1
         + (Số giờ - 1) × Giá giờ tiếp
         + Phụ phí qua đêm (nếu có)
```

### Ví Dụ 1: Xe Máy - Trong Ngày
```
Vào: 08:00
Ra: 11:30
Số giờ: 4 giờ (làm tròn 3.5h lên)

Tính tiền:
- Giờ 1: 5,000 VND
- Giờ 2-4: 3,000 × 3 = 9,000 VND
TỔNG: 14,000 VND
```

### Ví Dụ 2: Ô Tô - Qua Đêm
```
Vào: 22:00
Ra: 08:00 (ngày hôm sau)
Số giờ: 10 giờ

Tính tiền:
- Giờ 1: 10,000 VND
- Giờ 2-10: 5,000 × 9 = 45,000 VND
- Qua đêm: 20,000 VND
TỔNG: 75,000 VND
```

### Code Tính Tiền
```cpp
float TinhTienGui(int soGio, BangGia bangGia, int gioVao) {
    if (soGio <= 0) return 0.0;

    float tongTien = 0.0;

    // Giờ đầu tiên
    tongTien = bangGia.giaGio1;

    // Các giờ tiếp theo
    if (soGio > 1) {
        tongTien += (soGio - 1) * bangGia.giaGioTiep;
    }

    // Qua đêm (22h-6h): tính thêm
    if (gioVao >= 22 || gioVao < 6) {
        tongTien += bangGia.giaQuaDem;
    }

    return tongTien;
}
```

---

## ⏰ TÍNH SỐ GIỜ ĐỖ

### Phương Pháp Parse Giờ
```cpp
int TinhSoGio(const string& gioVao, const string& gioRa) {
    // Parse giờ vào (hh:mm)
    int gioV, phutV;
    // ... parse từ string

    // Parse giờ ra
    int gioR, phutR;
    // ... parse từ string

    // Tính tổng phút
    int tongPhutVao = gioV * 60 + phutV;
    int tongPhutRa = gioR * 60 + phutR;

    int soPhut = tongPhutRa - tongPhutVao;
    if (soPhut < 0) soPhut += 24 * 60; // Qua ngày

    // Làm tròn lên
    int soGio = soPhut / 60;
    if (soPhut % 60 > 0) soGio++;

    return soGio;
}
```

### Ví Dụ
```
08:00 → 11:30
= 3 giờ 30 phút
= Làm tròn lên 4 giờ
```

---

## 📋 ĐỊNH DẠNG VÉ VÀ HÓA ĐƠN

### Vé Gửi Xe (Vào Bãi)
```
========================================
       VE GUI XE
       BAI DO XE ABC
       123 Nguyen Hue, Q1
========================================
Ma ve: V1
Bien so: 59A-12345
Loai xe: XeMay
So cho: 15
Gio vao: 15/11/2025 08:00
========================================
Vui long giu ve de lay xe!
========================================
```

### Hóa Đơn (Ra Bãi)
```
========================================
       HOA DON GUI XE
       BAI DO XE ABC
========================================
Bien so: 59A-12345
Loai xe: XeMay
So cho: 15
----------------------------------------
Gio vao: 15/11/2025 08:00
Gio ra: 15/11/2025 11:30
So gio: 4 gio
----------------------------------------
Tien gui: 14,000 VND
========================================
   CAM ON QUY KHACH!
   HEN GAP LAI!
========================================
```

---

## 📊 THỐNG KÊ

### Các Chỉ Số Quan Trọng

```cpp
void ThongKe(ChoDoXe* dsCho, int demCho) {
    int tongXeMay = 0, tongOTo = 0;
    int xeMayDang = 0, oToDang = 0;
    int xeMayTrong = 0, oToTrong = 0;

    for (int i = 0; i < demCho; i++) {
        if (dsCho[i].loaiXe == "XeMay") {
            tongXeMay++;
            if (dsCho[i].trangThai == "DangSuDung") {
                xeMayDang++;
            } else {
                xeMayTrong++;
            }
        }
        // Tương tự cho ô tô...
    }

    // Tính tỷ lệ lấp đầy
    float tyLeLapDay = (float)(xeMayDang + oToDang) /
                       (tongXeMay + tongOTo) * 100;

    cout << "Ty le lap day: " << tyLeLapDay << "%" << endl;
}
```

### Ví Dụ Thống Kê
```
===== THONG KE =====
XE MAY:
  Tong: 50 cho
  Dang su dung: 35 cho
  Trong: 15 cho

O TO:
  Tong: 30 cho
  Dang su dung: 20 cho
  Trong: 10 cho

Ty le lap day: 68.75%
```

---

## 💡 TÍNH NĂNG NÂNG CAO (TÙY CHỌN)

### 1. Đặt Chỗ Trước
```cpp
struct DatCho {
    string maDat;
    string bienSo;
    string loaiXe;
    string gioHen;
    int soChoDat;
};
```

### 2. Thẻ Tháng
```cpp
struct TheTh ang {
    string maThe;
    string bienSo;
    string loaiXe;
    string ngayBatDau;
    string ngayHetHan;
    float giaThang;     // Ví dụ: 500,000 VND/tháng
};
```

### 3. Camera Nhận Diện Biển Số
```cpp
string NhanDienBienSo(string urlCamera) {
    // Tích hợp API OCR
    // Tự động nhận diện không cần nhập tay
}
```

### 4. Thanh Toán Điện Tử
```cpp
bool ThanhToanQRCode(float soTien) {
    // Generate QR code
    // Kết nối Momo, ZaloPay...
}
```

### 5. Thống Kê Doanh Thu
```cpp
void ThongKeDoanhThu(const string& ngay) {
    // Đọc tất cả vé trong ngày
    // Tính tổng doanh thu
    // Số xe vào/ra
    // Giờ cao điểm
}
```

### 6. Cảnh Báo Sắp Đầy
```cpp
void CanhBaoSapDay(ChoDoXe* dsCho, int demCho) {
    int soChoTrong = DemChoTrong(dsCho, demCho);

    if (soChoTrong < 5) {
        cout << "CANH BAO: Sap het cho!" << endl;
        // Gửi SMS cho quản lý
    }
}
```

---

## 📂 CẤU TRÚC FILE

### DanhSachChoDoXe.txt
```
SoCho,LoaiXe,TrangThai,BienSo
1,XeMay,Trong,
2,XeMay,DangSuDung,59A-12345
3,OTo,Trong,
4,OTo,DangSuDung,30G-98765
```

### BangGia.txt
```
LoaiXe,GiaGio1,GiaGioTiep,GiaQuaDem
XeMay,5000,3000,10000
OTo,10000,5000,20000
```

### VeGuiXe.txt
```
MaVe,BienSo,LoaiXe,SoCho,GioVao,GioRa,SoGio,TienGui
V1,59A-12345,XeMay,2,15/11/2025 08:00,ChuaRa,0,0
V2,30G-98765,OTo,4,15/11/2025 09:00,15/11/2025 12:00,3,25000
```

---

## 🎯 ÁP DỤNG VÀO DỰ ÁN KHÁC

### 1. Bãi Xe Thông Minh
**Thêm:**
- Camera AI nhận diện biển số
- Barrier tự động nâng hạ
- App mobile xem chỗ trống
- Thanh toán không tiếp xúc

### 2. Bãi Xe Sân Bay
**Thêm:**
- Giá theo khoảng cách (gần/xa nhà ga)
- Booking online trước
- Shuttle bus
- Valet parking (gửi xe hộ)

### 3. Bãi Xe Chung Cư
**Thêm:**
- Thẻ cư dân (miễn phí)
- Khách (tính tiền)
- Giới hạn thời gian cho khách
- Phạt đỗ sai chỗ

### 4. Bãi Xe Trung Tâm Thương Mại
**Thêm:**
- Free 3 giờ đầu với hóa đơn mua hàng
- Stamp validation
- VIP parking

---

## ⚡ TỐI ƯU HÓA

### 1. Tìm Chỗ Nhanh
```cpp
// Thay vì duyệt hết, tìm ngay chỗ đầu tiên trống
int TimChoTrongNhanh(ChoDoXe* dsCho, int demCho,
                     const string& loaiXe) {
    for (int i = 0; i < demCho; i++) {
        if (dsCho[i].loaiXe == loaiXe &&
            dsCho[i].trangThai == "Trong") {
            return i;  // Trả về ngay
        }
    }
    return -1;
}
```

### 2. Cache Số Chỗ Trống
```cpp
// Lưu biến global để không phải đếm mỗi lần
int soChoXeMayTrong = 50;
int soChoOToTrong = 30;

// Cập nhật khi vào/ra
void VaoBai() {
    // ...
    if (loaiXe == "XeMay") {
        soChoXeMayTrong--;
    }
}
```

---

## ✅ CHECKLIST HOÀN THÀNH

- [ ] Định nghĩa struct ChoDoXe, BangGia, VeGuiXe
- [ ] Đọc file chỗ đỗ và bảng giá
- [ ] Vào bãi: Tìm chỗ trống, tạo vé
- [ ] In vé gửi xe
- [ ] Ra bãi: Tính số giờ
- [ ] Tính tiền theo bảng giá
- [ ] Xử lý qua đêm
- [ ] In hóa đơn
- [ ] Cập nhật trạng thái chỗ đỗ
- [ ] Thống kê tỷ lệ lấp đầy
- [ ] Test với nhiều trường hợp

---

## 💭 CÂU HỎI THẢO LUẬN

1. **Nếu khách mất vé?**
   - Tìm theo biển số
   - Tính tiền từ đầu ngày
   - Phạt thêm phí mất vé

2. **Nếu đỗ quá 24 giờ?**
   - Tính theo ngày
   - Giá ưu đãi cho dài hạn

3. **Xe quá khổ (xe tải)?**
   - Chiếm 2 chỗ ô tô
   - Giá × 2

4. **Peak hours?**
   - Tăng giá giờ cao điểm
   - Giảm giá giờ thấp điểm

5. **Loyalty program?**
   - Thẻ tháng
   - Tích điểm
   - Giảm giá khách quen

---

**Made with ❤️ for students | Parking Management System**
