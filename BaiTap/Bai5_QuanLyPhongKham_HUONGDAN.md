# BÀI 5: QUẢN LÝ PHÒNG KHÁM

## 📋 Mô Tả Bài Toán
Xây dựng hệ thống quản lý phòng khám bao gồm:
- Đăng ký bệnh nhân mới
- Quản lý bác sĩ theo chuyên khoa
- Đặt lịch hẹn khám
- Tạo phiếu khám bệnh
- Quản lý dịch vụ y tế
- Tính toán chi phí khám

## 🎯 Khái Niệm Áp Dụng
- ✅ Healthcare management system
- ✅ Patient registration (đăng ký bệnh nhân)
- ✅ Appointment scheduling (đặt lịch hẹn)
- ✅ Medical records (hồ sơ bệnh án)
- ✅ Service billing (tính tiền dịch vụ)

---

## 🏗️ PHÂN TÍCH THIẾT KẾ

### 1. Xác Định Thực Thể

#### 👤 Bệnh Nhân (Patient)
```cpp
struct BenhNhan {
    string maBN;        // Tự động sinh: BN1001, BN1002...
    string hoTen;
    int namSinh;
    string gioiTinh;    // Nam/Nu
    string soDienThoai;
    string diaChi;
    string tienSuBenh;  // Bệnh mãn tính, dị ứng...
};
```

#### 👨‍⚕️ Bác Sĩ (Doctor)
```cpp
struct BacSi {
    string maBS;
    string hoTen;
    string chuyenKhoa;  // Nhi khoa, Tim mạch, Da liễu...
    string soPhongKham;
    string lichLamViec; // "8h-12h, 14h-18h"
};
```

#### 💉 Dịch Vụ Khám (Medical Service)
```cpp
struct DichVuKham {
    string maDV;
    string tenDichVu;   // Xét nghiệm máu, siêu âm...
    float donGia;
    string moTa;
};
```

#### 📅 Lịch Hẹn (Appointment)
```cpp
struct LichHen {
    string maLichHen;
    string maBN;
    string tenBN;
    string maBS;
    string tenBS;
    string ngayHen;     // dd/mm/yyyy
    string gioHen;      // hh:mm
    string lyDoKham;
    string trangThai;   // DaDat, DaKham, HuyHen
};
```

#### 📋 Phiếu Khám (Medical Record)
```cpp
struct PhieuKham {
    string maPhieuKham;
    string maBN;
    string tenBN;
    string maBS;
    string tenBS;
    string ngayKham;
    string chanDoan;
    string ghiChu;
    string* dsMaDV;         // Dịch vụ đã sử dụng
    int soLuongDV;
    float tongTienDichVu;
    float tienKham;
    float tienThuoc;
    float tongTien;
};
```

### 2. Thiết Kế Mối Quan Hệ

```
BenhNhan (1) -----> (N) LichHen
LichHen (N) -----> (1) BacSi
BenhNhan (1) -----> (N) PhieuKham
PhieuKham (N) -----> (1) BacSi
PhieuKham (N) -----> (N) DichVuKham
```

---

## 🔄 QUY TRÌNH ĐĂNG KÝ BỆNH NHÂN

### Sơ Đồ Luồng
```
Bắt đầu
   ↓
Kiểm tra: Bệnh nhân cũ hay mới?
   ↓
[Bệnh nhân mới]
   ↓
Sinh mã tự động (BN1001++)
   ↓
Nhập thông tin:
   - Họ tên
   - Năm sinh
   - Giới tính
   - Số điện thoại
   - Địa chỉ
   - Tiền sử bệnh
   ↓
Lưu vào file DanhSachBenhNhan.txt
   ↓
Kết thúc
```

### Code Minh Họa
```cpp
void DangKyBenhNhanMoi(BenhNhan* dsBN, int& demBN) {
    BenhNhan bn;

    // Sinh mã tự động
    bn.maBN = "BN" + IntToStr(demBN + 1001);

    cout << "Ma benh nhan: " << bn.maBN << endl;

    // Nhập thông tin...

    dsBN[demBN] = bn;
    demBN++;

    LuuFileBenhNhan(dsBN, demBN, "DanhSachBenhNhan.txt");
}
```

---

## 📅 ĐẶT LỊCH HẸN KHÁM

### Quy Trình
1. Chọn bệnh nhân (cũ hoặc mới)
2. Hiển thị danh sách bác sĩ theo chuyên khoa
3. Chọn bác sĩ
4. Nhập ngày và giờ hẹn
5. Nhập lý do khám
6. Tạo phiếu hẹn
7. Lưu lịch hẹn

### Ví Dụ Phiếu Hẹn
```
========================================
       PHIEU HEN KHAM
========================================
Ma lich hen: LH1
Benh nhan: Nguyen Van A (BN1001)
Bac si: BS. Tran Thi B (BS001)
Chuyen khoa: Nhi khoa
Phong kham: P101
Ngay hen: 15/11/2025
Gio hen: 09:00
Ly do: Kham suc khoe dinh ky
========================================
Vui long den truoc gio hen 15 phut!
========================================
```

---

