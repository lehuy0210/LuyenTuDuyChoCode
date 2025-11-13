# BÀI 13: HỆ THỐNG QUẢN LÝ TRƯỜNG HỌC

## 📋 TỔNG QUAN

Hệ thống quản lý trường học với:
- **Quản lý học sinh**: Thông tin cá nhân, lớp học
- **Quản lý điểm**: 5 môn (Toán, Văn, Anh, Lý, Hóa)
- **Tính điểm TB**: Tự động tính và xếp loại
- **Thống kê**: Theo lớp (số HS giỏi/khá/TB/yếu)

---

## 🎯 CÁC KHÁI NIỆM QUAN TRỌNG

### 1. **Tính điểm TB và xếp loại**

```cpp
void TinhDiemTBVaXepLoai(HocSinh& hs) {
    // Tính điểm trung bình 5 môn
    hs.diemTB = (hs.diemToan + hs.diemVan + hs.diemAnh +
                 hs.diemLy + hs.diemHoa) / 5.0;

    // Xếp loại
    if (hs.diemTB >= 8.0) {
        hs.xepLoai = "Gioi";          // >= 8.0
    } else if (hs.diemTB >= 6.5) {
        hs.xepLoai = "Kha";           // 6.5 - 7.9
    } else if (hs.diemTB >= 5.0) {
        hs.xepLoai = "TrungBinh";     // 5.0 - 6.4
    } else {
        hs.xepLoai = "Yeu";           // < 5.0
    }
}
```

---

### 2. **Thống kê theo lớp**

```cpp
void ThongKeLop() {
    // Chọn lớp
    string maLop = dsLopHoc[chon].maLop;

    int soGioi = 0, soKha = 0, soTB = 0, soYeu = 0;
    float tongDiemTB = 0;
    int soHSLop = 0;

    // Duyệt tất cả học sinh
    for (int i = 0; i < soLuongHS; i++) {
        if (dsHocSinh[i].maLop == maLop) {
            soHSLop++;
            tongDiemTB += dsHocSinh[i].diemTB;

            // Đếm xếp loại
            if (dsHocSinh[i].xepLoai == "Gioi") soGioi++;
            else if (dsHocSinh[i].xepLoai == "Kha") soKha++;
            else if (dsHocSinh[i].xepLoai == "TrungBinh") soTB++;
            else if (dsHocSinh[i].xepLoai == "Yeu") soYeu++;
        }
    }

    // Hiển thị kết quả
    cout << "Tong so HS: " << soHSLop << "\n";
    cout << "Diem TB lop: " << tongDiemTB / soHSLop << "\n";
    cout << "So HS Gioi: " << soGioi << "\n";
    cout << "So HS Kha: " << soKha << "\n";
    cout << "So HS TB: " << soTB << "\n";
    cout << "So HS Yeu: " << soYeu << "\n";
}
```

---

### 3. **Nhập điểm tự động tính TB**

```cpp
void NhapDiem() {
    HocSinh* hs = TimHocSinh(maHS);

    // Nhập điểm 5 môn
    cin >> hs->diemToan;
    cin >> hs->diemVan;
    cin >> hs->diemAnh;
    cin >> hs->diemLy;
    cin >> hs->diemHoa;

    // Tự động tính điểm TB và xếp loại
    TinhDiemTBVaXepLoai(*hs);

    cout << "Diem TB: " << hs->diemTB << "\n";
    cout << "Xep loai: " << hs->xepLoai << "\n";

    GhiHocSinh();  // Lưu file
}
```

---

## 📊 DỮ LIỆU MẪU

### File: DanhSachLopHoc.txt
```
MaLop,TenLop,SiSo
L10A1,10A1,40
L10A2,10A2,38
L11A1,11A1,35
```

### File: DanhSachHocSinh.txt
```
MaHS,HoTen,NgaySinh,MaLop,DiemToan,DiemVan,DiemAnh,DiemLy,DiemHoa,DiemTB,XepLoai
HS0001,Nguyen Van A,15/01/2010,L10A1,8.5,7.0,9.0,8.0,7.5,8.0,Gioi
HS0002,Tran Thi B,20/03/2010,L10A1,7.0,8.5,7.5,6.5,7.0,7.3,Kha
```

---

## 🎓 ỨNG DỤNG

1. **Trường đại học**: Quản lý sinh viên, học phần, tín chỉ
2. **Trung tâm đào tạo**: Quản lý học viên, lớp học
3. **Online learning**: Coursera, Udemy - tracking progress

---

## 💡 MỞ RỘNG

1. **Học phí**: Tính theo học kỳ, miễn giảm HS giỏi 20%
2. **Điểm danh**: Check-in hàng ngày, thống kê tỷ lệ đi học
3. **Lịch học**: Thời khóa biểu, phòng học
4. **Thư viện điểm**: Điểm qua các kỳ, biểu đồ tiến bộ
5. **Xếp hạng**: Top HS giỏi nhất khóa

Chúc thành công! 📚
