#include <iostream>
#include <string>
using namespace std;

string I2S(int n) {
    if (!n) return "0";
    string s = "", t = "";
    if (n < 0) { s = "-"; n = -n; }
    while (n) { t += char('0' + n % 10); n /= 10; }
    for (int i = t.size() - 1; i >= 0; i--) s += t[i];
    return s;
}

struct T { string n; int v; };
T a[25];
int c = 0;

void X() {
    T t;
    t.n = "N" + I2S(c + 1);
    cout << "\nVal: ";
    cin >> t.v;
    a[c++] = t;
}

void L() {
    cout << "\n=== LIST ===\n";
    for (int i = 0; i < c; i++)
        cout << a[i].n << " " << a[i].v << "\n";
}

int main() {
    int o;
    do {
        cout << "\n1.Add 2.List 0.Exit\n: ";
        cin >> o;
        if (o == 1) X();
        else if (o == 2) L();
    } while (o);
    return 0;
}
