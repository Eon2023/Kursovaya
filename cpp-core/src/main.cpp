#include "star.hpp"
#include "planet.hpp"
#include "satellite.hpp"

#include <array>
#include <iostream>
#include <memory>

#ifdef _WIN32
#include <windows.h>
#endif

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
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::cout << std::unitbuf;  // чтобы сообщения std::cerr не обгоняли вывод

    std::cout << "=== ЛР 3. Часть 2. C++: умные указатели ===\n";

    std::cout << "\n========== Секция 1: статические объекты, композиция ==========\n";
    {
        auto sun = std::make_shared<Star>("Sun", 1.989e30, 696340.0);
        Planet earth("Earth", 5.97e24, 1.5e8, sun);

        earth.AddSatellite("Moon", 7.35e22, 384400.0);
        earth.AddSatellite("Phobos", 1.07e16, 9376.0);

        earth.Print();
        std::cout << "use_count звезды: " << sun.use_count()
                  << " (планета держит weak_ptr и не владеет звездой)\n";
        std::cout << "--- выходим из блока, смотрим порядок деструкторов ---\n";
    }

    std::cout << "\n========== Секция 2: агрегация, shared_ptr и weak_ptr ==========\n";
    {
        auto sun = std::make_shared<Star>("Sirius", 4.0e30, 1.19e6);
        std::cout << "Сразу после создания звезды: use_count = " << sun.use_count() << "\n";

        {
            auto starCopy = sun;
            std::cout << "После копии shared_ptr:      use_count = " << sun.use_count() << "\n";
        }

        std::cout << "После уничтожения копии:     use_count = " << sun.use_count() << "\n";

        Planet planet("Sirius-b", 1.0e27, 2.0e8, sun);
        planet.AddSatellite("Sirius-b-I", 1.0e22, 500000.0);

        planet.Print();
        std::cout << "Звезда жива: " << (planet.GetHostStar() ? "да" : "нет") << "\n";

        sun.reset();
        std::cout << "--- последний shared_ptr на звезду уничтожен ---\n";
        planet.Print();
        std::cout << "Звезда жива: " << (planet.GetHostStar() ? "да" : "нет") << "\n";
        std::cout << "--- планета продолжает работать без звезды ---\n";
    }

    std::cout << "\n========== Секция 3: проверка правила ==========\n";
    {
        auto sun2 = std::make_shared<Star>("Sun2", 1.989e30, 696340.0);
        std::cout << "Пробуем создать планету слишком близко к звезде...\n";
        Planet bad("Bad", 1.0e22, 100.0, sun2);
        bad.Print();
    }

    std::cout << "\n========== Секция 4: передача по ссылке и указателю ==========\n";
    {
        auto sun3 = std::make_shared<Star>("Sun3", 1.989e30, 696340.0);
        Planet earth3("Earth3", 5.97e24, 1.5e8, sun3);

        PrintPlanetByRef(earth3);
        PrintPlanetByPtr(&earth3);
    }

    std::cout << "\n========== Секция 5: unique_ptr и передача владения ==========\n";
    {
        auto s = std::make_shared<Star>("Vega", 4.1e30, 1.7e6);

        auto p1 = std::make_unique<Planet>("Vega-b", 1.0e24, 1.0e8, s);
        auto p2 = std::make_unique<Planet>("Vega-c", 2.0e24, 2.0e8, s);

        p1->AddSatellite("Vega-b-I", 1.0e22, 300000.0);
        p2->AddSatellite("Vega-c-I", 1.5e22, 400000.0);

        p1->Print();
        p2->Print();

        std::unique_ptr<Planet> owner = std::move(p1);
        std::cout << "После std::move исходный указатель p1: "
                  << (p1 ? "владеет объектом" : "пуст") << "\n";
        std::cout << "--- выходим из блока: delete не нужен ---\n";
    }

    std::cout << "\n========== Секция 6: массив указателей ==========\n";
    {
        auto host = std::make_shared<Star>("Alpha Centauri A", 2.188e30, 8.5e5);

        constexpr int COUNT = 3;
        std::array<std::unique_ptr<Planet>, COUNT> planets;

        planets[0] = std::make_unique<Planet>("Planet-1", 1.0e24, 1.0e8, host);
        planets[1] = std::make_unique<Planet>("Planet-2", 2.0e24, 2.0e8, host);
        planets[2] = std::make_unique<Planet>("Planet-3", 3.0e24, 3.0e8, host);

        planets[0]->AddSatellite("Moon-1", 1.0e22, 300000.0);
        planets[1]->AddSatellite("Moon-2", 1.5e22, 400000.0);

        for (int i = 0; i < COUNT; ++i) {
            planets[i]->Print();
        }

        std::cout << "--- массив уничтожается автоматически, delete[] не нужен ---\n";
    }

    std::cout << "\n========== Секция 7: vector<unique_ptr<Planet>> ==========\n";
    {
        auto host = std::make_shared<Star>("Proxima Centauri", 2.4e29, 1.0e5);

        std::vector<std::unique_ptr<Planet>> planets;
        planets.push_back(std::make_unique<Planet>("Proxima-b", 1.0e24, 7.0e6, host));
        planets.push_back(std::make_unique<Planet>("Proxima-c", 2.0e24, 1.5e7, host));

        planets[0]->AddSatellite("Proxima-b-I", 1.0e22, 50000.0);

        for (const auto& p : planets) {
            p->Print();
        }
    }

    std::cout << "\n========== Программа завершена ==========\n";
    return 0;
}
