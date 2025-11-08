#include <iostream>
#include <memory>
#include "include/point.h"
#include "include/pentagon.h"
#include "include/hexagon.h"
#include "include/octagon.h"
#include "include/array.h"

using namespace std;

void clearIn() {
    cin.clear();
    cin.ignore(10000, '\n');
}

double readD(string m) {
    double v;
    while (true) {
        cout << m;
        cin >> v;
        if (!cin.fail() && v > 0) {
            clearIn();
            return v;
        }
        cout << "err ";
        clearIn();
    }
}

int readI(string m, int mn, int mx) {
    int v;
    while (true) {
        cout << m;
        cin >> v;
        if (!cin.fail() && v >= mn && v < mx) {
            clearIn();
            return v;
        }
        cout << "err ";
        clearIn();
    }
}

void showMenu() {
    cout << "\n1. Add pent\n";
    cout << "2. Add hex\n";
    cout << "3. Add oct\n";
    cout << "4. Show all\n";
    cout << "5. Delete\n";
    cout << "6. Total area\n";
    cout << "7. Compare\n";
    cout << "8. Demo\n";
    cout << "0. Exit\n";
    cout << "Choice: ";
}

void addPent(Array<FigurePtr<double>>& a) {
    double x = readD("X: ");
    double y = readD("Y: ");
    double r = readD("R: ");
    a.add(make_shared<Pentagon<double>>(x, y, r));
    cout << "OK\n";
}

void addHex(Array<FigurePtr<double>>& a) {
    double x = readD("X: ");
    double y = readD("Y: ");
    double r = readD("R: ");
    a.add(make_shared<Hexagon<double>>(x, y, r));
    cout << "OK\n";
}

void addOct(Array<FigurePtr<double>>& a) {
    double x = readD("X: ");
    double y = readD("Y: ");
    double r = readD("R: ");
    a.add(make_shared<Octagon<double>>(x, y, r));
    cout << "OK\n";
}

void showAll(Array<FigurePtr<double>>& a) {
    if (a.empty()) {
        cout << "Empty\n";
        return;
    }
    for (size_t i = 0; i < a.size(); i++) {
        cout << i << ". " << a[i]->type();
        cout << " c: " << a[i]->center();
        cout << " a: " << a[i]->area() << endl;
    }
}

void delFig(Array<FigurePtr<double>>& a) {
    if (a.empty()) {
        cout << "Empty\n";
        return;
    }
    showAll(a);
    int idx = readI("Idx: ", 0, a.size());
    try {
        a.remove(idx);
        cout << "Del\n";
    } catch (...) {
        cout << "Err\n";
    }
}

void totalArea(Array<FigurePtr<double>>& a) {
    if (a.empty()) {
        cout << "Empty\n";
        return;
    }
    double sum = 0;
    for (size_t i = 0; i < a.size(); i++) {
        sum += a[i]->area();
    }
    cout << "Total: " << sum << endl;
}

void compare(Array<FigurePtr<double>>& a) {
    if (a.size() < 2) {
        cout << "Need 2\n";
        return;
    }
    showAll(a);
    int i1 = readI("First: ", 0, a.size());
    int i2 = readI("Second: ", 0, a.size());
    auto& f1 = *a[i1];
    auto& f2 = *a[i2];
    cout << f1.type() << " < " << f2.type() << ": " << (f1 < f2) << endl;
    cout << "Equal: " << (f1 == f2) << endl;
}

void demo(Array<FigurePtr<double>>& a) {
    a.add(make_shared<Pentagon<double>>(0, 0, 3));
    a.add(make_shared<Hexagon<double>>(2, 1, 2.5));
    a.add(make_shared<Octagon<double>>(-1, -2, 4));
    cout << "Demo added\n";
    showAll(a);
}

int main() {
    cout << "Shapes lab\n";
    
    Array<FigurePtr<double>> arr;
    int ch;
    
    do {
        showMenu();
        cin >> ch;
        clearIn();
        
        switch (ch) {
            case 1: addPent(arr); break;
            case 2: addHex(arr); break;
            case 3: addOct(arr); break;
            case 4: showAll(arr); break;
            case 5: delFig(arr); break;
            case 6: totalArea(arr); break;
            case 7: compare(arr); break;
            case 8: demo(arr); break;
            case 0: cout << "Bye\n"; break;
            default: cout << "Bad\n"; break;
        }
    } while (ch != 0);
    
    return 0;
}