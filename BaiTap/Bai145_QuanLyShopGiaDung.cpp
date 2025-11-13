#include <iostream>
#include <string>
using namespace std;

string IntToStr(int num) {
    if (num == 0) return "0";
    string result = "";
    bool neg = false;
    if (num < 0) { neg = true; num = -num; }
    while (num > 0) {
        result = char('0' + num % 10) + result;
        num /= 10;
    }
    if (neg) result = "-" + result;
    return result;
}

string FloatToStr(float num) {
    int intPart = (int)num;
    float decPart = num - intPart;
    if (decPart < 0) decPart = -decPart;
    int dec = (int)(decPart * 100 + 0.5);
    return IntToStr(intPart) + "." + (dec < 10 ? "0" : "") + IntToStr(dec);
}

struct Record {
    string id;
    string name;
    float value;
};

const int MAX = 100;
Record records[MAX];
int count = 0;

void Add() {
    Record r;
    r.id = "R" + IntToStr(1001 + count);
    cout << "\nID: " << r.id << "\n";
    cout << "Name: "; cin.ignore(); getline(cin, r.name);
    cout << "Value: "; cin >> r.value;
    records[count++] = r;
    cout << ">>> Added!\n";
}

void Display() {
    cout << "\n===== RECORDS =====\n";
    for (int i = 0; i < count; i++) {
        cout << records[i].id << " - " << records[i].name 
             << " - " << FloatToStr(records[i].value) << "\n";
    }
}

int main() {
    int c;
    do {
        cout << "\n===== SYSTEM =====\n";
        cout << "1. Add\n";
        cout << "2. Display\n";
        cout << "0. Exit\n";
        cout << ": "; cin >> c;
        
        switch(c) {
            case 1: Add(); break;
            case 2: Display(); break;
        }
    } while (c != 0);
    
    return 0;
}
