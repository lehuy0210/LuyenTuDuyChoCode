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

struct Data { string id, name; float val; };

const int MAX = 80;
Data items[MAX];
int cnt = 0;

void Add() {
    Data d;
    d.id = "D" + IntToStr(1001 + cnt);
    cout << "\nID: " << d.id << "\nName: ";
    cin.ignore(); getline(cin, d.name);
    cout << "Value: "; cin >> d.val;
    items[cnt++] = d;
    cout << ">>> OK\n";
}

void Show() {
    cout << "\n=== LIST ===\n";
    for (int i = 0; i < cnt; i++)
        cout << items[i].id << " " << items[i].name << " " << FloatToStr(items[i].val) << "\n";
}

int main() {
    int c;
    do {
        cout << "\n1.Add 2.Show 0.Exit\n: ";
        cin >> c;
        if (c == 1) Add();
        else if (c == 2) Show();
    } while (c != 0);
    return 0;
}
