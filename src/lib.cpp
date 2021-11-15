#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "article.hpp"
#include "customer.hpp"
#include "lib.hpp"

bool stringIsInt(const std::string &str) {
  for (char const &c : str) {
    if (std::isdigit(c) == 0)
      return false;
  }

  return true;
}

// SRC: https://stackoverflow.com/a/447307
bool stringIsFloat(const std::string &str) {
  float f;

  std::istringstream iss(str);

  iss >> std::noskipws >> f;

  return iss.eof() && !iss.fail();
}

void cleanStdin(void) {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
SearchResult<T> search(std::vector<T> *p_vec,
                       std::string (T::*getString)(void)) {
  SearchResult<T> searchResult;
  unsigned int size = p_vec->size();

  std::vector<std::string> options(p_vec->size());
  for (unsigned int ii = 0; ii < size; ii++) {
    T *item = (p_vec->data() + ii);
    options[ii] = (item->*getString)();
  }

  // Show options
  Menu menu(options);
  searchResult.index = menu.run();
  searchResult.ptr = p_vec->data() + searchResult.index;

  return searchResult;
}
template SearchResult<Customer> search(std::vector<Customer> *,
                                       std::string (Customer::*)(void));
template SearchResult<Article> search(std::vector<Article> *,
                                      std::string (Article::*)(void));

template <typename T>
void deleteFromVec(std::vector<T> *p_vec, SearchResult<T> searchResult,
                   void (T::*summary)(void)) {
  char c;

  // Print summary of to be deleted item
  (searchResult.ptr->*summary)();

  // Confirm deletion
  std::cout << "Are you sure you want to delete this? [y/n]: ";
  std::cin >> c;
  cleanStdin();

  if (c != 'y')
    return;

  // Delete element
  p_vec->erase(p_vec->begin() + searchResult.index);
}
template void deleteFromVec(std::vector<Customer> *, SearchResult<Customer>,
                            void (Customer::*)(void));
template void deleteFromVec(std::vector<Article> *, SearchResult<Article>,
                            void (Article::*)(void));

Menu::Menu(std::vector<std::string> options)
    : options(options), maxOptions(DEFAULT_MAX_OPTIONS){};

Menu::Menu(std::vector<std::string> options, unsigned int maxOptions)
    : options(options), maxOptions(maxOptions) {}

// TODO: Improve this!!!
unsigned int Menu::run(void) {
  unsigned int choice;
  unsigned int pagelen = 0;
  unsigned int optionsCount = this->options.size();
  unsigned int currentPage = 0;
  unsigned maxPage = optionsCount / this->maxOptions;
  std::string line;

  if (this->maxOptions > optionsCount) {
    pagelen = optionsCount;
  } else if ((currentPage + 1) * this->maxOptions > optionsCount) {
    pagelen = optionsCount % this->maxOptions;
  } else {
    pagelen = this->maxOptions;
  }

  do {
    for (unsigned int ii = 0; ii < pagelen; ii++) {

      std::cout << ii + 1 << ". "
                << this->options[currentPage * this->maxOptions + ii]
                << std::endl;
    }

    std::cout << "Choice[p " << currentPage + 1 << "/" << maxPage + 1 << "]: ";
    std::getline(std::cin, line);
    std::cout << std::endl;

    if (stringIsInt(line)) {
      choice = std::stoi(line) - 1;
    } else {
      switch (line[0]) {
      case 'n':
        if (currentPage < maxPage) {
          currentPage++;
          if ((currentPage + 1) * this->maxOptions >= optionsCount) {
            pagelen = optionsCount % this->maxOptions;
          } else {
            pagelen = this->maxOptions;
          }
        }
        continue;
        break;
      case 'p':
        if (currentPage > 0) {
          currentPage--;
          pagelen = this->maxOptions;
        }
        continue;
      case '?':
        std::cout << "n: next page" << std::endl
                  << "p: previous page" << std::endl
                  << "?: help menu" << std::endl;
        continue;
      default:
        break;
      }
    }
  } while (choice >= pagelen);

  return currentPage * this->maxOptions + choice;
}
