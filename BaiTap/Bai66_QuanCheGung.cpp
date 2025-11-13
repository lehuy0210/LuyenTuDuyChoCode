#include <iostream>
using namespace std;
int main() {
    cout << "=== QUAN CHE GUNG ===\nChe gung: 25k | Che buoi: 28k | Che dau: 30k\n";
    cout << "Ly che: "; int ly; cin >> ly;
    cout << "Loai (1=Gung, 2=Buoi, 3=Dau): "; int loai; cin >> loai;
    int gia[] = {25000, 28000, 30000};
    cout << "[OK] Tong: " << (ly * gia[loai-1]) << " VND\n";
    return 0;
}
