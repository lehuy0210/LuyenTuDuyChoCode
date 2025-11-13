# BÀI 3: HỆ THỐNG QUẢN LÝ SINH VIÊN

## 📋 Mô Tả Bài Toán
Tạo ứng dụng quản lý danh sách sinh viên với các chức năng:
- Thêm, xóa, sửa sinh viên
- Tìm kiếm sinh viên
- Sắp xếp danh sách
- Thống kê điểm số
- Xử lý file CSV
- Kiểm tra dữ liệu đầu vào (validation)
- Xử lý lỗi

## 🎯 Khái Niệm Áp Dụng
- ✅ File I/O (đọc/ghi file)
- ✅ Data validation (kiểm tra dữ liệu)
- ✅ Error handling (xử lý lỗi)
- ✅ Modular design (thiết kế module)
- ✅ Sorting algorithms (thuật toán sắp xếp)
- ✅ Searching algorithms (thuật toán tìm kiếm)

---

## 🏗️ PHÂN TÍCH THIẾT KẾ

### 1. Xác Định Thực Thể

#### 👨‍🎓 Sinh Viên (Student)
```cpp
struct SinhVien {
    string maSV;      // Mã sinh viên (unique)
    string hoTen;     // Họ tên
    string lop;       // Lớp
    float diemTB;     // Điểm trung bình (0.0 - 10.0)
};
```

### 2. Sơ Đồ Chức Năng

```
Hệ Thống Quản Lý Sinh Viên
    │
    ├── CRUD Operations
    │   ├── Thêm sinh viên
    │   ├── Xóa sinh viên
    │   ├── Sửa thông tin
    │   └── Hiển thị danh sách
    │
    ├── Tìm kiếm
    │   ├── Theo mã sinh viên
    │   ├── Theo họ tên
    │   ├── Theo lớp
    │   └── Theo khoảng điểm
    │
    ├── Sắp xếp
    │   ├── Theo điểm (tăng/giảm)
    │   └── Theo tên
    │
    ├── Thống kê
    │   ├── Điểm trung bình chung
    │   ├── Điểm cao nhất/thấp nhất
    │   └── Phân loại học lực
    │
    └── File I/O
        ├── Đọc file CSV
        └── Lưu file CSV
```

---

## 🔧 CÁC HÀM TỰ VIẾT KHÔNG DÙNG BUILT-IN

### 1. Chuyển Chữ Thường Thành Chữ Hoa
```cpp
string ToUpper(const string& str) {
    string ketqua = "";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            // Khoảng cách giữa 'A' và 'a' là 32
            ketqua = ketqua + char(str[i] - 32);
        } else {
            ketqua = ketqua + str[i];
        }
    }
    return ketqua;
}
```

**Giải thích:**
- Mã ASCII: 'a' = 97, 'A' = 65
- Khoảng cách = 97 - 65 = 32
- Để chuyển 'a' → 'A': 'a' - 32 = 'A'

### 2. Kiểm Tra Chuỗi Con (Substring Search)
```cpp
bool Contains(const string& str, const string& subStr) {
    if (subStr.length() > str.length()) return false;

    // Duyệt từng vị trí có thể
    for (int i = 0; i <= str.length() - subStr.length(); i++) {
        bool found = true;

        // Kiểm tra từng ký tự
        for (int j = 0; j < subStr.length(); j++) {
            if (str[i + j] != subStr[j]) {
                found = false;
                break;
            }
        }

        if (found) return true;
    }

    return false;
}
```

**Ví dụ:**
```cpp
Contains("Nguyen Van An", "Van")  // true
Contains("Tran Thi Binh", "Pham") // false
```

### 3. Tách Tên Từ Họ Tên
```cpp
string LayTen(const string& hoTen) {
    string ten = "";
    int viTriCach = -1;

    // Tìm dấu cách cuối cùng
    for (int i = hoTen.length() - 1; i >= 0; i--) {
        if (hoTen[i] == ' ') {
            viTriCach = i;
            break;
        }
    }

    // Lấy phần sau dấu cách
    if (viTriCach != -1) {
        for (int i = viTriCach + 1; i < hoTen.length(); i++) {
            ten = ten + hoTen[i];
        }
    } else {
        ten = hoTen; // Không có dấu cách
    }

    return ten;
}
```

