#include <iostream>
#include <memory>
#include "include/point.h"
#include "include/pentagon.h"
#include "include/hexagon.h"
#include "include/octagon.h"
#include "include/array.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

double readDouble(string msg) {
    double val;
    while (true) {
        cout << msg;
        cin >> val;
        if (!cin.fail() && val > 0) {
            clearInput();
            return val;
        }
        cout << "error ";
        clearInput();
    }
}

int readInt(string msg, int min, int max) {
    int val;
    while (true) {
        cout << msg;
        cin >> val;
        if (!cin.fail() && val >= min && val < max) {
            clearInput();
            return val;
        }
        cout << "error ";
        clearInput();
    }
}

void showMenu() {
    cout << "\n1. Add pentagon\n";
    cout << "2. Add hexagon\n";
    cout << "3. Add octagon\n";
    cout << "4. Show all\n";
    cout << "5. Delete\n";
    cout << "6. Total area\n";
    cout << "7. Compare\n";
    cout << "8. Demo\n";
    cout << "0. Exit\n";
    cout << "Choice: ";
}

void addPentagon(Array<FigurePtr<double>>& arr) {
    double x = readDouble("Center X: ");
    double y = readDouble("Center Y: ");
    double r = readDouble("Radius: ");
    arr.add(make_shared<Pentagon<double>>(x, y, r));
    cout << "Added\n";
}

void addHexagon(Array<FigurePtr<double>>& arr) {
    double x = readDouble("Center X: ");
    double y = readDouble("Center Y: ");
    double r = readDouble("Radius: ");
    arr.add(make_shared<Hexagon<double>>(x, y, r));
    cout << "Added\n";
}

void addOctagon(Array<FigurePtr<double>>& arr) {
    double x = readDouble("Center X: ");
    double y = readDouble("Center Y: ");
    double r = readDouble("Radius: ");
    arr.add(make_shared<Octagon<double>>(x, y, r));
    cout << "Added\n";
}

void showAll(Array<FigurePtr<double>>& arr) {
    if (arr.empty()) {
        cout << "Empty\n";
        return;
    }
    for (size_t i = 0; i < arr.size(); i++) {
        cout << i << ". " << arr[i]->type();
        cout << " center: " << arr[i]->center();
        cout << " area: " << arr[i]->area() << endl;
    }
}

void deleteFig(Array<FigurePtr<double>>& arr) {
    if (arr.empty()) {
        cout << "Empty\n";
        return;
    }
    showAll(arr);
    int idx = readInt("Index: ", 0, arr.size());
    try {
        arr.remove(idx);
        cout << "Deleted\n";
    } catch (...) {
        cout << "Error\n";
    }
}

void totalArea(Array<FigurePtr<double>>& arr) {
    if (arr.empty()) {
        cout << "Empty\n";
        return;
    }
    double sum = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        sum += arr[i]->area();
    }
    cout << "Total area: " << sum << endl;
}

void compare(Array<FigurePtr<double>>& arr) {
    if (arr.size() < 2) {
        cout << "Need 2 figures\n";
        return;
    }
    showAll(arr);
    int i1 = readInt("First: ", 0, arr.size());
    int i2 = readInt("Second: ", 0, arr.size());
    auto& f1 = *arr[i1];
    auto& f2 = *arr[i2];
    cout << f1.type() << " < " << f2.type() << ": " << (f1 < f2) << endl;
    cout << "Equal: " << (f1 == f2) << endl;
}

void demo(Array<FigurePtr<double>>& arr) {
    arr.add(make_shared<Pentagon<double>>(0, 0, 3));
    arr.add(make_shared<Hexagon<double>>(2, 1, 2.5));
    arr.add(make_shared<Octagon<double>>(-1, -2, 4));
    cout << "Demo figures added\n";
    showAll(arr);
}

int main() {
    cout << "Shapes program\n";
    
    Array<FigurePtr<double>> arr;
    int choice;
    
    do {
        showMenu();
        cin >> choice;
        clearInput();
        
        switch (choice) {
            case 1: addPentagon(arr); break;
            case 2: addHexagon(arr); break;
            case 3: addOctagon(arr); break;
            case 4: showAll(arr); break;
            case 5: deleteFig(arr); break;
            case 6: totalArea(arr); break;
            case 7: compare(arr); break;
            case 8: demo(arr); break;
            case 0: cout << "Bye\n"; break;
            default: cout << "Invalid\n"; break;
        }
    } while (choice != 0);
    
    return 0;
}