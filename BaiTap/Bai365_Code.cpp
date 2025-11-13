#include <iostream>
#include <string>
using namespace std;

string N(int n) {
    if (!n) return "0";
    string s = "", t = "";
    if (n < 0) { s = "-"; n = -n; }
    while (n) { t += char('0' + n % 10); n /= 10; }
    for (int i = t.size() - 1; i >= 0; i--) s += t[i];
    return s;
}

struct D { string id; float val; };
D db[30];
int c = 0;

void I() {
    D d;
    d.id = "D" + N(c + 1);
    cout << "\nID: " << d.id << "\nVal: ";
    cin >> d.val;
    db[c++] = d;
    cout << ">>> OK\n";
}

void P() {
    cout << "\n=== DB ===\n";
    for (int i = 0; i < c; i++)
        cout << db[i].id << " " << db[i].val << "\n";
}

int main() {
    int o;
    do {
        cout << "\n1.Insert 2.Print 0.Exit\n: ";
        cin >> o;
        if (o == 1) I();
        else if (o == 2) P();
    } while (o);
    return 0;
}
