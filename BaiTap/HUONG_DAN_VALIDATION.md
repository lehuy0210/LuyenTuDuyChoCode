# HƯỚNG DẪN: DATA VALIDATION (KIỂM TRA DỮ LIỆU HỢP LẸ)

**Dành cho sinh viên trung bình khá - Dựa trên bài Quản lý Mượn Trả Sách**

---

## 📋 MỤC LỤC

1. [Validation là gì?](#1-validation-là-gì)
2. [Tại sao cần Validation?](#2-tại-sao-cần-validation)
3. [Các loại Validation](#3-các-loại-validation)
4. [Validation trong Code](#4-validation-trong-code)
5. [Best Practices](#5-best-practices)
6. [Bài tập thực hành](#6-bài-tập-thực-hành)

---

## 1. VALIDATION LÀ GÌ?

**Validation** (Kiểm tra dữ liệu hợp lệ) là quá trình kiểm tra xem dữ liệu đầu vào có **đúng, đủ và hợp lệ** không trước khi xử lý.

### Ví dụ đơn giản:

```cpp
// ❌ KHÔNG CÓ VALIDATION
int tuoi;
cin >> tuoi;
cout << "Ban " << tuoi << " tuoi";
// Nếu user nhập -5 hoặc 999 → Sai logic nhưng vẫn chạy!

// ✅ CÓ VALIDATION
int tuoi;
cin >> tuoi;
if (tuoi < 0 || tuoi > 150)  // Kiểm tra hợp lệ
{
    cout << "Tuoi khong hop le!";
    return;
}
cout << "Ban " << tuoi << " tuoi";
```

---

## 2. TẠI SAO CẦN VALIDATION?

### 2.1. Bảo vệ chương trình khỏi crash

```cpp
// ❌ KHÔNG VALIDATION
int arr[10];
int index;
cin >> index;
arr[index] = 100;  // Nếu index = 999 → CRASH!

// ✅ CÓ VALIDATION
int arr[10];
int index;
cin >> index;
if (index >= 0 && index < 10)  // Kiểm tra
{
    arr[index] = 100;
}
else
{
    cout << "Index khong hop le!";
}
```

### 2.2. Tránh dữ liệu vô nghĩa

| Trường hợp | Không validation | Có validation |
|------------|------------------|---------------|
| Tuổi = -5 | Chấp nhận | Báo lỗi |
| Ngày 32/13/2025 | Chấp nhận | Báo lỗi |
| Số lượng mượn = 0 | Chấp nhận | Báo lỗi |
| Tên rỗng | Chấp nhận | Báo lỗi |

### 2.3. Cải thiện trải nghiệm người dùng

```
❌ Không validation:
User nhập sai → Chương trình crash → User bực mình

✅ Có validation:
User nhập sai → Thông báo lỗi rõ ràng → User sửa lại → Thành công
```

### 2.4. Bảo mật

```cpp
// ❌ SQL Injection (nếu không validate)
string tenDangNhap = userInput;  // userInput = "admin' OR '1'='1"
// → Hack được vào hệ thống!

// ✅ Validate input trước
if (KiemTraKyTuDacBiet(tenDangNhap))
{
    cout << "Ten dang nhap chua ky tu khong hop le!";
    return;
}
```

---

## 3. CÁC LOẠI VALIDATION

### 3.1. Validation theo Kiểu dữ liệu

| Kiểu | Ví dụ | Validation cần có |
|------|-------|-------------------|
| **Số nguyên** | Tuổi, số lượng | > 0, trong khoảng hợp lý |
| **Chuỗi** | Tên, địa chỉ | Không rỗng, độ dài tối thiểu/tối đa |
| **Ngày tháng** | 13/11/2025 | Đúng format, ngày hợp lệ |
| **Email** | abc@gmail.com | Có @, có domain |
| **Số điện thoại** | 0912345678 | 10-11 số, bắt đầu 0 |

### 3.2. Validation theo Logic nghiệp vụ

| Logic | Ví dụ |
|-------|-------|
| **Tồn tại** | Sách có trong thư viện không? |
| **Đủ số lượng** | Số sách còn đủ để mượn không? |
| **Quan hệ** | Ngày trả phải sau ngày mượn |
| **Trùng lặp** | Email đã tồn tại chưa? |
| **Quyền hạn** | User có quyền xóa không? |

### 3.3. Validation theo Định dạng

| Định dạng | Pattern | Ví dụ hợp lệ |
|-----------|---------|--------------|
| **Ngày** | dd/mm/yyyy | 13/11/2025 |
| **Email** | text@domain.com | abc@gmail.com |
| **Số điện thoại** | 0xxxxxxxxx | 0912345678 |
| **Mã sinh viên** | SVxxxxxx | SV001234 |

---

## 4. VALIDATION TRONG CODE

### 4.1. Kiểm tra Chuỗi Rỗng

```cpp
// Kiem tra chuoi co rong khong
bool KiemTraChuoiRong(const string& str)
{
    if (str.empty())  // Độ dài = 0
        return true;

    // Kiểm tra chuỗi chỉ có khoảng trắng/tab/newline
    for (int i = 0; i < (int)str.length(); i++)
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            return false;  // Có ký tự không phải khoảng trắng
    }
    return true;  // Chỉ toàn khoảng trắng
}
```

**Ví dụ sử dụng:**

```cpp
string ten;
getline(cin, ten);

if (KiemTraChuoiRong(ten))
{
    cout << "Ten khong duoc rong!" << endl;
    return;
}
```

**Test cases:**

| Input | Kết quả | Lý do |
|-------|---------|-------|
| `""` | Rỗng ✅ | Độ dài = 0 |
| `"   "` | Rỗng ✅ | Chỉ có space |
| `"  \t\n  "` | Rỗng ✅ | Chỉ có space/tab/newline |
| `"Nguyen Van A"` | Không rỗng ❌ | Có ký tự chữ |
| `"  A  "` | Không rỗng ❌ | Có ký tự A |

---

### 4.2. Kiểm tra Ngày Tháng Hợp Lệ

#### **Bước 1: Tách chuỗi thành ngày/tháng/năm**

```cpp
bool TachNgayThang(const string& chuoiNgay, NgayThang& nt)
{
    string ngay = "", thang = "", nam = "";
    int phan = 0;  // 0=ngày, 1=tháng, 2=năm

    for (int i = 0; i < (int)chuoiNgay.length(); i++)
    {
        if (chuoiNgay[i] == '/' || chuoiNgay[i] == '-')
        {
            phan++;
            if (phan > 2)  // Quá nhiều dấu phân cách
                return false;
        }
        else if (chuoiNgay[i] >= '0' && chuoiNgay[i] <= '9')
        {
            // Ghép số vào phần tương ứng
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

    // Phải đủ 3 phần
    if (ngay.empty() || thang.empty() || nam.empty())
        return false;

    // Chuyển sang số
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
→ Duyệt từng ký tự:
  - '1' → ngay = "1"
  - '3' → ngay = "13"
  - '/' → phan = 1
  - '1' → thang = "1"
  - '1' → thang = "11"
  - '/' → phan = 2
  - '2' → nam = "2"
  - '0' → nam = "20"
  - '2' → nam = "202"
  - '5' → nam = "2025"
→ nt.ngay = 13, nt.thang = 11, nt.nam = 2025
```

#### **Bước 2: Kiểm tra ngày hợp lệ**

```cpp
bool KiemTraNgayHopLe(const string& chuoiNgay)
{
    NgayThang nt;
    if (!TachNgayThang(chuoiNgay, nt))
        return false;

    // 1. Kiểm tra tháng (1-12)
    if (nt.thang < 1 || nt.thang > 12)
        return false;

    // 2. Kiểm tra năm (2000-2100)
    if (nt.nam < MIN_YEAR || nt.nam > MAX_YEAR)
        return false;

    // 3. Số ngày trong mỗi tháng
    int ngayTrongThang[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //                      Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec

    // 4. Xử lý năm nhuận
    bool namNhuan = (nt.nam % 4 == 0 && nt.nam % 100 != 0) || (nt.nam % 400 == 0);
    if (namNhuan)
        ngayTrongThang[1] = 29;  // Tháng 2 có 29 ngày

    // 5. Kiểm tra ngày trong khoảng hợp lệ
    if (nt.ngay < 1 || nt.ngay > ngayTrongThang[nt.thang - 1])
        return false;

    return true;  // Hợp lệ
}
```

**Test cases:**

| Input | Kết quả | Lý do |
|-------|---------|-------|
| `13/11/2025` | ✅ Hợp lệ | Ngày, tháng, năm đều đúng |
| `32/01/2025` | ❌ Không hợp lệ | Tháng 1 chỉ có 31 ngày |
| `29/02/2024` | ✅ Hợp lệ | 2024 là năm nhuận |
| `29/02/2023` | ❌ Không hợp lệ | 2023 không phải năm nhuận |
| `31/04/2025` | ❌ Không hợp lệ | Tháng 4 chỉ có 30 ngày |
| `13/13/2025` | ❌ Không hợp lệ | Không có tháng 13 |
| `13-11-2025` | ✅ Hợp lệ | Dấu `-` cũng được chấp nhận |
| `13/11/abcd` | ❌ Không hợp lệ | Năm không phải số |

**Giải thích năm nhuận:**

```cpp
// Năm nhuận là năm:
// - Chia hết cho 4 NHƯNG không chia hết cho 100
//   VÍ DỤ: 2024, 2028 (chia hết 4, không chia hết 100)
// HOẶC
// - Chia hết cho 400
//   VÍ DỤ: 2000, 2400 (chia hết 400)

bool namNhuan = (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);

// TEST:
// 2024: 2024 % 4 = 0 ✅, 2024 % 100 = 24 ≠ 0 ✅ → Năm nhuận
// 2023: 2023 % 4 = 3 ≠ 0 ❌ → Không phải năm nhuận
// 1900: 1900 % 4 = 0 ✅, 1900 % 100 = 0 ❌ → Không phải năm nhuận
// 2000: 2000 % 400 = 0 ✅ → Năm nhuận
```

---

### 4.3. Kiểm tra Số Lượng Hợp Lệ

```cpp
// Kiem tra so luong hop le
bool KiemTraSoLuong(int soLuong, int soLuongMax)
{
    return soLuong > 0 && soLuong <= soLuongMax;
}
```

**Ví dụ sử dụng:**

```cpp
int soLuongMuon;
int soLuongConLai = 10;  // Thư viện còn 10 quyển

cout << "Nhap so luong muon: ";
cin >> soLuongMuon;

if (!KiemTraSoLuong(soLuongMuon, soLuongConLai))
{
    if (soLuongMuon <= 0)
        cout << "So luong phai lon hon 0!" << endl;
    else if (soLuongMuon > soLuongConLai)
        cout << "Khong du sach de muon!" << endl;
    return;
}

cout << "Muon thanh cong " << soLuongMuon << " quyen!";
```

**Test cases:**

| soLuongMuon | soLuongMax | Kết quả | Lý do |
|-------------|------------|---------|-------|
| 5 | 10 | ✅ Hợp lệ | 0 < 5 ≤ 10 |
| 10 | 10 | ✅ Hợp lệ | 0 < 10 ≤ 10 |
| 0 | 10 | ❌ Không hợp lệ | Không thể mượn 0 quyển |
| -5 | 10 | ❌ Không hợp lệ | Số âm |
| 15 | 10 | ❌ Không hợp lệ | Vượt quá số lượng có |

---

### 4.4. Kiểm tra Sách Tồn Tại

```cpp
// Kiem tra sach co ton tai khong
// Trả về: index nếu tìm thấy, -1 nếu không tìm thấy
int TimSach(Sach* dsSach, int dem, const string& tenSach)
{
    for (int i = 0; i < dem; i++)
    {
        if (dsSach[i].tenSach == tenSach)
            return i;  // Tìm thấy ở vị trí i
    }
    return -1;  // Không tìm thấy
}
```

**Ví dụ sử dụng:**

```cpp
string tenSachMuon = "Lap Trinh C++";
int viTri = TimSach(dsSach, dem, tenSachMuon);

if (viTri == -1)
{
    cout << "Khong tim thay sach '" << tenSachMuon << "' trong thu vien!" << endl;
    return;
}

// Tìm thấy → Xử lý tiếp
cout << "Tim thay sach o vi tri: " << viTri << endl;
cout << "So luong con lai: " << dsSach[viTri].soLuongConLai << endl;
```

**Tại sao trả về index thay vì true/false?**

```cpp
// ❌ Cách 1: Trả về bool (không tối ưu)
bool TimThay(Sach* ds, int dem, string ten);
// → Tìm 2 lần: 1 lần kiểm tra có, 1 lần lấy index

// ✅ Cách 2: Trả về index (tối ưu)
int TimSach(Sach* ds, int dem, string ten);
// → Tìm 1 lần: vừa biết có/không, vừa có index luôn
```

---

### 4.5. Kiểm tra Tràn Mảng

```cpp
void DocFileDanhSachSach(Sach* dsSach, int& dem)
{
    dem = 0;
    string line;

    while (getline(inFile, line) && dem < MAX_SACH)  // ✅ Kiểm tra dem < MAX_SACH
    {
        // Parse và lưu vào dsSach[dem]
        dsSach[dem].tenSach = ...;
        dem++;
    }

    // Cảnh báo nếu đạt giới hạn
    if (dem >= MAX_SACH)
    {
        GhiLog("CANH BAO: Da dat gioi han toi da " + IntToString(MAX_SACH) + " sach!");
    }
}
```

**Giải thích:**

```cpp
// ❌ KHÔNG KIỂM TRA
Sach* dsSach = new Sach[100];  // Mảng có 100 phần tử (index 0-99)
int dem = 0;

while (getline(inFile, line))
{
    dsSach[dem] = ...;  // Nếu file có 150 dòng → dem = 100, 101, 102...
    dem++;              // → TRÀN MẢNG → CRASH!
}

// ✅ CÓ KIỂM TRA
while (getline(inFile, line) && dem < 100)  // Dừng khi dem = 100
{
    dsSach[dem] = ...;  // dem chỉ chạy từ 0-99
    dem++;
}
```

---

### 4.6. Kiểm tra Quan Hệ Giữa Các Trường

```cpp
// Ngày trả phải sau ngày mượn
void MuonTheoTenSach(...)
{
    string ngayMuon = NhapNgayThang("ngay muon");
    string ngayTra = NhapNgayThang("ngay tra");

    // Kiểm tra quan hệ
    NgayThang ntMuon, ntTra;
    TachNgayThang(ngayMuon, ntMuon);
    TachNgayThang(ngayTra, ntTra);

    if (SoSanhNgayThang(ntTra, ntMuon) <= 0)  // Ngày trả <= ngày mượn
    {
        cout << "CANH BAO: Ngay tra phai sau ngay muon!" << endl;
        GhiLog("CANH BAO: Ngay tra khong hop ly - Muon: " + ngayMuon + ", Tra: " + ngayTra);
    }
}
```

**Test cases:**

| Ngày mượn | Ngày trả | Kết quả | Lý do |
|-----------|----------|---------|-------|
| 10/11/2025 | 20/11/2025 | ✅ Hợp lệ | Trả sau mượn 10 ngày |
| 10/11/2025 | 10/11/2025 | ⚠️ Cảnh báo | Trả cùng ngày mượn |
| 20/11/2025 | 10/11/2025 | ❌ Không hợp lệ | Trả trước mượn |

---

## 5. BEST PRACTICES

### 5.1. Validate càng sớm càng tốt (Fail Fast)

```cpp
// ❌ KHÔNG TỐT: Validate sau khi xử lý nhiều
void MuonSach(...)
{
    // Làm nhiều thứ...
    CapNhatDatabase();
    GhiLog();
    GuiEmail();

    // Rồi mới validate
    if (soLuong <= 0)  // Quá muộn!
        return;
}

// ✅ TỐT: Validate ngay từ đầu
void MuonSach(...)
{
    // Validate đầu tiên
    if (soLuong <= 0)
    {
        cout << "So luong khong hop le!";
        return;
    }

    // Xử lý sau
    CapNhatDatabase();
    GhiLog();
    GuiEmail();
}
```

### 5.2. Thông báo lỗi rõ ràng

```cpp
// ❌ KHÔNG TỐT
if (!KiemTraNgayHopLe(ngay))
{
    cout << "Loi!" << endl;  // Lỗi gì???
}

// ✅ TỐT
if (!KiemTraNgayHopLe(ngay))
{
    cout << "Ngay khong hop le! Vui long nhap dung dinh dang dd/mm/yyyy." << endl;
    cout << "Vi du: 13/11/2025" << endl;
}
```

### 5.3. Validate nhiều lớp

```cpp
// Lớp 1: Validate format
if (!TachNgayThang(ngay, nt))
{
    cout << "Dinh dang ngay sai!";
    return false;
}

// Lớp 2: Validate giá trị
if (nt.thang < 1 || nt.thang > 12)
{
    cout << "Thang phai tu 1-12!";
    return false;
}

// Lớp 3: Validate logic nghiệp vụ
if (nt.ngay > ngayTrongThang[nt.thang - 1])
{
    cout << "Thang " << nt.thang << " khong co " << nt.ngay << " ngay!";
    return false;
}
```

### 5.4. Tách hàm validation riêng

```cpp
// ✅ TỐT: Mỗi validation 1 hàm
bool KiemTraNgayHopLe(const string& ngay);
bool KiemTraSoLuong(int soLuong, int max);
bool KiemTraChuoiRong(const string& str);
int TimSach(Sach* ds, int dem, const string& ten);

// ❌ KHÔNG TỐT: Tất cả trong 1 hàm
void XuLyMuonSach(...)
{
    // 100 dòng validation ở đây
    // Khó đọc, khó maintain
}
```

### 5.5. Log các lỗi validation

```cpp
if (!KiemTraNgayHopLe(ngay))
{
    cout << "Ngay khong hop le!" << endl;
    GhiLog("User nhap ngay khong hop le: " + ngay);  // ✅ Log để debug
    return false;
}
```

---

## 6. BÀI TẬP THỰC HÀNH

### **Bài 1: Kiểm tra Email hợp lệ**

Viết hàm kiểm tra email có hợp lệ không:
- Phải có duy nhất 1 ký tự `@`
- Phần trước @ không rỗng
- Phần sau @ phải có ít nhất 1 dấu `.`
- Không chứa khoảng trắng

```cpp
bool KiemTraEmail(const string& email)
{
    // TODO: Implement
}

// Test cases:
// "abc@gmail.com" → true
// "abc123@yahoo.com.vn" → true
// "abc" → false (không có @)
// "@gmail.com" → false (trước @ rỗng)
// "abc@gmail" → false (sau @ không có .)
// "abc @gmail.com" → false (có khoảng trắng)
```

<details>
<summary>Xem đáp án</summary>

```cpp
bool KiemTraEmail(const string& email)
{
    int demAt = 0;
    int viTriAt = -1;

    // Kiểm tra khoảng trắng và đếm @
    for (int i = 0; i < (int)email.length(); i++)
    {
        if (email[i] == ' ')
            return false;  // Có khoảng trắng
        if (email[i] == '@')
        {
            demAt++;
            viTriAt = i;
        }
    }

    // Phải có đúng 1 @
    if (demAt != 1)
        return false;

    // @ không ở đầu
    if (viTriAt == 0)
        return false;

    // @ không ở cuối
    if (viTriAt == (int)email.length() - 1)
        return false;

    // Phần sau @ phải có ít nhất 1 dấu .
    bool coDau = false;
    for (int i = viTriAt + 1; i < (int)email.length(); i++)
    {
        if (email[i] == '.')
        {
            coDau = true;
            break;
        }
    }

    return coDau;
}
```
</details>

---

### **Bài 2: Kiểm tra Số điện thoại Việt Nam**

Viết hàm kiểm tra số điện thoại hợp lệ:
- Độ dài 10 hoặc 11 số
- Bắt đầu bằng 0
- Chỉ chứa chữ số

```cpp
bool KiemTraSoDienThoai(const string& sdt)
{
    // TODO: Implement
}

// Test cases:
// "0912345678" → true
// "0123456789" → true
// "012345678" → false (chỉ 9 số)
// "123456789" → false (không bắt đầu bằng 0)
// "091234567a" → false (có chữ cái)
```

<details>
<summary>Xem đáp án</summary>

```cpp
bool KiemTraSoDienThoai(const string& sdt)
{
    // Kiểm tra độ dài
    int len = (int)sdt.length();
    if (len != 10 && len != 11)
        return false;

    // Phải bắt đầu bằng 0
    if (sdt[0] != '0')
        return false;

    // Tất cả phải là chữ số
    for (int i = 0; i < len; i++)
    {
        if (sdt[i] < '0' || sdt[i] > '9')
            return false;
    }

    return true;
}
```
</details>

---

### **Bài 3: Kiểm tra Mật khẩu mạnh**

Viết hàm kiểm tra mật khẩu có đủ mạnh không:
- Độ dài tối thiểu 8 ký tự
- Có ít nhất 1 chữ hoa
- Có ít nhất 1 chữ thường
- Có ít nhất 1 chữ số

```cpp
bool KiemTraMatKhauManh(const string& matKhau)
{
    // TODO: Implement
}

// Test cases:
// "Abc12345" → true
// "abc12345" → false (không có chữ hoa)
// "ABC12345" → false (không có chữ thường)
// "Abcdefgh" → false (không có số)
// "Abc123" → false (chỉ 6 ký tự)
```

<details>
<summary>Xem đáp án</summary>

```cpp
bool KiemTraMatKhauManh(const string& matKhau)
{
    // Kiểm tra độ dài
    if ((int)matKhau.length() < 8)
        return false;

    bool coHoa = false;
    bool coThuong = false;
    bool coSo = false;

    for (int i = 0; i < (int)matKhau.length(); i++)
    {
        if (matKhau[i] >= 'A' && matKhau[i] <= 'Z')
            coHoa = true;
        else if (matKhau[i] >= 'a' && matKhau[i] <= 'z')
            coThuong = true;
        else if (matKhau[i] >= '0' && matKhau[i] <= '9')
            coSo = true;
    }

    return coHoa && coThuong && coSo;
}
```
</details>

---

### **Bài 4: Kiểm tra Mã sinh viên**

Viết hàm kiểm tra mã sinh viên hợp lệ (format: SVxxxxxx):
- Bắt đầu bằng "SV"
- Theo sau là 6 chữ số

```cpp
bool KiemTraMaSinhVien(const string& maSV)
{
    // TODO: Implement
}

// Test cases:
// "SV001234" → true
// "SV123456" → true
// "sv001234" → false (chữ thường)
// "SV12345" → false (chỉ 5 số)
// "SV12345a" → false (có chữ cái)
```

<details>
<summary>Xem đáp án</summary>

```cpp
bool KiemTraMaSinhVien(const string& maSV)
{
    // Kiểm tra độ dài
    if ((int)maSV.length() != 8)
        return false;

    // Kiểm tra bắt đầu bằng "SV"
    if (maSV[0] != 'S' || maSV[1] != 'V')
        return false;

    // Kiểm tra 6 ký tự sau là số
    for (int i = 2; i < 8; i++)
    {
        if (maSV[i] < '0' || maSV[i] > '9')
            return false;
    }

    return true;
}
```
</details>

---

### **Bài 5: Tổng hợp - Validate Form đăng ký**

Viết hàm validate form đăng ký người dùng:

```cpp
struct NguoiDung
{
    string hoTen;
    string email;
    string soDienThoai;
    int tuoi;
    string matKhau;
};

bool ValidateFormDangKy(const NguoiDung& nd, string& loiThongBao)
{
    // TODO: Implement
    // Trả về true nếu hợp lệ
    // Nếu không hợp lệ, gán lỗi vào loiThongBao và trả về false
}

// Yêu cầu:
// - Họ tên: không rỗng, độ dài 3-50 ký tự
// - Email: hợp lệ (dùng hàm KiemTraEmail)
// - Số điện thoại: hợp lệ (dùng hàm KiemTraSoDienThoai)
// - Tuổi: 16-100
// - Mật khẩu: đủ mạnh (dùng hàm KiemTraMatKhauManh)
```

<details>
<summary>Xem đáp án</summary>

```cpp
bool ValidateFormDangKy(const NguoiDung& nd, string& loiThongBao)
{
    // 1. Kiểm tra họ tên
    if (KiemTraChuoiRong(nd.hoTen))
    {
        loiThongBao = "Ho ten khong duoc rong!";
        return false;
    }
    int lenHoTen = (int)nd.hoTen.length();
    if (lenHoTen < 3 || lenHoTen > 50)
    {
        loiThongBao = "Ho ten phai tu 3-50 ky tu!";
        return false;
    }

    // 2. Kiểm tra email
    if (!KiemTraEmail(nd.email))
    {
        loiThongBao = "Email khong hop le!";
        return false;
    }

    // 3. Kiểm tra số điện thoại
    if (!KiemTraSoDienThoai(nd.soDienThoai))
    {
        loiThongBao = "So dien thoai khong hop le!";
        return false;
    }

    // 4. Kiểm tra tuổi
    if (nd.tuoi < 16 || nd.tuoi > 100)
    {
        loiThongBao = "Tuoi phai tu 16-100!";
        return false;
    }

    // 5. Kiểm tra mật khẩu
    if (!KiemTraMatKhauManh(nd.matKhau))
    {
        loiThongBao = "Mat khau khong du manh! (Can it nhat 8 ky tu, co chu hoa, chu thuong va so)";
        return false;
    }

    loiThongBao = "";
    return true;
}
```
</details>

---

## 📊 TÓM TẮT

### Validation là gì?
- Kiểm tra dữ liệu đầu vào **đúng, đủ, hợp lệ**

### Tại sao cần?
- ✅ Bảo vệ chương trình khỏi crash
- ✅ Tránh dữ liệu vô nghĩa
- ✅ Cải thiện trải nghiệm người dùng
- ✅ Bảo mật

### Các loại validation:
1. **Validation format**: Ngày tháng, email, số điện thoại
2. **Validation giá trị**: Số dương, trong khoảng
3. **Validation logic nghiệp vụ**: Tồn tại, đủ số lượng, quan hệ
4. **Validation bảo mật**: Buffer overflow, injection

### Best practices:
1. Validate càng sớm càng tốt
2. Thông báo lỗi rõ ràng
3. Validate nhiều lớp
4. Tách hàm validation riêng
5. Log các lỗi validation

---

## 🎯 CHECKLIST VALIDATION

Khi viết code, hãy tự hỏi:

- [ ] Dữ liệu input có thể rỗng không?
- [ ] Dữ liệu input có thể âm không?
- [ ] Dữ liệu input có thể quá lớn không?
- [ ] Format có đúng không? (ngày, email, sdt)
- [ ] Dữ liệu có tồn tại trong hệ thống không?
- [ ] Có đủ để thực hiện thao tác không? (đủ số lượng, đủ quyền)
- [ ] Quan hệ giữa các trường có hợp lý không?
- [ ] Có nguy cơ tràn mảng không?
- [ ] Có nguy cơ bị hack không? (injection, XSS)

---

**Chúc bạn học tốt!** 🚀
