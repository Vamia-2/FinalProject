#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <memory>

using namespace std;

class Car {
protected:
    string brand;
    int year;
    double price;
    string configuration;
    string country;
    string saleDate;
    string buyerName;

public:
    Car(const string& brand, int year, double price, const string& configuration,
        const string& country, const string& saleDate, const string& buyerName)
        : brand(brand), year(year), price(price), configuration(configuration),
        country(country), saleDate(saleDate), buyerName(buyerName) {}

    virtual ~Car() = default;

    virtual void display() const {
        cout << "Марка: " << brand << ", Рік: " << year << ", Ціна: " << price
            << ", Комплектація: " << configuration << ", Країна: " << country
            << ", Дата продажу: " << saleDate << ", Покупець: " << buyerName << endl;
    }

    virtual void saveToFile(ofstream& out) const {
        out << brand << "," << year << "," << price << "," << configuration
            << "," << country << "," << saleDate << "," << buyerName;
    }

    // Віртуальний метод для редагування
    virtual void edit() {
        cout << "Редагування інформації базового класу недоступне." << endl;
    }

    virtual string getType() const = 0;
};
class UsedCar : public Car {
    string ownerName;
    double mileage;
    int condition;

public:
    UsedCar(const string& brand, int year, double price, const string& configuration,
        const string& country, const string& saleDate, const string& buyerName,
        const string& ownerName, double mileage, int condition)
        : Car(brand, year, price, configuration, country, saleDate, buyerName),
        ownerName(ownerName), mileage(mileage), condition(condition) {}

    void display() const override {
        Car::display();
        cout << " Власник: " << ownerName << ", Пробіг: " << mileage
            << " км, Стан: " << condition << "%" << endl;
    }

    void saveToFile(ofstream& out) const override {
        Car::saveToFile(out);
        out << "," << ownerName << "," << mileage << "," << condition << endl;
    }

    string getType() const override {
        return "Уживані авто";
    }

    void edit() override {
        cout << "Редагування інформації про уживане авто." << endl;
        cout << "Введіть нового власника: ";
        cin >> ownerName;
    }
};
class SportCar : public Car {
    double acceleration;
    double engineVolume;
    int power;

public:
    SportCar(const string& brand, int year, double price, const string& configuration,
        const string& country, const string& saleDate, const string& buyerName,
        double acceleration, double engineVolume, int power)
        : Car(brand, year, price, configuration, country, saleDate, buyerName),
        acceleration(acceleration), engineVolume(engineVolume), power(power) {}

    void display() const override {
        Car::display();
        cout << " Розгін до 100 км/год: " << acceleration << " с, Об'єм двигуна: "
            << engineVolume << " л, Потужність: " << power << " к.с." << endl;
    }

    void saveToFile(ofstream& out) const override {
        Car::saveToFile(out);
        out << "," << acceleration << "," << engineVolume << "," << power << endl;
    }

    string getType() const override {
        return "Спортивні авто";
    }

    void edit() override {
        cout << "Редагування спортивного авто." << endl;
        cout << "Введіть нову потужність (к.с.): ";
        cin >> power;
    }
};

// Дочірній клас "Спецтехніка"
class SpecialVehicle : public Car {
    string type;
    double weight;
    string dimensions;

public:
    SpecialVehicle(const string& brand, int year, double price, const string& configuration,
        const string& country, const string& saleDate, const string& buyerName,
        const string& type, double weight, const string& dimensions)
        : Car(brand, year, price, configuration, country, saleDate, buyerName),
        type(type), weight(weight), dimensions(dimensions) {}

    void display() const override {
        Car::display();
        cout << " Тип: " << type << ", Вага: " << weight << " т, Габарити: " << dimensions << endl;
    }

    void saveToFile(ofstream& out) const override {
        Car::saveToFile(out);
        out << "," << type << "," << weight << "," << dimensions << endl;
    }

    string getType() const override {
        return "Спецтехніка";
    }

    void edit() override {
        cout << "Редагування спецтехніки." << endl;
        cout << "Введіть нову вагу (т): ";
        cin >> weight;
    }
};

// Основний контейнер для роботи з об'єктами
class CarRepository {
    vector<shared_ptr<Car>> cars;

public:
    void addCar(shared_ptr<Car> car) {
        cars.push_back(car);
    }

    void displayAll() const {
        for (const auto& car : cars) {
            car->display();
            cout << "----------------------------------" << endl;
        }
    }

    void saveToFile(const string& filename) const {
        ofstream out(filename);
        if (!out)
            throw runtime_error("Неможливо відкрити файл для запису.");

        for (const auto& car : cars) {
            car->saveToFile(out);
        }
    }

    void sortByPrice() {
        sort(cars.begin(), cars.end(), [](const shared_ptr<Car>& a, const shared_ptr<Car>& b) {
            return a->getType() < b->getType();
            });
    }

    void searchByType(const string& type) const {
        for (const auto& car : cars) {
            if (car->getType() == type) {
                car->display();
            }
        }
    }
};