## 🏥 TẠO PHIẾU KHÁM BỆNH

### Quy Trình
```
Bắt đầu
   ↓
Chọn bệnh nhân
   ↓
Chọn bác sĩ khám
   ↓
Nhập chẩn đoán
   ↓
Nhập ghi chú (nếu có)
   ↓
┌─────────────────────────────┐
│ Chọn dịch vụ đã sử dụng:   │
│ - Xét nghiệm máu           │
│ - Siêu âm                  │
│ - X-quang                  │
│ - CT Scan                  │
│ - Nội soi                  │
└─────────────────────────────┘
   ↓
Nhập tiền khám
   ↓
Nhập tiền thuốc
   ↓
Tính tổng tiền:
   = Tiền dịch vụ + Tiền khám + Tiền thuốc
   ↓
In phiếu khám
   ↓
Lưu file
   ↓
Kết thúc
```

### Công Thức Tính Tiền
```
Tổng tiền dịch vụ = Σ Đơn giá dịch vụ
TỔNG TIỀN = Tổng tiền dịch vụ + Tiền khám + Tiền thuốc
```

### Ví Dụ
```
Xét nghiệm máu:     150,000 VND
Siêu âm:            300,000 VND
Tiền khám:          200,000 VND
Tiền thuốc:         350,000 VND
--------------------------------
TỔNG TIỀN:        1,000,000 VND
```

---

## 💊 DANH SÁCH DỊCH VỤ Y TẾ

### Các Dịch Vụ Thường Gặp

| Mã DV | Tên Dịch Vụ | Đơn Giá | Mô Tả |
|-------|-------------|---------|--------|
| DV001 | Xét nghiệm máu | 150,000 | Xét nghiệm cơ bản |
| DV002 | Xét nghiệm nước tiểu | 100,000 | Kiểm tra tiểu đường |
| DV003 | Siêu âm | 300,000 | Siêu âm không đau |
| DV004 | X-quang | 250,000 | Chụp X-quang |
| DV005 | CT Scan | 800,000 | Chụp CT |
| DV006 | Nội soi | 500,000 | Nội soi dạ dày |
| DV007 | Điều trị cấp cứu | 200,000 | Xử lý cấp cứu |
| DV008 | Tiêm thuốc | 50,000 | Tiêm |

---

## 👨‍⚕️ QUẢN LÝ BÁC SĨ THEO CHUYÊN KHOA

### Các Chuyên Khoa Phổ Biến

**1. Nhi Khoa (Pediatrics)**
- Khám cho trẻ em 0-16 tuổi
- Tiêm chủng, theo dõi phát triển

**2. Tim Mạch (Cardiology)**
- Khám bệnh tim, huyết áp
- Điện tâm đồ

**3. Tiêu Hóa (Gastroenterology)**
- Bệnh dạ dày, ruột
- Nội soi dạ dày

**4. Da Liễu (Dermatology)**
- Bệnh da, mụn, dị ứng
- Điều trị thẩm mỹ

**5. Thần Kinh (Neurology)**
- Đau đầu, mất ngủ
- Đột quỵ

### Hiển Thị Bác Sĩ Theo Chuyên Khoa
```cpp
void HienThiBacSiTheoChuyenKhoa(BacSi* dsBS, int demBS,
                                 const string& chuyenKhoa) {
    cout << "BAC SI CHUYEN KHOA: " << chuyenKhoa << endl;

    for (int i = 0; i < demBS; i++) {
        if (dsBS[i].chuyenKhoa == chuyenKhoa) {
            cout << dsBS[i].maBS << " - "
                 << dsBS[i].hoTen << " - "
                 << "Phong " << dsBS[i].soPhongKham << endl;
        }
    }
}
```

---

## 📋 ĐỊNH DẠNG PHIẾU KHÁM

```
========================================
       PHONG KHAM ABC
       123 Le Loi, Quan 1
       Tel: 0123456789
========================================
       PHIEU KHAM BENH
========================================
Ma phieu: PK1
Ngay kham: 15/11/2025 10:30
----------------------------------------
Benh nhan: Nguyen Van A (BN1001)
Nam sinh: 1990
Gioi tinh: Nam
Dia chi: 123 Nguyen Hue
Tien su benh: Khong
----------------------------------------
Bac si kham: BS. Tran Thi B (BS001)
Chuyen khoa: Nhi khoa
----------------------------------------
CHAN DOAN: Viem hong
Ghi chu: Nghi ngoi, uong nhieu nuoc
----------------------------------------
DICH VU DA SU DUNG:
- Xet nghiem mau: 150,000 VND
- Sieu am: 300,000 VND
----------------------------------------
Tien dich vu:      450,000 VND
Tien kham:         200,000 VND
Tien thuoc:        350,000 VND
========================================
TONG TIEN:       1,000,000 VND
========================================

   CAM ON QUY KHACH!
```

---

## 🔐 BẢO MẬT THÔNG TIN Y TẾ

### Quy Định Quan Trọng

1. **Bảo mật hồ sơ bệnh án**
   - Chỉ bác sĩ và bệnh nhân được xem
   - Không tiết lộ cho bên thứ 3

