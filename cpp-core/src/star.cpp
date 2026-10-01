#include "star.hpp"

#include <iostream>

namespace planetary {

Star::Star(const std::string& name, double mass, double radius):
m_name {name},
m_mass {mass},
m_radius {radius}
{
    if (m_mass <= 0.0)
    {
        std::cerr << "Ошибка: Звезда '" << m_name << "' Имеет не положительную массу. Установлено стандартное знчаение 1.0.\n";
        m_mass = 1.0;
    }
        if (m_radius <= 0.0)
    {
        std::cerr << "Ошибка: Звезда '" << m_name << "' Имеет не положительный радиус. Установлено стандартное знчаение 1.0.\n";
        m_radius = 1.0;
    }
}

Star::~Star()
{
    std::cout << "Звезда была уничтожена: " << m_name << "\n";
}

void Star::Print() const
{
std::cout << "Звезда " << m_name << ", масса = " << m_mass << ", радиус = " << m_radius << "\n";
}

bool Star::CanHostPlanet(double distance) const
{
constexpr double MIN_DISTANCE = 1.5;
return distance >= m_radius * MIN_DISTANCE;
}

}