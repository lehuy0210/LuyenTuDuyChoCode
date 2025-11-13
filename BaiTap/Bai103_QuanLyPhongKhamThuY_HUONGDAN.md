# BÀI 103: QUẢN LÝ PHÒNG KHÁM THÚ Y

## 📚 Mô tả
Hệ thống phòng khám thú y cho chó, mèo, chim và các loại thú cưng khác.

## 🎯 Tính năng
- Đăng ký thông tin thú cưng
- Khám bệnh và chẩn đoán
- Tính tiền khám + tiền thuốc
- Quản lý hồ sơ bệnh án thú cưng

## 📊 Struct
```cpp
struct ThuCung {
    string ma;
    string ten;
    string loai;
    int tuoi;
    float canNang;
    string chuSoHuu;
    string sdt;
};

struct PhieuKham {
    string maPK;
    string maThuCung;
    string ngayKham;
    string trieuChung;
    string chuanDoan;
    float tienKham;
    float tienThuoc;
    float tongTien;
};
```

## 💡 Kiến thức
- Pet clinic management
- Medical records
- Owner information tracking
