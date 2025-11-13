#include <iostream>
#include <string>
using namespace std;

string N(int n) {
    if (!n) return "0";
    string r = "", t = "";
    if (n < 0) { r = "-"; n = -n; }
    while (n) { t += char('0' + n % 10); n /= 10; }
    for (int i = t.size() - 1; i >= 0; i--) r += t[i];
    return r;
}

struct I { int v; };
I ls[10];
int sz = 0;

void A() {
    I i;
    cout << "\nV: ";
    cin >> i.v;
    ls[sz++] = i;
}

void S() {
    for (int i = 0; i < sz; i++)
        cout << ls[i].v << " ";
    cout << "\n";
}

int main() {
    int o;
    do {
        cout << "\n1.A 2.S 0.X\n: ";
        cin >> o;
        if (o == 1) A();
        else if (o == 2) S();
    } while (o);
    return 0;
}