**Ví dụ:**
- "Nguyen Van An" → "An"
- "Tran Binh" → "Binh"

---

## ✅ DATA VALIDATION (KIỂM TRA DỮ LIỆU)

### 1. Validate Mã Sinh Viên
```cpp
bool ValidateMaSV(const string& maSV) {
    // Độ dài tối thiểu
    if (maSV.length() < 3) {
        cout << "Ma sinh vien phai co it nhat 3 ky tu!" << endl;
        return false;
    }

    // Không chứa khoảng trắng
    for (int i = 0; i < maSV.length(); i++) {
        if (maSV[i] == ' ') {
            cout << "Ma sinh vien khong duoc chua khoang trang!" << endl;
            return false;
        }
    }

    return true;
}
```

### 2. Validate Họ Tên
```cpp
bool ValidateHoTen(const string& hoTen) {
    if (hoTen.length() < 2) {
        cout << "Ho ten phai co it nhat 2 ky tu!" << endl;
        return false;
    }

    // Kiểm tra có ký tự chữ cái
    bool coKyTuChuCai = false;
    for (int i = 0; i < hoTen.length(); i++) {
        if ((hoTen[i] >= 'A' && hoTen[i] <= 'Z') ||
            (hoTen[i] >= 'a' && hoTen[i] <= 'z')) {
            coKyTuChuCai = true;
            break;
        }
    }

    if (!coKyTuChuCai) {
        cout << "Ho ten phai co ky tu chu cai!" << endl;
        return false;
    }

    return true;
}
```

### 3. Validate Điểm
```cpp
bool ValidateDiem(float diem) {
    if (diem < 0.0 || diem > 10.0) {
        cout << "Diem phai nam trong khoang 0.0 - 10.0!" << endl;
        return false;
    }
    return true;
}
```

### Quy Tắc Validation
| Trường | Quy tắc |
|--------|---------|
| Mã SV | ≥ 3 ký tự, không chứa khoảng trắng, unique |
| Họ tên | ≥ 2 ký tự, có ít nhất 1 chữ cái |
| Lớp | ≥ 2 ký tự |
| Điểm | 0.0 ≤ điểm ≤ 10.0 |

---

## 📂 XỬ LÝ FILE CSV

### 1. Cấu Trúc File
```
MaSV,HoTen,Lop,DiemTB
SV001,Nguyen Van An,CNTT1,8.5
SV002,Tran Thi Binh,CNTT1,7.2
```

### 2. Đọc File
```cpp
void DocFileSinhVien(SinhVien* dsSV, int& demSV, const string& tenFile) {
    ifstream inFile(tenFile);
    if (!inFile.is_open()) {
        throw runtime_error("Khong the mo file");
    }

    string line;
    getline(inFile, line); // Bỏ qua dòng tiêu đề

    while (getline(inFile, line)) {
        string phan[4] = {"", "", "", ""};
        int viTri = 0;

        // Tách dòng theo dấu phẩy
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ',') {
                viTri++;
            } else {
                phan[viTri] += line[i];
            }
        }

        // Validate và thêm vào mảng
        if (ValidateMaSV(phan[0]) && ValidateHoTen(phan[1])) {
            dsSV[demSV].maSV = phan[0];
            dsSV[demSV].hoTen = phan[1];
            dsSV[demSV].lop = phan[2];
            dsSV[demSV].diemTB = StrToFloat(phan[3]);
            demSV++;
        }
    }

    inFile.close();
}
```

### 3. Lưu File
```cpp
void LuuFileSinhVien(SinhVien* dsSV, int demSV, const string& tenFile) {
    ofstream outFile(tenFile);

    // Ghi tiêu đề
    outFile << "MaSV,HoTen,Lop,DiemTB" << endl;

    // Ghi dữ liệu
    for (int i = 0; i < demSV; i++) {
        outFile << dsSV[i].maSV << ","
                << dsSV[i].hoTen << ","
                << dsSV[i].lop << ","
                << dsSV[i].diemTB << endl;
    }

    outFile.close();
}
```

