#include <iostream>
#include <string>
using namespace std;

string S(int n) {
    if (!n) return "0";
    string r = "", t = "";
    if (n < 0) { r = "-"; n = -n; }
    while (n) { t += char('0' + n % 10); n /= 10; }
    for (int i = t.size() - 1; i >= 0; i--) r += t[i];
    return r;
}

struct R { string k; float v; };
R arr[15];
int cnt = 0;

void Add() {
    R r;
    r.k = S(cnt + 1);
    cout << "\nValue: ";
    cin >> r.v;
    arr[cnt++] = r;
}

void Print() {
    for (int i = 0; i < cnt; i++)
        cout << arr[i].k << ":" << arr[i].v << " ";
    cout << "\n";
}

int main() {
    int c;
    do {
        cout << "\n1.Add 2.Print 0.Exit\n: ";
        cin >> c;
        if (c == 1) Add();
        else if (c == 2) Print();
    } while (c);
    return 0;
}
