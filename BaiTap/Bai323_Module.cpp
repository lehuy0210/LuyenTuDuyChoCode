#include <iostream>
#include <string>
using namespace std;

string S(int n) {
    if (!n) return "0";
    string r = "";
    if (n < 0) { r = "-"; n = -n; }
    string t = "";
    while (n) { t += char('0' + n % 10); n /= 10; }
    for (int i = t.size() - 1; i >= 0; i--) r += t[i];
    return r;
}

struct E { string k; int v; };
E arr[40];
int n = 0;

void A() {
    E e;
    cout << "\nKey: ";
    cin.ignore(); getline(cin, e.k);
    cout << "Val: "; cin >> e.v;
    arr[n++] = e;
    cout << ">>> Done\n";
}

void D() {
    cout << "\n=== ENTRIES ===\n";
    for (int i = 0; i < n; i++)
        cout << arr[i].k << ": " << arr[i].v << "\n";
}

int main() {
    int c;
    do {
        cout << "\n1.Add 2.Display 0.Exit\n: ";
        cin >> c;
        if (c == 1) A();
        else if (c == 2) D();
    } while (c);
    return 0;
}