---

## 🔍 TÌM KIẾM (SEARCHING)

### 1. Tìm Kiếm Tuyến Tính (Linear Search)
```cpp
int TimSinhVienTheoMa(SinhVien* dsSV, int demSV, const string& maSV) {
    for (int i = 0; i < demSV; i++) {
        if (dsSV[i].maSV == maSV) {
            return i; // Trả về vị trí
        }
    }
    return -1; // Không tìm thấy
}
```

**Độ phức tạp:** O(n)

### 2. Tìm Kiếm Theo Họ Tên (Substring)
```cpp
void TimTheoHoTen(SinhVien* dsSV, int demSV, const string& tuKhoa) {
    string tuKhoaUpper = ToUpper(tuKhoa);

    for (int i = 0; i < demSV; i++) {
        string hoTenUpper = ToUpper(dsSV[i].hoTen);

        if (Contains(hoTenUpper, tuKhoaUpper)) {
            // Hiển thị kết quả
            cout << dsSV[i].maSV << " - "
                 << dsSV[i].hoTen << " - "
                 << dsSV[i].lop << " - "
                 << dsSV[i].diemTB << endl;
        }
    }
}
```

### 3. Tìm Kiếm Theo Khoảng Điểm
```cpp
void TimTheoDiem(SinhVien* dsSV, int demSV, float min, float max) {
    for (int i = 0; i < demSV; i++) {
        if (dsSV[i].diemTB >= min && dsSV[i].diemTB <= max) {
            // Hiển thị kết quả
        }
    }
}
```

---

## 📊 SẮP XẾP (SORTING)

### 1. Selection Sort - Sắp Xếp Theo Điểm
```cpp
void SapXepTheoDiem(SinhVien* dsSV, int demSV, bool tangDan) {
    for (int i = 0; i < demSV - 1; i++) {
        int viTriChon = i;

        // Tìm phần tử nhỏ nhất/lớn nhất
        for (int j = i + 1; j < demSV; j++) {
            if (tangDan) {
                if (dsSV[j].diemTB < dsSV[viTriChon].diemTB) {
                    viTriChon = j;
                }
            } else {
                if (dsSV[j].diemTB > dsSV[viTriChon].diemTB) {
                    viTriChon = j;
                }
            }
        }

        // Hoán đổi
        if (viTriChon != i) {
            SinhVien temp = dsSV[i];
            dsSV[i] = dsSV[viTriChon];
            dsSV[viTriChon] = temp;
        }
    }
}
```

**Độ phức tạp:** O(n²)

### 2. Bubble Sort - Sắp Xếp Theo Tên
```cpp
void SapXepTheoTen(SinhVien* dsSV, int demSV) {
    for (int i = 0; i < demSV - 1; i++) {
        for (int j = 0; j < demSV - i - 1; j++) {
            // Lấy tên của 2 sinh viên
            string ten1 = LayTen(dsSV[j].hoTen);
            string ten2 = LayTen(dsSV[j + 1].hoTen);

            // Chuyển sang chữ hoa để so sánh
            string ten1Upper = ToUpper(ten1);
            string ten2Upper = ToUpper(ten2);

            // So sánh và hoán đổi
            if (ten1Upper > ten2Upper) {
                SinhVien temp = dsSV[j];
                dsSV[j] = dsSV[j + 1];
                dsSV[j + 1] = temp;
            }
        }
    }
}
```

**Độ phức tạp:** O(n²)

### So Sánh Các Thuật Toán Sắp Xếp

| Thuật toán | Độ phức tạp | Ưu điểm | Nhược điểm |
|------------|-------------|---------|------------|
| Selection Sort | O(n²) | Đơn giản, ít swap | Chậm với dữ liệu lớn |
| Bubble Sort | O(n²) | Rất đơn giản | Chậm nhất |
| Insertion Sort | O(n²) | Tốt với dữ liệu gần sắp xếp | Chậm với dữ liệu lớn |

