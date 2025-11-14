# HƯỚNG DẪN: LOGGING, EXCEPTION HANDLING & DATE/TIME PROCESSING

**Dành cho sinh viên trung bình khá - Dựa trên bài Quản lý Mượn Trả Sách**

---

## 📝 PHẦN 1: LOGGING (GHI NHẬT KÝ)

### 1.1. Logging là gì?

**Logging** là việc ghi lại các sự kiện, hành động, hoặc lỗi xảy ra trong chương trình vào file để:
- Theo dõi hoạt động của chương trình
- Debug khi có lỗi
- Phân tích hành vi người dùng
- Audit (kiểm toán) hệ thống

### 1.2. Tại sao cần Logging?

Khi chương trình chạy xong, bạn không biết:
- Điều gì đã xảy ra?
- Ai đã làm gì?
- Lỗi xảy ra ở đâu?

Logging giúp bạn "nhìn lại quá khứ" của chương trình!

### 1.3. Cách implement Logging trong C++

#### **Ví dụ từ code:**

```cpp
void GhiLog(string noidung)
{
    try
    {
        ofstream logFile("log.txt", ios::app);  // ios::app = ghi thêm vào cuối file
        if (!logFile.is_open())
        {
            throw runtime_error("Khong the mo file log.txt de ghi!");
        }

        // Lấy thời gian hiện tại
        NgayThang nt;
        LayThoiGianHienTai(nt);
        time_t thoiGianHienTai = time(0);
        tm* thoiGianDocDuoc = localtime(&thoiGianHienTai);

        // Ghi log với format: [DD/MM/YYYY HH:MM:SS] nội dung
        logFile << "[" << nt.ngay << "/" << nt.thang << "/" << nt.nam << " "
                << thoiGianDocDuoc->tm_hour << ":"
                << thoiGianDocDuoc->tm_min << ":"
                << thoiGianDocDuoc->tm_sec << "] "
                << noidung << endl;
        logFile.close();
    }
    catch (exception& e)
    {
        cout << "Loi ghi log: " << e.what() << endl;
    }
}
```

#### **Giải thích:**

| Thành phần | Ý nghĩa |
|------------|---------|
| `ios::app` | Append - ghi thêm vào cuối file (không xóa nội dung cũ) |
| `time(0)` | Lấy thời gian hiện tại (dạng timestamp) |
| `localtime()` | Chuyển timestamp thành ngày giờ có thể đọc |
| `[timestamp]` | Đánh dấu thời điểm sự kiện xảy ra |

### 1.4. Khi nào nên ghi Log?

✅ **NÊN ghi log:**
- Khi bắt đầu/kết thúc chương trình
- Khi đọc/ghi file
- Khi user thực hiện hành động quan trọng (mượn sách, trả sách)
- Khi có lỗi xảy ra
- Khi có cảnh báo

❌ **KHÔNG NÊN ghi log:**
- Quá nhiều (mỗi dòng code đều log)
- Thông tin nhạy cảm (password, thẻ tín dụng)

#### **Ví dụ trong code:**

```cpp
// Bắt đầu chương trình
GhiLog("=== BAT DAU CHUONG TRINH ===");

// Đọc file thành công
GhiLog("Doc file DanhSachSach.txt thanh cong. Tong: " + to_string(dem) + " sach.");

// User mượn sách
GhiLog("Muon sach thanh cong: " + tenSach + " (" + to_string(soLuongMuon) + " quyen) - " + tenDocGia);

// Phát hiện quá hạn
GhiLog("PHAT HIEN QUA HAN: " + phieuMuon->tenDocGia + " - " + phieuMuon->tenSach);

// Lỗi
GhiLog("Loi doc file: " + string(e.what()));
```

### 1.5. Format Log tốt

