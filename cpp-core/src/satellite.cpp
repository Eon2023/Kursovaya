#include "satellite.hpp"

#include <iostream>
#include <cmath>

namespace planetary 
{
    Satellite::Satellite(const std::string& name, double mass, double orbitRadius):
    m_name {name},
    m_mass {mass},
    m_orbitRadius {orbitRadius},
    m_angle {0.0}
    {
        if (m_mass <= 0.0)
    {
        std::cerr << "Ошибка: Спутник '" << m_name << "' Имеет не положительную массу. Установлено стандартное знчаение 1.0.\n";
        m_mass = 1.0;
    }
        if (m_orbitRadius <= 0.0)
    {
        std::cerr << "Ошибка: Спутник '" << m_name << "' Имеет не положительный радиус орбиты. Установлено стандартное знчаение 1.0.\n";
        m_orbitRadius = 1.0;
    }
    }

    Satellite::~Satellite()
    {
        std::cout << "Спутник был  уничтожен: " << m_name << "\n";
    }

    void Satellite::UpdatePosition(double dt)
    {
        constexpr double BASE_SPEED = 1.0;
        const double angl_speed = BASE_SPEED / m_orbitRadius;
        m_angle += angl_speed * dt;
    }

    void Satellite::Print() const
    {
            std::cout << "Спутник " << m_name
              << ", масса = " << m_mass
              << ", радиус орбиты = " << m_orbitRadius
              << ", угол = " << m_angle << "\n";
    }
}