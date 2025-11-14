#include <iostream>
#include <string>
using namespace std;

string NumStr(int n) {
    if (!n) return "0";
    string r = "";
    if (n < 0) { r = "-"; n = -n; }
    string t = "";
    while (n) { t += char('0' + n % 10); n /= 10; }
    for (int i = t.size() - 1; i >= 0; i--) r += t[i];
    return r;
}

struct Record { string id; int value; };
Record db[60];
int size = 0;

void Add() {
    Record r;
    r.id = "R" + NumStr(size + 1);
    cout << "\nID: " << r.id << "\nValue: ";
    cin >> r.value;
    db[size++] = r;
    cout << ">>> Added\n";
}

void Show() {
    cout << "\n=== RECORDS ===\n";
    for (int i = 0; i < size; i++)
        cout << db[i].id << " " << db[i].value << "\n";
}

int main() {
    int c;
    do {
        cout << "\n1.Add 2.Show 0.Exit\n: ";
        cin >> c;
        if (c == 1) Add();
        else if (c == 2) Show();
    } while (c);
    return 0;
}
