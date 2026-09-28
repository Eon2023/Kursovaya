#pragma once

#include <string>

namespace planetary{

    class Satellite {

        private:
        std::string m_name;
        double m_mass;
        double m_orbitRadius;
        double m_angle;

        public: 
        Satellite(const std::string& name, double mass, double orbitRadius);
        ~Satellite();

        Satellite(const Satellite&)            = delete;
        Satellite(Satellite&&)                 = delete;
        Satellite& operator=(const Satellite&) = delete;
        Satellite& operator=(Satellite&&)      = delete;

        void UpdatePosition(double dt);
        void Print() const;

        [[nodiscard]] const std::string& GetName() const {return m_name; }
        [[nodiscard]] double GetMass() const {return m_mass; }
        [[nodiscard]] double GetOrbitRadius() const {return m_orbitRadius; }
    };
}