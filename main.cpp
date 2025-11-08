#include <iostream>
#include <memory>
#include <limits>
#include "include/point.h"
#include "include/pentagon.h"
#include "include/hexagon.h"
#include "include/octagon.h"
#include "include/array.h"

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getValidDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value <= 0) {
            std::cout << "Ошибка: введите положительное число! ";
            clearInputBuffer();
        } else {
            clearInputBuffer();
            return value;
        }
    }
}

int getValidInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cout << "Ошибка: введите число от " << min << " до " << max << "! ";
            clearInputBuffer();
        } else {
            clearInputBuffer();
            return value;
        }
    }
}

void printMenu() {
    std::cout << "\n=== Меню работы с фигурами ===" << std::endl;
    std::cout << "1. Добавить пятиугольник" << std::endl;
    std::cout << "2. Добавить шестиугольник" << std::endl;
    std::cout << "3. Добавить восьмиугольник" << std::endl;
    std::cout << "4. Показать все фигуры" << std::endl;
    std::cout << "5. Удалить фигуру по индексу" << std::endl;
    std::cout << "6. Вычислить общую площадь" << std::endl;
    std::cout << "7. Сравнить две фигуры" << std::endl;
    std::cout << "8. Запустить демо-пример" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите действие: ";
}

void addPentagon(Array<FigurePtr<double>>& figures) {
    std::cout << "\n--- Создание пятиугольника ---" << std::endl;
    double x = getValidDouble("Введите координату X центра: ");
    double y = getValidDouble("Введите координату Y центра: ");
    double radius = getValidDouble("Введите радиус описанной окружности: ");
    
    auto pentagon = std::make_shared<Pentagon<double>>(x, y, radius);
    figures.add(pentagon);
    std::cout << "Пятиугольник добавлен успешно!" << std::endl;
}

void addHexagon(Array<FigurePtr<double>>& figures) {
    std::cout << "\n--- Создание шестиугольника ---" << std::endl;
    double x = getValidDouble("Введите координату X центра: ");
    double y = getValidDouble("Введите координату Y центра: ");
    double radius = getValidDouble("Введите радиус описанной окружности: ");
    
    auto hexagon = std::make_shared<Hexagon<double>>(x, y, radius);
    figures.add(hexagon);
    std::cout << "Шестиугольник добавлен успешно!" << std::endl;
}

void addOctagon(Array<FigurePtr<double>>& figures) {
    std::cout << "\n--- Создание восьмиугольника ---" << std::endl;
    double x = getValidDouble("Введите координату X центра: ");
    double y = getValidDouble("Введите координату Y центра: ");
    double radius = getValidDouble("Введите радиус описанной окружности: ");
    
    auto octagon = std::make_shared<Octagon<double>>(x, y, radius);
    figures.add(octagon);
    std::cout << "Восьмиугольник добавлен успешно!" << std::endl;
}

void showAllFigures(Array<FigurePtr<double>>& figures) {
    if (figures.empty()) {
        std::cout << "\nСписок фигур пуст!" << std::endl;
        return;
    }
    
    std::cout << "\n=== Список всех фигур ===" << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Фигура #" << i << " - " << figures[i]->name() << ":" << std::endl;
        std::cout << "  Центр: " << figures[i]->geometric_center() << std::endl;
        std::cout << "  Площадь: " << figures[i]->area() << std::endl;
    }
}

void removeFigure(Array<FigurePtr<double>>& figures) {
    if (figures.empty()) {
        std::cout << "\nСписок фигур пуст!" << std::endl;
        return;
    }
    
    showAllFigures(figures);
    int index = getValidInt("\nВведите индекс фигуры для удаления: ", 0, figures.size() - 1);
    
    try {
        figures.remove_at(index);
        std::cout << "Фигура успешно удалена!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка при удалении: " << e.what() << std::endl;
    }
}

