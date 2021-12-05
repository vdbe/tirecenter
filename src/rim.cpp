#include "rim.hpp"

#include <iostream>

Rim::Rim() {}
Rim::Rim(std::string name, std::string manufacturer, int stock, int diameter,
         float price, char type, bool aluminium, std::string color, int width)
    : Article(name, manufacturer, stock, diameter, price, type),
      aluminium(aluminium), color(color), width(width) {}

Rim::~Rim() {
#ifdef PRINT_DESTRUCTORS
  std::cout << "Rim::~Rim()" << std::endl;
#endif
}

bool Rim::getAluminium(void) { return this->aluminium; }
void Rim::setAluminium(bool aluminium) { this->aluminium = aluminium; }

std::string Rim::getColor(void) { return this->color; }
void Rim::setColor(std::string color) { this->color = color; }

int Rim::getWidth(void) { return this->width; }
void Rim::setWidth(int width) { this->width = width; }

void Rim::show(void) {
  std::cout << "=== Article ===" << std::endl
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
