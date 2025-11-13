#include <iostream>
#include <string>
using namespace std;

string Int2Str(int n) {
    if (!n) return "0";
    string s = "", t = "";
    if (n < 0) { s = "-"; n = -n; }
    while (n) { t += char('0' + n % 10); n /= 10; }
    for (int i = t.size() - 1; i >= 0; i--) s += t[i];
    return s;
}

struct V { string id; int val; };
V vec[20];
int sz = 0;

void Push() {
    V v;
    v.id = Int2Str(sz + 1);
    cout << "\nVal: ";
    cin >> v.val;
    vec[sz++] = v;
}

void Show() {
    for (int i = 0; i < sz; i++)
        cout << vec[i].id << ":" << vec[i].val << " ";
    cout << "\n";
}

int main() {
    int o;
    do {
        cout << "\n1.Push 2.Show 0.Exit\n: ";
        cin >> o;
        if (o == 1) Push();
        else if (o == 2) Show();
    } while (o);
    return 0;
}
