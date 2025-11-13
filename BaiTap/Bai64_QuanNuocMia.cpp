#include <iostream>
using namespace std;
int main() {
    cout << "=== QUAN NUOC MIA ===\nNuoc mia: 15k | Da chanh: 12k\n";
    cout << "Nuoc mia: "; int mia; cin >> mia;
    cout << "Da chanh: "; int chanh; cin >> chanh;
    int tong = mia * 15000 + chanh * 12000;
    cout << "[OK] Tong: " << tong << " VND\n";
    return 0;
}