---

## ➕ CRUD OPERATIONS

### 1. Thêm Sinh Viên (Create)
```cpp
void ThemSinhVien(SinhVien* dsSV, int& demSV, int maxSV) {
    if (demSV >= maxSV) {
        cout << "Danh sach da day!" << endl;
        return;
    }

    SinhVien sv;

    // Nhập và validate từng trường
    do {
        cout << "Nhap ma sinh vien: ";
        cin >> sv.maSV;

        if (!ValidateMaSV(sv.maSV)) continue;

        // Kiểm tra trùng mã
        if (TimSinhVienTheoMa(dsSV, demSV, sv.maSV) != -1) {
            cout << "Ma sinh vien da ton tai!" << endl;
            continue;
        }

        break;
    } while (true);

    // Nhập các trường khác...

    dsSV[demSV] = sv;
    demSV++;

    cout << "Them sinh vien thanh cong!" << endl;
}
```

### 2. Xóa Sinh Viên (Delete)
```cpp
void XoaSinhVien(SinhVien* dsSV, int& demSV) {
    string maSV;
    cout << "Nhap ma sinh vien can xoa: ";
    cin >> maSV;

    int viTri = TimSinhVienTheoMa(dsSV, demSV, maSV);

    if (viTri == -1) {
        cout << "Khong tim thay sinh vien!" << endl;
        return;
    }

    // Hiển thị thông tin và xác nhận
    // ...

    // Dịch chuyển mảng
    for (int i = viTri; i < demSV - 1; i++) {
        dsSV[i] = dsSV[i + 1];
    }

    demSV--;

    cout << "Xoa thanh cong!" << endl;
}
```

### 3. Sửa Sinh Viên (Update)
```cpp
void SuaSinhVien(SinhVien* dsSV, int demSV) {
    string maSV;
    cout << "Nhap ma sinh vien can sua: ";
    cin >> maSV;

    int viTri = TimSinhVienTheoMa(dsSV, demSV, maSV);

    if (viTri == -1) {
        cout << "Khong tim thay sinh vien!" << endl;
        return;
    }

    // Hiển thị thông tin hiện tại
    // ...

    // Nhập thông tin mới
    cout << "Nhap thong tin moi (Enter de giu nguyen):" << endl;

    string hoTenMoi;
    cout << "Ho ten moi: ";
    cin.ignore();
    getline(cin, hoTenMoi);

    if (hoTenMoi.length() > 0 && ValidateHoTen(hoTenMoi)) {
        dsSV[viTri].hoTen = hoTenMoi;
    }

    // Tương tự cho các trường khác...

    cout << "Sua thanh cong!" << endl;
}
```

---

## 📈 THỐNG KÊ

### 1. Tính Điểm Trung Bình
```cpp
float TinhDiemTrungBinh(SinhVien* dsSV, int demSV) {
    if (demSV == 0) return 0.0;

    float tongDiem = 0.0;
    for (int i = 0; i < demSV; i++) {
        tongDiem += dsSV[i].diemTB;
    }

    return tongDiem / demSV;
}
```

### 2. Tìm Điểm Cao Nhất/Thấp Nhất
```cpp
void TimDiemCaoThap(SinhVien* dsSV, int demSV,
                    float& diemCao, float& diemThap) {
    if (demSV == 0) return;

    diemCao = dsSV[0].diemTB;
    diemThap = dsSV[0].diemTB;

    for (int i = 1; i < demSV; i++) {
        if (dsSV[i].diemTB > diemCao) {
            diemCao = dsSV[i].diemTB;
        }
        if (dsSV[i].diemTB < diemThap) {
            diemThap = dsSV[i].diemTB;
        }
    }
}
```

