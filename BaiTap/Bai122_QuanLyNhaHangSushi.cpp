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

struct Product {
    string id;
    string name;
    float price;
    int stock;
};

struct Bill {
    string billId;
    string customerName;
    float total;
};

const int MAX = 100;
Product products[MAX];
Bill bills[MAX];
int productCount = 0;
int billCount = 0;

void AddProduct() {
    Product p;
    p.id = "P" + IntToStr(1001 + productCount);
    cout << "\nID: " << p.id << "\n";
    cout << "Name: "; cin.ignore(); getline(cin, p.name);
    cout << "Price: "; cin >> p.price;
    cout << "Stock: "; cin >> p.stock;
    products[productCount++] = p;
    cout << ">>> Added!\n";
}

void CreateBill() {
    Bill b;
    b.billId = "B" + IntToStr(2001 + billCount);
    
    cout << "\n===== NEW BILL =====\n";
    cout << "Bill ID: " << b.billId << "\n";
    cout << "Customer: "; cin.ignore(); getline(cin, b.customerName);
    
    cout << "\nProducts:\n";
    for (int i = 0; i < productCount; i++) {
        cout << products[i].id << " - " << products[i].name 
             << " - " << FloatToStr(products[i].price) << " VND\n";
    }
    
    string pid;
    int qty;
    cout << "\nProduct ID: "; cin >> pid;
    cout << "Quantity: "; cin >> qty;
    
    float price = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == pid) {
            price = products[i].price;
            break;
        }
    }
    
    b.total = price * qty;
    bills[billCount++] = b;
    
    cout << "\n>>> Total: " << FloatToStr(b.total) << " VND\n";
}

int main() {
    int choice;
    do {
        cout << "\n===== SYSTEM =====\n";
        cout << "1. Add Product\n";
        cout << "2. Create Bill\n";
        cout << "0. Exit\n";
        cout << "Choice: "; cin >> choice;
        
        switch(choice) {
            case 1: AddProduct(); break;
            case 2: CreateBill(); break;
        }
    } while (choice != 0);
    
    return 0;
}
