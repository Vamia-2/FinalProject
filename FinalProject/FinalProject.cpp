#include "Car.h"

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    try {

        CarRepository repository;

        repository.addCar(make_shared<UsedCar>("Toyota", 2015, 15000, "Середній", "Японія", "2023-01-01", "Іваненко Іван", "Петренко Петро", 120000, 80));
        repository.addCar(make_shared<SportCar>("Ferrari", 2022, 250000, "Максимальний", "Італія", "2024-01-01", "Сидоренко Сидір", 3.5, 4.5, 650));
        repository.addCar(make_shared<SpecialVehicle>("Cat", 2020, 80000, "Будівельна", "США", "2023-06-15", "Ковальчук Микола", "Бульдозер", 8.5, "3x2x1.5"));

        repository.displayAll();
        repository.sortByPrice();
        cout << "Відсортований список:\n";
        repository.displayAll();

        repository.saveToFile("cars.txt");
    }
    catch (const exception& ex) {
        cerr << "Помилка: " << ex.what() << endl;
    }

    return 0;
}

