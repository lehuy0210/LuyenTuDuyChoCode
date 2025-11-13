#include <iostream>
using namespace std;
int main() {
    cout << "=== SIEU THI MINI ===\n";
    cout << "So mat hang: "; int n; cin >> n;
    int tong = 0;
    for (int i = 0; i < n; i++) {
        int gia, sl; cin >> gia >> sl;
        tong += gia * sl;
    }
    cout << "[OK] Tong: " << tong << " VND\n";
    return 0;
}
