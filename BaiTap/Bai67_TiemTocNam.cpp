#include <iostream>
using namespace std;
int main() {
    cout << "=== TIEM TOC NAM ===\nCat: 80k | Goi dau: 50k | Nhuom: 300k\n";
    cout << "Dich vu (1=Cat, 2=GoiDau, 3=Nhuom): "; int dv; cin >> dv;
    int gia[] = {80000, 50000, 300000};
    cout << "[OK] Tong: " << gia[dv-1] << " VND\n";
    return 0;
}
