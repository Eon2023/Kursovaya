#pragma once

#include "star.hpp"
#include "satellite.hpp"

#include <memory>
#include <vector>
#include <string>


namespace planetary {

    class Planet{

        private:
        std::string m_name;
        double m_mass;
        double m_orbitRadius;
        double m_angle;

        const Star* m_hostStar;
        std::vector<std::unique_ptr<Satellite>> m_satellites;

        public:
        Planet(const std::string& name, double mass, double orbitRadius, const Star* hostStar);
        ~Planet();


        Planet(const Planet&)            = delete;
        Planet(Planet&&)                 = delete;
        Planet& operator=(const Planet&) = delete;
        Planet& operator=(Planet&&)      = delete;

        void AddSatellite(const std::string& name, double mass, double orbitRadius);
        void UpdatePosition(double dt);
        void Print() const;

        [[nodiscard]] const std::string& GetName() const {return m_name; }
        [[nodiscard]] double GetMass() const {return m_mass; }
        [[nodiscard]] double GetOrbitRadius() const {return m_orbitRadius; }
        [[nodiscard]] std::size_t GetSatelliteCount() const { return m_satellites.size(); }
        [[nodiscard]] const Star* GetHostStar() const {return m_hostStar;}

    };
}