void calculateTotalArea(Array<FigurePtr<double>>& figures) {
    if (figures.empty()) {
        std::cout << "\nСписок фигур пуст!" << std::endl;
        return;
    }
    
    double total = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total += figures[i]->area();
    }
    
    std::cout << "\nОбщая площадь всех фигур: " << total << std::endl;
}

void compareFigures(Array<FigurePtr<double>>& figures) {
    if (figures.size() < 2) {
        std::cout << "\nНедостаточно фигур для сравнения! Нужно как минимум 2 фигуры." << std::endl;
        return;
    }
    
    showAllFigures(figures);
    std::cout << "\n--- Сравнение фигур ---" << std::endl;
    int index1 = getValidInt("Введите индекс первой фигуры: ", 0, figures.size() - 1);
    int index2 = getValidInt("Введите индекс второй фигуры: ", 0, figures.size() - 1);
    
    auto& fig1 = *figures[index1];
    auto& fig2 = *figures[index2];
    
    std::cout << "\nРезультаты сравнения:" << std::endl;
    std::cout << "Фигура 1: " << fig1.name() << " (площадь: " << fig1.area() << ")" << std::endl;
    std::cout << "Фигура 2: " << fig2.name() << " (площадь: " << fig2.area() << ")" << std::endl;
    std::cout << "Первая фигура < Второй фигуры: " << (fig1 < fig2) << std::endl;
    std::cout << "Первая фигура > Второй фигуры: " << (fig1 > fig2) << std::endl;
    std::cout << "Фигуры равны по площади: " << (fig1 == fig2) << std::endl;
    std::cout << "Фигуры разные по площади: " << (fig1 != fig2) << std::endl;
}

void runDemo(Array<FigurePtr<double>>& figures) {
    std::cout << "\n=== Запуск демо-примера ===" << std::endl;
    
    // Добавляем демо-фигуры
    auto demo1 = std::make_shared<Pentagon<double>>(0, 0, 3.0);
    auto demo2 = std::make_shared<Hexagon<double>>(2, 1, 2.5);
    auto demo3 = std::make_shared<Octagon<double>>(-1, -2, 4.0);
    
    figures.add(demo1);
    figures.add(demo2);
    figures.add(demo3);
    
    std::cout << "Добавлены демо-фигуры:" << std::endl;
    std::cout << "- Пятиугольник (центр: 0,0, радиус: 3)" << std::endl;
    std::cout << "- Шестиугольник (центр: 2,1, радиус: 2.5)" << std::endl;
    std::cout << "- Восьмиугольник (центр: -1,-2, радиус: 4)" << std::endl;
    
    showAllFigures(figures);
    
    double total = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total += figures[i]->area();
    }
    std::cout << "Общая площадь демо-фигур: " << total << std::endl;
}

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "   Работа с геометрическими фигурами" << std::endl;
    std::cout << " 5-угольник, 6-угольник, 8-угольник" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    std::cout << "\nОграничения ввода:" << std::endl;
    std::cout << "- Координаты: любые числа" << std::endl;
    std::cout << "- Радиус: только положительные числа" << std::endl;
    std::cout << "- Индексы: целые числа в пределах размера массива" << std::endl;
    std::cout << "- При ошибочном вводе программа запросит данные повторно" << std::endl;
    
    Array<FigurePtr<double>> figures;
    int choice;
    
    do {
        printMenu();
        std::cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addPentagon(figures);
                break;
            case 2:
                addHexagon(figures);
                break;
            case 3:
                addOctagon(figures);
                break;
            case 4:
                showAllFigures(figures);
                break;
            case 5:
                removeFigure(figures);
                break;
            case 6:
                calculateTotalArea(figures);
                break;
            case 7:
                compareFigures(figures);
                break;
            case 8:
                runDemo(figures);
                break;
            case 0:
                std::cout << "\nВыход из программы..." << std::endl;
                break;
            default:
                std::cout << "\nНеверный выбор! Попробуйте снова." << std::endl;
                break;
        }
    } while (choice != 0);
    
    return 0;
}