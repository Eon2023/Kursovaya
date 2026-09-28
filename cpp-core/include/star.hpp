#pragma once
#include <string>


namespace planetary {

    class Star {

        private: 
        std::string m_name;
        double m_mass;
        double m_radius;

        public: 
        Star(const std::string& name, double mass, double radius);
        ~Star();

        Star(const Star&)            = delete;
        Star(Star&&)                 = delete;
        Star& operator=(const Star&) = delete;
        Star& operator=(Star&&)      = delete;

        void Print() const;
        bool CanHostPlanet(double distance) const;

        [[nodiscard]] const std::string& GetName() const {return m_name; }
        [[nodiscard]] double GetMass() const {return m_mass; }
        [[nodiscard]] double GetRadius() const {return m_radius; }

    };

}