```
[13/11/2025 14:30:25] === BAT DAU CHUONG TRINH ===
[13/11/2025 14:30:25] Doc file DanhSachSach.txt thanh cong. Tong: 5 sach.
[13/11/2025 14:30:45] Muon sach thanh cong: Lap Trinh C++ (2 quyen) - Nguyen Van A
[13/11/2025 14:30:45] Chua den han: Nguyen Van A - Lap Trinh C++
[13/11/2025 14:30:45] === KET THUC CHUONG TRINH ===
```

### 1.6. Bài tập thực hành

**Câu 1:** Thêm log khi sách hết (không thể mượn)
```cpp
GhiLog("Sach het: " + tenSach);
```

**Câu 2:** Thêm log khi user nhập ngày không hợp lệ
```cpp
GhiLog("Ngay khong hop le: " + ngay);
```

**Câu 3:** Tạo hàm ghi log có cấp độ (INFO, WARNING, ERROR)
```cpp
void GhiLog(string capDo, string noidung)
{
    // [13/11/2025 14:30:25] [ERROR] Khong the mo file
}
```

---

## ⚠️ PHẦN 2: EXCEPTION HANDLING (XỬ LÝ NGOẠI LỆ)

### 2.1. Exception là gì?

**Exception** (ngoại lệ) là các lỗi, sự cố bất thường xảy ra khi chương trình chạy:
- File không tồn tại
- Chia cho 0
- Hết bộ nhớ
- Dữ liệu không đúng định dạng

### 2.2. Tại sao cần xử lý Exception?

❌ **Không xử lý:**
```
Chương trình CRASH → User mất dữ liệu → Trải nghiệm tệ
```

✅ **Có xử lý:**
```
Lỗi xảy ra → Thông báo cho user → Tiếp tục chạy hoặc thoát an toàn
```

### 2.3. Cú pháp Try-Catch-Throw

```cpp
try
{
    // Code có thể gây lỗi
}
catch (exception& e)
{
    // Xử lý khi có lỗi
}
```

#### **Ví dụ từ code:**

```cpp
void DocFileDanhSachSach(Sach* dsSach, int& dem)
{
    try
    {
        ifstream inFile("DanhSachSach.txt");

        if (!inFile.is_open())
        {
            // Ném (throw) exception khi không mở được file
            throw runtime_error("Khong the mo file DanhSachSach.txt de doc!");
        }

        // Code đọc file...

        // Chuyển đổi string sang số
        try
        {
            soLuong = stoi(soLuongStr);  // Có thể gây lỗi nếu không phải số
        }
        catch (...)  // Bắt mọi loại exception
        {
            GhiLog("Loi chuyen doi so luong cho dong " + to_string(soDong));
            soLuong = 0;  // Gán giá trị mặc định
        }
    }
    catch (exception& e)  // Bắt exception cụ thể
    {
        cout << "Loi: " << e.what() << endl;
        GhiLog("Loi doc file: " + string(e.what()));
    }
}
```

### 2.4. Các loại Exception phổ biến

| Exception | Khi nào xảy ra | Ví dụ |
|-----------|----------------|-------|
| `runtime_error` | Lỗi runtime chung | File không mở được |
| `invalid_argument` | Tham số không hợp lệ | Số âm khi cần số dương |
| `out_of_range` | Vượt quá giới hạn | Truy cập mảng index âm |
| `logic_error` | Lỗi logic | Chia cho 0 |
| `...` | Bắt mọi exception | Không biết lỗi gì |

### 2.5. Best Practices

#### ✅ NÊN:

```cpp
// 1. Throw exception cụ thể
if (!inFile.is_open())
{
    throw runtime_error("Khong the mo file DanhSachSach.txt");
}

// 2. Catch exception cụ thể trước, chung sau
try { ... }
catch (runtime_error& e) { ... }  // Cụ thể
catch (exception& e) { ... }      // Chung
catch (...) { ... }               // Mọi loại

// 3. Log lỗi
catch (exception& e)
{
    GhiLog("Loi: " + string(e.what()));
    cout << "Loi: " << e.what() << endl;
}

// 4. Giải phóng tài nguyên kể cả khi có lỗi
try { ... }
catch (...)
{
    delete[] arr;  // Giải phóng bộ nhớ
    throw;         // Ném lại exception
}
```