### 3. Phân Loại Học Lực
```cpp
void PhanLoaiHocLuc(SinhVien* dsSV, int demSV) {
    int xuatSac = 0, gioi = 0, kha = 0, trungBinh = 0, yeu = 0;

    for (int i = 0; i < demSV; i++) {
        float diem = dsSV[i].diemTB;

        if (diem >= 9.0) xuatSac++;
        else if (diem >= 8.0) gioi++;
        else if (diem >= 6.5) kha++;
        else if (diem >= 5.0) trungBinh++;
        else yeu++;
    }

    cout << "Xuat sac (>= 9.0): " << xuatSac << endl;
    cout << "Gioi (>= 8.0): " << gioi << endl;
    cout << "Kha (>= 6.5): " << kha << endl;
    cout << "Trung binh (>= 5.0): " << trungBinh << endl;
    cout << "Yeu (< 5.0): " << yeu << endl;
}
```

**Bảng Phân Loại:**
| Điểm | Xếp loại |
|------|----------|
| ≥ 9.0 | Xuất sắc |
| ≥ 8.0 | Giỏi |
| ≥ 6.5 | Khá |
| ≥ 5.0 | Trung bình |
| < 5.0 | Yếu |

---

## ⚠️ XỬ LÝ LỖI (ERROR HANDLING)

### 1. Try-Catch cho File I/O
```cpp
try {
    ifstream inFile(tenFile);
    if (!inFile.is_open()) {
        throw runtime_error("Khong the mo file");
    }

    // Đọc file...
    inFile.close();

} catch (exception& e) {
    cout << "Loi: " << e.what() << endl;
}
```

### 2. Kiểm Tra Input
```cpp
// Kiểm tra mảng đầy
if (demSV >= maxSV) {
    cout << "Danh sach da day!" << endl;
    return;
}

// Kiểm tra mảng rỗng
if (demSV == 0) {
    cout << "Danh sach rong!" << endl;
    return;
}

// Kiểm tra không tìm thấy
if (viTri == -1) {
    cout << "Khong tim thay!" << endl;
    return;
}
```

### 3. Xác Nhận Trước Khi Xóa
```cpp
char xacNhan;
cout << "Ban co chac chan muon xoa? (y/n): ";
cin >> xacNhan;

if (xacNhan != 'y' && xacNhan != 'Y') {
    cout << "Huy xoa!" << endl;
    return;
}
```

---

## 💡 THIẾT KẾ MODULE (MODULAR DESIGN)

### Phân Chia Chức Năng

```
main.cpp
    │
    ├── Module Validation
    │   ├── ValidateMaSV()
    │   ├── ValidateHoTen()
    │   ├── ValidateDiem()
    │   └── ValidateLop()
    │
    ├── Module File I/O
    │   ├── DocFileSinhVien()
    │   └── LuuFileSinhVien()
    │
    ├── Module CRUD
    │   ├── ThemSinhVien()
    │   ├── XoaSinhVien()
    │   ├── SuaSinhVien()
    │   └── HienThiDanhSach()
    │
    ├── Module Tìm kiếm
    │   ├── TimTheoMa()
    │   ├── TimTheoHoTen()
    │   ├── TimTheoLop()
    │   └── TimTheoDiem()
    │
    ├── Module Sắp xếp
    │   ├── SapXepTheoDiem()
    │   └── SapXepTheoTen()
    │
    └── Module Thống kê
        ├── TinhDiemTrungBinh()
        ├── TimDiemCaoThap()
        └── PhanLoaiHocLuc()
```

### Ưu Điểm Module Hóa
- ✅ Code dễ đọc, dễ bảo trì
- ✅ Tái sử dụng code
- ✅ Dễ debug
- ✅ Dễ mở rộng

---

## 🎯 ÁP DỤNG VÀO DỰ ÁN KHÁC

### 1. Quản Lý Nhân Viên
**Tương tự:**
- Sinh viên → Nhân viên
- Mã SV → Mã NV
- Lớp → Phòng ban
- Điểm TB → Lương

**Thêm:**
- Ngày vào làm
- Chức vụ
- Hệ số lương

### 2. Quản Lý Sách Thư Viện
**Tương tự:**
- Sinh viên → Sách
- Mã SV → ISBN
- Họ tên → Tên sách
- Lớp → Thể loại

