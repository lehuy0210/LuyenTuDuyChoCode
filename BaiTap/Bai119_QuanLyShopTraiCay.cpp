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
    string ma;
    string ten;
    float gia;
    int soLuong;
};

struct Order {
    string maOrder;
    string tenKH;
    string sdtKH;
    float tongTien;
};

const int MAX_ITEM = 100;
const int MAX_ORDER = 200;
Item dsItem[MAX_ITEM];
Order dsOrder[MAX_ORDER];
int soItem = 0;
int soOrder = 0;

void ThemItem() {
    Item item;
    item.ma = "IT" + IntToStr(1001 + soItem);
    cout << "\nMa: " << item.ma << "\n";
    cout << "Ten: "; cin.ignore(); getline(cin, item.ten);
    cout << "Gia: "; cin >> item.gia;
    cout << "So luong: "; cin >> item.soLuong;
    dsItem[soItem++] = item;
    cout << ">>> Them thanh cong!\n";
}

void TaoOrder() {
    Order order;
    order.maOrder = "ORD" + IntToStr(2001 + soOrder);
    
    cout << "\n===== TAO ORDER =====\n";
    cout << "Ma order: " << order.maOrder << "\n";
    cout << "Ten khach hang: "; cin.ignore(); getline(cin, order.tenKH);
    cout << "SDT: "; getline(cin, order.sdtKH);
    
    cout << "\nDanh sach san pham:\n";
    for (int i = 0; i < soItem; i++) {
        cout << dsItem[i].ma << " - " << dsItem[i].ten 
             << " - " << FloatToStr(dsItem[i].gia) << " VND\n";
    }
    
    string ma;
    int sl;
    cout << "\nMa san pham: "; cin >> ma;
    cout << "So luong: "; cin >> sl;
    
    float gia = 0;
    for (int i = 0; i < soItem; i++) {
        if (dsItem[i].ma == ma) {
            gia = dsItem[i].gia;
            break;
        }
    }
    
    order.tongTien = gia * sl;
    dsOrder[soOrder++] = order;
    
    cout << "\n>>> Tong tien: " << FloatToStr(order.tongTien) << " VND\n";
}

void HienThiOrder() {
    cout << "\n===== DANH SACH ORDER =====\n";
    for (int i = 0; i < soOrder; i++) {
        cout << dsOrder[i].maOrder << " - " << dsOrder[i].tenKH 
             << " - " << FloatToStr(dsOrder[i].tongTien) << " VND\n";
    }
}

int main() {
    int chon;
    do {
        cout << "\n===== HE THONG =====\n";
        cout << "1. Them san pham\n";
        cout << "2. Tao order\n";
        cout << "3. Hien thi order\n";
        cout << "0. Thoat\n";
        cout << "Chon: "; cin >> chon;
        
        switch(chon) {
            case 1: ThemItem(); break;
            case 2: TaoOrder(); break;
            case 3: HienThiOrder(); break;
        }
    } while (chon != 0);
    
    return 0;
}
