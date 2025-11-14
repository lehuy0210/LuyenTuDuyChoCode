# BÀI 1: QUẢN LÝ THƯ VIỆN SÁCH

## 📋 Mô Tả Bài Toán
Xây dựng hệ thống quản lý thư viện cho phép:
- Mượn/trả sách
- Quản lý độc giả
- Thống kê sách quá hạn
- Logging các thao tác
- Xử lý ngoại lệ

## 🎯 Khái Niệm Áp Dụng
- ✅ Logging (ghi nhật ký)
- ✅ Exception handling (xử lý ngoại lệ)
- ✅ Date/Time processing (xử lý ngày tháng)
- ✅ File I/O (đọc/ghi file)
- ✅ Data structures (cấu trúc dữ liệu)

---

## 🏗️ PHÂN TÍCH THIẾT KẾ

### 1. Xác Định Thực Thể (Entities)

#### 📚 Sách (Book)
```cpp
struct Sach {
    string ISBN;        // Mã sách duy nhất
    string tenSach;     // Tên sách
    string tacGia;      // Tác giả
    int soLuong;        // Số lượng còn lại
};
```

#### 👤 Độc Giả (Reader)
```cpp
struct DocGia {
    string maDocGia;    // Mã độc giả duy nhất
    string hoTen;       // Họ tên
    string soDienThoai; // Số điện thoại
};
```

#### 📝 Phiếu Mượn (Borrow Record)
```cpp
struct PhieuMuon {
    string maPhieu;     // Mã phiếu
    string maDocGia;    // Mã độc giả
    string ISBN;        // Mã sách
    int soLuongMuon;    // Số lượng mượn
    string ngayMuon;    // Ngày mượn (dd/mm/yyyy)
    string ngayTra;     // Ngày trả dự kiến
    bool daTra;         // Đã trả chưa
};
```

### 2. Thiết Kế Mối Quan Hệ

```
DocGia (1) -----> (N) PhieuMuon
PhieuMuon (N) -----> (1) Sach
```

- Một độc giả có thể có nhiều phiếu mượn
- Một phiếu mượn chỉ thuộc về một độc giả
- Một phiếu mượn chỉ mượn một loại sách

---

## 🔧 CÁC HÀM QUAN TRỌNG KHÔNG DÙNG BUILT-IN

### 1. Chuyển String Sang Int (Thay thế stoi)
```cpp
int ChuyenStringSangInt(const string& str) {
    int ketqua = 0;
    bool amDuong = false;
    int batdau = 0;

    // Kiểm tra dấu âm
    if (str.length() > 0 && str[0] == '-') {
        amDuong = true;
        batdau = 1;
    }

    // Duyệt từng ký tự
    for (int i = batdau; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            ketqua = ketqua * 10 + (str[i] - '0');
        } else {
            break;
        }
    }

    return amDuong ? -ketqua : ketqua;
}
```

**Giải thích:**
- Duyệt từng ký tự trong string
- Kiểm tra ký tự có phải số không (từ '0' đến '9')
- Chuyển ký tự sang số: `str[i] - '0'`
- Tích lũy kết quả: `ketqua = ketqua * 10 + chuSo`

### 2. Chuyển Int Sang String (Thay thế to_string)
```cpp
string ChuyenIntSangString(int so) {
    if (so == 0) return "0";

    string ketqua = "";
    bool amDuong = false;

    if (so < 0) {
        amDuong = true;
        so = -so;
    }

    while (so > 0) {
        int chuSo = so % 10;
        ketqua = char('0' + chuSo) + ketqua;
        so = so / 10;
    }

    if (amDuong) {
        ketqua = '-' + ketqua;
    }

    return ketqua;
}
```

**Giải thích:**
- Lấy từng chữ số từ phải sang trái: `so % 10`
- Chuyển số sang ký tự: `char('0' + chuSo)`
- Ghép vào đầu chuỗi kết quả
- Chia số cho 10 để lấy phần còn lại: `so = so / 10`

### 3. Xử Lý Ngày Tháng

#### Tách Ngày/Tháng/Năm từ String
```cpp
void TachNgayThangNam(const string& ngayStr, int& ngay, int& thang, int& nam) {
    string ngayS = "", thangS = "", namS = "";
    int phan = 0;

    for (int i = 0; i < ngayStr.length(); i++) {
        if (ngayStr[i] == '/' || ngayStr[i] == '-') {
            phan++;
        } else {
            if (phan == 0) ngayS += ngayStr[i];
            else if (phan == 1) thangS += ngayStr[i];
            else if (phan == 2) namS += ngayStr[i];
        }
    }

    ngay = ChuyenStringSangInt(ngayS);
    thang = ChuyenStringSangInt(thangS);
    nam = ChuyenStringSangInt(namS);
}
```

