#include <cstring>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "article.hpp"
#include "customer.hpp"
#include "lib.hpp"
#include <algorithm>
#include <cctype>
#include <locale>

namespace lib {

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

// SRC: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}

void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

template <typename T>
SearchResult<T> search(std::vector<T *> &vec,
                       std::string (T::*getString)(void) const) {
  if (vec.size() == 0) {
    return SearchResult<T>{
        0,
        NULL,
    };
  }

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
                                       std::string (Customer::*)(void) const);
template SearchResult<Article> search(std::vector<Article *> &,
                                      std::string (Article::*)(void) const);

template <typename T>
void deleteFromVec(std::vector<T *> &vec, SearchResult<T> searchResult,
                   void (T::*summary)(void) const) {
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
  delete searchResult.item;
  vec.erase(vec.begin() + searchResult.index);
}
template void deleteFromVec(std::vector<Customer *> &, SearchResult<Customer>,
                            void (Customer::*)(void) const);
template void deleteFromVec(std::vector<Article *> &, SearchResult<Article>,
                            void (Article::*)(void) const);

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

SearchResult<Article> searchArticle(std::vector<Article *> &articles) {
  const static char *filterOptions[] = {"All", "Filter on diameter",
                                        "Filter on type"};
  int choice = choose((char **)filterOptions, 3, 8);

  SearchResult<Article> searchResult;
  if (choice == 1) {
    // Get all articles diameters
    std::map<int64_t, int64_t> diameters;
    for (Article *article : articles) {
      int64_t diameter = article->getDiameter();

      if (diameters.find(diameter) == diameters.end()) {
        // New diameter
        diameters[diameter] = 1;
      } else {
        // Add counter
        diameters[diameter]++;
      }
    }

    // TODO: add size
    // Place diamters in vector
    std::vector<int64_t> key;
    std::vector<std::string *> optionString;
    char **options = (char **)malloc((diameters.size()) * sizeof(char **));
    int cnt = 0;
    for (std::map<int64_t, int64_t>::iterator it = diameters.begin();
         it != diameters.end(); ++it) {
      key.push_back(it->first);
      std::string *s = new std::string;
      *s = "Diameter " + std::to_string(it->first);
      optionString.push_back(s);

      options[cnt] = s->data();
      cnt++;
    }

    choice = choose(options, cnt + 1, 8);
    for (int ii = 0; ii < cnt; ii++) {
      delete optionString[ii];
    }
    free(options);

    // Create vector with just matching diametrs
    int64_t diameter = key[choice];
    std::vector<Article *> filterdArticles;
    for (Article *article : articles) {
      if (article->getDiameter() == diameter) {
        filterdArticles.push_back(article);
      }
    }

    // Finaly search
    searchResult = search(filterdArticles, &Article::getName);
    getCorrectSearchIndex(articles, searchResult);

  } else if (choice == 2) {
    const static char *typeOptions[] = {"Just Tires", "Just rims", "Both"};
    choice = choose((char **)typeOptions, 3, 8);
    const static char type[] = {'t', 'r'};

    if (choice == 2) {
      searchResult = search(articles, &Article::getName);
    } else {
      std::vector<Article *> filterdArticles;
      for (Article *article : articles) {
        if (article->getType() == type[choice]) {
          filterdArticles.push_back(article);
        }
      }

      searchResult = search(filterdArticles, &Article::getName);
      getCorrectSearchIndex(articles, searchResult);
    }

  } else {
    searchResult = search(articles, &Article::getName);
  }

  return searchResult;
}

SearchResult<Customer> searchCustomer(std::vector<Customer *> &customers) {
  SearchResult<Customer> searchResult;
  const static char *typeOptions[] = {"Private customer", "Companies", "Both"};
  const static char type[] = {'c', 'b'};

  int choice = choose((char **)typeOptions, 3, 8);
  if (choice == 2) {
    searchResult = search(customers, &Customer::getName);
  } else {
    std::vector<Customer *> filterdCustomers;
    for (Customer *customer : customers) {
      if (customer->getType() == type[choice]) {
        filterdCustomers.push_back(customer);
      }
    }

    searchResult = search(filterdCustomers, &Customer::getName);
    getCorrectSearchIndex(customers, searchResult);
  }

  return searchResult;
}

template <typename T>
void getCorrectSearchIndex(std::vector<T *> &vec,
                           SearchResult<T> &searchResult) {
  T *searchItem = searchResult.item;
  for (uint64_t ii = 0; ii < vec.size(); ii++) {
    if (vec[ii] == searchItem) {
      searchResult.index = ii;
      return;
    }
  }
}
template void getCorrectSearchIndex(std::vector<Article *> &,
                                    SearchResult<Article> &);
template void getCorrectSearchIndex(std::vector<Customer *> &,
                                    SearchResult<Customer> &);

template <typename T, typename U>
bool checkIfExists(std::vector<T *> vec, U value_to_check,
                   U (T::*fun)(void) const) {
  for (T *item : vec) {
    if ((item->*fun)() == value_to_check) {
      return true;
    }
  }

  return false;
}
template bool checkIfExists(std::vector<Customer *>, std::string,
                            std::string (Customer::*)(void) const);
template bool checkIfExists(std::vector<Article *>, std::string,
                            std::string (Article::*)(void) const);

} // namespace lib
