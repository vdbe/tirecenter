#include <cstring>
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
SearchResult<T> search(std::vector<T *> &vec,
                       std::string (T::*getString)(void)) {
  // SearchResult<T> searchResult;
  unsigned int index;
  unsigned int size = vec.size();
  char **options = NULL;

  // Allocate memory for option pointers
  options = (char **)malloc(size * sizeof(char **));
  std::string **string_options =
      (std::string **)malloc(size * sizeof(std::string **));
  if (options == NULL || string_options == 0)
    exit(1);

  for (unsigned int ii = 0; ii < size; ii++) {
    std::string *s = new std::string;
    *s = (vec[ii]->*getString)();

    options[ii] = s->data();

    string_options[ii] = s;
  }

  index = choose(options, size, 8);

  SearchResult<T> searchResult = {index, vec[index]};

  // Free pointer array to data of strings
  free(options);
  // Clear strings
  for (unsigned int ii = 0; ii < size; ii++) {
    delete string_options[ii];
  }
  // Free pointer array to strings
  free(string_options);

  return searchResult;
}
template SearchResult<Customer> search(std::vector<Customer *> &,
                                       std::string (Customer::*)(void));
template SearchResult<Article> search(std::vector<Article *> &,
                                      std::string (Article::*)(void));

template <typename T>
void deleteFromVec(std::vector<T *> &vec, SearchResult<T> searchResult,
                   void (T::*summary)(void)) {
  char c;

  // Print summary of to be deleted item
  (searchResult.item->*summary)();

  // Confirm deletion
  std::cout << "Are you sure you want to delete this? [y/n]: ";
  std::cin >> c;
  cleanStdin();

  if (c != 'y')
    return;

  // Delete element
  vec.erase(vec.begin() + searchResult.index);
}
template void deleteFromVec(std::vector<Customer *> &, SearchResult<Customer>,
                            void (Customer::*)(void));
template void deleteFromVec(std::vector<Article *> &, SearchResult<Article>,
                            void (Article::*)(void));

void _draw_page(char *options[], size_t size) {
  for (size_t ii = 0; ii < size; ii++) {
    std::cout << ii + 1 << ". " << options[ii] << std::endl;
  }
}

size_t choose(char *options[], size_t size, size_t max_options) {
  size_t page = 0;
  size_t max_page = size / max_options;
  size_t page_len;

  std::string line;
  size_t choice = -1;

  if (max_options > size) {
    page_len = size;
  } else if ((page + 1) * max_options > size) {
    page_len = size % max_options;
  } else {
    page_len = max_options;
  }

  // I know don't use `while(true) {...}`
  do {
    _draw_page((char **)(options + (page * max_options)), page_len);

    std::cout << "Choice[p " << page + 1 << "/" << max_page + 1 << "]: ";
    std::getline(std::cin, line);
    std::cout << std::endl;

    if (stringIsInt(line) == false) {
      switch (line[0]) {
      case 'n':
        if (page < max_page) {
          page++;
          if ((page + 1) * max_options >= size) {
            page_len = size % max_options;
          } else {
            page_len = max_options;
          }
        }
        continue;
        break;
      case 'p':
        if (page > 0) {
          page--;
          page_len = max_options;
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
    } else {
      choice = std::stoi(line) - 1;
    }
  } while (choice >= page_len);

  return page * max_options + choice;
}