#### ❌ KHÔNG NÊN:

```cpp
// 1. Catch nhưng không làm gì
catch (...) { }  // ❌ Im lặng nuốt lỗi

// 2. Catch quá rộng
catch (...) { }  // ❌ Không biết lỗi gì

// 3. Throw exception không rõ ràng
throw "Loi";  // ❌ Nên dùng runtime_error("Loi")
```

### 2.6. Ví dụ thực tế từ code

#### **Ví dụ 1: Parse số an toàn**

```cpp
try
{
    soLuong = stoi(soLuongStr);
    if (soLuong < 0)
    {
        GhiLog("Loi: so luong am");
        soLuong = 0;
    }
}
catch (...)
{
    GhiLog("Loi chuyen doi so luong");
    soLuong = 0;  // Giá trị mặc định
}
```

#### **Ví dụ 2: Nested try-catch (try-catch lồng nhau)**

```cpp
void DocFileDanhSachSach(Sach* dsSach, int& dem)
{
    try  // Outer try: xử lý lỗi file
    {
        ifstream inFile("DanhSachSach.txt");
        if (!inFile.is_open())
            throw runtime_error("Khong the mo file!");

        while (getline(inFile, line))
        {
            try  // Inner try: xử lý lỗi từng dòng
            {
                soLuong = stoi(soLuongStr);
            }
            catch (...)  // Chỉ xử lý lỗi dòng này, tiếp tục đọc dòng khác
            {
                soLuong = 0;
            }
        }
    }
    catch (exception& e)  // Lỗi file → dừng hẳn
    {
        cout << "Loi: " << e.what() << endl;
    }
}
```

### 2.7. Bài tập thực hành

**Câu 1:** Throw exception khi số lượng mượn > số lượng có sẵn
```cpp
if (soLuongMuon > dsSach[viTri].soLuongConLai)
{
    throw invalid_argument("So luong muon vuot qua so sach co san!");
}
```

**Câu 2:** Viết hàm chia an toàn
```cpp
double ChiaAnToan(int a, int b)
{
    try
    {
        if (b == 0)
            throw runtime_error("Khong the chia cho 0!");
        return (double)a / b;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        return 0;
    }
}
```

---

## 📅 PHẦN 3: DATE/TIME PROCESSING (XỬ LÝ NGÀY THÁNG)

### 3.1. Tại sao xử lý Date/Time khó?

- Tháng 2 có 28 hoặc 29 ngày (năm nhuận)
- Tháng có 30 hoặc 31 ngày
- So sánh ngày phức tạp (30/12/2023 < 01/01/2024)
- Nhiều format khác nhau (dd/mm/yyyy, mm-dd-yyyy, yyyy/mm/dd)

### 3.2. Struct lưu trữ Ngày Tháng

```cpp
struct NgayThang
{
    int ngay;   // 1-31
    int thang;  // 1-12
    int nam;    // 2000-2100
};
```

**Tại sao dùng struct?**
- Dễ so sánh (`SoSanhNgayThang(nt1, nt2)`)
- Dễ truyền tham số (chỉ cần 1 biến thay vì 3 biến)
- Dễ mở rộng (thêm giờ phút giây sau)

### 3.3. Parse Ngày Tháng từ String

```cpp
bool TachNgayThang(const string& chuoiNgay, NgayThang& nt)
{
    string ngay = "", thang = "", nam = "";
    int phan = 0;  // 0=ngày, 1=tháng, 2=năm

    for (size_t i = 0; i < chuoiNgay.length(); i++)
    {
        if (chuoiNgay[i] == '/' || chuoiNgay[i] == '-')
        {
            phan++;
            if (phan > 2)
                return false;  // Quá nhiều dấu phân cách
        }
        else if (chuoiNgay[i] >= '0' && chuoiNgay[i] <= '9')
        {
            if (phan == 0)
                ngay += chuoiNgay[i];
            else if (phan == 1)
                thang += chuoiNgay[i];
            else if (phan == 2)
                nam += chuoiNgay[i];
        }
        else
        {
            return false;  // Ký tự không hợp lệ
        }
    }

    // Kiểm tra đủ 3 phần
    if (ngay.empty() || thang.empty() || nam.empty())
        return false;

    // Chuyển đổi sang số
    try
    {
        nt.ngay = stoi(ngay);
        nt.thang = stoi(thang);
        nt.nam = stoi(nam);
        return true;
    }
    catch (...)
    {
        return false;
    }
}
```

