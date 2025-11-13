#include <iostream>
#include <string>
using namespace std;

string IntToStr(int num) {
    if (num == 0) return "0";
    string result = "";
    bool isNegative = false;
    if (num < 0) { isNegative = true; num = -num; }
    while (num > 0) {
        result = char('0' + num % 10) + result;
        num /= 10;
    }
    if (isNegative) result = "-" + result;
    return result;
}

string FloatToStr(float num) {
    int intPart = (int)num;
    float decimalPart = num - intPart;
    if (decimalPart < 0) decimalPart = -decimalPart;
    int dec = (int)(decimalPart * 100 + 0.5);
    return IntToStr(intPart) + "." + (dec < 10 ? "0" : "") + IntToStr(dec);
}

struct Item {
    string id;
    string name;
    float price;
};

struct Transaction {
    string txId;
    string itemId;
    int quantity;
    float amount;
};

const int MAX = 150;
Item items[MAX];
Transaction txs[MAX];
int itemCnt = 0;
int txCnt = 0;

void AddItem() {
    Item it;
    it.id = "I" + IntToStr(1001 + itemCnt);
    cout << "\nID: " << it.id << "\n";
    cout << "Name: "; cin.ignore(); getline(cin, it.name);
    cout << "Price: "; cin >> it.price;
    items[itemCnt++] = it;
    cout << ">>> Success!\n";
}

void NewTransaction() {
    Transaction tx;
    tx.txId = "TX" + IntToStr(3001 + txCnt);
    
    cout << "\n===== NEW TRANSACTION =====\n";
    cout << "TX ID: " << tx.txId << "\n";
    
    cout << "\nItems:\n";
    for (int i = 0; i < itemCnt; i++) {
        cout << items[i].id << " - " << items[i].name 
             << " - " << FloatToStr(items[i].price) << "\n";
    }
    
    cout << "\nItem ID: "; cin >> tx.itemId;
    cout << "Qty: "; cin >> tx.quantity;
    
    float p = 0;
    for (int i = 0; i < itemCnt; i++) {
        if (items[i].id == tx.itemId) {
            p = items[i].price;
            break;
        }
    }
    
    tx.amount = p * tx.quantity;
    txs[txCnt++] = tx;
    
    cout << "\n>>> Amount: " << FloatToStr(tx.amount) << " VND\n";
}

int main() {
    int opt;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Add Item\n";
        cout << "2. New Transaction\n";
        cout << "0. Exit\n";
        cout << "Option: "; cin >> opt;
        
        switch(opt) {
            case 1: AddItem(); break;
            case 2: NewTransaction(); break;
        }
    } while (opt != 0);
    
    return 0;
}
