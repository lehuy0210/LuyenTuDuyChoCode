#include <iostream>
using namespace std;
int main() {
    cout << "=== Parking ===\n";
    cout << "So luong: "; int n; cin >> n;
    cout << "Don gia: "; int gia; cin >> gia;
    cout << "[OK] Tong: " << (n * gia) << " VND\n";
    return 0;
}
