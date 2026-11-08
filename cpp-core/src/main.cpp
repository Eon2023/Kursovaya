#include "star.hpp"
#include "planet.hpp"
#include "satellite.hpp"

#include <iostream>
#include <memory>

using namespace planetary;
void PrintPlanetByRef(const Planet& p) {
    std::cout << "[по ссылке] ";
    p.Print();
}

void PrintPlanetByPtr(const Planet* p) {
    std::cout << "[по указателю] ";
    p->Print();
}

int main() {
    std::cout << "========== Секция 1: статические объекты, композиция ==========\n";
    {
        Star sun("Sun", 1.989e30, 696340.0);
        Planet earth("Earth", 5.97e24, 1.5e8, &sun);

        earth.AddSatellite("Moon", 7.35e22, 384400.0);
        earth.AddSatellite("Phobos", 1.07e16, 9376.0);

        earth.Print();
        std::cout << "--- выходим из блока, смотрим порядок деструкторов ---\n";
    }

    std::cout << "\n========== Секция 2: агрегация ==========\n";
    Star* sun = new Star("Sirius", 4.0e30, 1.19e6);
    {
        Planet planet("Sirius-b", 1.0e27, 2.0e8, sun);
        planet.AddSatellite("Sirius-b-I", 1.0e22, 500000.0);

        planet.Print();
        std::cout << "--- планета уничтожается, а звезда остаётся ---\n";
    }
    std::cout << "Звезда всё ещё жива: ";
    sun->Print();

    delete sun;
    std::cout << "\n========== Секция 3: проверка правила ==========\n";
    {
        Star sun2("Sun2", 1.989e30, 696340.0);
        std::cout << "Пробуем создать планету слишком близко к звезде...\n";
        Planet bad("Bad", 1.0e22, 100.0, &sun2); 
        bad.Print();
    }

    std::cout << "\n========== Секция 4: передача по ссылке и указателю ==========\n";
    {
        Star sun3("Sun3", 1.989e30, 696340.0);
        Planet earth3("Earth3", 5.97e24, 1.5e8, &sun3);

        PrintPlanetByRef(earth3);
        PrintPlanetByPtr(&earth3);
    }

    std::cout << "\n========== Секция 5: динамическая инициализация ==========\n";
    {
        Star* s = new Star("Vega", 4.1e30, 1.7e6);

        Planet* p1 = new Planet("Vega-b", 1.0e24, 1.0e8, s);
        Planet* p2 = new Planet("Vega-c", 2.0e24, 2.0e8, s);

        p1->AddSatellite("Vega-b-I", 1.0e22, 300000.0);
        p2->AddSatellite("Vega-c-I", 1.5e22, 400000.0);

        p1->Print();
        p2->Print();

        delete p1;
        delete p2;
        delete s;
    }

    std::cout << "\n========== Секция 6: массив указателей ==========\n";
    {
        Star host("Alpha Centauri A", 2.188e30, 8.5e5);

        constexpr int COUNT = 3;
        Planet* planets[COUNT];

        planets[0] = new Planet("Planet-1", 1.0e24, 1.0e8, &host);
        planets[1] = new Planet("Planet-2", 2.0e24, 2.0e8, &host);
        planets[2] = new Planet("Planet-3", 3.0e24, 3.0e8, &host);

        planets[0]->AddSatellite("Moon-1", 1.0e22, 300000.0);
        planets[1]->AddSatellite("Moon-2", 1.5e22, 400000.0);

        for (int i = 0; i < COUNT; ++i) {
            planets[i]->Print();
        }

        for (int i = 0; i < COUNT; ++i) {
            delete planets[i];
        }
    }

    std::cout << "\n========== Секция 7: vector<unique_ptr<Planet>> ==========\n";
    {
        Star host("Proxima Centauri", 2.4e29, 1.0e5);

        std::vector<std::unique_ptr<Planet>> planets;
        planets.push_back(std::make_unique<Planet>("Proxima-b", 1.0e24, 7.0e6, &host));
        planets.push_back(std::make_unique<Planet>("Proxima-c", 2.0e24, 1.5e7, &host));

        planets[0]->AddSatellite("Proxima-b-I", 1.0e22, 50000.0);

        for (const auto& p : planets) {
            p->Print();
        }
    }
  

    std::cout << "\n========== Программа завершена ==========\n";
    return 0;
}