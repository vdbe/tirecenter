#include "rim.hpp"

bool Rim::getAluminium(void) { return this->aluminium; }
void Rim::setAluminium(bool aluminium) { this->aluminium = aluminium; }

std::string Rim::getColor(void) { return this->color; }
void Rim::setColor(std::string color) { this->color = color; }

int Rim::getWidth(void) { return this->width; }
void Rim::setWidth(int width) { this->width = width; }