2. **Tiền sử bệnh**
   - Lưu trữ an toàn
   - Cập nhật định kỳ

3. **Dữ liệu nhạy cảm**
   - CMND/Passport
   - Địa chỉ, số điện thoại
   - Thông tin bệnh lý

---

## 💡 TÍNH NĂNG NÂNG CAO (TÙY CHỌN)

### 1. Nhắc Lịch Hẹn
```cpp
void NhacLichHen(LichHen* dsLichHen, int demLichHen) {
    string ngayHienTai = GetCurrentDate();

    for (int i = 0; i < demLichHen; i++) {
        if (dsLichHen[i].ngayHen == ngayHienTai) {
            // Gửi SMS/Email nhắc nhở
            cout << "Nhac nho: " << dsLichHen[i].tenBN
                 << " co lich hen ngay hom nay!" << endl;
        }
    }
}
```

### 2. Hồ Sơ Bệnh Án Điện Tử
```cpp
struct HoSoBenhAn {
    string maBN;
    PhieuKham* dsPhieuKham;
    int soLanKham;
    string chanDoanChinh;
    string thuocDangDung;
};
```

### 3. Đơn Thuốc
```cpp
struct DonThuoc {
    string maDonThuoc;
    string maBN;
    string maBS;
    Thuoc* dsThuoc;
    int soLuongThuoc;
    string cachDung;
};
```

### 4. Thống Kê
```cpp
void ThongKeBenhNhan() {
    // Số bệnh nhân theo tháng
    // Bệnh phổ biến
    // Doanh thu theo chuyên khoa
}
```

### 5. Đặt Lịch Online
```cpp
bool KiemTraLichRanh(BacSi* bs, string ngay, string gio) {
    // Kiểm tra bác sĩ có rảnh không
    // Tránh trùng lịch
}
```

---

## 📂 CẤU TRÚC FILE

### DanhSachBenhNhan.txt
```
MaBN,HoTen,NamSinh,GioiTinh,SoDienThoai,DiaChi,TienSuBenh
BN1001,NguyenVanA,1990,Nam,0912345678,123NguyenHue,Khong
```

### DanhSachBacSi.txt
```
MaBS,HoTen,ChuyenKhoa,SoPhongKham,LichLamViec
BS001,BS.NguyenVanA,NhiKhoa,P101,8h-12h,14h-17h
```

### DanhSachDichVu.txt
```
MaDV,TenDichVu,DonGia,MoTa
DV001,XetNghiemMau,150000,Xet nghiem co ban
```

### LichHen.txt
```
MaLichHen,MaBN,TenBN,MaBS,TenBS,NgayHen,GioHen,LyDo,TrangThai
LH1,BN1001,NguyenVanA,BS001,BS.TranB,15/11/2025,09:00,KhamTongQuat,DaDat
```

---

## 🎯 ÁP DỤNG VÀO DỰ ÁN KHÁC

### 1. Nha Khoa
**Tương tự:**
- Bệnh nhân → Khách hàng
- Bác sĩ → Nha sĩ
- Dịch vụ → Lấy cao răng, trám răng, niềng răng

### 2. Phòng Thú Y
**Tương tự:**
- Bệnh nhân → Thú cưng
- Chủ nhân → Thông tin người nuôi
- Dịch vụ → Tiêm phòng, khám bệnh

### 3. Spa/Massage
**Tương tự:**
- Bệnh nhân → Khách hàng
- Bác sĩ → Nhân viên kỹ thuật viên
- Dịch vụ → Massage, chăm sóc da

---

## ✅ CHECKLIST HOÀN THÀNH

- [ ] Định nghĩa struct BenhNhan, BacSi, DichVuKham, LichHen, PhieuKham
- [ ] Sinh mã bệnh nhân tự động (BN1001++)
- [ ] Đăng ký bệnh nhân mới với đầy đủ thông tin
- [ ] Quản lý bác sĩ theo chuyên khoa
- [ ] Đặt lịch hẹn khám
- [ ] Tạo phiếu khám bệnh
- [ ] Chọn nhiều dịch vụ y tế
- [ ] Tính tổng tiền = Dịch vụ + Khám + Thuốc
- [ ] In phiếu khám đẹp
- [ ] Lưu hồ sơ bệnh án
- [ ] Test với dữ liệu mẫu

---

## 💭 CÂU HỎI THẢO LUẬN

1. **Nếu bệnh nhân quên mang CMND?**
   - Cho phép nhập số điện thoại hoặc họ tên để tra cứu

2. **Nếu bác sĩ bận?**
   - Hiển thị lịch rảnh
   - Đề xuất bác sĩ khác cùng chuyên khoa

3. **Bảo hiểm y tế?**
   - Thêm trường `baoHiem` vào BenhNhan
   - Tính giảm trừ theo tỷ lệ

4. **Đơn thuốc?**
   - Tạo struct Thuoc
   - Liên kết với PhieuKham

5. **Theo dõi tiến độ điều trị?**
   - Lưu nhiều PhieuKham của cùng 1 bệnh nhân
   - So sánh chẩn đoán qua các lần khám

---

**Made with ❤️ for students | Healthcare Management System**