**Ví dụ:**
```
Input: "13/11/2025"
→ ngay="13", thang="11", nam="2025"
→ nt.ngay=13, nt.thang=11, nt.nam=2025
```

### 3.4. Validation Ngày Tháng

```cpp
bool KiemTraNgayHopLe(const string& chuoiNgay)
{
    NgayThang nt;
    if (!TachNgayThang(chuoiNgay, nt))
        return false;

    // Kiểm tra tháng
    if (nt.thang < 1 || nt.thang > 12)
        return false;

    // Kiểm tra năm
    if (nt.nam < 2000 || nt.nam > 2100)
        return false;

    // Số ngày trong mỗi tháng
    int ngayTrongThang[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Năm nhuận: chia hết cho 4 NHƯNG không chia hết cho 100
    //            HOẶC chia hết cho 400
    bool namNhuan = (nt.nam % 4 == 0 && nt.nam % 100 != 0) || (nt.nam % 400 == 0);
    if (namNhuan)
        ngayTrongThang[1] = 29;  // Tháng 2 có 29 ngày

    // Kiểm tra ngày
    if (nt.ngay < 1 || nt.ngay > ngayTrongThang[nt.thang - 1])
        return false;

    return true;
}
```

**Ví dụ kiểm tra:**

| Input | Kết quả | Lý do |
|-------|---------|-------|
| `13/11/2025` | ✅ Hợp lệ | Ngày, tháng, năm đúng |
| `31/02/2024` | ❌ Không hợp lệ | Tháng 2 không có 31 ngày |
| `29/02/2024` | ✅ Hợp lệ | 2024 là năm nhuận |
| `29/02/2023` | ❌ Không hợp lệ | 2023 không phải năm nhuận |
| `32/01/2025` | ❌ Không hợp lệ | Không có ngày 32 |
| `13/13/2025` | ❌ Không hợp lệ | Không có tháng 13 |

### 3.5. So sánh Ngày Tháng

```cpp
// Trả về: -1 nếu nt1 < nt2
//          0 nếu nt1 == nt2
//          1 nếu nt1 > nt2
int SoSanhNgayThang(const NgayThang& nt1, const NgayThang& nt2)
{
    // So sánh năm trước
    if (nt1.nam != nt2.nam)
        return (nt1.nam < nt2.nam) ? -1 : 1;

    // Nếu năm bằng nhau, so sánh tháng
    if (nt1.thang != nt2.thang)
        return (nt1.thang < nt2.thang) ? -1 : 1;

    // Nếu tháng bằng nhau, so sánh ngày
    if (nt1.ngay != nt2.ngay)
        return (nt1.ngay < nt2.ngay) ? -1 : 1;

    // Hoàn toàn giống nhau
    return 0;
}
```

**Ví dụ:**

```cpp
NgayThang nt1 = {30, 12, 2023};  // 30/12/2023
NgayThang nt2 = {01, 01, 2024};  // 01/01/2024

int ketQua = SoSanhNgayThang(nt1, nt2);
// ketQua = -1 (vì 30/12/2023 < 01/01/2024)
```

### 3.6. Lấy Thời Gian Hiện Tại

```cpp
void LayThoiGianHienTai(NgayThang& nt)
{
    time_t thoiGianHienTai = time(0);             // Lấy timestamp hiện tại
    tm* thoiGianDocDuoc = localtime(&thoiGianHienTai);  // Chuyển thành struct tm

    nt.ngay = thoiGianDocDuoc->tm_mday;           // Ngày (1-31)
    nt.thang = thoiGianDocDuoc->tm_mon + 1;       // Tháng (0-11 → cộng 1)
    nt.nam = thoiGianDocDuoc->tm_year + 1900;     // Năm (từ 1900 → cộng 1900)
}
```

