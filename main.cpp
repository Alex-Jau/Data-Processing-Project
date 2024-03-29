#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Function to read data from an input file
std::vector<std::string> read_input_file(const std::string &file_path) {
  std::vector<std::string> lines;
  std::ifstream file(file_path);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
  }
  return lines;
}

// Function to remove excess space and comments from the code
std::vector<std::string>
remove_comments_and_excess_spaces(std::vector<std::string> &lines) {
  std::vector<std::string> cleaned_lines;
  for (const std::string &line : lines) {
    std::string cleaned_line;
    bool in_comment = false;
    for (char c : line) {
      if (!in_comment && c == '/') {
        in_comment = true;
      } else if (in_comment && c == '/') {
        break;
      } else if (!in_comment && !std::isspace(c)) {
        cleaned_line.push_back(c);
      }
    }
    if (!cleaned_line.empty()) {
      cleaned_lines.push_back(cleaned_line);
    }
  }
  return cleaned_lines;
}

// Function to print the code after removing excess space and comments
void print_code(const std::vector<std::string> &lines) {
  for (const std::string &line : lines) {
    std::cout << line << std::endl;
  }
}

// my code for the tokenization is all wack

int main() {
  std::string input_file_path = "input_file.txt";
  std::vector<std::string> lines = read_input_file(input_file_path);

  std::cout << "Code after removing excess space and comments:\n";
  std::vector<std::string> cleaned_lines =
      remove_comments_and_excess_spaces(lines);
  print_code(cleaned_lines);
  std::cout << std::endl;

  return 0;
}
