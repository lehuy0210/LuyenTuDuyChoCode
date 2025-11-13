#include <iostream>
#include <string>
using namespace std;

string IntToStr(int n) {
    if (!n) return "0";
    string s = "";
    if (n < 0) { s = "-"; n = -n; }
    string t = "";
    while (n) { t += char('0' + n % 10); n /= 10; }
    for (int i = t.length() - 1; i >= 0; i--) s += t[i];
    return s;
}

struct Entry { string code; float amount; };

Entry entries[80];
int count = 0;

void Create() {
    Entry e;
    e.code = "E" + IntToStr(count + 1);
    cout << "\nCode: " << e.code << "\nAmount: ";
    cin >> e.amount;
    entries[count++] = e;
    cout << ">>> Created\n";
}

void Display() {
    cout << "\n=== ENTRIES ===\n";
    float sum = 0;
    for (int i = 0; i < count; i++) {
        cout << entries[i].code << " " << entries[i].amount << "\n";
        sum += entries[i].amount;
    }
    cout << "Total: " << sum << "\n";
}

int main() {
    int o;
    do {
        cout << "\n1.Create 2.Display 0.Exit\n: ";
        cin >> o;
        if (o == 1) Create();
        else if (o == 2) Display();
    } while (o);
    return 0;
}
