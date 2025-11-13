#include <iostream>
#include <string>
using namespace std;
string IntToStr(int n) { if (!n) return "0"; string s = ""; while (n > 0) { s = char('0' + n % 10) + s; n /= 10; } return s; }
struct BanhMi { string ten; float gia; };
BanhMi ds[5] = {{"Pate", 25000}, {"Thit", 30000}, {"Xa xiu", 35000}};
void Ban() {
    for (int i = 0; i < 3; i++) cout << (i+1) << ". " << ds[i].ten << " - " << IntToStr((int)ds[i].gia) << "\n";
    cout << "Chon: "; int c, sl; cin >> c >> sl; c--;
    cout << "[OK] Tong: " << IntToStr((int)(ds[c].gia * sl)) << " VND\n";
}
int main() { while (1) { cout << "\n1. Ban | 0. Thoat\n"; int c; cin >> c; if (c == 1) Ban(); else break; } return 0; }