#### So Sánh 2 Ngày
```cpp
int SoSanhNgay(int ngay1, int thang1, int nam1,
               int ngay2, int thang2, int nam2) {
    // So sánh năm
    if (nam1 < nam2) return -1;
    if (nam1 > nam2) return 1;

    // So sánh tháng
    if (thang1 < thang2) return -1;
    if (thang1 > thang2) return 1;

    // So sánh ngày
    if (ngay1 < ngay2) return -1;
    if (ngay1 > ngay2) return 1;

    return 0; // Bằng nhau
}
```

---

## 📂 XỬ LÝ FILE

### 1. Đọc File CSV (Comma Separated Values)
```cpp
void DocFileSach(Sach* dsSach, int& demSach, const string& tenFile) {
    ifstream inFile(tenFile);
    if (!inFile.is_open()) {
        throw runtime_error("Khong the mo file");
    }

    string line;
    getline(inFile, line); // Bỏ qua dòng tiêu đề

    while (getline(inFile, line)) {
        string phan[4] = {"", "", "", ""};
        int viTri = 0;

        // Tách dòng theo dấu phay
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ',') {
                viTri++;
            } else {
                phan[viTri] += line[i];
            }
        }

        // Gán vào struct
        dsSach[demSach].ISBN = phan[0];
        dsSach[demSach].tenSach = phan[1];
        dsSach[demSach].tacGia = phan[2];
        dsSach[demSach].soLuong = ChuyenStringSangInt(phan[3]);

        demSach++;
    }

    inFile.close();
}
```

### 2. Ghi File
```cpp
void LuuFileSach(Sach* dsSach, int demSach, const string& tenFile) {
    ofstream outFile(tenFile);

    // Ghi tiêu đề
    outFile << "ISBN,TenSach,TacGia,SoLuong" << endl;

    // Ghi dữ liệu
    for (int i = 0; i < demSach; i++) {
        outFile << dsSach[i].ISBN << ","
                << dsSach[i].tenSach << ","
                << dsSach[i].tacGia << ","
                << dsSach[i].soLuong << endl;
    }

    outFile.close();
}
```

---

## 📝 LOGGING (GHI NHẬT KÝ)

### Hàm Ghi Log
```cpp
void GhiLog(const string& noidung) {
    ofstream logFile("log.txt", ios::app); // Mở chế độ append

    // Lấy thời gian hiện tại
    time_t thoiGian = time(0);
    tm* tg = localtime(&thoiGian);

    // Ghi log với timestamp
    logFile << "["
            << ChuyenIntSangString(tg->tm_mday) << "/"
            << ChuyenIntSangString(tg->tm_mon + 1) << "/"
            << ChuyenIntSangString(tg->tm_year + 1900) << " "
            << ChuyenIntSangString(tg->tm_hour) << ":"
            << ChuyenIntSangString(tg->tm_min) << ":"
            << ChuyenIntSangString(tg->tm_sec) << "] "
            << noidung << endl;

    logFile.close();
}
```

### Khi Nào Cần Ghi Log?
- ✅ Bắt đầu/kết thúc chương trình
- ✅ Đọc/ghi file thành công hoặc thất bại
- ✅ Các thao tác quan trọng (mượn sách, trả sách)
- ✅ Phát hiện lỗi hoặc ngoại lệ
- ✅ Cảnh báo (quá hạn, hết sách)

---

## ⚠️ XỬ LÝ NGOẠI LỆ (EXCEPTION HANDLING)

### 1. Try-Catch Cơ Bản
```cpp
try {
    // Code có thể gây lỗi
    ifstream inFile(tenFile);
    if (!inFile.is_open()) {
        throw runtime_error("Khong the mo file");
    }
    // Xử lý file...

} catch (exception& e) {
    cout << "Loi: " << e.what() << endl;
    GhiLog("Loi: " + string(e.what()));
}
```

### 2. Các Trường Hợp Cần Xử Lý
- ❌ File không tồn tại
- ❌ Dữ liệu không hợp lệ
- ❌ Sách hết
- ❌ Độc giả không tồn tại
- ❌ Số lượng không hợp lệ
- ❌ Định dạng ngày sai

---

## 🔍 CÁC NGHIỆP VỤ CHÍNH

### 1. Mượn Sách
**Các bước:**
1. Nhập mã độc giả → Kiểm tra độc giả có tồn tại
2. Hiển thị danh sách sách
3. Nhập ISBN sách → Kiểm tra sách có tồn tại
4. Kiểm tra số lượng sách còn lại
5. Nhập số lượng mượn → Validate
6. Nhập ngày mượn và ngày trả
7. Tạo phiếu mượn
8. Giảm số lượng sách
9. Lưu phiếu mượn vào file
10. Ghi log

```cpp
void MuonSach(Sach* dsSach, int demSach,
              DocGia* dsDocGia, int demDocGia,
              int& soPhieuMuon) {
    // 1. Kiểm tra độc giả
    // 2. Kiểm tra sách
    // 3. Validate số lượng
    // 4. Tạo phiếu mượn
    // 5. Cập nhật số lượng sách
    // 6. Lưu file và ghi log
}
```

