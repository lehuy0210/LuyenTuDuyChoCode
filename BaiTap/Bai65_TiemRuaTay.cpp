#include <iostream>
using namespace std;
int main() {
    cout << "=== TIEM RUA XE TAY ===\n";
    cout << "Loai (1=XeMay 30k, 2=OTo 80k): "; int loai; cin >> loai;
    int gia = (loai == 1) ? 30000 : 80000;
    cout << "Danh bong (+20k)? (1=Co, 0=Khong): "; int bong; cin >> bong;
    if (bong) gia += 20000;
    cout << "[OK] Tong: " << gia << " VND\n";
    return 0;
}