**Thêm:**
- Tác giả
- Nhà xuất bản
- Năm xuất bản

### 3. Quản Lý Bệnh Nhân
**Tương tự:**
- Sinh viên → Bệnh nhân
- Mã SV → Mã BN
- Lớp → Phòng

**Thêm:**
- Chẩn đoán
- Ngày nhập viện
- Chi phí điều trị

### 4. Quản Lý Khách Hàng
**Tương tự:**
- Sinh viên → Khách hàng
- Điểm TB → Điểm tích lũy

**Thêm:**
- Số điện thoại
- Email
- Địa chỉ
- Lịch sử mua hàng

---

## 📊 THUẬT TOÁN NÂNG CAO (TÙY CHỌN)

### 1. Binary Search (Tìm Kiếm Nhị Phân)
**Yêu cầu:** Mảng đã được sắp xếp

```cpp
int BinarySearch(SinhVien* dsSV, int demSV, const string& maSV) {
    int left = 0;
    int right = demSV - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (dsSV[mid].maSV == maSV) {
            return mid;
        } else if (dsSV[mid].maSV < maSV) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}
```

**Độ phức tạp:** O(log n)

### 2. Quick Sort (Sắp Xếp Nhanh)
```cpp
void QuickSort(SinhVien* dsSV, int left, int right) {
    if (left >= right) return;

    int pivot = Partition(dsSV, left, right);
    QuickSort(dsSV, left, pivot - 1);
    QuickSort(dsSV, pivot + 1, right);
}
```

**Độ phức tạp:** O(n log n)

---

## ✅ CHECKLIST HOÀN THÀNH

- [ ] Định nghĩa struct SinhVien
- [ ] Viết các hàm validate đầy đủ
- [ ] Implement đọc/ghi file CSV
- [ ] Implement CRUD đầy đủ (Thêm, Xóa, Sửa, Hiển thị)
- [ ] Implement 4 loại tìm kiếm
- [ ] Implement 2 loại sắp xếp
- [ ] Implement module thống kê
- [ ] Xử lý lỗi đầy đủ (try-catch, validate)
- [ ] Xác nhận trước khi xóa
- [ ] Lưu file trước khi thoát
- [ ] Test với dữ liệu mẫu
- [ ] Kiểm tra memory leak

---

## 🚀 NÂNG CAO (TÙY CHỌN)

1. **Export sang Excel/PDF** - Xuất dữ liệu sang định dạng khác
2. **Import từ Excel** - Nhập dữ liệu hàng loạt
3. **Phân trang** - Hiển thị 10 sinh viên/trang
4. **Lịch sử thao tác** - Ghi lại log các thao tác
5. **Backup tự động** - Tự động sao lưu định kỳ
6. **Quản lý điểm từng môn** - Mở rộng thành bảng điểm chi tiết
7. **Tìm kiếm nâng cao** - Tìm kiếm đa điều kiện
8. **Báo cáo thống kê** - Biểu đồ, chart

---

## 📚 KIẾN THỨC BỔ SUNG

### Độ Phức Tạp Thuật Toán

| Thao tác | Độ phức tạp |
|----------|-------------|
| Tìm kiếm tuyến tính | O(n) |
| Tìm kiếm nhị phân | O(log n) |
| Bubble Sort | O(n²) |
| Selection Sort | O(n²) |
| Quick Sort | O(n log n) |
| Thêm vào cuối mảng | O(1) |
| Xóa ở giữa mảng | O(n) |

### Best Practices

1. **Luôn validate input** trước khi xử lý
2. **Kiểm tra điều kiện** trước khi thực hiện thao tác
3. **Xác nhận** với người dùng trước khi xóa/sửa
4. **Lưu file** thường xuyên hoặc trước khi thoát
5. **Xử lý lỗi** với try-catch
6. **Comment code** ở những chỗ phức tạp
7. **Đặt tên hàm** rõ ràng, có nghĩa
8. **Module hóa code** thành các hàm nhỏ

---

**Made with ❤️ for students | Phù hợp sinh viên trung bình - khá**
