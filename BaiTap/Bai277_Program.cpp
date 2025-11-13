#include <iostream>
#include <string>
using namespace std;

string Str(int n) {
    if (!n) return "0";
    string s = "";
    if (n < 0) { s = "-"; n = -n; }
    string t = "";
    while (n) { t += char('0' + n % 10); n /= 10; }
    for (int i = t.size() - 1; i >= 0; i--) s += t[i];
    return s;
}

struct Data { string name; int val; };
Data items[50];
int cnt = 0;

void New() {
    Data d;
    cout << "\nName: ";
    cin.ignore(); getline(cin, d.name);
    cout << "Value: "; cin >> d.val;
    items[cnt++] = d;
    cout << ">>> OK\n";
}

void List() {
    cout << "\n=== DATA ===\n";
    for (int i = 0; i < cnt; i++)
        cout << (i+1) << ". " << items[i].name << " = " << items[i].val << "\n";
}

int main() {
    int o;
    do {
        cout << "\n1.New 2.List 0.Exit\n: ";
        cin >> o;
        if (o == 1) New();
        else if (o == 2) List();
    } while (o);
    return 0;
}
