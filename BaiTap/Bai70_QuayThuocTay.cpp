#include <iostream>
using namespace std;
int main() {
    cout << "=== QUAY THUOC TAY ===\nParacetamol: 5k | Vitamin C: 8k | Cao dan hong: 15k\n";
    cout << "1=Para, 2=VitC, 3=CaoDanHong\nChon: "; int loai, sl; cin >> loai >> sl;
    int gia[] = {5000, 8000, 15000};
    cout << "[OK] Tong: " << (gia[loai-1] * sl) << " VND\n";
    return 0;
}
