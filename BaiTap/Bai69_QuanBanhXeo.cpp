#include <iostream>
using namespace std;
int main() {
    cout << "=== QUAN BANH XEO ===\nBanh xeo: 35k | Nem lui: 40k\n";
    cout << "Banh xeo: "; int xeo; cin >> xeo;
    cout << "Nem lui: "; int nem; cin >> nem;
    int tong = xeo * 35000 + nem * 40000;
    cout << "[OK] Tong: " << tong << " VND\n";
    return 0;
}
