#include "planet.hpp"
#include "star.hpp"
#include "satellite.hpp"

#include <iostream>
#include <memory>
#include <utility>

namespace planetary 
{

Planet::Planet(const std::string& name, double mass, double orbitRadius, const Star* hostStar):
m_name {name},
m_mass {mass},
m_orbitRadius {orbitRadius},
m_angle {0.0},
m_hostStar {hostStar}
{
    if (m_hostStar == nullptr)
    {
        std::cerr << "Ошибка: планета '" << m_name << "' создана без домашней звезды.\n";
    }
    else if (!m_hostStar->CanHostPlanet(m_orbitRadius))
    {
        std::cerr << "Ошибка: планета '" << m_name << "' слишком близко к звезде '" << m_hostStar->GetName() << "'. Орбита скорректирована.\n";
    }
    if (m_mass <= 0.0)
        {
            std::cerr << "Ошибка: Планета '" << m_name << "' Имеет не положительную массу. Установлено стандартное знчаение 1.0.\n";
            m_mass = 1.0;
        }
    if (m_orbitRadius <= 0.0)
        {
            std::cerr << "Ошибка: Планета '" << m_name << "' Имеет не положительный радиус орбиты. Установлено стандартное знчаение 1.0.\n";
            m_orbitRadius = 1.0;
        }
}

Planet::~Planet() {
    m_satellites.clear();
    std::cout << "Планета уничтожена: " << m_name << "\n";
}

void Planet::AddSatellite(const std::string& name, double mass, double orbitRadius)
{
    auto sat = std::make_unique<Satellite>(name, mass, orbitRadius);
    m_satellites.push_back(std::move(sat));
}

void Planet::UpdatePosition(double dt)
{
    constexpr double BASE_SPEED = 0.5;
    const double angl_speed = BASE_SPEED / m_orbitRadius;
    m_angle = angl_speed * dt;

    for (const auto& sat : m_satellites)
    {
        sat->UpdatePosition(dt);
    }

}

void Planet::Print() const {
    std::cout << "Планета " << m_name
              << ", масса = " << m_mass
              << ", радиус орбиты = " << m_orbitRadius
              << ", угол = " << m_angle;

    if (m_hostStar != nullptr) {
        std::cout << ", вокруг звезды: " << m_hostStar->GetName();
    }
    std::cout << "\n";

    for (const auto& sat : m_satellites) {
        sat->Print();
    }
}

}