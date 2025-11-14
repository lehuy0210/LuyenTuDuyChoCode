#include <iostream>
using namespace std;
int main() {
    cout << "=== PHOTOCOPY ===\n";
    cout << "So trang: "; int n; cin >> n;
    cout << "Mau (1=Den-trang 500d, 2=Mau 2000d): "; int loai; cin >> loai;
    int tong = n * (loai == 1 ? 500 : 2000);
    cout << "[OK] Tong: " << tong << " VND\n";
    return 0;
}
