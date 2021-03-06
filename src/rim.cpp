#include "rim.hpp"

#include <iostream>

Rim::Rim() {}
Rim::Rim(std::string name, std::string manufacturer, int64_t stock,
         int64_t diameter, float price, char type, bool aluminium,
         std::string color, int64_t width)
    : Article(name, manufacturer, stock, diameter, price, type),
      aluminium(aluminium), color(color), width(width) {}

Rim::~Rim() {
#ifdef PRINT_DESTRUCTORS
  std::cout << "Rim::~Rim()" << std::endl;
#endif
}

bool Rim::getAluminium(void) const { return this->aluminium; }
void Rim::setAluminium(bool aluminium) { this->aluminium = aluminium; }

std::string Rim::getColor(void) const { return this->color; }
void Rim::setColor(std::string color) { this->color = color; }

int64_t Rim::getWidth(void) const { return this->width; }
void Rim::setWidth(int64_t width) { this->width = width; }

void Rim::show(void) const {
  std::cout << "=== Rim ===" << std::endl
            << "\tName: " << this->name << std::endl
            << "\tManufacturer: " << this->manufacturer << std::endl
            << "\tDiameter: " << this->diameter << std::endl
            << "\tAluminium: " << this->aluminium << std::endl
            << "\tColor: " << this->color << std::endl
            << "\tWidth: " << this->width << std::endl
            << "\tType: " << this->type << std::endl
            << "\tStock: " << this->stock << std::endl
            << "\tPrice: " << this->price << std::endl;
}

void Rim::showSummary(void) const {
  std::cout << "=== Rim ===" << std::endl
            << "\tName: " << this->name << std::endl
            << "\tStock: " << this->stock << std::endl
            << "\tPrice: " << this->price << std::endl;
}

Article *Rim::clone(void) const { return new Rim(*this); }
