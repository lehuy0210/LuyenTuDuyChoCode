# BÀI 15: SPA/SALON

## Pattern
- **Gói liệu trình**: Mua trước N buổi, dùng dần
- **Điểm danh**: Mỗi lần dùng = trừ 1 buổi
- **Tracking**: Theo dõi số buổi còn lại

```cpp
int conLai = soBuoiGoi - buoiDaSuDung;
if (conLai > 0) {
    buoiDaSuDung++;
    cout << "Con lai: " << conLai - 1 << " buoi\n";
}
```

Ứng dụng: Gym (gói tập), massage, yoga
