#include <iostream>
using namespace std;
int main() {
    cout << "=== TIEM COM ===\nCom: 15k | Canh: 10k | Thit: 25k\n";
    cout << "Suat com: "; int com; cin >> com;
    cout << "Canh: "; int canh; cin >> canh;
    cout << "Thit: "; int thit; cin >> thit;
    int tong = com * 15000 + canh * 10000 + thit * 25000;
    cout << "[OK] Tong: " << tong << " VND\n";
    return 0;
}
