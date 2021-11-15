#pragma once

#if !defined(DEFAULT_MAX_OPTIONS)
#define DEFAULT_MAX_OPTIONS 8
#endif

#include <iostream>
#include <memory>
#include <string>
#include <vector>

template <typename T> struct SearchResult {
  unsigned int index;
  T *ptr;
};

void cleanStdin(void);

bool stringIsInt(const std::string &);
bool stringIsFloat(const std::string &);

template <typename T>
SearchResult<T> search(std::vector<T> *, std::string (T::*)(void));

template <typename T>
void deleteFromVec(std::vector<T> *, SearchResult<T>, void (T::*)(void));

class Menu {
private:
  std::vector<std::string> options;
  unsigned int maxOptions;

public:
  Menu(std::vector<std::string>, unsigned int);
  Menu(std::vector<std::string>);
  unsigned int run(void);
};
