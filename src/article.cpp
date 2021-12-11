#include "article.hpp"

#include <fstream>
#include <iostream>

Article::Article() {}
Article::Article(std::string name, std::string manufacturer, int64_t stock,
                 int64_t diameter, float price, char type)
    : name(name), manufacturer(manufacturer), stock(stock), diameter(diameter),
      price(price), type(type) {}

Article::~Article() {
#ifdef PRINT_DESTRUCTORS
  std::cout << "Article::~Article()" << std::endl;
#endif
}

std::string Article::getName(void) const { return this->name; }
void Article::setName(std::string name) { this->name = name; }

std::string Article::getManufacturer(void) const { return this->manufacturer; }
void Article::setManufacturer(std::string manufacturer) {
  this->manufacturer = manufacturer;
}

int64_t Article::getStock(void) const { return this->stock; }
void Article::setStock(int64_t stock) { this->stock = stock; }

int64_t Article::getDiameter(void) const { return this->diameter; }
void Article::setDiameter(int64_t diameter) { this->diameter = diameter; }

float Article::getPrice(void) const { return this->price; }
void Article::setPrice(float price) { this->price = price; }

char Article::getType(void) const { return this->type; }
void Article::setType(char type) { this->type = type; }

/*
void Article::show(void) const {
  std::cout << "=== Article ===" << std::endl
            << "\tName: " << this->name << std::endl
            << "\tManufacturer: " << this->manufacturer << std::endl
            << "\tDiameter: " << this->diameter << std::endl
            << "\tType: " << this->type << std::endl
            << "\tStock: " << this->stock << std::endl
            << "\tPrice: " << this->price << std::endl;
}

void Article::showSummary(void) const {
  std::cout << "=== Article ===" << std::endl
            << "\tName: " << this->name << std::endl
            << "\tStock: " << this->stock << std::endl
            << "\tPrice: " << this->price << std::endl;
}

Article *Article::clone(void) const { return new Article(*this); }
*/