**Lưu ý:**
- `tm_mon`: 0-11 (tháng 1 = 0, tháng 12 = 11) → phải cộng 1
- `tm_year`: số năm kể từ 1900 → phải cộng 1900
- `tm_mday`: ngày trong tháng (1-31)

### 3.7. Kiểm tra Quá Hạn

```cpp
void KiemTraQuaHan(PhieuMuon* phieuMuon)
{
    NgayThang ngayTra, ngayHienTai;

    // Parse ngày trả từ string
    if (!TachNgayThang(phieuMuon->ngayTra, ngayTra))
    {
        cout << "Loi: Khong the doc ngay tra!" << endl;
        return;
    }

    // Lấy ngày hiện tại
    LayThoiGianHienTai(ngayHienTai);

    // So sánh
    int ketQua = SoSanhNgayThang(ngayHienTai, ngayTra);

    if (ketQua > 0)
    {
        cout << "*** QUA HAN TRA SACH ***" << endl;
    }
    else if (ketQua == 0)
    {
        cout << "Dung han tra sach hom nay!" << endl;
    }
    else
    {
        cout << "Chua den han tra sach." << endl;
    }
}
```

**Ví dụ:**

| Ngày hôm nay | Ngày trả | Kết quả |
|--------------|----------|---------|
| 13/11/2025 | 10/11/2025 | ❌ QUÁ HẠN (hôm nay > ngày trả) |
| 13/11/2025 | 13/11/2025 | ⚠️ ĐÚNG HẠN (phải trả hôm nay) |
| 13/11/2025 | 20/11/2025 | ✅ CHƯA ĐẾN HẠN (còn 7 ngày) |

### 3.8. Bài tập thực hành

**Câu 1:** Viết hàm kiểm tra ngày trả phải sau ngày mượn

```cpp
bool KiemTraNgayHopLy(const string& ngayMuon, const string& ngayTra)
{
    NgayThang ntMuon, ntTra;
    TachNgayThang(ngayMuon, ntMuon);
    TachNgayThang(ngayTra, ntTra);

    // Ngày trả phải sau ngày mượn (hoặc bằng)
    return SoSanhNgayThang(ntTra, ntMuon) >= 0;
}
```

**Câu 2:** Tính số ngày giữa 2 ngày (nâng cao)

```cpp
int TinhSoNgay(const NgayThang& nt1, const NgayThang& nt2)
{
    // Chuyển thành timestamp rồi trừ nhau
    // (Sinh viên tự implement hoặc dùng thư viện)
}
```

**Câu 3:** Kiểm tra năm nhuận

```cpp
bool LaNamNhuan(int nam)
{
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}
```

**Câu 4:** Format ngày đẹp

```cpp
string FormatNgay(const NgayThang& nt)
{
    // 13/11/2025 → "13 thang 11 nam 2025"
    // 01/01/2024 → "01 thang 01 nam 2024"
}
```

---

## 🎯 TÓM TẮT

### Logging
- Ghi lại mọi sự kiện quan trọng
- Format: `[timestamp] nội dung`
- Dùng `ios::app` để ghi thêm

### Exception Handling
- Dùng `try-catch` để xử lý lỗi
- `throw` exception khi có lỗi
- Luôn log lỗi để debug

### Date/Time
- Dùng struct `NgayThang` để lưu trữ
- Parse cẩn thận, validation kỹ
- Xử lý năm nhuận
- So sánh theo thứ tự: năm → tháng → ngày

---

## 📚 TÀI LIỆU THAM KHẢO

- C++ `<ctime>` library: https://cplusplus.com/reference/ctime/
- Exception handling best practices
- File I/O trong C++

---

**Chúc bạn học tốt!** 🚀
