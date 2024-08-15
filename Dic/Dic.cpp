#include "Dic.h"

#include <fstream>
#include <iostream>

int main(void) {
  Dictionary dict;
  std::fstream file("eng_dic.txt");
  if (!file) {
    std::cerr << "Unable to open" << '\n';
    return 1;
  }

  std::string word, mean;
  while (getline(file, word)) {
    if (getline(file, mean)) {
      dict.Insert(word, mean);
    }
  }
  file.close();

  std::string input;
  while (true) {
    std::cout << "Input a word : ";
    std::getline(std::cin, input);

    if (input == "exit") break;

    std::string result = dict.search(input);
    std::cout << result << '\n';
  }

  return 0;
}