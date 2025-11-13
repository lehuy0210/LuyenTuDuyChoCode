#include <iostream>
#include <string>
using namespace std;

string IntToStr(int n) {
    if (n == 0) return "0";
    string s = "";
    bool neg = n < 0;
    if (neg) n = -n;
    while (n > 0) { s = char('0' + n % 10) + s; n /= 10; }
    return neg ? "-" + s : s;
}

string FloatToStr(float n) {
    int i = (int)n;
    int d = (int)((n - i) * 100 + 0.5);
    if (d < 0) d = -d;
    return IntToStr(i) + "." + (d < 10 ? "0" : "") + IntToStr(d);
}

struct Item { string code, desc; float price; };

Item list[100];
int total = 0;

void Insert() {
    Item it;
    it.code = "C" + IntToStr(1001 + total);
    cout << "\nCode: " << it.code << "\nDesc: ";
    cin.ignore(); getline(cin, it.desc);
    cout << "Price: "; cin >> it.price;
    list[total++] = it;
    cout << ">>> Done\n";
}

void View() {
    cout << "\n=== ITEMS ===\n";
    for (int i = 0; i < total; i++)
        cout << list[i].code << " " << list[i].desc << " " << FloatToStr(list[i].price) << "\n";
}

int main() {
    int opt;
    do {
        cout << "\n1.Insert 2.View 0.Exit\n: ";
        cin >> opt;
        if (opt == 1) Insert();
        else if (opt == 2) View();
    } while (opt != 0);
    return 0;
}