### 2. Thống Kê Sách Quá Hạn
**Các bước:**
1. Đọc file PhieuMuon.txt
2. Lọc các phiếu chưa trả (daTra = false)
3. So sánh ngày trả với ngày hiện tại
4. Hiển thị danh sách phiếu quá hạn
5. Đếm số lượng

```cpp
void ThongKeSachQuaHan() {
    // Đọc từng phiếu mượn
    // Kiểm tra chưa trả và so sánh ngày
    // Hiển thị kết quả
}
```

---

## 💡 MẸO LẬP TRÌNH CHO SINH VIÊN

### 1. Module Hóa Code
```cpp
// Tách các chức năng thành hàm riêng
void DocFile();
void GhiFile();
void HienThiMenu();
void XuLyLuaChon();
```

### 2. Đặt Tên Có Nghĩa
```cpp
// Tốt
int demSach, demDocGia;
string maPhieu, ngayMuon;

// Không tốt
int d, n;
string s, x;
```

### 3. Comment Quan Trọng
```cpp
// Comment ý nghĩa, không comment code rõ ràng
for (int i = 0; i < demSach; i++) {
    // Tìm sách theo ISBN
    if (dsSach[i].ISBN == ISBN) {
        return i;
    }
}
```

### 4. Kiểm Tra Biên
```cpp
// Luôn kiểm tra giới hạn mảng
if (demSach < MAX && demSach >= 0) {
    // Xử lý
}

// Kiểm tra input
if (soLuong <= 0 || soLuong > tonKho) {
    cout << "So luong khong hop le!" << endl;
    return;
}
```

---

## 🎯 ÁP DỤNG VÀO DỰ ÁN KHÁC

### 1. Quản Lý Bán Hàng
**Tương tự:**
- Sách → Sản phẩm
- Độc giả → Khách hàng
- Phiếu mượn → Hóa đơn
- Ngày trả → Ngày giao hàng

### 2. Quản Lý Sinh Viên
**Tương tự:**
- Sách → Môn học
- Độc giả → Sinh viên
- Phiếu mượn → Phiếu đăng ký
- Quá hạn → Nợ môn

### 3. Quản Lý Khách Sạn
**Tương tự:**
- Sách → Phòng
- Độc giả → Khách hàng
- Phiếu mượn → Phiếu đặt phòng
- Ngày trả → Ngày check-out

---

## 📊 CẤU TRÚC FILE DỮ LIỆU

### DanhSachSach.txt
```
ISBN,TenSach,TacGia,SoLuong
978-1234567890,LapTrinhC++,NguyenVanA,10
978-1234567891,CauTrucDuLieu,TranVanB,5
```

### DanhSachDocGia.txt
```
MaDocGia,HoTen,SoDienThoai
DG001,NguyenVanMinh,0912345678
DG002,TranThiHuong,0923456789
```

### PhieuMuon.txt
```
MaPhieu,MaDocGia,ISBN,SoLuong,NgayMuon,NgayTra,DaTra
PM1,DG001,978-1234567890,2,10/11/2025,17/11/2025,0
```

### log.txt
```
[13/11/2025 10:30:45] === BAT DAU CHUONG TRINH ===
[13/11/2025 10:30:46] Doc file sach thanh cong
[13/11/2025 10:31:20] Muon sach thanh cong - PM1
[13/11/2025 10:32:00] === KET THUC CHUONG TRINH ===
```

---

## ✅ CHECKLIST HOÀN THÀNH

- [ ] Định nghĩa struct Sach, DocGia, PhieuMuon
- [ ] Viết hàm ChuyenStringSangInt (không dùng stoi)
- [ ] Viết hàm ChuyenIntSangString (không dùng to_string)
- [ ] Viết hàm xử lý ngày tháng
- [ ] Viết hàm đọc file CSV
- [ ] Viết hàm ghi file
- [ ] Viết hàm GhiLog với timestamp
- [ ] Implement chức năng mượn sách
- [ ] Implement chức năng thống kê quá hạn
- [ ] Xử lý ngoại lệ đầy đủ
- [ ] Test với dữ liệu mẫu
- [ ] Kiểm tra memory leak (delete động)

---

## 🚀 NÂNG CAO (TÙY CHỌN)

1. **Thêm chức năng trả sách** - Cập nhật trạng thái daTra
2. **Tìm kiếm sách theo tên** - Duyệt mảng và so sánh
3. **Sắp xếp sách theo tên** - Bubble sort hoặc Selection sort
4. **Tính tiền phạt quá hạn** - Tính số ngày quá hạn × giá phạt
5. **Xuất báo cáo** - Thống kê số sách mượn nhiều nhất

---

## 📚 TÀI LIỆU THAM KHẢO

- Xử lý file: `ifstream`, `ofstream`
- Xử lý ngoại lệ: `try-catch`, `throw`
- Xử lý thời gian: `<ctime>`, `time()`, `localtime()`
- Con trỏ động: `new`, `delete`, `delete[]`

---

**Made with ❤️ for students | Phù hợp sinh viên trung bình - khá**
