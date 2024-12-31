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
        cout << "�����: " << brand << ", г�: " << year << ", ֳ��: " << price
            << ", ������������: " << configuration << ", �����: " << country
            << ", ���� �������: " << saleDate << ", ��������: " << buyerName << endl;
    }

    virtual void saveToFile(ofstream& out) const {
        out << brand << "," << year << "," << price << "," << configuration
            << "," << country << "," << saleDate << "," << buyerName;
    }

    // ³��������� ����� ��� �����������
    virtual void edit() {
        cout << "����������� ���������� �������� ����� ����������." << endl;
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
        cout << " �������: " << ownerName << ", �����: " << mileage
            << " ��, ����: " << condition << "%" << endl;
    }

    void saveToFile(ofstream& out) const override {
        Car::saveToFile(out);
        out << "," << ownerName << "," << mileage << "," << condition << endl;
    }

    string getType() const override {
        return "������ ����";
    }

    void edit() override {
        cout << "����������� ���������� ��� ������� ����." << endl;
        cout << "������ ������ ��������: ";
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
        cout << " ����� �� 100 ��/���: " << acceleration << " �, ��'�� �������: "
            << engineVolume << " �, ���������: " << power << " �.�." << endl;
    }

    void saveToFile(ofstream& out) const override {
        Car::saveToFile(out);
        out << "," << acceleration << "," << engineVolume << "," << power << endl;
    }

    string getType() const override {
        return "�������� ����";
    }

    void edit() override {
        cout << "����������� ����������� ����." << endl;
        cout << "������ ���� ��������� (�.�.): ";
        cin >> power;
    }
};

// ������� ���� "����������"
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
        cout << " ���: " << type << ", ����: " << weight << " �, ��������: " << dimensions << endl;
    }

    void saveToFile(ofstream& out) const override {
        Car::saveToFile(out);
        out << "," << type << "," << weight << "," << dimensions << endl;
    }

    string getType() const override {
        return "����������";
    }

    void edit() override {
        cout << "����������� ����������." << endl;
        cout << "������ ���� ���� (�): ";
        cin >> weight;
    }
};

// �������� ��������� ��� ������ � ��'������
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
            throw runtime_error("��������� ������� ���� ��� ������.");

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