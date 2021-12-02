#include "tire.hpp"

#include <iostream>

#include "article.hpp"

Tire::Tire() {}
Tire::Tire(std::string name, std::string manufacturer, int stock, int diameter,
           float price, char type, int width, int height,
           std::string speedIndex, char season)
    : Article(name, manufacturer, stock, diameter, price, type), width(width),
      height(height), speedIndex(speedIndex), season(season) {}

Tire::~Tire() {
#ifdef PRINT_DESTRUCTORS
  std::cout << "Tire::~Tire()" << std::endl;
#endif
}

int Tire::getWidth(void) { return this->width; }
void Tire::setWidth(int width) { this->width = width; }

int Tire::getHeight(void) { return this->height; }
void Tire::setHeight(int height) { this->height = height; }

std::string Tire::getSpeedIndex(void) { return this->speedIndex; }
void Tire::setSpeedIndex(std::string speedIndex) {
  this->speedIndex = speedIndex;
}

char Tire::getSeason(void) { return this->season; }
void Tire::setSeason(char season) { this->season = season; }

void Tire::show(void) {
  std::cout << "=== Tire ===" << std::endl
            << "\tName: " << this->name << std::endl
            << "\tManufacturer: " << this->manufacturer << std::endl
            << "\tDiameter: " << this->diameter << std::endl
            << "\tWidth: " << this->width << std::endl
            << "\tHeight: " << this->height << std::endl
            << "\tSpeed Index: " << this->speedIndex << std::endl
            << "\tType: " << this->type << std::endl
            << "\tStock: " << this->stock << std::endl
            << "\tPrice: " << this->price << std::endl;
}
