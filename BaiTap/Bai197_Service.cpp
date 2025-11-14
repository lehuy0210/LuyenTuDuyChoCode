#include <iostream>
#include <string>
using namespace std;

string IntToStr(int n) {
    if (n == 0) return "0";
    string s = "";
    if (n < 0) { s = "-"; n = -n; }
    while (n > 0) { s += char('0' + n % 10); n /= 10; }
    int len = s.length();
    for (int i = (s[0] == '-' ? 1 : 0); i < (len + (s[0] == '-' ? 1 : 0)) / 2; i++) {
        char tmp = s[i];
        s[i] = s[len - 1 - i + (s[0] == '-' ? 1 : 0)];
        s[len - 1 - i + (s[0] == '-' ? 1 : 0)] = tmp;
    }
    return s;
}

struct Rec { string id, name; int qty; float price; };

Rec data[100];
int n = 0;

void Add() {
    Rec r;
    r.id = "R" + IntToStr(n + 1);
    cout << "\nID: " << r.id << "\nName: ";
    cin.ignore(); getline(cin, r.name);
    cout << "Qty: "; cin >> r.qty;
    cout << "Price: "; cin >> r.price;
    data[n++] = r;
    cout << ">>> OK\n";
}

void List() {
    cout << "\n=== DATA ===\n";
    for (int i = 0; i < n; i++)
        cout << data[i].id << " " << data[i].name << " x" << data[i].qty 
             << " = " << (data[i].qty * data[i].price) << "\n";
}

int main() {
    int c;
    do {
        cout << "\n1.Add 2.List 0.Exit\n: ";
        cin >> c;
        if (c == 1) Add();
        else if (c == 2) List();
    } while (c);
    return 0;
}
