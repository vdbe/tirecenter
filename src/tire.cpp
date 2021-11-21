#include "tire.hpp"

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
